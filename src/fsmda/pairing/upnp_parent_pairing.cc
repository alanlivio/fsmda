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
#include "fsmda/pairing/upnp_parent_pairing.h"
#include "fsmda/utils/upnp_fsmda_utils.h"

using std::clog;
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
  device_service_ = new PLT_Service(this, UpnpFsmdaUtils::kPpmServiceType,
                                    UpnpFsmdaUtils::kPpmServiceId,
                                    UpnpFsmdaUtils::kPpmServiceName);
  device_service_->SetSCPDXML((const char *)UpnpFsmdaUtils::kPpmServiceScpdXml);
}

/*----------------------------------------------------------------------
 |   UpnpParentPairing::~UpnpParentPairing
 +---------------------------------------------------------------------*/
UpnpParentPairing::~UpnpParentPairing() {
  StopPairingService();
  delete device_service_;
  ctrl_point_.Detach();
  device_host_.Detach();
}

/*----------------------------------------------------------------------
 |   UpnpChildPairing::SetServiceOwner
 +---------------------------------------------------------------------*/
int UpnpParentPairing::SetServiceOwner(DevicePairingPpmInterface *service_owner) {
  parent_pairing_manager_ = service_owner;
}

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
  res = AddService(device_service_);
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
         << classIndex << "," << deviceDesc.GetChars() << ")" << endl;
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
                                               void *userdata) {}
NPT_Result UpnpParentPairing::OnDeviceRemoved(PLT_DeviceDataReference &device) {
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
  clog << "UpnpParentPairing::StartPairingService()::NPT_Result res="
       << NPT_ResultText(res) << endl;
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
    RemoveService(device_service_);
    upnp_instance_->RemoveDevice(device_host_);
    ctrl_point_->RemoveListener(this);
    upnp_instance_->RemoveCtrlPoint(ctrl_point_);
    UpnpFsmdaUtils::ReleaseInstance();
    upnp_instance_ = NULL;
  }
  return 0;
}
