/*
 * Task.cc
 *
 *  Created on: Feb 19, 2022
 *      Author: veins
 */



 #ifndef TASK
 #define TASK


namespace veins {

class Task {

private:
    const char* taskID;
    int taskOwner;
    double taskGenerationTime;
    double taskReceivingTime;
    double taskStartProcessingTime;
    double taskCompleteTime;
    int taskSize;
    int taskPriority;
    double comWeight;
    int taskStatus;
    double distance;
    double speed;
    enum taskStatus {Sent=0, Received=1,Queued=2, Processing=3, Completed=4, Expired=5, Result=6};

public:
    Task() {
                // TODO Auto-generated constructor stub

     }

    Task(const char* taskID, int taskSize, int taskPriority, double taskReceivingTime) {
        this->taskID=taskID;
        this->taskPriority=taskPriority;
        this->taskSize=taskSize;
        this->taskReceivingTime=taskReceivingTime;
    }

    ~Task() {
        // TODO Auto-generated destructor stub
    }

    double getTaskCompleteTime() const {
        return taskCompleteTime;
    }

    void setTaskCompleteTime(double taskCompleteTime) {
        this->taskCompleteTime = taskCompleteTime;
    }

    const char* getTaskId() const {
        return taskID;
    }

    void setTaskId(const char *taskId) {
        taskID = taskId;
    }

    int getTaskPriority() const {
        return taskPriority;
    }

    void setTaskPriority(int taskPriority) {
        this->taskPriority = taskPriority;
    }

    int getTaskSize() const {
        return taskSize;
    }

    void setTaskSize(int taskSize) {
        this->taskSize = taskSize;
    }

    double getTaskGenerationTime() const {
        return taskGenerationTime;
    }

    void setTaskGenerationTime(double taskGenerationTime) {
        this->taskGenerationTime = taskGenerationTime;
    }

    double getTaskReceivingTime() const {
        return taskReceivingTime;
    }

    void setTaskReceivingTime(double taskReceivingTime) {
        this->taskReceivingTime = taskReceivingTime;
    }

    int getTaskStatus() const {
        return taskStatus;
    }

    void setTaskStatus(int taskStatus) {
        this->taskStatus = taskStatus;
    }

    int getTaskOwner() const {
        return taskOwner;
    }

    void setTaskOwner(int taskOwner) {
        this->taskOwner = taskOwner;
    }

    double getDistance() const {
        return distance;
    }

    void setDistance(double distance) {
        this->distance = distance;
    }

    double getSpeed() const {
        return speed;
    }

    void setSpeed(double speed) {
        this->speed = speed;
    }

    double getComWeight() const {
        return comWeight;
    }

    void setComWeight(double comWeight) {
        this->comWeight = comWeight;
    }

    double getTaskStartProcessingTime() const {
        return taskStartProcessingTime;
    }

    void setTaskStartProcessingTime(double taskStartProcessingTime) {
        this->taskStartProcessingTime = taskStartProcessingTime;
    }
};

}
#endif




