#ifndef FSMDA_COMMUNICATION_UPNP_PASSIVE_PCM_H_
#define FSMDA_COMMUNICATION_UPNP_PASSIVE_PCM_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/
#include <string>
#include <NptTypes.h>
#include <PltDeviceHost.h>
#include <PltUPnP.h>
#include <PltCtrlPoint.h>
#include "fsmda/model/passive_objects_api.h"
#include "fsmda/communication/communication_service_interface.h"

using std::string;

/*----------------------------------------------------------------------
 |   UpnpPassivePcm  class
 +---------------------------------------------------------------------*/
class UpnpPassivePcm : public PLT_DeviceHost,
                       public PLT_CtrlPointListener,
                       public PassiveClassListenerInterface,
                       public CommunicationServiceInterface {
 public:
  // public constructors & destructors
  UpnpPassivePcm();
  virtual ~UpnpPassivePcm();

  // PassivePCMInterface overloaded methods
  virtual void NotifyError(const string& message, const string& object_id);

  // public CommunicationServiceInterface overload methods
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
};

#endif  // FSMDA_COMMUNICATION_UPNP_PASSIVE_PCM_H_
