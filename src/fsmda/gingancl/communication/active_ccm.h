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
  prepare (string objectID, string objectSrc, vector<Property> properties,
	   vector<Event> evts);
  virtual void
  addEvent (string objectID, Event evt);

  virtual void
  removeEvent (string objectID, string eventID);

  virtual void
  postAction (string objectID, string eventID, string action);

  virtual void
  reportPropertyValue (string objectID, string name, string value);

  virtual void
  setPropertyValue (string objectID, string name, string value,
		    unsigned int duration);
};

#endif /* FSMDA_GINGANCL_COMMUNICATION_ACTIVE_CCM_H_ */
