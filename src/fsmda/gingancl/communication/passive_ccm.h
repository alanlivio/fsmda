#ifndef FSMDA_GINGANCL_COMMUNICATION_PASSIVE_CCM_H_
#define FSMDA_GINGANCL_COMMUNICATION_PASSIVE_CCM_H_

#include "fsmda/model/communication/passive_object_control.h"

class PassiveCCM : public PassiveCCMInterface
{
public:
  PassiveCCM ();
  virtual
  ~PassiveCCM ();

  //////////////////// PassiveCCMInterface functions ////////////////////
  virtual void
  prepare (const string& position);

  virtual void
  sendContent (char* content);
};

#endif /* FSMDA_GINGANCL_COMMUNICATION_PASSIVE_CCM_H_ */
