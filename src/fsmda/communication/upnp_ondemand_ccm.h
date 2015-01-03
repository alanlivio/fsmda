#ifndef FSMDA_COMMUNICATION_SERVICES_UPNP_ONDEMAND_CCM_H_
#define FSMDA_COMMUNICATION_SERVICES_UPNP_ONDEMAND_CCM_H_
/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/
#include <string>
#include <NptTypes.h>
#include <PltDeviceHost.h>
#include <PltUPnP.h>
#include <PltCtrlPoint.h>
#include "fsmda/model/ondemand_objects_api.h"
#include "fsmda/communication/communication_service_interface.h"

using std::string;

/*----------------------------------------------------------------------
 |   UpnpOnDemandCcm class
 +---------------------------------------------------------------------*/
class UpnpOnDemandCcm : public PLT_DeviceHost,
                        public PLT_CtrlPointListener,
                        public OnDemandCcmInterface,
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

  // PLT_DeviceHost overloaded methods
  virtual NPT_Result SetupServices();
  virtual NPT_Result OnAction(PLT_ActionReference& action,
                              const PLT_HttpRequestContext& context);

  // PLT_CtrlPointListener overloaded methods
  virtual NPT_Result OnDeviceAdded(PLT_DeviceDataReference& device);
  virtual NPT_Result OnDeviceRemoved(PLT_DeviceDataReference& device);
  virtual NPT_Result OnActionResponse(NPT_Result res,
                                      PLT_ActionReference& action,
                                      void* userdata);
  virtual NPT_Result OnEventNotify(PLT_Service* service,
                                   NPT_List<PLT_StateVariable*>* vars);

 private:
  string ondemand_folder_;
  string uuid_;
  bool service_start_;
  PLT_UPnP* upnp_reference_;
};

#endif  // FSMDA_COMMUNICATION_SERVICES_UPNP_ONDEMAND_CCM_H_
