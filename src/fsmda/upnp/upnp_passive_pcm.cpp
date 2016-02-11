/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include "fsmda/upnp/upnp_passive_pcm.h"

/*----------------------------------------------------------------------
 |   UpnpPassivePcm::UpnpPassivePcm
 +---------------------------------------------------------------------*/
UpnpPassivePcm::UpnpPassivePcm() {}

/*----------------------------------------------------------------------
 |   UpnpPassivePcm::~UpnpPassivePcm
 +---------------------------------------------------------------------*/
UpnpPassivePcm::~UpnpPassivePcm() {}

/*----------------------------------------------------------------------
 |   UpnpPassivePcm::NotifyError
 +---------------------------------------------------------------------*/
void UpnpPassivePcm::NotifyError(const string& message,
                                 const string& object_id) {}

/*----------------------------------------------------------------------
 |   UpnpPassivePcm::StartCommunicationService
 +---------------------------------------------------------------------*/
int UpnpPassivePcm::StartCommunicationService() {}

/*----------------------------------------------------------------------
 |   UpnpPassivePcm::StopCommunicationService
 +---------------------------------------------------------------------*/
int UpnpPassivePcm::StopCommunicationService() {}

/*----------------------------------------------------------------------
 |   UpnpPassivePcm::StopCommunicationService
 +---------------------------------------------------------------------*/
bool UpnpPassivePcm::IsCommunicationServiceStarted() {}
/*----------------------------------------------------------------------
 |   UpnpPassivePcm::SetupServices
 +---------------------------------------------------------------------*/
NPT_Result UpnpPassivePcm::SetupServices() {}

/*----------------------------------------------------------------------
 |   UpnpPassivePcm::OnAction
 +---------------------------------------------------------------------*/
NPT_Result UpnpPassivePcm::OnAction(
    PLT_ActionReference& action, const PLT_HttpRequestContext& context) {}
/*----------------------------------------------------------------------
 |   UpnpPassivePcm::OnDeviceAdded
 +---------------------------------------------------------------------*/
NPT_Result UpnpPassivePcm::OnDeviceAdded(PLT_DeviceDataReference& device) {
}

/*----------------------------------------------------------------------
 |   UpnpPassivePcm::OnDeviceRemoved
 +---------------------------------------------------------------------*/
NPT_Result UpnpPassivePcm::OnDeviceRemoved(
    PLT_DeviceDataReference& device) {}

/*----------------------------------------------------------------------
 |   UpnpPassivePcm::OnActionResponse
 +---------------------------------------------------------------------*/
NPT_Result UpnpPassivePcm::OnActionResponse(NPT_Result res,
                                                 PLT_ActionReference& action,
                                                 void* userdata) {}

/*----------------------------------------------------------------------
 |   UpnpPassivePcm::OnEventNotify
 +---------------------------------------------------------------------*/
NPT_Result UpnpPassivePcm::OnEventNotify(
    PLT_Service* service, NPT_List<PLT_StateVariable*>* vars) {}
