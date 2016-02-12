#include "fsmda/upnp/upnp_ondemand_pcm.h"
#include <string>

UpnpOnDemandPcm::UpnpOnDemandPcm() {}

UpnpOnDemandPcm::~UpnpOnDemandPcm() {}

int UpnpOnDemandPcm::StartCommunicationService() {}

int UpnpOnDemandPcm::StopCommunicationService() {}

bool UpnpOnDemandPcm::IsCommunicationServiceStarted() {}

void UpnpOnDemandPcm::NotifyOnDemandContent(const string& action,
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
