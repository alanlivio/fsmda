#ifndef FSMDA_GINGANCL_COMMUNICATION_ACTIVE_PCM_H_
#define FSMDA_GINGANCL_COMMUNICATION_ACTIVE_PCM_H_

#include "fsmda/model/communication/active_object_control.h"

class ActivePCM : public ActivePCMInterface
{
public:
  ActivePCM ();

  virtual
  ~ActivePCM ();

  //////////////////// ActivePCMInterface functions ////////////////////
  virtual void
  requestPropertyValue (string objectID, string name);

  virtual void
  notifyEventTransition (string objectID, string eventID, string transition);

  virtual void
  notifyError (string objectID, string message);
};

#endif /* FSMDA_GINGANCL_COMMUNICATION_ACTIVE_PCM_H_ */
