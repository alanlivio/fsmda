#ifndef FSMDA_GINGANCL_COMMUNICATION_ON_DEMAND_PCM_H_
#define FSMDA_GINGANCL_COMMUNICATION_ON_DEMAND_PCM_H_

#include "fsmda/model/communication/ondemand_object_control.h"

class OnDemandPCM : public OnDemandPCMInterface
{
public:
  OnDemandPCM ();
  virtual
  ~OnDemandPCM ();

  //////////////////// OnDemandPCMInterface functions ////////////////////
  virtual void
  notifyOnDemandContent (string action, string location);

};

#endif /* FSMDA_GINGANCL_COMMUNICATION_ON_DEMAND_PCM_H_ */
