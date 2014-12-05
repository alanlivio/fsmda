#ifndef FSMDA_COMMUNICATION_UPNP_ONDEMAND_CCM_H_
#define FSMDA_COMMUNICATION_UPNP_ONDEMAND_CCM_H_
/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include "fsmda/communication/upnp_service_cm_interface.h"
#include <string>

class PLT_UPnP;

using std::string;

/*----------------------------------------------------------------------
 |   UpnpOnDemandCcm class
 +---------------------------------------------------------------------*/
class UpnpOnDemandCcm : public ServiceCmInterface {
 public:
  // class fields and methods

  // public constructors & destructors
  UpnpOnDemandCcm();
  virtual ~UpnpOnDemandCcm();

  // ServiceCMInterface overloaded methods
  virtual int StartCommunicationService();
  virtual int StopCommunicationService();
  virtual bool IsServiceStartd();

 private:
  string ondemand_folder_;
  string uuid_;
  bool service_start_;
  PLT_UPnP* upnp_reference_;
};

#endif  // FSMDA_COMMUNICATION_UPNP_ONDEMAND_CCM_H_
