#ifndef FSMDA_GINGANCL_COMMUNICATION_PASSIVE_PCM_H_
#define FSMDA_GINGANCL_COMMUNICATION_PASSIVE_PCM_H_

#include "fsmda/model/communication/passive_object_control.h"

class PassivePCM : public PassivePCMInterface
{
public:
  PassivePCM ();

  virtual
  ~PassivePCM ();

  //////////////////// PassivePCMInterface functions ////////////////////
  virtual void
  notifyError (const string& message, const string& objectId);
};

#endif /* FSMDA_GINGANCL_COMMUNICATION_PASSIVE_PCM_H_ */
