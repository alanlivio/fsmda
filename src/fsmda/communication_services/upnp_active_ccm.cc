/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include "fsmda/communication_services/upnp_active_ccm.h"
#include "fsmda/model/active_object_interfaces.h"

/*----------------------------------------------------------------------
 |   UpnpActiveCcm::UpnpActiveCcm
 +---------------------------------------------------------------------*/
UpnpActiveCcm::UpnpActiveCcm() {}

/*----------------------------------------------------------------------
 |   UpnpActiveCcm::~UpnpActiveCcm
 +---------------------------------------------------------------------*/
UpnpActiveCcm::~UpnpActiveCcm() {}

/*----------------------------------------------------------------------
 |   UpnpActiveCcm::StartCommunicationService
 +---------------------------------------------------------------------*/
int UpnpActiveCcm::StartCommunicationService() {}

/*----------------------------------------------------------------------
 |   UpnpActiveCcm::StopCommunicationService
 +---------------------------------------------------------------------*/
int UpnpActiveCcm::StopCommunicationService() {}

/*----------------------------------------------------------------------
 |   UpnpActiveCcm::IsCommunicationServiceStarted
 +---------------------------------------------------------------------*/
bool UpnpActiveCcm::IsCommunicationServiceStarted() {}

/*----------------------------------------------------------------------
 |   UpnpActiveCcm::Prepare
 +---------------------------------------------------------------------*/
void UpnpActiveCcm::Prepare(const string& object_id, const string& object_src,
                            vector<Property> properties, vector<Event> evts) {}

/*----------------------------------------------------------------------
 |   UpnpActiveCcm::AddEvent
 +---------------------------------------------------------------------*/
void UpnpActiveCcm::AddEvent(const string& object_id, Event evt) {}

/*----------------------------------------------------------------------
 |   UpnpActiveCcm::RemoveEvent
 +---------------------------------------------------------------------*/
void UpnpActiveCcm::RemoveEvent(const string& object_id,
                                const string& event_id) {}

/*----------------------------------------------------------------------
 |   UpnpActiveCcm::PostAction
 +---------------------------------------------------------------------*/
void UpnpActiveCcm::PostAction(const string& object_id, const string& event_id,
                               const string& action) {}

/*----------------------------------------------------------------------
 |   UpnpActiveCcm::ReportPropertyValue
 +---------------------------------------------------------------------*/
void UpnpActiveCcm::ReportPropertyValue(const string& object_id,
                                        const string& name,
                                        const string& value) {}

/*----------------------------------------------------------------------
 |   UpnpActiveCcm::SetPropertyValue
 +---------------------------------------------------------------------*/
void UpnpActiveCcm::SetPropertyValue(const string& object_id,
                                     const string& name, const string& value,
                                     unsigned int duration) {}

/*----------------------------------------------------------------------
 |   UpnpActiveCcm::SetupServices
 +---------------------------------------------------------------------*/
NPT_Result UpnpActiveCcm::SetupServices() {}

/*----------------------------------------------------------------------
 |   UpnpActiveCcm::OnAction
 +---------------------------------------------------------------------*/
NPT_Result UpnpActiveCcm::OnAction(PLT_ActionReference& action,
                                   const PLT_HttpRequestContext& context) {}
/*----------------------------------------------------------------------
 |   UpnpActiveCcm::OnDeviceAdded
 +---------------------------------------------------------------------*/
NPT_Result UpnpActiveCcm::OnDeviceAdded(PLT_DeviceDataReference& device) {}

/*----------------------------------------------------------------------
 |   UpnpActiveCcm::OnDeviceRemoved
 +---------------------------------------------------------------------*/
NPT_Result UpnpActiveCcm::OnDeviceRemoved(PLT_DeviceDataReference& device) {}

/*----------------------------------------------------------------------
 |   UpnpActiveCcm::OnActionResponse
 +---------------------------------------------------------------------*/
NPT_Result UpnpActiveCcm::OnActionResponse(NPT_Result res,
                                           PLT_ActionReference& action,
                                           void* userdata) {}

/*----------------------------------------------------------------------
 |   UpnpActiveCcm::OnEventNotify
 +---------------------------------------------------------------------*/
NPT_Result UpnpActiveCcm::OnEventNotify(PLT_Service* service,
                                        NPT_List<PLT_StateVariable*>* vars) {}
