#ifndef FSMDA_UPNP_UPNP_PASSIVE_CCM_H_
#define FSMDA_UPNP_UPNP_PASSIVE_CCM_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/
#include <string>
#include <NptTypes.h>
#include <PltDeviceHost.h>
#include <PltUPnP.h>
#include <PltCtrlPoint.h>
#include "fsmda/model/passive_objects_api.h"

/*----------------------------------------------------------------------
 |   UpnpPassiveCcm  class
 +---------------------------------------------------------------------*/
class UpnpPassiveCcm : public PLT_DeviceHost,
                       public PLT_CtrlPointListener,
                       public PassiveClassInterface {
 public:
  // public constructors & destructors
  UpnpPassiveCcm();
  virtual ~UpnpPassiveCcm();

  // public CommunicationServiceInterface overload methods
  virtual int StartCommunicationService();
  virtual int StopCommunicationService();
  virtual bool IsCommunicationServiceStarted();

  // PassiveCCMInterface overloaded methods
  virtual void Prepare(const string& position);
  virtual void SendContent(char* content);

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
