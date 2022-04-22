//
// Copyright (C) 2016 David Eckhoff <david.eckhoff@fau.de>
//
// Documentation for these modules is at http://veins.car2x.org/
//
// SPDX-License-Identifier: GPL-2.0-or-later
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//

#include "veins/modules/application/traci/MyVeinsApp.h"
#include "veins/modules/application/traci/TraCIDemo11pMessage_m.h"
#include "veins/modules/application/traci/HeartBeatMessage_m.h"
//#include "veins/modules/application/traci/HBMessage_m.h"

#include "ctime"

#include "veins/modules/application/traci/Node.cc"

using namespace veins;

Define_Module(veins::MyVeinsApp);

simsignal_t MyVeinsApp::numSent = registerSignal("numSent");

simsignal_t MyVeinsApp::systemDelay= registerSignal("systemDelay");

simsignal_t MyVeinsApp::queueDelay= registerSignal("queueDelay");

simsignal_t MyVeinsApp::serverDelay= registerSignal("serverDelay");

simsignal_t MyVeinsApp::queueSize= registerSignal("queueSize");

void MyVeinsApp::initialize(int stage)
{
    DemoBaseApplLayer::initialize(stage);
    if (stage == 0) {

        serverDelay = registerSignal("serverDelay");
        systemDelay = registerSignal("systemDelay");
        queueDelay = registerSignal("queueDelay");

        // Initializing members and pointers of your application goes here
        EV << "Initializing " << par("appName").stringValue() << std::endl;

        CH_HB_Interval=par("CH_HB_Interval");
        CM_HB_Interval=par("CM_HB_Interval");
        setClusterHeadId(0); //vehicle with no CH


        srand((unsigned)time(0));

        serverTimer=0;
        serverStatus=IDLE;

        numSent=0;


        if(this->getParentModule()->getId()%5==0){
            findHost()->getDisplayString().setTagArg("i", 1, "yellow");

            setCarType(CH); //  this is cluster head

            //            int range = 10000 - 5000 + 1;
            //            int num = rand() % range + min;

            //            MIPS= (rand() % 5000) + 5000; // just random, further we can apply a prob. distribution here
            MIPS=1000;

            std::ostringstream str;
            str << "My MIPS are:"<< MIPS <<"\n" ;
            this->getParentModule()->bubble(str.str().c_str());


            EV<<"myMIPS"<< MIPS <<"\n";


            //            MIPS=5000;
        }
        else{
            setCarType(FREE);

            CM_Task_Interval=par("CM_Task_Interval");
            last_Task_Sent=simTime().dbl();
            countTasksSent=0;

            MIPS=500;
        }


    }
    else if (stage == 1) {
        // Initializing members that require initialized other modules goes here
    }
}

void MyVeinsApp::finish()
{
    DemoBaseApplLayer::finish();


//    for(unsigned int i=0; i<Tasks.size(); i++){
//
//
//        if(Tasks[i]->getTaskStatus()==Completed){
//
//            recordScalar("systemDelay", (Tasks[i]->getTaskCompleteTime() - Tasks[i]->getTaskGenerationTime()));
//            recordScalar("serverDelay", (Tasks[i]->getTaskCompleteTime() - Tasks[i]->getTaskStartProcessingTime()));
//        }
//        else if(Tasks[i]->getTaskStatus()==Processing){
//            //emit(queueDelay,(Tasks[i]->getTaskStartProcessingTime() - Tasks[i]->getTaskReceivingTime()));
//
//            recordScalar("queueDelay", (Tasks[i]->getTaskStartProcessingTime() - Tasks[i]->getTaskReceivingTime()));
//        }
//
//
//    }

    recordScalar("numSent", numSent);
    recordScalar("serverDelay",serverDelay);
    recordScalar("queueDelay", queueDelay);
    recordScalar("systemDelay", systemDelay);
    recordScalar("queueSize", Tasks.size());



    // statistics recording goes here
}

void MyVeinsApp::onBSM(DemoSafetyMessage* bsm)
{

    // Your application has received a beacon message from another car or RSU
    // code for handling the message goes here
}

void MyVeinsApp::onWSM(BaseFrame1609_4* frame)
{
    if(dynamic_cast<HeartBeatMessage* > (frame)){

        HeartBeatMessage* hb = check_and_cast<HeartBeatMessage*>(frame);
        if(CarType==CH){
            if(hb->getReceipeintID()==this->getParentModule()->getId()){

                for(unsigned int i=0; i<clusterMembers2.size(); i++){
                    if(clusterMembers2[i]->getNodeId()==hb->getSenderID()){
                        clusterMembers2[i]->setLastBeaconReceived(simTime().dbl());
                        // add more things like residual energy, current memory, queue size etc...sim.num_depart*sim.clock
                        this->getParentModule()->bubble("connection time updated at CH ");
                        break;
                    }
                }
            }

        }
        else if(CarType==CM){
            if(hb->getSenderID()==clusterHeadID){
                last_HB_Received=simTime().dbl();
            }
        }

    }
    else if (dynamic_cast<TraCIDemo11pMessage* > (frame)){


        TraCIDemo11pMessage* wsm = check_and_cast<TraCIDemo11pMessage*>(frame);

        //        if(wsm->getMessageType()==WRESULT){
        //
        //            this->getParentModule()->bubble("result received here ");
        //
        //
        //        }



        if(wsm->getReceipeintID()==BROADCAST){
            if(CarType==FREE && CarState!=ACKWAITING){
                if(wsm->getMessageType()==ADVERTIZEMENT){

                    Coord myPosition=mobility->getPositionAt(simTime());
                    Coord senderPosition=wsm->getPosition();
                    double distance=myPosition.distance(senderPosition);

                    EV<< " mydistance "<<distance;

                    //                    if(distance is less then we say required) then make connection (need to work on this)


                    //initiate connection
                    TraCIDemo11pMessage* msgCon = new TraCIDemo11pMessage();
                    populateWSM(msgCon);
                    msgCon->setDemoData(mobility->getRoadId().c_str());
                    msgCon->setMessageType(CON);

                    msgCon->setId(this->getParentModule()->getId()); // send its own id

                    msgCon->setReceipeintID(wsm->getId()); //send message to node from where ADVERTIZEMENT received

                    CarState=ACKWAITING;

                    timer=simTime().dbl();


                    last_HB_Sent=simTime().dbl();
                    sendDown(msgCon);

                }

            }
        }


        //unicast/destined for me
        else if(wsm->getReceipeintID()==this->getParentModule()->getId()){

            if(wsm->getMessageType()==CONACK && CarState==ACKWAITING){

                if(wsm->getReceipeintID()==this->getParentModule()->getId()){
                    setClusterHeadId(wsm->getId());

                    findHost()->getDisplayString().setTagArg("i", 1, "green");
                    CarType=CM;
                    CarState=JOINED;

                    //str << "NODE - "<< this->getParentModule()->getId() <<" has joined CH-"<<wsm->getId();
                    std::ostringstream str;
                    str << "I have joined a CH " << clusterHeadID ;
                    this->getParentModule()->bubble(str.str().c_str());


                    //this->getParentModule()->bubble("I have joined a CH ");
                    EV<< "Node: " << this->getParentModule()->getId() <<" has joined CH: "<< wsm->getId() <<"\n";

                    //send workload

                    TraCIDemo11pMessage* workload = new TraCIDemo11pMessage();
                    populateWSM(workload);
                    workload->setDemoData(mobility->getRoadId().c_str());
                    workload->setMessageType(WORKLOAD);

                    std::ostringstream msgID;
                    msgID << this->getParentModule()->getId() << "-" << clusterHeadID;


                    int sizeTask= 250;


                    workload->setTaskSize(sizeTask);
                    this->getParentModule()->bubble(msgID.str().c_str());
                    workload->setReceipeintID(clusterHeadID);

                    sendDown(workload);

                }
            }

            else if(wsm->getMessageType()==CON){
                if(CarType==CH){
                    clusterMembers.push_back(wsm->getId()); //array of ints

                    Node *n = new Node(wsm->getId(), simTime().dbl()); //object

                    clusterMembers2.push_back(n); //array of objects


                    std::ostringstream str;
                    str << "I have " << clusterMembers2.size() << " members" ;
                    this->getParentModule()->bubble(str.str().c_str());


                    TraCIDemo11pMessage* msgConAck = new TraCIDemo11pMessage();

                    populateWSM(msgConAck);

                    msgConAck->setDemoData(mobility->getRoadId().c_str());

                    msgConAck->setMessageType(CONACK);
                    msgConAck->setId(this->getParentModule()->getId());

                    msgConAck->setReceipeintID(wsm->getId());
                    last_HB_Sent=simTime().dbl();
                    sendDown(msgConAck);
                }
            }

            else if(wsm->getMessageType()==WORKLOAD){
                if(CarType==CH){



                    std::ostringstream str;
                    str << "Received task from  " << wsm->getId()  ;
                    this->getParentModule()->bubble(str.str().c_str());
                    EV<<"Received task from  " << wsm->getId() <<"\n";

                    Task *tsk = new Task(wsm->getMessageID(),wsm->getTaskSize(), wsm->getTaskPriority(), simTime().dbl());
                    tsk->setTaskStatus(1); //received=1
                    tsk->setTaskOwner(wsm->getId());
                    tsk->setTaskGenerationTime(wsm->getCreationTime().dbl());
                    tsk->setTaskReceivingTime(simTime().dbl());

                    //calculate distance

                    Coord myPosition=mobility->getPositionAt(simTime());
                    Coord senderPosition=wsm->getPosition();
                    double distance=myPosition.distance(senderPosition);
                    tsk->setDistance(distance);
                    tsk->setSpeed(wsm->getNodeSpeed());
                    tsk->setTaskPriority(wsm->getTaskPriority());


                    double comWeight=CalculateCommulativeWeight2(tsk->getSpeed(), tsk->getDistance(), tsk->getTaskPriority(), tsk->getTaskSize());

                    std::ostringstream str2;
                    str2 << "com Weight:"<< comWeight <<"\n";
                    this->getParentModule()->bubble(str2.str().c_str());



                    tsk->setComWeight(comWeight);


                    tsk->setTaskStatus(Queued);
                    Tasks.push_back(tsk);






                    if(serverStatus==IDLE){
                        if(Tasks.size()>1){
                            int temp=0;
                            double tempComWeight=Tasks[0]->getComWeight();
                            for(unsigned int i=1; i<Tasks.size(); i++){
                                if(Tasks[i]->getComWeight()>tempComWeight && Tasks[i]->getTaskStatus()==Queued){
                                    tempComWeight=Tasks[i]->getComWeight();
                                    temp=i;
                                }
                            }
                            currentTaskIndex=temp;
                            serverTimer=(Tasks[temp]->getTaskSize()/MIPS)  + simTime().dbl();
                            Tasks[temp]->setTaskStatus(Processing);
                            Tasks[temp]->setTaskStartProcessingTime(simTime().dbl());
                            serverStatus=BUSY;
                        }
                        else{
                            if(Tasks[0]->getTaskStatus()==Queued){
                                serverTimer=(Tasks[0]->getTaskSize()/MIPS) + simTime().dbl();
                                currentTaskIndex=0;
                                Tasks[0]->setTaskStatus(Processing);
                                Tasks[0]->setTaskStartProcessingTime(simTime().dbl());
                                serverStatus=BUSY;
                            }

                        }
                    }



                    //                    if(Tasks.size()>0){
                    //                        tsk->setTaskCompleteTime((wsm->getTaskSize()/MIPS)+ Tasks[Tasks.size()-1]->getTaskCompleteTime());
                    //                    }
                    //                    else{
                    //                        tsk->setTaskCompleteTime((wsm->getTaskSize()/MIPS)+simTime().dbl());
                    //                    }
                    //
                    //                    Tasks.push_back(tsk); //array of objects
                }

            }

            else if(wsm->getMessageType()==WRESULT){
                if(CarType==CM){
                    if(Tasks.size()>0){
                        EV<< "checkpt-2";
                        for(unsigned int i=0; i<Tasks.size(); i++){

                            if(Tasks[i]->getTaskId() == wsm->getMessageID()){ //error possible
                                EV<< "checkpt-3";
                                double delay=simTime().dbl()- Tasks[i]->getTaskGenerationTime();

                                std::ostringstream str;
                                str << "ASDF-Task ID: " << wsm->getMessageID() << " Completed in delay: "<< delay;
                                this->getParentModule()->bubble(str.str().c_str());


                                //                                Tasks.erase(Tasks[i]);
                                break;

                            }
                        }
                    }
                }

            }






            //            else if(CarType==FREE){
            //                if(wsm->getMessageType()==CONACK){
            //
            //                }
            //            }
            //            else if(CarType==CM){
            //
            //                EV<< "checkpt-0";
            //                if(wsm->getMessageType()==HB_CH){
            //
            //                }
            //            }


            //            else if(CarType==CH){
            ////                if(wsm->getMessageType()==CON){
            ////
            ////
            ////
            ////
            ////                }
            ////                else if(wsm->getMessageType()==HB_CM){
            ////
            ////                }
            ////
            ////                else  if(wsm->getMessageType()==FIN){
            ////
            ////                }
            ////            }
            //        }


            // Your application has received a data message from another car or RSU
            // code for handling the message goes here, see TraciDemo11p.cc for examples

        } //closing dynamic cast wsm
    }
}

double CalculateWeight(int min, int max, double input, bool effect){

    int sum=0;

    for(unsigned int i=min;i<=max;i++){
        sum+=i;
    }

    double weight=(input * (max-min))/sum;

    if(effect){
        return weight;
    }
    else{
        return (1-weight);
    }


}
double MyVeinsApp::CalculateCommulativeWeight(double speed, double distance, int priority, int taskSize){

    double comWeight= CalculateWeight(1, 60, speed, false) + CalculateWeight(10, 500, distance, false) + CalculateWeight(1, 5, priority, true) + CalculateWeight(10, 500, taskSize, false);
    return comWeight;
}
double CalculateWeight2(double input, double weight){
    return input * weight;
}

double MyVeinsApp::CalculateCommulativeWeight2(double speed, double distance, int priority, int taskSize){

    double comWeight= CalculateWeight2(speed, 0.1) + CalculateWeight2(distance, 0.1) + CalculateWeight2( priority, 0.3) + CalculateWeight2(taskSize, 0.5);
    return comWeight;
}

void MyVeinsApp::onWSA(DemoServiceAdvertisment* wsa)
{
    // Your application has received a service advertisement from another car or RSU
    // code for handling the message goes here, see TraciDemo11p.cc for examples
}

void MyVeinsApp::handleSelfMsg(cMessage* msg)
{
    DemoBaseApplLayer::handleSelfMsg(msg);
    // this method is for self messages (mostly timers)
    // it is important to call the DemoBaseApplLayer function for BSM and WSM transmission
}

void MyVeinsApp::handlePositionUpdate(cObject* obj)
{
    DemoBaseApplLayer::handlePositionUpdate(obj);

    if(CarType==CH){
        //findHost()->getDisplayString().setTagArg("i", 1, "white");
        TraCIDemo11pMessage* wsm = new TraCIDemo11pMessage();
        populateWSM(wsm);
        wsm->setDemoData(mobility->getRoadId().c_str());

        wsm->setId(getParentModule()->getId()); // each CH will broadcast its own id to all free vehicls, then free vehicls will join this CH by this id

        wsm->setPosition(mobility->getPositionAt(simTime()));

        wsm->setMIPS(MIPS); // add mips of CH in broadcast

        wsm->setNodeSpeed(mobility->getSpeed()); //add speed of CH
        wsm->setMessageType(ADVERTIZEMENT);
        wsm->setReceipeintID(BROADCAST); // broadcast

        //        wsm->setDriverName("CH's driver");

        sendDown(wsm);

        if(simTime().dbl()-last_HB_Sent > CH_HB_Interval){
            HeartBeatMessage* hb=new HeartBeatMessage();
            populateWSM(hb);

            hb->setSenderID(this->getParentModule()->getId());
            last_HB_Sent=simTime().dbl();
            sendDown(hb);
        }


        if(serverStatus==BUSY){
            if(simTime().dbl() >= serverTimer){
                emit(queueSize, Tasks.size());
                emit(serverDelay, (simTime().dbl() - Tasks[currentTaskIndex]->getTaskStartProcessingTime()));
                emit(systemDelay, (simTime().dbl() - Tasks[currentTaskIndex]->getTaskReceivingTime()));
                emit(queueDelay, (Tasks[currentTaskIndex]->getTaskStartProcessingTime()- Tasks[currentTaskIndex]->getTaskReceivingTime()));


                Tasks[currentTaskIndex]->setTaskCompleteTime(simTime().dbl());
                Tasks[currentTaskIndex]->setTaskStatus(Completed);

                double systemDelay=simTime().dbl() - Tasks[currentTaskIndex]->getTaskReceivingTime();
                std::ostringstream str;
                str << "Task arrive " <<std::to_string(Tasks[currentTaskIndex]->getTaskReceivingTime()) <<"Queueing delay   "<<std::to_string(Tasks[currentTaskIndex]->getTaskStartProcessingTime() - Tasks[currentTaskIndex]->getTaskReceivingTime()) <<" completed" <<std::to_string(systemDelay);
                this->getParentModule()->bubble(str.str().c_str());
                serverStatus=IDLE;


                TraCIDemo11pMessage* wsmResult = new TraCIDemo11pMessage();
                populateWSM(wsm);
                wsmResult->setMessageType(WRESULT);
                wsmResult->setReceipeintID(Tasks[currentTaskIndex]->getTaskOwner());
                wsm->setMessageID(Tasks[currentTaskIndex]->getTaskId());
                wsmResult->setId(this->getParentModule()->getId());
                sendDown(wsmResult);






                // to debug the delays, look into serverTimer and currentIndex


                //                std::ostringstream str;
                //                str << "Task " <<  Tasks[currentTaskIndex]->getTaskId() << " completed in ";
                //                this->getParentModule()->bubble(str.str().c_str());





                //                recordScalar("systemDelay", (simTime().dbl()- Tasks[currentTaskIndex]->getTaskGenerationTime()));
                //            Tasks.erase(Tasks.begin()+currentTaskIndex);




                if(Tasks.size()==0){
                    serverStatus=IDLE;
                }
                else{
                    int temp=-1;
                    double tempComWeight=-1;
                    for(unsigned int h=0; h< Tasks.size(); h++){
                        if(Tasks[h]->getTaskStatus()==Queued){
                            tempComWeight=Tasks[h]->getComWeight();
                            temp=h;
                            break;
                        }
                    }

                    if(temp != -1 && tempComWeight != -1){
                        for(unsigned int i=1; i<Tasks.size(); i++){
                            if(Tasks[i]->getComWeight()>tempComWeight && Tasks[i]->getTaskStatus()==Queued){
                                tempComWeight=Tasks[i]->getComWeight();
                                temp=i;
                            }
                        }
                        currentTaskIndex=temp;
                        serverTimer=(Tasks[temp]->getTaskSize()/MIPS)  + simTime().dbl();
                        Tasks[temp]->setTaskStartProcessingTime(simTime().dbl());
                        Tasks[temp]->setTaskStatus(Processing);
                        serverStatus=BUSY;
                    }



                    //                    double queueDelay=simTime().dbl() - Tasks[currentTaskIndex]->getTaskReceivingTime();
                    //
                    //

                    //                    std::ostringstream str;
                    //                    str << "Queue Time:"<< queueDelay <<"\n" ;
                    //                    this->getParentModule()->bubble(str.str().c_str());


                }
            }
        }

        //
        //        if(Tasks.size() >0 ){
        //            if(Tasks[0]->getTaskCompleteTime() <= simTime().dbl()){
        //                //sending result back to client
        //                TraCIDemo11pMessage* wsmResult = new TraCIDemo11pMessage();
        //                populateWSM(wsm);
        //                wsmResult->setMessageType(WRESULT);
        //                wsmResult->setReceipeintID(Tasks[0]->getTaskOwner());
        //                wsm->setMessageID(Tasks[0]->getTaskId());
        //                wsmResult->setId(this->getParentModule()->getId());
        //                sendDown(wsmResult);
        //                std::ostringstream str;
        //                str << "Task " <<  Tasks[0]->getTaskId() << " completed";
        //                this->getParentModule()->bubble(str.str().c_str());
        //                recordScalar("systemDelay", (simTime().dbl()- Tasks[0]->getTaskGenerationTime()));
        //                Tasks.erase(Tasks.begin()+0);
        //            }
        //        }



    }
    else if(CarType==FREE){

        if( (simTime().dbl()-timer) > 1){
            CarState=AVAILABLE;
        }
    }
    else if(CarType==CM){
        EV<< "MY CH is " << clusterHeadID ;
        if(simTime().dbl()-last_HB_Sent > CM_HB_Interval){
            HeartBeatMessage* hb=new HeartBeatMessage();
            populateWSM(hb);
            hb->setReceipeintID(clusterHeadID);
            hb->setSenderID(this->getParentModule()->getId());
            last_HB_Sent=simTime().dbl();
            sendDown(hb);
        }

        if(simTime().dbl()-last_Task_Sent > CM_Task_Interval){
            TraCIDemo11pMessage* wsmTask = new TraCIDemo11pMessage();
            populateWSM(wsmTask);
            countTasksSent +=1;
            //seting id

            std::string s = std::to_string(countTasksSent);
            s=s + "-" + std::to_string(this->getParentModule()->getId());
            char const *mID = s.c_str();

            wsmTask->setMessageID(mID);



            wsmTask->setMessageType(WORKLOAD);

            int sizeTask= 250;




            wsmTask->setTaskSize(sizeTask); //temp fix
            wsmTask->setReceipeintID(this->CH);
            wsmTask->setId(this->getParentModule()->getId()); //set sender id
            wsmTask->setPosition(mobility->getPositionAt(simTime()));
            wsmTask->setNodeSpeed(mobility->getSpeed());
            last_Task_Sent= simTime().dbl();


            Task *tsk=new Task();
            tsk->setTaskId(mID);
            tsk->setTaskGenerationTime(simTime().dbl());

            Tasks.push_back(tsk);


            sendDown(wsmTask);

            numSent +=1;

            std::ostringstream str;
            str << "I sent task to  " << clusterHeadID << "of size "<< 100 ;
            this->getParentModule()->bubble(str.str().c_str());
            EV<< "I sent task to  " << clusterHeadID << "of size "<< 100 <<"\n";
        }



    }

}
