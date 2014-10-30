#ifndef FSMDA_GINGANCL_COMMUNICATION_ONDEMAND_PCM_H_
#define FSMDA_GINGANCL_COMMUNICATION_ONDEMAND_PCM_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include <fsmda/model/communication/ondemand_object_control.h>
#include <string>

using namespace std;

/*----------------------------------------------------------------------
 |   OnDemandPCM class
 +---------------------------------------------------------------------*/
class OnDemandPCM : public OnDemandPCMInterface
{
public:
  // public constructors & destructors
  OnDemandPCM ();
  virtual
  ~OnDemandPCM ();

  // OnDemandPCMInterface overloaded methods
  virtual void
  notifyOnDemandContent (const string& action, const string& location);
};

#endif /* FSMDA_GINGANCL_COMMUNICATION_ONDEMAND_PCM_H_ */
