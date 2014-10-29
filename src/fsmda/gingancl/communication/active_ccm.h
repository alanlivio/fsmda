#ifndef FSMDA_GINGANCL_COMMUNICATION_ACTIVE_CCM_H_
#define FSMDA_GINGANCL_COMMUNICATION_ACTIVE_CCM_H_

#include "fsmda/model/communication/active_object_control.h"

class ActiveCCM : public ActiveCCMInterface
{
public:
  ActiveCCM ();

  virtual
  ~ActiveCCM ();

  //////////////////// ActiveCCMInterface functions ////////////////////
  virtual void
  prepare (const string& objectID, const string& objectSrc, vector<Property> properties,
	   vector<Event> evts);
  virtual void
  addEvent (const string& objectID, Event evt);

  virtual void
  removeEvent (const string& objectID, const string& eventID);

  virtual void
  postAction (const string& objectID, const string& eventID, const string& action);

  virtual void
  reportPropertyValue (const string& objectID, const string& name, const string& value);

  virtual void
  setPropertyValue (const string& objectID, const string& name, const string& value,
		    unsigned int duration);
};

#endif /* FSMDA_GINGANCL_COMMUNICATION_ACTIVE_CCM_H_ */
