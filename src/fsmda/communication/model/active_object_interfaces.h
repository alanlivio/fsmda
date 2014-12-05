#ifndef FSMDA_COMMUNICATION_MODEL_ACTIVE_OBJECT_INTERFACES_H_
#define FSMDA_COMMUNICATION_MODEL_ACTIVE_OBJECT_INTERFACES_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include <string>
#include <vector>

using std::string;
using std::vector;

/*----------------------------------------------------------------------
 |   Property class
 +---------------------------------------------------------------------*/
class Property {
  const string propertyName;
  const string propertyValue;
};

/*----------------------------------------------------------------------
 |   Event class
 +---------------------------------------------------------------------*/
class Event {
  const string eventId;
  const string eventType;
  const string eventDesc;
};

/*----------------------------------------------------------------------
 |   ActivePcmInterface abstract class
 +---------------------------------------------------------------------*/
class ActivePcmInterface {
 public:
  // public constructors & destructors
  virtual ~ActivePcmInterface() {
  }

  // public pure virtual methods
  virtual void
  requestPropertyValue(const string& objectID, const string& name)=0;
  virtual void
  notifyEventTransition(const string& objectID, const string& eventID,
                        const string& transition)=0;
  virtual void
  notifyError(const string& objectID, const string& message)=0;
};

/*----------------------------------------------------------------------
 |   ActiveCcmInterface abstract class
 +---------------------------------------------------------------------*/
class ActiveCcmInterface {
 public:
  // public constructors & destructors
  virtual ~ActiveCcmInterface() {
  }

  // public pure virtual methods
  virtual void
  prepare(const string& objectID, const string& objectSrc,
          vector<Property> properties, vector<Event> evts)=0;
  virtual void
  addEvent(const string& objectID, Event evt)=0;
  virtual void
  removeEvent(const string& objectID, const string& eventID)=0;
  virtual void
  postAction(const string& objectID, const string& eventID,
             const string& action)=0;
  virtual void
  reportPropertyValue(const string& objectID, const string& name,
                      const string& value)=0;
  virtual void
  setPropertyValue(const string& objectID, const string& name,
                   const string& value, unsigned int duration)=0;
};

#endif  // FSMDA_COMMUNICATION_MODEL_ACTIVE_OBJECT_INTERFACES_H_
