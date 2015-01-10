/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include <iostream>
#include <sstream>
#include "fsmda/upnp/upnp_active_ccm.h"
#include "fsmda/upnp/upnp_fsmda_utils.h"

using std::cout;
using std::clog;
using std::stringstream;
using std::endl;

/*----------------------------------------------------------------------
 |   UpnpActiveCcm::UpnpActiveCcm
 +---------------------------------------------------------------------*/
UpnpActiveCcm::UpnpActiveCcm(PLT_DeviceHostReference host_device,
                             PLT_DeviceDataReference& remote_device,
                             PLT_CtrlPointReference ctrl_point,
                             const string& application_id,
                             unsigned int class_index) {
  host_device_ = host_device;
  remote_device_ = remote_device;
  ctrl_point_ = ctrl_point;
  application_id_ = string(application_id);
  class_index_ = class_index;
  //  ctrl_point_->AddListener(this);
}

/*----------------------------------------------------------------------
 |   UpnpActiveCcm::~UpnpActiveCcm
 +---------------------------------------------------------------------*/
UpnpActiveCcm::~UpnpActiveCcm() {
  ctrl_point_.Detach();
  host_device_.Detach();
  remote_device_.Detach();
}

/*----------------------------------------------------------------------
 |   UpnpActiveCcm::ReportPropertyValue
 +---------------------------------------------------------------------*/
void UpnpActiveCcm::ReportPropertyValue(const string& object_id,
                                        const string& name,
                                        const string& value) {}
/*----------------------------------------------------------------------
 |   UpnpActiveCcm::NotifyEventTransition
 +---------------------------------------------------------------------*/
void UpnpActiveCcm::NotifyEventTransition(const string& object_id,
                                          const string& event_id,
                                          const string& transition) {}

/*----------------------------------------------------------------------
 |   UpnpActiveCcm::NotifyError
 +---------------------------------------------------------------------*/
void UpnpActiveCcm::NotifyError(const string& object_id,
                                const string& message) {}

/*----------------------------------------------------------------------
 |   UpnpActiveCcm::OnAction
 +---------------------------------------------------------------------*/
NPT_Result UpnpActiveCcm::OnAction(PLT_ActionReference& action,
                                   const PLT_HttpRequestContext& context) {}

/*----------------------------------------------------------------------
 |   UpnpActiveCcm::OnDeviceAdded
 +---------------------------------------------------------------------*/
NPT_Result UpnpActiveCcm::OnDeviceAdded(PLT_DeviceDataReference& device) {}

/*---------------------------------------------------------------------
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
