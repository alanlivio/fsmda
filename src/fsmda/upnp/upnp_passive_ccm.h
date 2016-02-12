#ifndef FSMDA_UPNP_UPNP_PASSIVE_CCM_H_
#define FSMDA_UPNP_UPNP_PASSIVE_CCM_H_

#include <string>
#include <NptTypes.h>
#include <PltDeviceHost.h>
#include <PltUPnP.h>
#include <PltCtrlPoint.h>
#include "fsmda/model/passive_objects_api.h"

class UpnpPassiveCcm : public PLT_DeviceHost,
                       public PLT_CtrlPointListener,
                       public PassiveClassInterface {
 public:
  // public constructors & destructors
  UpnpPassiveCcm();
  virtual ~UpnpPassiveCcm();

  // public CommunicationServiceInterface overload methods
  virtual int start_communication_service();
  virtual int StopCommunicationService();
  virtual bool is_communication_service_started();

  // PassiveCCMInterface overloaded methods
  virtual void prepare(const string& position);
  virtual void send_content(char* content);

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
};

#endif  // FSMDA_UPNP_UPNP_PASSIVE_CCM_H_
