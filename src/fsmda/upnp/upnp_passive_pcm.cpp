

#include "fsmda/upnp/upnp_passive_pcm.h"


UpnpPassivePcm::UpnpPassivePcm() {}


UpnpPassivePcm::~UpnpPassivePcm() {}


void UpnpPassivePcm::NotifyError(const string& message,
                                 const string& object_id) {}


int UpnpPassivePcm::StartCommunicationService() {}


int UpnpPassivePcm::StopCommunicationService() {}


bool UpnpPassivePcm::IsCommunicationServiceStarted() {}

NPT_Result UpnpPassivePcm::SetupServices() {}


NPT_Result UpnpPassivePcm::OnAction(
    PLT_ActionReference& action, const PLT_HttpRequestContext& context) {}

NPT_Result UpnpPassivePcm::OnDeviceAdded(PLT_DeviceDataReference& device) {
}


NPT_Result UpnpPassivePcm::OnDeviceRemoved(
    PLT_DeviceDataReference& device) {}


NPT_Result UpnpPassivePcm::OnActionResponse(NPT_Result res,
                                                 PLT_ActionReference& action,
                                                 void* userdata) {}


NPT_Result UpnpPassivePcm::OnEventNotify(
    PLT_Service* service, NPT_List<PLT_StateVariable*>* vars) {}
