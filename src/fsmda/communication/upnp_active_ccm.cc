/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include <iostream>
#include <sstream>
#include "fsmda/communication/upnp_active_ccm.h"
#include "fsmda/utils/upnp_fsmda_utils.h"

using std::cout;
using std::clog;
using std::stringstream;
using std::endl;

/*----------------------------------------------------------------------
 |   UpnpActiveCcm::UpnpActiveCcm
 +---------------------------------------------------------------------*/
UpnpActiveCcm::UpnpActiveCcm(PLT_DeviceHostReference device_host,
                             PLT_CtrlPointReference ctrl_point) {
  device_host_ = device_host;
  ctrl_point_ = ctrl_point;
  //  ctrl_point_->AddListener(this);
}

/*----------------------------------------------------------------------
 |   UpnpActiveCcm::~UpnpActiveCcm
 +---------------------------------------------------------------------*/
UpnpActiveCcm::~UpnpActiveCcm() {
  ctrl_point_.Detach();
  device_host_.Detach();
}

/*----------------------------------------------------------------------
 |   UpnpActiveCcm::RequestPropertyValue
 +---------------------------------------------------------------------*/
void UpnpActiveCcm::RequestPropertyValue(const string& object_id,
                                         const string& name) {}

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
 |   UpnpActiveCcm::SetPlayer
 +---------------------------------------------------------------------*/
void UpnpActiveCcm::SetPlayer(ActiveClassInterface* player) {
  player_ = player;
}
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
