/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <NptConfig.h>
#include <NptResults.h>
#include <NptStrings.h>
#include <PltFileMediaServer.h>
#include <PltService.h>
#include <PltStateVariable.h>
#include "fsmda/parent_class_handler.h"
#include "fsmda/upnp/upnp_ppm.h"
#include "fsmda/upnp/upnp_fsmda_utils.h"
#include "fsmda/upnp/upnp_passive_pcm.h"
#include "fsmda/upnp/upnp_active_pcm.h"
#include "fsmda/upnp/upnp_ondemand_pcm.h"
#include "fsmda/upnp/upnp_mediacapture_pcm.h"

using std::clog;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::stringstream;
using std::map;
using std::find;

/*----------------------------------------------------------------------
 |   UpnpPpm::UpnpPpm
 +---------------------------------------------------------------------*/
UpnpPpm::UpnpPpm()
    : PLT_DeviceHost("/", NULL, UpnpFsmdaUtils::kParentDeviceType,
                     UpnpFsmdaUtils::kParentDeviceFriendlyName, true, 0, true),
      device_host_(this),
      ctrl_point_(new PLT_CtrlPoint()),
      upnp_instance_(NULL),
      parent_class_handler_(NULL) {
  m_ModelDescription = UpnpFsmdaUtils::kParentDeviceModelDescription;
  m_ModelURL = UpnpFsmdaUtils::kParentDeviceModelUrl;
  m_ModelNumber = UpnpFsmdaUtils::kParentDeviceNumber;
  m_ModelName = UpnpFsmdaUtils::kParentDeviceModelName;
  m_Manufacturer = UpnpFsmdaUtils::kFsmdaManufacturer;
  m_ManufacturerURL = UpnpFsmdaUtils::kFsmdaManufacturerUrl;

  // create parent pairing service
  cpm_service_ = new PLT_Service(this, UpnpFsmdaUtils::kPpmServiceType,
                                 UpnpFsmdaUtils::kPpmServiceId,
                                 UpnpFsmdaUtils::kPpmServiceName);
  cpm_service_->SetSCPDXML((const char *)UpnpFsmdaUtils::kPpmServiceScpdXml);

  // create passive service
  passive_service_ =
      new PLT_Service(this, UpnpFsmdaUtils::kPassivePcmServiceType,
                      UpnpFsmdaUtils::kPassivePcmServiceId,
                      UpnpFsmdaUtils::kPassivePcmServiceName);
  passive_service_->SetSCPDXML(
      (const char *)UpnpFsmdaUtils::kPassivePcmServiceScpdXml);

  // create active service
  active_service_ = new PLT_Service(this, UpnpFsmdaUtils::kActivePcmServiceType,
                                    UpnpFsmdaUtils::kActivePcmServiceId,
                                    UpnpFsmdaUtils::kActivePcmServiceName);
  active_service_->SetSCPDXML(
      (const char *)UpnpFsmdaUtils::kActivePcmServiceScpdXml);

  // create ondemand service
  ondemand_service_ =
      new PLT_Service(this, UpnpFsmdaUtils::kOnDemandPcmServiceType,
                      UpnpFsmdaUtils::kOnDemandPcmServiceId,
                      UpnpFsmdaUtils::kOnDemandPcmServiceName);
  ondemand_service_->SetSCPDXML(
      (const char *)UpnpFsmdaUtils::kOnDemandPcmServiceScpdXml);

  // create media catpure service
  mediacapture_service_ =
      new PLT_Service(this, UpnpFsmdaUtils::kMediaCapturePcmServiceType,
                      UpnpFsmdaUtils::kMediaCapturePcmServiceId,
                      UpnpFsmdaUtils::kMediaCapturePcmServiceName);
  mediacapture_service_->SetSCPDXML(
      (const char *)UpnpFsmdaUtils::kMediaCapturePcmServiceScpdXml);
}

/*----------------------------------------------------------------------
 |   UpnpPpm::~UpnpPpm
 +---------------------------------------------------------------------*/
UpnpPpm::~UpnpPpm() {
  StopPairingService();
  delete cpm_service_;
  ctrl_point_.Detach();
  device_host_.Detach();
}

/*----------------------------------------------------------------------
 |   UpnpPpm::ClassAnnouncement
 +---------------------------------------------------------------------*/
void UpnpPpm::ClassAnnouncement(const string &application_id,
                                unsigned int class_index,
                                const string &class_desc,
                                const string &class_function) {}

/*----------------------------------------------------------------------
 |   UpnpCpm::AddDeviceClassForDiscover
 +---------------------------------------------------------------------*/
int UpnpPpm::AddDeviceClassForDiscover(
    DeviceClassDiscoverParams *discover_params) {
  discover_params_list_.push_back(discover_params);
}

/*----------------------------------------------------------------------
 |   UpnpCpm::RemoveDeviceClassForDiscover
 +---------------------------------------------------------------------*/
int UpnpPpm::RemoveDeviceClassForDiscover(
    DeviceClassDiscoverParams *discover_params) {
  // TODO(alan@telemidia.puc-rio.br): create tests to this
  discover_params_list_.erase(find(discover_params_list_.begin(),
                                   discover_params_list_.end(),
                                   discover_params));
}

/*----------------------------------------------------------------------
 |   UpnpPpm::SetupServices
 +---------------------------------------------------------------------*/
NPT_Result UpnpPpm::SetupServices() {
  clog << "UpnpPpm::SetupServices()" << endl;
  NPT_Result res;
  res = AddService(cpm_service_);
  if (res == NPT_FAILURE) return NPT_FAILURE;
  res = AddService(passive_service_);
  if (res == NPT_FAILURE) return NPT_FAILURE;
  res = AddService(active_service_);
  if (res == NPT_FAILURE) return NPT_FAILURE;
  res = AddService(ondemand_service_);
  if (res == NPT_FAILURE) return NPT_FAILURE;
  res = AddService(mediacapture_service_);
  if (res == NPT_FAILURE) return NPT_FAILURE;
  return res;
}

/*----------------------------------------------------------------------
 |   UpnpPpm::OnAction
 +---------------------------------------------------------------------*/
NPT_Result UpnpPpm::OnAction(PLT_ActionReference &action,
                             const PLT_HttpRequestContext &context) {
  clog << "UpnpPpm::OnAction()" << endl;
  NPT_String name = action->GetActionDesc().GetName();
  clog << "UpnpPpm::OnAction()::action name=" << name.GetChars() << endl;

  if (name.Compare("addDeviceToClass") == 0) {
    // handling addDeviceToClass call
    NPT_String application_id;
    action->GetArgumentValue("application_id", application_id);
    NPT_String deviceAddr;
    action->GetArgumentValue("deviceAddr", deviceAddr);
    NPT_Int32 class_index;
    action->GetArgumentValue("class_index", class_index);
    NPT_String deviceDesc;
    action->GetArgumentValue("deviceDesc", deviceDesc);
    clog << "UpnpPpm::OnAction::receive addDeviceToClass("
         << application_id.GetChars() << "," << deviceAddr.GetChars() << ","
         << class_index << ","
         << "deviceDesc.size()=" << deviceDesc.GetLength() << ")" << endl;

    // call parent_class_handler_->AddDeviceToClass
    if (parent_class_handler_ != NULL) {
      parent_class_handler_->ReportAddDeviceToClass(application_id.GetChars(),
                                                    class_index);
    }
    return NPT_SUCCESS;
  } else if (name.Compare("getChildIndex") == 0) {
    // handling getChildIndex call
    NPT_String application_id;
    action->GetArgumentValue("application_id", application_id);
    NPT_String device_addr;
    action->GetArgumentValue("deviceAddr", device_addr);
    NPT_Int32 class_index;
    action->GetArgumentValue("class_index", class_index);
    clog << "UpnpPpm::OnAction:: receive getChildIndex("
         << application_id.GetChars() << "," << device_addr.GetChars() << ","
         << class_index << ")" << endl;
    action->SetArgumentValue("ret", "100");
    if (parent_class_handler_ != NULL) {
      parent_class_handler_->GetAvaliableChildIndex(application_id.GetChars(),
                                                    class_index);
    }
    return NPT_SUCCESS;
  }
  action->SetError(501, "Action Failed");
  return NPT_FAILURE;
}

NPT_Result UpnpPpm::OnEventNotify(PLT_Service *service,
                                  NPT_List<PLT_StateVariable *> *vars) {}
NPT_Result UpnpPpm::OnActionResponse(NPT_Result res,
                                     PLT_ActionReference &action,
                                     void *userdata) {
  clog << "UpnpPpm::OnActionResponse()" << endl;
  NPT_String action_name = action->GetActionDesc().GetName();
  clog << "UpnpPpm::OnActionResponse()::action_name=" << action_name.GetChars()
       << endl;
}

NPT_Result UpnpPpm::OnDeviceRemoved(PLT_DeviceDataReference &device) {
  clog << "UpnpPpm::OnDeviceRemoved()::device->GetType="
       << device->GetType().GetChars() << endl;
  if (!device->GetType().Compare(UpnpFsmdaUtils::kChildDeviceType)) {
    string app_id = discover_params_list_.front()->application_id_;
    if (parent_class_handler_ != NULL)
      parent_class_handler_->GetClassHandlingHpe(app_id)
          ->setClassVariableValue(string("system(2).size"), string("0"));
  }
}

NPT_Result UpnpPpm::OnDeviceAdded(PLT_DeviceDataReference &device_data) {
  if (!device_data->GetUUID().Compare(m_UUID)) return NPT_FAILURE;
  if (device_data->GetType().Compare(UpnpFsmdaUtils::kChildDeviceType))
    return NPT_FAILURE;
  clog << "UpnpPpm::OnDeviceAdded() " << endl;
  clog << "UpnpPpm::OnDeviceAdded()::device->GetFriendlyName="
       << device_data->GetFriendlyName().GetChars() << endl;
  clog << "UpnpPpm::OnDeviceAdded()::device->GetType="
       << device_data->GetType().GetChars() << endl;
  clog << "UpnpPpm::OnDeviceAdded()::device->GetUUID="
       << device_data->GetUUID().GetChars() << endl;
  clog << "UpnpPpm::OnDeviceAdded()::device->GetURLBase()->"
       << device_data->GetURLBase().ToString().GetChars() << endl;

  PLT_Service *service;
  if (!device_data->GetType().Compare(UpnpFsmdaUtils::kChildDeviceType)) {
    device_data->FindServiceByType(UpnpFsmdaUtils::kCpmServiceType, service);
    vector<DeviceClassDiscoverParams *>::iterator iter;
    iter = discover_params_list_.begin();
    while (iter != discover_params_list_.end()) {
      PLT_ActionReference action;
      ctrl_point_->CreateAction(device_data, UpnpFsmdaUtils::kCpmServiceType,
                                "classAnnouncement", action);
      if (action.IsNull()) {
        iter++;
        continue;
      }
      DeviceClassDiscoverParams *discover_params = (*iter);
      action->SetArgumentValue("application_id",
                               discover_params->application_id_.c_str());
      stringstream aux_string;
      aux_string << discover_params->class_index_;
      action->SetArgumentValue("class_index", aux_string.str().c_str());
      action->SetArgumentValue(
          "class_desc",
          discover_params->device_class_description_->rdf_content().c_str());
      action->SetArgumentValue("class_function", "class_function");
      ctrl_point_->InvokeAction(action, 0);
      iter++;
    }
    clog << "UpnpPpm::OnDeviceAdded():: "
            "discoverd_cpm_.push_back(device)" << endl;
    discovered_children_.push_back(device_data);
    return NPT_SUCCESS;
  } else {
    return NPT_FAILURE;
  }
}

/*----------------------------------------------------------------------
 |   UpnpPpm::StartPairingService
 +---------------------------------------------------------------------*/
int UpnpPpm::StartPairingService() {
  clog << "UpnpPpm::StartPairingService" << endl;
  if (upnp_instance_ == NULL) {
    upnp_instance_ = UpnpFsmdaUtils::GetRunningInstance();
  }
  NPT_Result res = upnp_instance_->AddDevice(device_host_);
  res = upnp_instance_->AddCtrlPoint(ctrl_point_);
  ctrl_point_->AddListener(this);
  if (res != NPT_SUCCESS) {
    return -1;
  } else {
    return 0;
  }
}

/*----------------------------------------------------------------------
 |   UpnpPpm::StopPairingService
 +---------------------------------------------------------------------*/
int UpnpPpm::StopPairingService() {
  if (upnp_instance_ != NULL) {
    RemoveService(cpm_service_);
    upnp_instance_->RemoveDevice(device_host_);
    ctrl_point_->RemoveListener(this);
    upnp_instance_->RemoveCtrlPoint(ctrl_point_);
    UpnpFsmdaUtils::ReleaseInstance();
    upnp_instance_ = NULL;
  }
  return 0;
}

/*----------------------------------------------------------------------
 |   UpnpPpm::pairing_service_started
 +---------------------------------------------------------------------*/
bool UpnpPpm::IsPairingServiceStarted() { return m_Started; }

/*----------------------------------------------------------------------
 |   UpnpPpm::registred_children
 +---------------------------------------------------------------------*/
unsigned int UpnpPpm::registred_children() {
  return discovered_children_.size();
}

/*----------------------------------------------------------------------
 |   UpnpCpm::set_service_owner
 +---------------------------------------------------------------------*/
int UpnpPpm::set_service_owner(ParentClassHandler *service_owner) {
  parent_class_handler_ = service_owner;
}

/*----------------------------------------------------------------------
 |   UpnpPpm::CreatePassivePcm
 +---------------------------------------------------------------------*/
PassiveClassListenerInterface *UpnpPpm::CreatePassivePcm(
    const string &application_id, unsigned int class_index) {
  UpnpPassivePcm *communication = new UpnpPassivePcm();
  return communication;
}

/*----------------------------------------------------------------------
 |   UpnpPpm::CreateActivePcm
 +---------------------------------------------------------------------*/
ActiveClassInterface *UpnpPpm::CreateActivePcm(const string &application_id,
                                               unsigned int class_index) {
  UpnpActivePcm *communication = new UpnpActivePcm(
      PLT_DeviceHostReference(this), discovered_children_.back(), ctrl_point_,
      application_id, class_index);
  return communication;
}

/*----------------------------------------------------------------------
 |   UpnpPpm::CreateMediaCapturePcm
 +---------------------------------------------------------------------*/
MediaCaptureClassListenerInterface *UpnpPpm::CreateMediaCapturePcm(
    const string &application_id, unsigned int class_index) {
  UpnpMediaCapturePcm *communication = new UpnpMediaCapturePcm();
  return communication;
}

/*----------------------------------------------------------------------
 |   UpnpPpm::CreateOnDemandPcm
 +---------------------------------------------------------------------*/
OnDemandClassListenerInterface *UpnpPpm::CreateOnDemandPcm(
    const string &application_id, unsigned int class_index) {
  UpnpOnDemandPcm *communication = new UpnpOnDemandPcm();
  return communication;
}
