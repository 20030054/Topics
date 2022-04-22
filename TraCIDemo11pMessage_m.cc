//
// Generated file, do not edit! Created by nedtool 5.6 from veins/modules/application/traci/TraCIDemo11pMessage.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include "TraCIDemo11pMessage_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

namespace veins {

// forward
template<typename T, typename A>
std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec);

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// operator<< for std::vector<T>
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

Register_Class(TraCIDemo11pMessage)

TraCIDemo11pMessage::TraCIDemo11pMessage(const char *name, short kind) : ::veins::BaseFrame1609_4(name,kind)
{
    this->senderAddress = -1;
    this->serial = 0;
    this->id = 0;
    this->messageType = 0;
    this->receipeintID = 0;
    this->TaskSize = 0;
    this->MIPS = 0;
    this->NodeSpeed = 0;
    this->taskPriority = 0;
}

TraCIDemo11pMessage::TraCIDemo11pMessage(const TraCIDemo11pMessage& other) : ::veins::BaseFrame1609_4(other)
{
    copy(other);
}

TraCIDemo11pMessage::~TraCIDemo11pMessage()
{
}

TraCIDemo11pMessage& TraCIDemo11pMessage::operator=(const TraCIDemo11pMessage& other)
{
    if (this==&other) return *this;
    ::veins::BaseFrame1609_4::operator=(other);
    copy(other);
    return *this;
}

void TraCIDemo11pMessage::copy(const TraCIDemo11pMessage& other)
{
    this->demoData = other.demoData;
    this->senderAddress = other.senderAddress;
    this->messageID = other.messageID;
    this->serial = other.serial;
    this->id = other.id;
    this->driverName = other.driverName;
    this->messageType = other.messageType;
    this->receipeintID = other.receipeintID;
    this->position = other.position;
    this->TaskSize = other.TaskSize;
    this->MIPS = other.MIPS;
    this->NodeSpeed = other.NodeSpeed;
    this->taskPriority = other.taskPriority;
}

void TraCIDemo11pMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::veins::BaseFrame1609_4::parsimPack(b);
    doParsimPacking(b,this->demoData);
    doParsimPacking(b,this->senderAddress);
    doParsimPacking(b,this->messageID);
    doParsimPacking(b,this->serial);
    doParsimPacking(b,this->id);
    doParsimPacking(b,this->driverName);
    doParsimPacking(b,this->messageType);
    doParsimPacking(b,this->receipeintID);
    doParsimPacking(b,this->position);
    doParsimPacking(b,this->TaskSize);
    doParsimPacking(b,this->MIPS);
    doParsimPacking(b,this->NodeSpeed);
    doParsimPacking(b,this->taskPriority);
}

void TraCIDemo11pMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::veins::BaseFrame1609_4::parsimUnpack(b);
    doParsimUnpacking(b,this->demoData);
    doParsimUnpacking(b,this->senderAddress);
    doParsimUnpacking(b,this->messageID);
    doParsimUnpacking(b,this->serial);
    doParsimUnpacking(b,this->id);
    doParsimUnpacking(b,this->driverName);
    doParsimUnpacking(b,this->messageType);
    doParsimUnpacking(b,this->receipeintID);
    doParsimUnpacking(b,this->position);
    doParsimUnpacking(b,this->TaskSize);
    doParsimUnpacking(b,this->MIPS);
    doParsimUnpacking(b,this->NodeSpeed);
    doParsimUnpacking(b,this->taskPriority);
}

const char * TraCIDemo11pMessage::getDemoData() const
{
    return this->demoData.c_str();
}

void TraCIDemo11pMessage::setDemoData(const char * demoData)
{
    this->demoData = demoData;
}

LAddress::L2Type& TraCIDemo11pMessage::getSenderAddress()
{
    return this->senderAddress;
}

void TraCIDemo11pMessage::setSenderAddress(const LAddress::L2Type& senderAddress)
{
    this->senderAddress = senderAddress;
}

const char * TraCIDemo11pMessage::getMessageID() const
{
    return this->messageID.c_str();
}

void TraCIDemo11pMessage::setMessageID(const char * messageID)
{
    this->messageID = messageID;
}

int TraCIDemo11pMessage::getSerial() const
{
    return this->serial;
}

void TraCIDemo11pMessage::setSerial(int serial)
{
    this->serial = serial;
}

int TraCIDemo11pMessage::getId() const
{
    return this->id;
}

void TraCIDemo11pMessage::setId(int id)
{
    this->id = id;
}

const char * TraCIDemo11pMessage::getDriverName() const
{
    return this->driverName.c_str();
}

void TraCIDemo11pMessage::setDriverName(const char * driverName)
{
    this->driverName = driverName;
}

int TraCIDemo11pMessage::getMessageType() const
{
    return this->messageType;
}

void TraCIDemo11pMessage::setMessageType(int messageType)
{
    this->messageType = messageType;
}

int TraCIDemo11pMessage::getReceipeintID() const
{
    return this->receipeintID;
}

void TraCIDemo11pMessage::setReceipeintID(int receipeintID)
{
    this->receipeintID = receipeintID;
}

Coord& TraCIDemo11pMessage::getPosition()
{
    return this->position;
}

void TraCIDemo11pMessage::setPosition(const Coord& position)
{
    this->position = position;
}

int TraCIDemo11pMessage::getTaskSize() const
{
    return this->TaskSize;
}

void TraCIDemo11pMessage::setTaskSize(int TaskSize)
{
    this->TaskSize = TaskSize;
}

int TraCIDemo11pMessage::getMIPS() const
{
    return this->MIPS;
}

void TraCIDemo11pMessage::setMIPS(int MIPS)
{
    this->MIPS = MIPS;
}

double TraCIDemo11pMessage::getNodeSpeed() const
{
    return this->NodeSpeed;
}

void TraCIDemo11pMessage::setNodeSpeed(double NodeSpeed)
{
    this->NodeSpeed = NodeSpeed;
}

int TraCIDemo11pMessage::getTaskPriority() const
{
    return this->taskPriority;
}

void TraCIDemo11pMessage::setTaskPriority(int taskPriority)
{
    this->taskPriority = taskPriority;
}

class TraCIDemo11pMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    TraCIDemo11pMessageDescriptor();
    virtual ~TraCIDemo11pMessageDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(TraCIDemo11pMessageDescriptor)

TraCIDemo11pMessageDescriptor::TraCIDemo11pMessageDescriptor() : omnetpp::cClassDescriptor("veins::TraCIDemo11pMessage", "veins::BaseFrame1609_4")
{
    propertynames = nullptr;
}

TraCIDemo11pMessageDescriptor::~TraCIDemo11pMessageDescriptor()
{
    delete[] propertynames;
}

bool TraCIDemo11pMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<TraCIDemo11pMessage *>(obj)!=nullptr;
}

const char **TraCIDemo11pMessageDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *TraCIDemo11pMessageDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int TraCIDemo11pMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 13+basedesc->getFieldCount() : 13;
}

unsigned int TraCIDemo11pMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<13) ? fieldTypeFlags[field] : 0;
}

const char *TraCIDemo11pMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "demoData",
        "senderAddress",
        "messageID",
        "serial",
        "id",
        "driverName",
        "messageType",
        "receipeintID",
        "position",
        "TaskSize",
        "MIPS",
        "NodeSpeed",
        "taskPriority",
    };
    return (field>=0 && field<13) ? fieldNames[field] : nullptr;
}

int TraCIDemo11pMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='d' && strcmp(fieldName, "demoData")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "senderAddress")==0) return base+1;
    if (fieldName[0]=='m' && strcmp(fieldName, "messageID")==0) return base+2;
    if (fieldName[0]=='s' && strcmp(fieldName, "serial")==0) return base+3;
    if (fieldName[0]=='i' && strcmp(fieldName, "id")==0) return base+4;
    if (fieldName[0]=='d' && strcmp(fieldName, "driverName")==0) return base+5;
    if (fieldName[0]=='m' && strcmp(fieldName, "messageType")==0) return base+6;
    if (fieldName[0]=='r' && strcmp(fieldName, "receipeintID")==0) return base+7;
    if (fieldName[0]=='p' && strcmp(fieldName, "position")==0) return base+8;
    if (fieldName[0]=='T' && strcmp(fieldName, "TaskSize")==0) return base+9;
    if (fieldName[0]=='M' && strcmp(fieldName, "MIPS")==0) return base+10;
    if (fieldName[0]=='N' && strcmp(fieldName, "NodeSpeed")==0) return base+11;
    if (fieldName[0]=='t' && strcmp(fieldName, "taskPriority")==0) return base+12;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *TraCIDemo11pMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",
        "LAddress::L2Type",
        "string",
        "int",
        "int",
        "string",
        "int",
        "int",
        "Coord",
        "int",
        "int",
        "double",
        "int",
    };
    return (field>=0 && field<13) ? fieldTypeStrings[field] : nullptr;
}

const char **TraCIDemo11pMessageDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *TraCIDemo11pMessageDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int TraCIDemo11pMessageDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    TraCIDemo11pMessage *pp = (TraCIDemo11pMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *TraCIDemo11pMessageDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    TraCIDemo11pMessage *pp = (TraCIDemo11pMessage *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string TraCIDemo11pMessageDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    TraCIDemo11pMessage *pp = (TraCIDemo11pMessage *)object; (void)pp;
    switch (field) {
        case 0: return oppstring2string(pp->getDemoData());
        case 1: {std::stringstream out; out << pp->getSenderAddress(); return out.str();}
        case 2: return oppstring2string(pp->getMessageID());
        case 3: return long2string(pp->getSerial());
        case 4: return long2string(pp->getId());
        case 5: return oppstring2string(pp->getDriverName());
        case 6: return long2string(pp->getMessageType());
        case 7: return long2string(pp->getReceipeintID());
        case 8: {std::stringstream out; out << pp->getPosition(); return out.str();}
        case 9: return long2string(pp->getTaskSize());
        case 10: return long2string(pp->getMIPS());
        case 11: return double2string(pp->getNodeSpeed());
        case 12: return long2string(pp->getTaskPriority());
        default: return "";
    }
}

bool TraCIDemo11pMessageDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    TraCIDemo11pMessage *pp = (TraCIDemo11pMessage *)object; (void)pp;
    switch (field) {
        case 0: pp->setDemoData((value)); return true;
        case 2: pp->setMessageID((value)); return true;
        case 3: pp->setSerial(string2long(value)); return true;
        case 4: pp->setId(string2long(value)); return true;
        case 5: pp->setDriverName((value)); return true;
        case 6: pp->setMessageType(string2long(value)); return true;
        case 7: pp->setReceipeintID(string2long(value)); return true;
        case 9: pp->setTaskSize(string2long(value)); return true;
        case 10: pp->setMIPS(string2long(value)); return true;
        case 11: pp->setNodeSpeed(string2double(value)); return true;
        case 12: pp->setTaskPriority(string2long(value)); return true;
        default: return false;
    }
}

const char *TraCIDemo11pMessageDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 1: return omnetpp::opp_typename(typeid(LAddress::L2Type));
        case 8: return omnetpp::opp_typename(typeid(Coord));
        default: return nullptr;
    };
}

void *TraCIDemo11pMessageDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    TraCIDemo11pMessage *pp = (TraCIDemo11pMessage *)object; (void)pp;
    switch (field) {
        case 1: return (void *)(&pp->getSenderAddress()); break;
        case 8: return (void *)(&pp->getPosition()); break;
        default: return nullptr;
    }
}

} // namespace veins

