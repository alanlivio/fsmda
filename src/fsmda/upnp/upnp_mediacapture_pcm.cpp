/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include "fsmda/upnp/upnp_mediacapture_pcm.h"

/*----------------------------------------------------------------------
 |   UpnpMediaCapturePcm::UpnpMediaCapturePcm
 +---------------------------------------------------------------------*/
UpnpMediaCapturePcm::UpnpMediaCapturePcm() {}

/*----------------------------------------------------------------------
 |   UpnpMediaCapturePcm::~UpnpMediaCapturePcm
 +---------------------------------------------------------------------*/
UpnpMediaCapturePcm::~UpnpMediaCapturePcm() {}

/*----------------------------------------------------------------------
 |   UpnpMediaCapturePcm::SendContent
 +---------------------------------------------------------------------*/
void UpnpMediaCapturePcm::SendContent(char* content, const string& resource_id,
                                      unsigned int child_index) {}

/*----------------------------------------------------------------------
 |   UpnpMediaCapturePcm::StartCommunicationService
 +---------------------------------------------------------------------*/
int UpnpMediaCapturePcm::StartCommunicationService() {}

/*----------------------------------------------------------------------
 |   UpnpMediaCapturePcm::StopCommunicationService
 +---------------------------------------------------------------------*/
int UpnpMediaCapturePcm::StopCommunicationService() {}

/*----------------------------------------------------------------------
 |   UpnpMediaCapturePcm::IsCommunicationServiceStarted
 +---------------------------------------------------------------------*/
bool UpnpMediaCapturePcm::IsCommunicationServiceStarted() {}
/*----------------------------------------------------------------------
 |   UpnpMediaCapturePcm::SetupServices
 +---------------------------------------------------------------------*/
NPT_Result UpnpMediaCapturePcm::SetupServices() {}

/*----------------------------------------------------------------------
 |   UpnpMediaCapturePcm::OnAction
 +---------------------------------------------------------------------*/
NPT_Result UpnpMediaCapturePcm::OnAction(
    PLT_ActionReference& action, const PLT_HttpRequestContext& context) {}

/*----------------------------------------------------------------------
 |   UpnpMediaCapturePcm::OnDeviceAdded
 +---------------------------------------------------------------------*/
NPT_Result UpnpMediaCapturePcm::OnDeviceAdded(PLT_DeviceDataReference& device) {
}

/*----------------------------------------------------------------------
 |   UpnpMediaCapturePcm::OnDeviceRemoved
 +---------------------------------------------------------------------*/
NPT_Result UpnpMediaCapturePcm::OnDeviceRemoved(
    PLT_DeviceDataReference& device) {}

/*----------------------------------------------------------------------
 |   UpnpMediaCapturePcm::OnActionResponse
 +---------------------------------------------------------------------*/
NPT_Result UpnpMediaCapturePcm::OnActionResponse(NPT_Result res,
                                                 PLT_ActionReference& action,
                                                 void* userdata) {}

/*----------------------------------------------------------------------
 |   UpnpMediaCapturePcm::OnEventNotify
 +---------------------------------------------------------------------*/
NPT_Result UpnpMediaCapturePcm::OnEventNotify(
    PLT_Service* service, NPT_List<PLT_StateVariable*>* vars) {}
