#ifndef FSMDA_COMMUNICATION_UPNP_ONDEMAND_CCM_H_
#define FSMDA_COMMUNICATION_UPNP_ONDEMAND_CCM_H_
/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/
#include <string>
#include "fsmda/communication/model/ondemand_object_interfaces.h"
#include "fsmda/communication/communication_service_interface.h"
#include "PltUPnP.h"

using std::string;

/*----------------------------------------------------------------------
 |   UpnpOnDemandCcm class
 +---------------------------------------------------------------------*/
class UpnpOnDemandCcm : public OnDemandCcmInterface,
                        public CommunicationServiceInterface {
 public:
  // class fields and methods

  // public constructors & destructors
  UpnpOnDemandCcm();
  virtual ~UpnpOnDemandCcm();

  // public CommunicationServiceInterface overloaded methods
  virtual int StartCommunicationService();
  virtual int StopCommunicationService();
  virtual bool IsCommunicationServiceStarted();

 private:
  string ondemand_folder_;
  string uuid_;
  bool service_start_;
  PLT_UPnP* upnp_reference_;
};

#endif  // FSMDA_COMMUNICATION_UPNP_ONDEMAND_CCM_H_
