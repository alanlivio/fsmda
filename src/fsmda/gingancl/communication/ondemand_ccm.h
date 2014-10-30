#ifndef SRC_FSMDA_GINGANCL_COMMUNICATION_ONDEMAND_CCM_H_
#define SRC_FSMDA_GINGANCL_COMMUNICATION_ONDEMAND_CCM_H_
/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include <fsmda/gingancl/communication/service_cm_interface.h>

/*----------------------------------------------------------------------
 |   OnDemandCCM class
 +---------------------------------------------------------------------*/
class OnDemandCCM : public ServiceCMInterface
{
public:
  // public constructors & destructors
  OnDemandCCM ();
  virtual
  ~OnDemandCCM ();

  // ServiceCMInterface overloaded methods
  virtual int
  start_communication_service ();
  virtual int
  stop_communication_service ();
};

#endif /* SRC_FSMDA_GINGANCL_COMMUNICATION_ONDEMAND_CCM_H_ */
