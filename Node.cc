

 #ifndef NODE
 #define NODE


namespace veins {

class Node {

private:
    int nodeID;
    double speed;
    double lastBeaconReceived;
public:
    Node() {
        // TODO Auto-generated constructor stub

    }
    ~Node() {
        // TODO Auto-generated destructor stub
    }
    Node(int id, double timer) {
        this->nodeID=id;
        this->lastBeaconReceived=timer;

        }
    int getNodeId() const {
        return nodeID;
    }

    void setNodeId(int nodeId) {
        nodeID = nodeId;
    }

    double getSpeed() const {
        return speed;
    }

    void setSpeed(double speed) {
        this->speed = speed;
    }

    double getLastBeaconReceived() const {
        return lastBeaconReceived;
    }

    void setLastBeaconReceived(double lastBeaconReceived) {
        this->lastBeaconReceived = lastBeaconReceived;
    }
};

}
#endif


