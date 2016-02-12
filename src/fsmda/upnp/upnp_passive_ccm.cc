

#include "fsmda/upnp/upnp_passive_ccm.h"
#include <string>

UpnpPassiveCcm::UpnpPassiveCcm() {}

UpnpPassiveCcm::~UpnpPassiveCcm() {}

int UpnpPassiveCcm::start_communication_service() {}

int UpnpPassiveCcm::StopCommunicationService() {}

bool UpnpPassiveCcm::is_communication_service_started() {}

void UpnpPassiveCcm::prepare(const string& position) {}

void UpnpPassiveCcm::send_content(char* content) {}

NPT_Result UpnpPassiveCcm::SetupServices() {}

NPT_Result UpnpPassiveCcm::OnAction(PLT_ActionReference& action,
                                    const PLT_HttpRequestContext& context) {}

NPT_Result UpnpPassiveCcm::OnDeviceAdded(PLT_DeviceDataReference& device) {}

NPT_Result UpnpPassiveCcm::OnDeviceRemoved(PLT_DeviceDataReference& device) {}

NPT_Result UpnpPassiveCcm::OnActionResponse(NPT_Result res,
                                            PLT_ActionReference& action,
                                            void* userdata) {}

NPT_Result UpnpPassiveCcm::OnEventNotify(PLT_Service* service,
                                         NPT_List<PLT_StateVariable*>* vars) {}
