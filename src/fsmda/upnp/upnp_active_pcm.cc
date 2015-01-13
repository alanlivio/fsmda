/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include <iostream>
#include <sstream>
#include "fsmda/upnp/upnp_active_pcm.h"
#include "fsmda/upnp/upnp_fsmda_utils.h"

using std::cout;
using std::clog;
using std::string;
using std::stringstream;
using std::endl;

/*----------------------------------------------------------------------
 |   UpnpActivePcm::UpnpActivePcm
 +---------------------------------------------------------------------*/
UpnpActivePcm::UpnpActivePcm(PLT_DeviceHostReference device_host,
                             PLT_DeviceDataReference &remote_device,
                             PLT_CtrlPointReference ctrl_point,
                             const string &application_id,
                             unsigned int class_index) {
  device_host_ = device_host;
  remote_device_ = remote_device;
  ctrl_point_ = ctrl_point;
  application_id_ = string(application_id);
  class_index_ = class_index;
  ctrl_point_->AddListener(this);
}

/*----------------------------------------------------------------------
 |   UpnpActivePcm::~UpnpActivePcm
 +---------------------------------------------------------------------*/
UpnpActivePcm::~UpnpActivePcm() {
  ctrl_point_->RemoveListener(this);
  ctrl_point_.Detach();
  device_host_.Detach();
}

/*----------------------------------------------------------------------
 |   UpnpActivePcm::Prepare
 +---------------------------------------------------------------------*/
void UpnpActivePcm::Prepare(const string &object_id, const string &object_src,
                            vector<Property> properties, vector<Event> evts) {}

/*----------------------------------------------------------------------
 |   UpnpActivePcm::AddEvent
 +---------------------------------------------------------------------*/
void UpnpActivePcm::AddEvent(const string &object_id, Event evt) {}

/*----------------------------------------------------------------------
 |   UpnpActivePcm::RemoveEvent
 +---------------------------------------------------------------------*/
void UpnpActivePcm::RemoveEvent(const string &object_id,
                                const string &event_id) {}

/*----------------------------------------------------------------------
 |   UpnpActivePcm::PostAction
 +---------------------------------------------------------------------*/
void UpnpActivePcm::PostAction(const string &object_id, const string &event_id,
                               const string &action) {
  clog << "UpnpActivePcm::PostAction():: " << endl;
  PLT_Service *service;
  PLT_ActionReference post_action;
  NPT_Result res = ctrl_point_->CreateAction(
      remote_device_, UpnpFsmdaUtils::kActiveCcmServiceType, "PostAction",
      post_action);
  if (post_action.IsNull()) {
    clog << "UpnpActivePcm::PostAction():: InvokeAction=" << NPT_ResultText(res)
         << endl;
    clog << "UpnpActivePcm::PostAction():: "
            "remote_device_->GetType().GetChars()="
         << remote_device_->GetType().GetChars() << endl;
    clog << "UpnpActivePcm::PostAction():: remote_device_->GetUUID().GetChars()"
         << remote_device_->GetUUID().GetChars() << endl;
    return;
  }
  post_action->SetArgumentValue("application_id", application_id_.c_str());
  stringstream aux_string;
  aux_string << class_index_;
  post_action->SetArgumentValue("class_index", aux_string.str().c_str());
  res = ctrl_point_->InvokeAction(post_action, 0);
  clog << "UpnpActivePcm::PostAction():: InvokeAction=" << NPT_ResultText(res)
       << endl;
  post_action_semaphore.WaitUntilEquals(1, NPT_TIMEOUT_INFINITE);
  request_var_action_semaphore.SetValue(0);
}

/*----------------------------------------------------------------------
 |   UpnpActivePcm::RequestPropertyValue
 +---------------------------------------------------------------------*/
void UpnpActivePcm::RequestPropertyValue(const string &object_id,
                                         const string &name) {
  clog << "UpnpActivePcm::PostAction():: " << endl;
  PLT_Service *service;
  PLT_ActionReference post_action;
  NPT_Result res = ctrl_point_->CreateAction(
      remote_device_, UpnpFsmdaUtils::kActiveCcmServiceType,
      "RequestPropertyValue", post_action);
  if (post_action.IsNull()) {
    clog << "UpnpActivePcm::PostAction():: InvokeAction=" << NPT_ResultText(res)
         << endl;
    clog << "UpnpActivePcm::PostAction():: "
            "remote_device_->GetType().GetChars()="
         << remote_device_->GetType().GetChars() << endl;
    clog << "UpnpActivePcm::PostAction():: remote_device_->GetUUID().GetChars()"
         << remote_device_->GetUUID().GetChars() << endl;
    return;
  }
  post_action->SetArgumentValue("application_id", application_id_.c_str());
  stringstream aux_string;
  aux_string << class_index_;
  post_action->SetArgumentValue("class_index", aux_string.str().c_str());
  post_action->SetArgumentValue("object_id", application_id_.c_str());
  post_action->SetArgumentValue("property_name", name.c_str());

  res = ctrl_point_->InvokeAction(post_action, 0);
  clog << "UpnpActivePcm::PostAction():: InvokeAction=" << NPT_ResultText(res)
       << endl;
  request_var_action_semaphore.WaitUntilEquals(1, NPT_TIMEOUT_INFINITE);
  request_var_action_semaphore.SetValue(0);
}
/*----------------------------------------------------------------------
 |   UpnpActivePcm::SetPropertyValue
 +---------------------------------------------------------------------*/
void UpnpActivePcm::SetPropertyValue(const string &object_id,
                                     const string &name, const string &value,
                                     unsigned int duration) {}
/*----------------------------------------------------------------------
 |   UpnpActivePcm::OnAction
 +---------------------------------------------------------------------*/
NPT_Result UpnpActivePcm::OnAction(PLT_ActionReference &action,
                                   const PLT_HttpRequestContext &context) {}

/*----------------------------------------------------------------------
 |   UpnpActivePcm::RegistryActiveClassListener
 +---------------------------------------------------------------------*/
void UpnpActivePcm::RegistryActiveClassListener(
    ActiveClassListenerInterface *hpe) {
  hpe_ = hpe;
}

/*----------------------------------------------------------------------
 |   UpnpActivePcm::OnDeviceAdded
 +---------------------------------------------------------------------*/
NPT_Result UpnpActivePcm::OnDeviceAdded(PLT_DeviceDataReference &device) {}

/*---------------------------------------------------------------------
 |   UpnpActivePcm::OnDeviceRemoved
 +---------------------------------------------------------------------*/
NPT_Result UpnpActivePcm::OnDeviceRemoved(PLT_DeviceDataReference &device) {}

/*----------------------------------------------------------------------
 |   UpnpActivePcm::OnActionResponse
 +---------------------------------------------------------------------*/
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
  if (!action_name.Compare("PostAction")) post_action_semaphore.SetValue(1);
  if (!action_name.Compare("RequestPropertyValue"))
    request_var_action_semaphore.SetValue(1);
}

/*----------------------------------------------------------------------
 |   UpnpActivePcm::OnEventNotify
 +---------------------------------------------------------------------*/
NPT_Result UpnpActivePcm::OnEventNotify(PLT_Service *service,
                                        NPT_List<PLT_StateVariable *> *vars) {}
