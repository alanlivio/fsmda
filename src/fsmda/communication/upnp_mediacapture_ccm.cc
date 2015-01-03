/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include "fsmda/communication/upnp_mediacapture_ccm.h"
#include <string>

/*----------------------------------------------------------------------
 |   UpnpMediaCaptureCcm::~UpnpMediaCaptureCcm
 +---------------------------------------------------------------------*/
UpnpMediaCaptureCcm::UpnpMediaCaptureCcm() {}

/*----------------------------------------------------------------------
 |   UpnpMediaCaptureCcm::~UpnpMediaCaptureCcm
 +---------------------------------------------------------------------*/
UpnpMediaCaptureCcm::~UpnpMediaCaptureCcm() {}

/*----------------------------------------------------------------------
 |   UpnpMediaCaptureCcm::StartCommunicationService
 +---------------------------------------------------------------------*/
int UpnpMediaCaptureCcm::StartCommunicationService() {}

/*----------------------------------------------------------------------
 |   UpnpMediaCaptureCcm::StopCommunicationService
 +---------------------------------------------------------------------*/
int UpnpMediaCaptureCcm::StopCommunicationService() {}

/*----------------------------------------------------------------------
 |   UpnpMediaCaptureCcm::IsCommunicationServiceStarted
 +---------------------------------------------------------------------*/
bool UpnpMediaCaptureCcm::IsCommunicationServiceStarted() {}

/*----------------------------------------------------------------------
 |   UpnpMediaCaptureCcm::~RequestContent
 +---------------------------------------------------------------------*/
void UpnpMediaCaptureCcm::RequestContent(const string& resource_id,
                                         unsigned int device_index) {}

/*----------------------------------------------------------------------
 |   UpnpMediaCaptureCcm::SetupServices
 +---------------------------------------------------------------------*/
NPT_Result UpnpMediaCaptureCcm::SetupServices() {}

/*----------------------------------------------------------------------
 |   UpnpMediaCaptureCcm::OnAction
 +---------------------------------------------------------------------*/
NPT_Result UpnpMediaCaptureCcm::OnAction(PLT_ActionReference& action,
                                   const PLT_HttpRequestContext& context) {}
/*----------------------------------------------------------------------
 |   UpnpMediaCaptureCcm::OnDeviceAdded
 +---------------------------------------------------------------------*/
NPT_Result UpnpMediaCaptureCcm::OnDeviceAdded(PLT_DeviceDataReference& device) {}

/*----------------------------------------------------------------------
 |   UpnpMediaCaptureCcm::OnDeviceRemoved
 +---------------------------------------------------------------------*/
NPT_Result UpnpMediaCaptureCcm::OnDeviceRemoved(PLT_DeviceDataReference& device) {}

/*----------------------------------------------------------------------
 |   UpnpMediaCaptureCcm::OnActionResponse
 +---------------------------------------------------------------------*/
NPT_Result UpnpMediaCaptureCcm::OnActionResponse(NPT_Result res,
                                           PLT_ActionReference& action,
                                           void* userdata) {}

/*----------------------------------------------------------------------
 |   UpnpMediaCaptureCcm::OnEventNotify
 +---------------------------------------------------------------------*/
NPT_Result UpnpMediaCaptureCcm::OnEventNotify(PLT_Service* service,
                                        NPT_List<PLT_StateVariable*>* vars) {}
