

#include "fsmda/upnp/upnp_mediacapture_pcm.h"

UpnpMediaCapturePcm::UpnpMediaCapturePcm() {}

UpnpMediaCapturePcm::~UpnpMediaCapturePcm() {}

void UpnpMediaCapturePcm::SendContent(char* content, const string& resource_id,
                                      unsigned int child_index) {}

int UpnpMediaCapturePcm::StartCommunicationService() {}

int UpnpMediaCapturePcm::StopCommunicationService() {}

bool UpnpMediaCapturePcm::IsCommunicationServiceStarted() {}

NPT_Result UpnpMediaCapturePcm::SetupServices() {}

NPT_Result UpnpMediaCapturePcm::OnAction(
    PLT_ActionReference& action, const PLT_HttpRequestContext& context) {}

NPT_Result UpnpMediaCapturePcm::OnDeviceAdded(PLT_DeviceDataReference& device) {
}

NPT_Result UpnpMediaCapturePcm::OnDeviceRemoved(
    PLT_DeviceDataReference& device) {}

NPT_Result UpnpMediaCapturePcm::OnActionResponse(NPT_Result res,
                                                 PLT_ActionReference& action,
                                                 void* userdata) {}

NPT_Result UpnpMediaCapturePcm::OnEventNotify(
    PLT_Service* service, NPT_List<PLT_StateVariable*>* vars) {}
