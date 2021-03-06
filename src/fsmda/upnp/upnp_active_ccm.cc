#include <iostream>
#include <sstream>
#include "fsmda/upnp/upnp_active_ccm.h"
#include "fsmda/upnp/upnp_fsmda_utils.h"

using std::cout;
using std::clog;
using std::stringstream;
using std::endl;

UpnpActiveCcm::UpnpActiveCcm(PLT_DeviceHostReference host_device,
                             PLT_DeviceDataReference& remote_device,
                             PLT_CtrlPointReference ctrl_point,
                             const string& application_id,
                             unsigned int class_index,
                             ActivePlayerInterface* player) {
  host_device_    = host_device;
  remote_device_  = remote_device;
  ctrl_point_     = ctrl_point;
  application_id_ = string(application_id);
  class_index_ = class_index;
  ctrl_point_->AddListener(this);
  player_ = player;
}

UpnpActiveCcm::~UpnpActiveCcm() {
  ctrl_point_->RemoveListener(this);
  ctrl_point_.Detach();
  host_device_.Detach();
  remote_device_.Detach();
}

void UpnpActiveCcm::report_property_value(const string& object_id,
                                          const string& name,
                                          const string& value) {
}

void UpnpActiveCcm::notify_event_transition(const string& object_id,
                                            const string& event_id,
                                            const string& transition) {
}

void UpnpActiveCcm::notify_error(const string& object_id,
                                 const string& message) {
}

NPT_Result UpnpActiveCcm::OnAction(PLT_ActionReference& action,
                                   const PLT_HttpRequestContext& context) {
  NPT_String name;
  name = action->GetActionDesc().GetName();
  clog << "UpnpActiveCcm::OnAction()::name=" << name.GetChars() << endl;

  if (name.Compare("RequestPropertyValue") == 0) {
    NPT_String property_name;

    // handling RequestPropertyValue call
    action->GetArgumentValue("property_name", property_name);
    clog << "UpnpActiveCcm::OnAction()::RequestPropertyValue("
         << property_name.GetChars() << ")" << endl;
    player_->request_roperty_value(property_name.GetChars());

  } else if (name.Compare("SetPropertyValue") == 0) {
    NPT_String object_id, property_name, property_value;
    NPT_UInt32 property_duration;

    // handling RequestPropertyValue call
    action->GetArgumentValue("object_id", object_id);
    action->GetArgumentValue("property_name", property_name);
    action->GetArgumentValue("property_value", property_value);
    action->GetArgumentValue("property_name", property_duration);
    clog << "UpnpActiveCcm::OnAction()::RequestPropertyValue("
         << property_name.GetChars() << ")" << endl;
    player_->set_property_value(property_name.GetChars(),
                                property_value.GetChars(), property_duration);
  }
  return NPT_SUCCESS;
}

NPT_Result UpnpActiveCcm::OnDeviceAdded(PLT_DeviceDataReference& device) {
}

NPT_Result UpnpActiveCcm::OnDeviceRemoved(PLT_DeviceDataReference& device) {
}

NPT_Result UpnpActiveCcm::OnActionResponse(NPT_Result res,
                                           PLT_ActionReference& action,
                                           void* userdata) {
}

NPT_Result UpnpActiveCcm::OnEventNotify(PLT_Service* service,
                                        NPT_List<PLT_StateVariable*>* vars) {
}
