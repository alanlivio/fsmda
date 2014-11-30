#ifndef UPNP_ONDEMAND_CCM_H_
#define UPNP_ONDEMAND_CCM_H_
/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include "fsmda/communication/upnp/upnp_service_cm_interface.h"
#include <string>

class PLT_UPnP;

using namespace std;

/*----------------------------------------------------------------------
 |   UpnpOnDemandCcm class
 +---------------------------------------------------------------------*/
class UpnpOnDemandCcm : public ServiceCmInterface {
 public:
  // class fields and methods

  // public constructors & destructors
  UpnpOnDemandCcm();
  virtual
  ~UpnpOnDemandCcm();

  // ServiceCMInterface overloaded methods
  virtual int
  start_communication_service();
  virtual int
  stop_communication_service();
  virtual bool
  is_service_started();

 private:
  string ondemand_folder_;
  string uuid_;
  bool service_start_;
  PLT_UPnP* upnp_reference_;
};

#endif /* UPNP_ONDEMAND_CCM_H_ */
