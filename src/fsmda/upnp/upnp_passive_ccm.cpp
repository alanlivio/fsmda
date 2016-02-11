/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include "fsmda/upnp/upnp_passive_ccm.h"
#include <string>

/*----------------------------------------------------------------------
 |   UpnpPassiveCcm::UpnpPassiveCcm
 +---------------------------------------------------------------------*/
UpnpPassiveCcm::UpnpPassiveCcm() {}

/*----------------------------------------------------------------------
 |   UpnpPassiveCcm::~UpnpPassiveCcm
 +---------------------------------------------------------------------*/
UpnpPassiveCcm::~UpnpPassiveCcm() {}

/*----------------------------------------------------------------------
 |   UpnpPassiveCcm::StartCommunicationService
 +---------------------------------------------------------------------*/
int UpnpPassiveCcm::StartCommunicationService() {}

/*----------------------------------------------------------------------
 |   UpnpPassiveCcm::StopCommunicationService
 +---------------------------------------------------------------------*/
int UpnpPassiveCcm::StopCommunicationService() {}

/*----------------------------------------------------------------------
 |   UpnpPassiveCcm::IsCommunicationServiceStarted
 +---------------------------------------------------------------------*/
bool UpnpPassiveCcm::IsCommunicationServiceStarted() {}

/*----------------------------------------------------------------------
 |   UpnpPassiveCcm::Prepare
 +---------------------------------------------------------------------*/
void UpnpPassiveCcm::Prepare(const string& position) {}

/*----------------------------------------------------------------------
 |   UpnpPassiveCcm::SendContent
 +---------------------------------------------------------------------*/
void UpnpPassiveCcm::SendContent(char* content) {}

/*----------------------------------------------------------------------
 |   UpnpPassiveCcm::SetupServices
 +---------------------------------------------------------------------*/
NPT_Result UpnpPassiveCcm::SetupServices() {}

/*----------------------------------------------------------------------
 |   UpnpPassiveCcm::OnAction
 +---------------------------------------------------------------------*/
NPT_Result UpnpPassiveCcm::OnAction(PLT_ActionReference& action,
                                    const PLT_HttpRequestContext& context) {}
/*----------------------------------------------------------------------
 |   UpnpPassiveCcm::OnDeviceAdded
 +---------------------------------------------------------------------*/
NPT_Result UpnpPassiveCcm::OnDeviceAdded(PLT_DeviceDataReference& device) {}

/*----------------------------------------------------------------------
 |   UpnpPassiveCcm::OnDeviceRemoved
 +---------------------------------------------------------------------*/
NPT_Result UpnpPassiveCcm::OnDeviceRemoved(PLT_DeviceDataReference& device) {}

/*----------------------------------------------------------------------
 |   UpnpPassiveCcm::OnActionResponse
 +---------------------------------------------------------------------*/
NPT_Result UpnpPassiveCcm::OnActionResponse(NPT_Result res,
                                            PLT_ActionReference& action,
                                            void* userdata) {}

/*----------------------------------------------------------------------
 |   UpnpPassiveCcm::OnEventNotify
 +---------------------------------------------------------------------*/
NPT_Result UpnpPassiveCcm::OnEventNotify(PLT_Service* service,
                                         NPT_List<PLT_StateVariable*>* vars) {}
