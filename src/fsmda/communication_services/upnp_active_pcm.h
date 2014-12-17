#ifndef FSMDA_COMMUNICATION_SERVICES_UPNP_ACTIVE_PCM_H_
#define FSMDA_COMMUNICATION_SERVICES_UPNP_ACTIVE_PCM_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/
#include <string>
#include <NptTypes.h>
#include <PltAction.h>
#include <PltDeviceHost.h>
#include <PltHttp.h>
#include <PltUPnP.h>
#include <PltCtrlPoint.h>
#include "fsmda/model/active_object_interfaces.h"
#include "fsmda/communication_services/communication_service_interface.h"

using std::string;

/*----------------------------------------------------------------------
 |   UpnpActivePcm class
 +---------------------------------------------------------------------*/
class UpnpActivePcm : public PLT_DeviceHost,
                      public PLT_CtrlPointListener,
                      public ActivePcmInterface,
                      public CommunicationServiceInterface {
 public:
  // public constructors & destructors
  UpnpActivePcm();
  virtual ~UpnpActivePcm();

  // public CommunicationServiceInterface overload methods
  virtual int StartCommunicationService();
  virtual int StopCommunicationService();
  virtual bool IsCommunicationServiceStarted();

  // ActivePcmInterface overloaded methods
  virtual void RequestPropertyValue(const string& object_id,
                                    const string& name);
  virtual void NotifyEventTransition(const string& object_id,
                                     const string& event_id,
                                     const string& transition);
  virtual void NotifyError(const string& object_id, const string& message);

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

#endif  // FSMDA_COMMUNICATION_SERVICES_UPNP_ACTIVE_PCM_H_
