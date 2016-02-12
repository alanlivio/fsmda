#include "fsmda/upnp/upnp_ondemand_pcm.h"
#include <string>

UpnpOnDemandPcm::UpnpOnDemandPcm() {}

UpnpOnDemandPcm::~UpnpOnDemandPcm() {}

int UpnpOnDemandPcm::start_communication_service() {}

int UpnpOnDemandPcm::stop_ommunication_service() {}

bool UpnpOnDemandPcm::is_communication_service_started() {}

void UpnpOnDemandPcm::notify_ondemand_content(const string& action,
                                              const string& location) {}

NPT_Result UpnpOnDemandPcm::SetupServices() {}

NPT_Result UpnpOnDemandPcm::OnAction(PLT_ActionReference& action,
                                     const PLT_HttpRequestContext& context) {}

NPT_Result UpnpOnDemandPcm::OnDeviceAdded(PLT_DeviceDataReference& device) {}

NPT_Result UpnpOnDemandPcm::OnDeviceRemoved(PLT_DeviceDataReference& device) {}

NPT_Result UpnpOnDemandPcm::OnActionResponse(NPT_Result res,
                                             PLT_ActionReference& action,
                                             void* userdata) {}

NPT_Result UpnpOnDemandPcm::OnEventNotify(PLT_Service* service,
                                          NPT_List<PLT_StateVariable*>* vars) {}
