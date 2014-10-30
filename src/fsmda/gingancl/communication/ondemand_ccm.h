#ifndef FSMDA_GINGANCL_COMMUNICATION_ONDEMAND_CCM_H_
#define FSMDA_GINGANCL_COMMUNICATION_ONDEMAND_CCM_H_
/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include <fsmda/gingancl/communication/service_cm_interface.h>
#include <string>

using namespace std;

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
  virtual bool
  is_service_started ();

private:
  string default_folder_;
  string default_uui_;
  bool service_start_;
};

#endif /* FSMDA_GINGANCL_COMMUNICATION_ONDEMAND_CCM_H_ */
