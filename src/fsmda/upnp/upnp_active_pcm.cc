#include <iostream>
#include <sstream>
#include "fsmda/upnp/upnp_active_pcm.h"
#include "fsmda/upnp/upnp_fsmda_utils.h"
#include "fsmda/utils/base64zip_coding.h"

using std::cout;
using std::clog;
using std::string;
using std::stringstream;
using std::endl;

UpnpActivePcm::UpnpActivePcm(PLT_DeviceHostReference device_host,
                             PLT_DeviceDataReference &remote_device,
                             PLT_CtrlPointReference ctrl_point,
                             const string &application_id,
                             unsigned int class_index) {
  device_host_    = device_host;
  remote_device_  = remote_device;
  ctrl_point_     = ctrl_point;
  application_id_ = string(application_id);
  class_index_ = class_index;
  ctrl_point_->AddListener(this);
}

UpnpActivePcm::~UpnpActivePcm() {
  ctrl_point_->RemoveListener(this);
  ctrl_point_.Detach();
  device_host_.Detach();
}

void UpnpActivePcm::prepare(const string &object_id, const string &object_src,
                            vector<Property> properties, vector<Event> evts) {
  clog << "UpnpActivePcm::Prepare():: " << endl;
  PLT_Service *service;
  PLT_ActionReference invoke_action;
  NPT_Result res = ctrl_point_->CreateAction(
      remote_device_, UpnpFsmdaUtils::kActiveCcmServiceType, "Prepare",
      invoke_action);
  if (invoke_action.IsNull()) {
    clog << "UpnpActivePcm::Prepare():: InvokeAction=" << NPT_ResultText(res)
         << endl;
    clog << "UpnpActivePcm::Prepare():: "
            "remote_device_->GetType().GetChars()="
         << remote_device_->GetType().GetChars() << endl;
    clog << "UpnpActivePcm::Prepare():: remote_device_->GetUUID().GetChars()"
         << remote_device_->GetUUID().GetChars() << endl;
    return;
  }
  invoke_action->SetArgumentValue("application_id", application_id_.c_str());
  stringstream aux_string;
  aux_string << class_index_;
  invoke_action->SetArgumentValue("class_index", aux_string.str().c_str());
  invoke_action->SetArgumentValue("object_id", object_id.c_str());
  invoke_action->SetArgumentValue("properties",
                                  Property::to_string(properties).c_str());
  invoke_action->SetArgumentValue("events", Event::to_string(evts).c_str());

  clog << "UpnpActivePcm::Prepare():: zip_directory=" << object_src << endl;
  zip_directory("/tmp/appdir.zip", object_src.c_str(), "/");
  string zip_base64 = getBase64FromFile("/tmp/appdir.zip");
  res = invoke_action->SetArgumentValue("object_src", zip_base64.c_str());
  clog << "UpnpActivePcm::Prepare():: SetArgumentValues=" << NPT_ResultText(res)
       << endl;

  res = ctrl_point_->InvokeAction(invoke_action, 0);
  prepare_action_semaphore.WaitUntilEquals(1, NPT_TIMEOUT_INFINITE);
  clog << "UpnpActivePcm::Prepare():: InvokeAction=" << NPT_ResultText(res)
       << endl;
  prepare_action_semaphore.WaitUntilEquals(1, NPT_TIMEOUT_INFINITE);
  prepare_action_semaphore.SetValue(0);
  invoked_actions_.push_back(invoke_action);
}

void UpnpActivePcm::add_event(const string &object_id, Event evt) {}

void UpnpActivePcm::remove_event(const string &object_id,
                                 const string &event_id) {}

void UpnpActivePcm::post_action(const string &object_id, const string &event_id,
                                const string &action) {
  clog << "UpnpActivePcm::PostAction():: " << endl;
  PLT_Service *service;
  PLT_ActionReference invoke_action;
  NPT_Result res = ctrl_point_->CreateAction(
      remote_device_, UpnpFsmdaUtils::kActiveCcmServiceType, "PostAction",
      invoke_action);
  if (invoke_action.IsNull()) {
    clog << "UpnpActivePcm::PostAction():: InvokeAction=" << NPT_ResultText(res)
         << endl;
    clog << "UpnpActivePcm::PostAction():: "
            "remote_device_->GetType().GetChars()="
         << remote_device_->GetType().GetChars() << endl;
    clog << "UpnpActivePcm::PostAction():: remote_device_->GetUUID().GetChars()"
         << remote_device_->GetUUID().GetChars() << endl;
    return;
  }
  invoke_action->SetArgumentValue("application_id", application_id_.c_str());
  stringstream aux_string;
  aux_string << class_index_;
  invoke_action->SetArgumentValue("class_index", aux_string.str().c_str());
  res = ctrl_point_->InvokeAction(invoke_action, 0);
  clog << "UpnpActivePcm::PostAction():: InvokeAction=" << NPT_ResultText(res)
       << endl;
  post_action_semaphore.WaitUntilEquals(1, NPT_TIMEOUT_INFINITE);
  post_action_semaphore.SetValue(0);
  invoked_actions_.push_back(invoke_action);
}

void UpnpActivePcm::request_property_value(const string &object_id,
                                           const string &property_name) {
  clog << "UpnpActivePcm::PostAction():: " << endl;
  PLT_Service *service;
  PLT_ActionReference invoke_action;
  NPT_Result res = ctrl_point_->CreateAction(
      remote_device_, UpnpFsmdaUtils::kActiveCcmServiceType,
      "RequestPropertyValue", invoke_action);
  if (invoke_action.IsNull()) {
    clog << "UpnpActivePcm::PostAction():: InvokeAction=" << NPT_ResultText(res)
         << endl;
    clog << "UpnpActivePcm::PostAction():: "
            "remote_device_->GetType().GetChars()="
         << remote_device_->GetType().GetChars() << endl;
    clog << "UpnpActivePcm::PostAction():: remote_device_->GetUUID().GetChars()"
         << remote_device_->GetUUID().GetChars() << endl;
    return;
  }
  invoke_action->SetArgumentValue("application_id", application_id_.c_str());
  stringstream aux_string;
  aux_string << class_index_;
  invoke_action->SetArgumentValue("class_index", aux_string.str().c_str());
  invoke_action->SetArgumentValue("object_id", application_id_.c_str());
  invoke_action->SetArgumentValue("property_name", property_name.c_str());

  res = ctrl_point_->InvokeAction(invoke_action, 0);
  clog << "UpnpActivePcm::PostAction():: InvokeAction=" << NPT_ResultText(res)
       << endl;
  request_var_action_semaphore.WaitUntilEquals(1, NPT_TIMEOUT_INFINITE);
  request_var_action_semaphore.SetValue(0);
  invoked_actions_.push_back(invoke_action);
}

void UpnpActivePcm::set_property_value(const string &object_id,
                                       const string &property_name,
                                       const string &property_value,
                                       unsigned int property_duration) {
  clog << "UpnpActivePcm::SetPropertyValue():: " << endl;
  PLT_Service *service;
  PLT_ActionReference invoke_action;
  NPT_Result res = ctrl_point_->CreateAction(
      remote_device_, UpnpFsmdaUtils::kActiveCcmServiceType, "SetPropertyValue",
      invoke_action);
  if (invoke_action.IsNull()) {
    clog << "UpnpActivePcm::SetPropertyValue():: InvokeAction="
         << NPT_ResultText(res) << endl;
    clog << "UpnpActivePcm::SetPropertyValue():: "
            "remote_device_->GetType().GetChars()="
         << remote_device_->GetType().GetChars() << endl;
    clog << "UpnpActivePcm::SetPropertyValue():: "
            "remote_device_->GetUUID().GetChars()"
         << remote_device_->GetUUID().GetChars() << endl;
    return;
  }
  invoke_action->SetArgumentValue("application_id", application_id_.c_str());
  stringstream aux_string;
  aux_string << class_index_;
  invoke_action->SetArgumentValue("class_index", aux_string.str().c_str());
  invoke_action->SetArgumentValue("object_id", object_id.c_str());
  invoke_action->SetArgumentValue("property_name", property_name.c_str());
  invoke_action->SetArgumentValue("property_value", property_value.c_str());
  stringstream aux_string2;
  aux_string2 << property_duration;
  invoke_action->SetArgumentValue("property_duration",
                                  aux_string2.str().c_str());

  res = ctrl_point_->InvokeAction(invoke_action, 0);
  clog << "UpnpActivePcm::SetPropertyValue():: InvokeAction="
       << NPT_ResultText(res) << endl;
  set_var_action_semaphore.WaitUntilEquals(1, NPT_TIMEOUT_INFINITE);
  set_var_action_semaphore.SetValue(0);
  invoked_actions_.push_back(invoke_action);
}

NPT_Result UpnpActivePcm::OnAction(PLT_ActionReference &action,
                                   const PLT_HttpRequestContext &context) {}

void UpnpActivePcm::UpdateRemoteHostAndExecuteStoredActions(
    PLT_DeviceDataReference &remote_device) {
  remote_device_ = remote_device;
  for (int i = 0; i < invoked_actions_.size(); i++) {
    NPT_Result res = ctrl_point_->InvokeAction(invoked_actions_[0]);
  }
}

void UpnpActivePcm::registry_active_class_listener(
    ActiveClassListenerInterface *hpe) {
  hpe_ = hpe;
}

NPT_Result UpnpActivePcm::OnDeviceAdded(PLT_DeviceDataReference &device) {}

NPT_Result UpnpActivePcm::OnDeviceRemoved(PLT_DeviceDataReference &device) {}

NPT_Result UpnpActivePcm::OnActionResponse(NPT_Result res,
                                           PLT_ActionReference &action,
                                           void *userdata) {
  clog << "UpnpActivePcm::OnActionResponse()::" << endl;
  NPT_String action_name = action->GetActionDesc().GetName();
  NPT_String service_name =
      action->GetActionDesc().GetService()->GetServiceType();
  NPT_String application_id;
  action->GetArgumentValue("application_id", application_id);
  NPT_Int32 class_index;
  action->GetArgumentValue("class_index", class_index);
  clog << "UpnpActivePcm::OnActionResponse()::action_name="
       << action_name.GetChars() << ",service_name=" << service_name.GetChars()
       << ", application_id=" << application_id.GetChars()
       << ",class_index=" << class_index << endl;
  if (!action_name.Compare("PostAction"))
    post_action_semaphore.SetValue(1);
  if (!action_name.Compare("RequestPropertyValue"))
    request_var_action_semaphore.SetValue(1);
  if (!action_name.Compare("Prepare"))
    prepare_action_semaphore.SetValue(1);
  if (!action_name.Compare("SetPropertyValue"))
    set_var_action_semaphore.SetValue(1);
}

NPT_Result UpnpActivePcm::OnEventNotify(PLT_Service *service,
                                        NPT_List<PLT_StateVariable *> *vars) {}
