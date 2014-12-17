/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include "fsmda/communication_services/upnp_active_pcm.h"

/*----------------------------------------------------------------------
 |   UpnpActivePcm::UpnpActivePcm
 +---------------------------------------------------------------------*/
UpnpActivePcm::UpnpActivePcm() {}

/*----------------------------------------------------------------------
 |   UpnpActivePcm::~UpnpActivePcm
 +---------------------------------------------------------------------*/
UpnpActivePcm::~UpnpActivePcm() {}

/*----------------------------------------------------------------------
 |   UpnpActivePcm::StartCommunicationService
 +---------------------------------------------------------------------*/
int UpnpActivePcm::StartCommunicationService() {}

/*----------------------------------------------------------------------
 |   UpnpActivePcm::StopCommunicationService
 +---------------------------------------------------------------------*/
int UpnpActivePcm::StopCommunicationService() {}

/*----------------------------------------------------------------------
 |   UpnpActivePcm::IsCommunicationServiceStarted
 +---------------------------------------------------------------------*/
bool UpnpActivePcm::IsCommunicationServiceStarted() {}

/*----------------------------------------------------------------------
 |   UpnpActivePcm::RequestPropertyValue
 +---------------------------------------------------------------------*/
void UpnpActivePcm::RequestPropertyValue(const string &object_id,
                                         const string &name) {}

/*----------------------------------------------------------------------
 |   UpnpActivePcm::NotifyEventTransition
 +---------------------------------------------------------------------*/
void UpnpActivePcm::NotifyEventTransition(const string &object_id,
                                          const string &event_id,
                                          const string &transition) {}

/*----------------------------------------------------------------------
 |   UpnpActivePcm::NotifyError
 +---------------------------------------------------------------------*/
void UpnpActivePcm::NotifyError(const string &object_id,
                                const string &message) {}

/*----------------------------------------------------------------------
 |   UpnpActivePcm::SetupServices
 +---------------------------------------------------------------------*/
NPT_Result UpnpActivePcm::SetupServices() {}

/*----------------------------------------------------------------------
 |   UpnpActivePcm::OnAction
 +---------------------------------------------------------------------*/
NPT_Result UpnpActivePcm::OnAction(PLT_ActionReference &action,
                                   const PLT_HttpRequestContext &context) {}

/*----------------------------------------------------------------------
 |   UpnpActivePcm::OnDeviceAdded
 +---------------------------------------------------------------------*/
NPT_Result UpnpActivePcm::OnDeviceAdded(PLT_DeviceDataReference &device) {}

/*----------------------------------------------------------------------
 |   UpnpActivePcm::OnDeviceRemoved
 +---------------------------------------------------------------------*/
NPT_Result UpnpActivePcm::OnDeviceRemoved(PLT_DeviceDataReference &device) {}

/*----------------------------------------------------------------------
 |   UpnpActivePcm::OnActionResponse
 +---------------------------------------------------------------------*/
NPT_Result UpnpActivePcm::OnActionResponse(NPT_Result res,
                                           PLT_ActionReference &action,
                                           void *userdata) {}

/*----------------------------------------------------------------------
 |   UpnpActivePcm::OnEventNotify
 +---------------------------------------------------------------------*/
NPT_Result UpnpActivePcm::OnEventNotify(PLT_Service *service,
                                        NPT_List<PLT_StateVariable *> *vars) {}
