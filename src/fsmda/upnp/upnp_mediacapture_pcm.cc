#include "fsmda/upnp/upnp_mediacapture_pcm.h"

UpnpMediaCapturePcm::UpnpMediaCapturePcm() {}

UpnpMediaCapturePcm::~UpnpMediaCapturePcm() {}

void UpnpMediaCapturePcm::send_content(char* content, const string& resource_id,
                                       unsigned int child_index) {}

int UpnpMediaCapturePcm::start_communication_service() {}

int UpnpMediaCapturePcm::stop_communication_service() {}

bool UpnpMediaCapturePcm::is_communication_service_started() {}

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
