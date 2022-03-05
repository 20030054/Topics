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

#pragma once

#include "veins/veins.h"

#include "veins/modules/application/ieee80211p/DemoBaseApplLayer.h"

#include "veins/modules/application/traci/HeartBeatMessage_m.h"

#include "Node.cc"
#include "Task.cc"


using namespace omnetpp;

namespace veins {

/**
 * @brief
 * This is a stub for a typical Veins application layer.
 * Most common functions are overloaded.
 * See MyVeinsApp.cc for hints
 *
 * @author David Eckhoff
 *
 */

class VEINS_API MyVeinsApp : public DemoBaseApplLayer {
protected:
    int CarType;
    int CarState;
    int clusterHeadID=-1;
    int MIPS;
    double last_HB_Received;
    double last_HB_Sent;
    double last_Task_Sent;
    double CM_Task_Interval;
    double CH_HB_Interval;
    double CM_HB_Interval;
    double timer;
    int countTasksSent;
    enum msgType {ADVERTIZEMENT=0, CON=1,CONACK=2, FIN=3, HB_CH=4, HB_CM=5, WORKLOAD=6,WRESULT=7,BROADCAST=-1};
    enum taskStatus {Sent=0, Received=1,Queued=2, Processing=3, Completed=4, Expired=5, Result=6};
    enum vType {CH=1,CM=2,FREE=3};
    enum vState {ACKWAITING=1, AVAILABLE=2,JOINED=3};

    static simsignal_t numSent;
    static simsignal_t systemDelay;


public:
    std::vector<int> clusterMembers;
    std::vector<Node*> clusterMembers2;
    std::vector<Task*> Tasks;
    void initialize(int stage) override;
    void finish() override;

    int getCarType() const {
        return CarType;
    }

    void setCarType(int carType) {
        CarType = carType;
    }

    int getClusterHeadId() const {
        return clusterHeadID;
    }

    void setClusterHeadId(int clusterHeadId) {
        clusterHeadID = clusterHeadId;
    }

protected:
    void onBSM(DemoSafetyMessage* bsm) override;
    //void onBSM(HBMessage* hbm);

    void onWSM(BaseFrame1609_4* wsm) override;
    void onWSA(DemoServiceAdvertisment* wsa) override;

    void handleSelfMsg(cMessage* msg) override;
    void handlePositionUpdate(cObject* obj) override;
    double CalculateCommulativeWeight(double speed, double distance, int priority, int taskSize);

};

} // namespace veins
