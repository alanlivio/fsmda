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
#include "fsmda/parent_pairing_manager.h"
#include "fsmda/upnp/upnp_parent_pairing.h"
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
 |   UpnpParentPairing::UpnpParentPairing
 +---------------------------------------------------------------------*/
UpnpParentPairing::UpnpParentPairing()
    : PLT_DeviceHost("/", NULL, UpnpFsmdaUtils::kPpmDeviceType,
                     UpnpFsmdaUtils::kPpmDeviceFriendlyName, true, 0, true),
      device_host_(this),
      ctrl_point_(new PLT_CtrlPoint()),
      upnp_instance_(NULL),
      parent_pairing_manager_(NULL) {
  m_ModelDescription = UpnpFsmdaUtils::kPpmDeviceModelDescription;
  m_ModelURL = UpnpFsmdaUtils::kPpmDeviceModelUrl;
  m_ModelNumber = UpnpFsmdaUtils::kPpmDeviceNumber;
  m_ModelName = UpnpFsmdaUtils::kPpmDeviceModelName;
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
 |   UpnpParentPairing::~UpnpParentPairing
 +---------------------------------------------------------------------*/
UpnpParentPairing::~UpnpParentPairing() {
  StopPairingService();
  delete cpm_service_;
  ctrl_point_.Detach();
  device_host_.Detach();
}

/*----------------------------------------------------------------------
 |   UpnpParentPairing::ClassAnnouncement
 +---------------------------------------------------------------------*/
void UpnpParentPairing::ClassAnnouncement(const std::string &application_id,
                                          unsigned int class_index,
                                          const std::string &class_desc,
                                          const std::string &class_function) {}

/*----------------------------------------------------------------------
 |   UpnpChildPairing::AddDeviceClassForDiscover
 +---------------------------------------------------------------------*/
int UpnpParentPairing::AddDeviceClassForDiscover(
    DeviceClassDiscoverParams *discover_params) {
  discover_params_list_.push_back(discover_params);
}

/*----------------------------------------------------------------------
 |   UpnpChildPairing::RemoveDeviceClassForDiscover
 +---------------------------------------------------------------------*/
int UpnpParentPairing::RemoveDeviceClassForDiscover(
    DeviceClassDiscoverParams *discover_params) {
  // TODO(alan@telemidia.puc-rio.br): create tests to this
  discover_params_list_.erase(find(discover_params_list_.begin(),
                                   discover_params_list_.end(),
                                   discover_params));
}

/*----------------------------------------------------------------------
 |   UpnpParentPairing::SetupServices
 +---------------------------------------------------------------------*/
NPT_Result UpnpParentPairing::SetupServices() {
  clog << "UpnpParentPairing::SetupServices()" << endl;
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
 |   UpnpParentPairing::OnAction
 +---------------------------------------------------------------------*/
NPT_Result UpnpParentPairing::OnAction(PLT_ActionReference &action,
                                       const PLT_HttpRequestContext &context) {
  NPT_String name = action->GetActionDesc().GetName();
  clog << "UpnpParentPairing::OnAction()::action.name=" << name.GetChars()
       << endl;

  if (name.Compare("addDeviceToClass") == 0) {
    // handling addDeviceToClass call
    NPT_String applicationId;
    action->GetArgumentValue("applicationId", applicationId);
    NPT_String deviceAddr;
    action->GetArgumentValue("deviceAddr", deviceAddr);
    NPT_Int32 classIndex;
    action->GetArgumentValue("classIndex", classIndex);
    NPT_String deviceDesc;
    action->GetArgumentValue("deviceDesc", deviceDesc);
    clog << "UpnpParentPairing::OnAction::receive addDeviceToClass("
         << applicationId.GetChars() << "," << deviceAddr.GetChars() << ","
         << classIndex << ","
         << "deviceDesc.size()=" << deviceDesc.GetLength() << ")" << endl;

    // call parent_pairing_manager_->AddDeviceToClass
    if (parent_pairing_manager_ != NULL) {
      parent_pairing_manager_->AddDeviceToClass(
          applicationId.GetChars(), deviceAddr.GetChars(), classIndex,
          deviceDesc.GetChars());
    }

    return NPT_SUCCESS;
  } else if (name.Compare("getChildIndex") == 0) {
    // handling getChildIndex call
    NPT_String application_id;
    action->GetArgumentValue("applicationId", application_id);
    NPT_String device_addr;
    action->GetArgumentValue("deviceAddr", device_addr);
    NPT_Int32 class_index;
    action->GetArgumentValue("classIndex", class_index);
    clog << "UpnpParentPairing::OnAction:: receive getChildIndex("
         << application_id.GetChars() << "," << device_addr.GetChars() << ","
         << class_index << ")" << endl;
    action->SetArgumentValue("ret", "100");
    if (parent_pairing_manager_ != NULL) {
      parent_pairing_manager_->GetChildIndex(
          application_id.GetChars(), device_addr.GetChars(), class_index);
    }
    return NPT_SUCCESS;
  }
  action->SetError(501, "Action Failed");
  return NPT_FAILURE;
}

NPT_Result UpnpParentPairing::OnEventNotify(
    PLT_Service *service, NPT_List<PLT_StateVariable *> *vars) {}
NPT_Result UpnpParentPairing::OnActionResponse(NPT_Result res,
                                               PLT_ActionReference &action,
                                               void *userdata) {
  NPT_String name = action->GetActionDesc().GetName();
  clog << "UpnpParentPairing::OnActionResponse()::action.name="
       << name.GetChars() << endl;
}
NPT_Result UpnpParentPairing::OnDeviceRemoved(PLT_DeviceDataReference &device) {
  clog << "UpnpParentPairing::OnDeviceRemoved()::device->GetType="
       << device->GetType().GetChars() << endl;
  if (!device->GetType().Compare(UpnpFsmdaUtils::kCpmDeviceType)) {
    string app_id = discover_params_list_.front()->application_id_;
    if (parent_pairing_manager_ != NULL)
      parent_pairing_manager_->hpes_map_[app_id]->setClassVariableValue(
          string("system(2).size"), string("0"));
  }
}

NPT_Result UpnpParentPairing::OnDeviceAdded(
    PLT_DeviceDataReference &device_data) {
  if (!device_data->GetUUID().Compare(m_UUID)) return NPT_SUCCESS;
  if (!device_data->GetType().StartsWith("urn:schemas-upnp-org:device:fsmda-",
                                         true))
    return NPT_FAILURE;
  clog << "UpnpParentPairing::OnDeviceAdded() " << endl;
  clog << "UpnpParentPairing::OnDeviceAdded()::device->GetFriendlyName="
       << device_data->GetFriendlyName().GetChars() << endl;
  clog << "UpnpParentPairing::OnDeviceAdded()::device->GetType="
       << device_data->GetType().GetChars() << endl;
  clog << "UpnpParentPairing::OnDeviceAdded()::device->GetUUID="
       << device_data->GetUUID().GetChars() << endl;
  clog << "UpnpParentPairing::OnDeviceAdded()::device->GetURLBase()->"
       << device_data->GetURLBase().ToString().GetChars() << endl;

  PLT_Service *parent_pairing;
  if (!device_data->GetType().Compare(UpnpFsmdaUtils::kCpmDeviceType)) {
    device_data->FindServiceByType(UpnpFsmdaUtils::kCpmServiceType,
                                   parent_pairing);
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
      action->SetArgumentValue("applicationId",
                               discover_params->application_id_.c_str());
      stringstream aux_string;
      aux_string << discover_params->class_index_;
      action->SetArgumentValue("classIndex", aux_string.str().c_str());
      action->SetArgumentValue(
          "classDesc",
          discover_params->device_class_description_->rdf_content().c_str());
      action->SetArgumentValue("classFunction", "classFunction");
      ctrl_point_->InvokeAction(action, 0);
      iter++;
    }
    clog << "UpnpParentPairing::OnDeviceAdded():: "
            "discoverd_cpm_.push_back(device)" << endl;
    discovered_children_.push_back(device_data);
    return NPT_SUCCESS;
  } else {
    return NPT_FAILURE;
  }
}

/*----------------------------------------------------------------------
 |   UpnpParentPairing::StartPairingService
 +---------------------------------------------------------------------*/
int UpnpParentPairing::StartPairingService() {
  clog << "UpnpParentPairing::StartPairingService" << endl;
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
 |   UpnpParentPairing::StopPairingService
 +---------------------------------------------------------------------*/
int UpnpParentPairing::StopPairingService() {
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
 |   UpnpParentPairing::pairing_service_started
 +---------------------------------------------------------------------*/
bool UpnpParentPairing::IsPairingServiceStarted() { return m_Started; }

/*----------------------------------------------------------------------
 |   UpnpParentPairing::registred_children
 +---------------------------------------------------------------------*/
unsigned int UpnpParentPairing::registred_children() {
  return discovered_children_.size();
}

/*----------------------------------------------------------------------
 |   UpnpChildPairing::set_service_owner
 +---------------------------------------------------------------------*/
int UpnpParentPairing::set_service_owner(ParentPairingManager *service_owner) {
  parent_pairing_manager_ = service_owner;
}

/*----------------------------------------------------------------------
 |   UpnpParentPairing::CreatePassivePcm
 +---------------------------------------------------------------------*/
PassiveClassListenerInterface *UpnpParentPairing::CreatePassivePcm(
    const string &application_id, unsigned int class_index) {
  UpnpPassivePcm *communication = new UpnpPassivePcm();
  return communication;
}

/*----------------------------------------------------------------------
 |   UpnpParentPairing::CreateActivePcm
 +---------------------------------------------------------------------*/
ActiveClassInterface *UpnpParentPairing::CreateActivePcm(
    const string &application_id, unsigned int class_index) {
  UpnpActivePcm *communication =
      new UpnpActivePcm(PLT_DeviceHostReference(this), ctrl_point_);
  return communication;
}

/*----------------------------------------------------------------------
 |   UpnpParentPairing::CreateMediaCapturePcm
 +---------------------------------------------------------------------*/
MediaCaptureClassListenerInterface *UpnpParentPairing::CreateMediaCapturePcm(
    const string &application_id, unsigned int class_index) {
  UpnpMediaCapturePcm *communication = new UpnpMediaCapturePcm();
  return communication;
}

/*----------------------------------------------------------------------
 |   UpnpParentPairing::CreateOnDemandPcm
 +---------------------------------------------------------------------*/
OnDemandClassListenerInterface *UpnpParentPairing::CreateOnDemandPcm(
    const string &application_id, unsigned int class_index) {
  UpnpOnDemandPcm *communication = new UpnpOnDemandPcm();
  return communication;
}
