/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include <iostream>
#include <string>
#include "fsmda/paring/parent_paring_manager.h"
#include "fsmda/paring/upnp_parent_paring.h"
#include "fsmda/utils/upnp_fsmda_utils.h"
#include "NptResults.h"
#include "NptStrings.h"
#include "NptTypes.h"
#include "PltAction.h"
#include "PltHttp.h"
#include "PltService.h"
#include "PltStateVariable.h"

using std::clog;
using std::endl;

/*----------------------------------------------------------------------
 |   UpnpParentParing::UpnpParentParing
 +---------------------------------------------------------------------*/
UpnpParentParing::UpnpParentParing(ParentParingManager* parent_paring_manager)
    : PLT_DeviceHost("/", NULL, UpnpFsmdaUtils::kPpmDeviceType,
                     UpnpFsmdaUtils::kPpmDeviceFriendlyName, true, 0, true),
      upnp_instance_(NULL),
      parent_paring_manager_(NULL),
      paired_childs_(0) {
  m_ModelDescription = UpnpFsmdaUtils::kPpmDeviceModelDescription;
  m_ModelURL = UpnpFsmdaUtils::kPpmDeviceModelUrl;
  m_ModelNumber = UpnpFsmdaUtils::kPpmDeviceNumber;
  m_ModelName = UpnpFsmdaUtils::kPpmDeviceModelName;
  m_Manufacturer = UpnpFsmdaUtils::kFsmdaManufacturer;
  m_ManufacturerURL = UpnpFsmdaUtils::kFsmdaManufacturerUrl;
  device_host_ = new PLT_DeviceHostReference(this);
  device_service_ = new PLT_Service(this, UpnpFsmdaUtils::kPpmServiceType,
                                    UpnpFsmdaUtils::kPpmServiceId,
                                    UpnpFsmdaUtils::kPpmServiceName);
  device_service_->SetSCPDXML((const char *)UpnpFsmdaUtils::kPpmServiceScpdXml);
  ctrl_point_ = new PLT_CtrlPointReference(new PLT_CtrlPoint());
  parent_paring_manager_ = parent_paring_manager;
}

/*----------------------------------------------------------------------
 |   UpnpParentParing::~UpnpParentParing
 +---------------------------------------------------------------------*/
UpnpParentParing::~UpnpParentParing() {
  this->StopService();
  delete device_service_;
  ctrl_point_->Detach();
  delete ctrl_point_;
  device_host_->Detach();
  delete device_host_;
}

/*----------------------------------------------------------------------
 |   UpnpParentParing::SetupServices
 +---------------------------------------------------------------------*/
NPT_Result UpnpParentParing::SetupServices() {
  clog << "UpnpParentParing::SetupServices()" << endl;
  NPT_Result res;
  res = AddService(device_service_);
  return res;
}

/*----------------------------------------------------------------------
 |   UpnpParentParing::OnAction
 +---------------------------------------------------------------------*/
NPT_Result UpnpParentParing::OnAction(PLT_ActionReference &action,
                                      const PLT_HttpRequestContext &context) {
  clog << "UpnpParentParing::OnAction()" << endl;
  NPT_String name = action->GetActionDesc().GetName();

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
    clog << "UpnpParentParing::OnAction:: receive addDeviceToClass("
         << applicationId.GetChars() << "," << deviceAddr.GetChars() << ","
         << classIndex << "," << deviceDesc.GetChars() << ")" << endl;
    if (parent_paring_manager_ != NULL) {
      parent_paring_manager_->AddDeviceToClass(
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
    clog << "UpnpParentParing::OnAction:: receive getChildIndex("
         << application_id.GetChars() << "," << device_addr.GetChars() << ","
         << class_index << ")" << endl;
    action->SetArgumentValue("ret", "100");
    if (parent_paring_manager_ != NULL) {
      parent_paring_manager_->GetChildIndex(
          application_id.GetChars(), device_addr.GetChars(), class_index);
    }
    return NPT_SUCCESS;
  }
  action->SetError(501, "Action Failed");
  return NPT_FAILURE;
}

NPT_Result UpnpParentParing::OnEventNotify(
    PLT_Service *service, NPT_List<PLT_StateVariable *> *vars) {}

NPT_Result UpnpParentParing::OnActionResponse(NPT_Result res,
                                              PLT_ActionReference &action,
                                              void *userdata) {}
NPT_Result UpnpParentParing::OnDeviceRemoved(PLT_DeviceDataReference &device) {}

NPT_Result UpnpParentParing::OnDeviceAdded(PLT_DeviceDataReference &device) {
  clog << "UpnpParentParing::OnDeviceAdded()" << endl;
  clog << "UpnpParentParing::OnDeviceAdded()::device->GetFriendlyName="
       << device->GetFriendlyName().GetChars() << endl;
  clog << "UpnpParentParing::OnDeviceAdded()::device->GetType="
       << device->GetType().GetChars() << endl;
  clog << "UpnpParentParing::OnDeviceAdded()::device->GetUUID="
       << device->GetUUID().GetChars() << endl;
  clog << "UpnpParentParing::OnDeviceAdded()::device->GetURLBase()->"
          "GetSCPDURL=" << device->GetURLBase().ToString().GetChars() << endl;
  clog << "UpnpParentParing::OnDeviceAdded()::device->GetServices()[0]->"
          "GetSCPDURL=" << device->GetServices()[0]->GetSCPDURL().GetChars()
       << endl;

  PLT_Service *parent_paring_service;
  if (!device->GetType().Compare(UpnpFsmdaUtils::kCpmDeviceType)) {
    device->FindServiceByType(UpnpFsmdaUtils::kCpmServiceType,
                              parent_paring_service);
    PLT_ActionReference action;
    (*ctrl_point_)->CreateAction(device, UpnpFsmdaUtils::kCpmServiceType,
                                 "classAnnouncement", action);
    if (!action.IsNull()) {
      action->SetArgumentValue("applicationId", "applicationId");
      action->SetArgumentValue("classIndex", "applicationId");
      action->SetArgumentValue("classDesc", "applicationId");
      action->SetArgumentValue("classFunction", "applicationId");
      (*ctrl_point_)->InvokeAction(action, 0);
    }
    clog << "--->discoverd_cpm_.push_back(device)" << endl;
    discoverd_cpm_.push_back(device);
    return NPT_SUCCESS;
  } else {
    return NPT_FAILURE;
  }
}

/*----------------------------------------------------------------------
 |   UpnpParentParing::StartService
 +---------------------------------------------------------------------*/
int UpnpParentParing::StartService() {
  clog << "UpnpParentParing::StartService" << endl;
  if (upnp_instance_ == NULL) {
    upnp_instance_ = UpnpFsmdaUtils::GetRunningUpnpInstance();
  }
  NPT_Result res = upnp_instance_->AddDevice(*device_host_);
  res = upnp_instance_->AddCtrlPoint(*ctrl_point_);
  (*ctrl_point_)->AddListener(this);
  if (res != NPT_SUCCESS) {
    return -1;
  } else {
    return 0;
  }
}

/*----------------------------------------------------------------------
 |   UpnpParentParing::StopService
 +---------------------------------------------------------------------*/
int UpnpParentParing::StopService() {
  if (upnp_instance_ != NULL) {
    RemoveService(device_service_);
    upnp_instance_->RemoveDevice(*device_host_);
    (*ctrl_point_)->RemoveListener(this);
    upnp_instance_->RemoveCtrlPoint(*ctrl_point_);
    UpnpFsmdaUtils::ReleaseUpnpInstance();
    upnp_instance_ = NULL;
  }
  return 0;
}
