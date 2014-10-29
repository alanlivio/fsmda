#ifndef FSMDA_ACTIVE_OBJECT_CONTROL_H_
#define FSMDA_ACTIVE_OBJECT_CONTROL_H_

#include <string>
#include <vector>

using namespace std;

class Property
{
  const string propertyName;
  const string propertyValue;
};

class Event
{
  const string eventId;
  const string eventType;
  const string eventDesc;
};

class ActivePCMInterface
{
public:
  virtual
  ~ActivePCMInterface ()
  {
  }

  virtual void
  requestPropertyValue (const string& objectID, const string& name)=0;

  virtual void
  notifyEventTransition (const string& objectID, const string& eventID, const string& transition)=0;

  virtual void
  notifyError (const string& objectID, const string& message)=0;
};

class ActiveCCMInterface
{
public:
  virtual
  ~ActiveCCMInterface ()
  {
  }

  virtual void
  prepare (const string& objectID, const string& objectSrc, vector<Property> properties,
	   vector<Event> evts)=0;
  virtual void
  addEvent (const string& objectID, Event evt)=0;

  virtual void
  removeEvent (const string& objectID, const string& eventID)=0;

  virtual void
  postAction (const string& objectID, const string& eventID, const string& action)=0;

  virtual void
  reportPropertyValue (const string& objectID, const string& name, const string& value)=0;

  virtual void
  setPropertyValue (const string& objectID, const string& name, const string& value,
		    unsigned int duration)=0;
};

#endif /* FSMDA_ACTIVE_OBJECT_CONTROL_H_ */
