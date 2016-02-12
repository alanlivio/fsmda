#include "fsmda/upnp/upnp_mediacapture_ccm.h"
#include <string>

UpnpMediaCaptureCcm::UpnpMediaCaptureCcm() {}

UpnpMediaCaptureCcm::~UpnpMediaCaptureCcm() {}

int UpnpMediaCaptureCcm::start_communication_service() {}

int UpnpMediaCaptureCcm::stop_ommunication_service() {}

bool UpnpMediaCaptureCcm::is_communication_service_started() {}

void UpnpMediaCaptureCcm::request_content(const string& resource_id,
                                          unsigned int device_index) {}

NPT_Result UpnpMediaCaptureCcm::SetupServices() {}

NPT_Result UpnpMediaCaptureCcm::OnAction(
    PLT_ActionReference& action, const PLT_HttpRequestContext& context) {}

NPT_Result UpnpMediaCaptureCcm::OnDeviceAdded(PLT_DeviceDataReference& device) {
}

NPT_Result UpnpMediaCaptureCcm::OnDeviceRemoved(
    PLT_DeviceDataReference& device) {}

NPT_Result UpnpMediaCaptureCcm::OnActionResponse(NPT_Result res,
                                                 PLT_ActionReference& action,
                                                 void* userdata) {}

NPT_Result UpnpMediaCaptureCcm::OnEventNotify(
    PLT_Service* service, NPT_List<PLT_StateVariable*>* vars) {}
