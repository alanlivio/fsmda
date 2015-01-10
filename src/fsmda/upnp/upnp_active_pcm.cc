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
  //  ctrl_point_->AddListener(this);
}

/*----------------------------------------------------------------------
 |   UpnpActivePcm::~UpnpActivePcm
 +---------------------------------------------------------------------*/
UpnpActivePcm::~UpnpActivePcm() {
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
}

/*----------------------------------------------------------------------
 |   UpnpActivePcm::RequestPropertyValue
 +---------------------------------------------------------------------*/
void UpnpActivePcm::RequestPropertyValue(const string &object_id,
                                         const string &name) {}
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
                                           void *userdata) {}

/*----------------------------------------------------------------------
 |   UpnpActivePcm::OnEventNotify
 +---------------------------------------------------------------------*/
NPT_Result UpnpActivePcm::OnEventNotify(PLT_Service *service,
                                        NPT_List<PLT_StateVariable *> *vars) {}
