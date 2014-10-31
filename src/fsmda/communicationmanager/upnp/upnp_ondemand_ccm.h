#ifndef UPNP_ONDEMAND_CCM_H_
#define UPNP_ONDEMAND_CCM_H_
/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include "fsmda/communicationmanager/upnp/upnp_service_cm_interface.h"
#include <string>

using namespace std;

/*----------------------------------------------------------------------
 |   UpnpOnDemandCcm class
 +---------------------------------------------------------------------*/
class UpnpOnDemandCcm : public ServiceCmInterface
{
public:
  // public constructors & destructors
  UpnpOnDemandCcm ();
  virtual
  ~UpnpOnDemandCcm ();

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

#endif /* UPNP_ONDEMAND_CCM_H_ */
