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
  requestPropertyValue (const string& objectID, const string& name);

  virtual void
  notifyEventTransition (const string& objectID, const string& eventID, const string& transition);

  virtual void
  notifyError (const string& objectID, const string& message);
};

#endif /* FSMDA_GINGANCL_COMMUNICATION_ACTIVE_PCM_H_ */
