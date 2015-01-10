/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include "fsmda/upnp/upnp_ondemand_pcm.h"
#include <string>

/*----------------------------------------------------------------------
 |   UpnpOnDemandPcm::UPnPOnDemandPCM
 +---------------------------------------------------------------------*/
UpnpOnDemandPcm::UpnpOnDemandPcm() {}

/*----------------------------------------------------------------------
 |   UpnpOnDemandPcm::~UPnPOnDemandPCM
 +---------------------------------------------------------------------*/
UpnpOnDemandPcm::~UpnpOnDemandPcm() {}

/*----------------------------------------------------------------------
 |   UpnpOnDemandPcm::StartCommunicationService
 +---------------------------------------------------------------------*/
int UpnpOnDemandPcm::StartCommunicationService() {}

/*----------------------------------------------------------------------
 |   UpnpOnDemandPcm::StopCommunicationService
 +---------------------------------------------------------------------*/
int UpnpOnDemandPcm::StopCommunicationService() {}

/*----------------------------------------------------------------------
 |   UpnpOnDemandPcm::IsCommunicationServiceStarted
 +---------------------------------------------------------------------*/
bool UpnpOnDemandPcm::IsCommunicationServiceStarted() {}

/*----------------------------------------------------------------------
 |   UPnPOnDemandPCM::NotifyOnDemandContent
 +---------------------------------------------------------------------*/
void UpnpOnDemandPcm::NotifyOnDemandContent(const string& action,
                                            const string& location) {}
/*----------------------------------------------------------------------
 |   UpnpOnDemandPcm::SetupServices
 +---------------------------------------------------------------------*/
NPT_Result UpnpOnDemandPcm::SetupServices() {}

/*----------------------------------------------------------------------
 |   UpnpOnDemandPcm::OnAction
 +---------------------------------------------------------------------*/
NPT_Result UpnpOnDemandPcm::OnAction(PLT_ActionReference& action,
                                     const PLT_HttpRequestContext& context) {}
/*----------------------------------------------------------------------
 |   UpnpOnDemandPcm::OnDeviceAdded
 +---------------------------------------------------------------------*/
NPT_Result UpnpOnDemandPcm::OnDeviceAdded(PLT_DeviceDataReference& device) {}

/*----------------------------------------------------------------------
 |   UpnpOnDemandPcm::OnDeviceRemoved
 +---------------------------------------------------------------------*/
NPT_Result UpnpOnDemandPcm::OnDeviceRemoved(PLT_DeviceDataReference& device) {}

/*----------------------------------------------------------------------
 |   UpnpOnDemandPcm::OnActionResponse
 +---------------------------------------------------------------------*/
NPT_Result UpnpOnDemandPcm::OnActionResponse(NPT_Result res,
                                             PLT_ActionReference& action,
                                             void* userdata) {}

/*----------------------------------------------------------------------
 |   UpnpOnDemandPcm::OnEventNotify
 +---------------------------------------------------------------------*/
NPT_Result UpnpOnDemandPcm::OnEventNotify(PLT_Service* service,
                                          NPT_List<PLT_StateVariable*>* vars) {}
