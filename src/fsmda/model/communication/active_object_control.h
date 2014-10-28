#ifndef FSMDA_ACTIVE_OBJECT_CONTROL_H_
#define FSMDA_ACTIVE_OBJECT_CONTROL_H_

#include <string>

using namespace std;

class Property
{
  string propertyName;
  string propertyValue;
};

class Event
{
  string eventId;
  string eventType;
  string eventDesc;
};

class ActivePCMInterface
{
public:
  virtual
  ~ActivePCMInterface ()
  {
  }

  virtual void
  requestPropertyValue (string objectID, string name)=0;

  virtual void
  notifyEventTransition (string objectID, string eventID, string transition)=0;

  virtual void
  notifyError (string objectID, string message)=0;
};

class ActiveCCMInterface
{
public:
  virtual
  ~ActiveCCMInterface ()
  {
  }

  virtual void
  prepare (string objectID, string objectSrc, vector<Property> properties,
	   vector<Event> evts)=0;
  virtual void
  addEvent (string objectID, Event evt)=0;

  virtual void
  removeEvent (string objectID, string eventID)=0;

  virtual void
  postAction (string objectID, string eventID, string action)=0;

  virtual void
  reportPropertyValue (string objectID, string name, string value)=0;

  virtual void
  setPropertyValue (string objectID, string name, string value,
		    unsigned int duration)=0;
};

#endif /* FSMDA_ACTIVE_OBJECT_CONTROL_H_ */
