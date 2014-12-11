/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include <iostream>
#include <string>
#include "fsmda/paring/upnp_child_paring.h"
#include "fsmda/paring/child_paring_manager.h"
#include "fsmda/utils/upnp_fsmda_utils.h"
#include "NptConfig.h"
#include "NptResults.h"
#include "NptStrings.h"
#include "PltFileMediaServer.h"
#include "PltService.h"
#include "PltStateVariable.h"

using std::clog;
using std::endl;

/*----------------------------------------------------------------------
 |   UpnpChildParing::UpnpChildParing
 +---------------------------------------------------------------------*/
UpnpChildParing::UpnpChildParing(ChildParingManager *child_paring_manager)
    : PLT_DeviceHost("/", NULL, UpnpFsmdaUtils::kCpmDeviceType,
                     UpnpFsmdaUtils::kCpmDeviceFriendlyName, true, 0, true),
      upnp_instance_(NULL),
      paired_with_parent_(false) {
  m_ModelDescription = UpnpFsmdaUtils::kCpmDeviceModelDescription;
  m_ModelURL = UpnpFsmdaUtils::kCpmDeviceModelUrl;
  m_ModelNumber = UpnpFsmdaUtils::kCpmDeviceModelNumber;
  m_ModelName = UpnpFsmdaUtils::kCpmDeviceModelName;
  m_Manufacturer = UpnpFsmdaUtils::kFsmdaManufacturer;
  m_ManufacturerURL = UpnpFsmdaUtils::kFsmdaManufacturerUrl;
  device_host_ = new PLT_DeviceHostReference(this);
  device_service_ = new PLT_Service(this, UpnpFsmdaUtils::kCpmServiceType,
                                    UpnpFsmdaUtils::kCpmServiceId,
                                    UpnpFsmdaUtils::kCpmServiceName);
  device_service_->SetSCPDXML((const char *)UpnpFsmdaUtils::kCpmServiceScpdXml);
  ctrl_point_ = new PLT_CtrlPointReference(new PLT_CtrlPoint());
  child_paring_manager_ = child_paring_manager;
}

/*----------------------------------------------------------------------
 |   UpnpChildParing::~UpnpChildParing
 +---------------------------------------------------------------------*/
UpnpChildParing::~UpnpChildParing() {
  this->StopParingService();
  delete device_service_;
  ctrl_point_->Detach();
  delete ctrl_point_;
  device_host_->Detach();
  delete device_host_;
}

/*----------------------------------------------------------------------
 |   UpnpChildParing::SetupServices
 +---------------------------------------------------------------------*/
NPT_Result UpnpChildParing::SetupServices() {
  clog << "UpnpChildParing::SetupServices()" << endl;
  NPT_Result res;
  res = AddService(device_service_);
  return res;
}

/*----------------------------------------------------------------------
 |   UpnpChildParing::OnAction
 +---------------------------------------------------------------------*/
NPT_Result UpnpChildParing::OnAction(PLT_ActionReference &action,
                                     const PLT_HttpRequestContext &context) {
  NPT_String name = action->GetActionDesc().GetName();
  clog << "UpnpChildParing::OnAction()::action.name=" << name.GetChars()
       << endl;

  // handling classAnnouncement call
  if (name.Compare("classAnnouncement") == 0) {
    NPT_String application_id;
    action->GetArgumentValue("applicationId", application_id);
    NPT_Int32 class_index;
    action->GetArgumentValue("classIndex", class_index);
    NPT_String class_desc;
    action->GetArgumentValue("classDesc", class_desc);
    NPT_String class_function;
    action->GetArgumentValue("classFunction", class_function);
    clog << "UpnpChildParing::OnAction receive classAnnouncement("
         << application_id.GetChars() << "," << class_index << ","
         << class_desc.GetChars() << "," << class_function.GetChars() << ")"
         << endl;
    clog << "UpnpChildParing::OnAction()::paired_with_parent_= true" << endl;
    paired_with_parent_ = true;
    if (child_paring_manager_ != NULL) {
      child_paring_manager_->ClassAnnouncement(
          application_id.GetChars(), class_index, class_desc.GetChars(),
          class_function.GetChars());
      return NPT_SUCCESS;
    }
  }
  action->SetError(501, "Action Failed");
  return NPT_FAILURE;
}

NPT_Result UpnpChildParing::OnEventNotify(PLT_Service *service,
                                          NPT_List<PLT_StateVariable *> *vars) {
}

NPT_Result UpnpChildParing::OnActionResponse(NPT_Result res,
                                             PLT_ActionReference &action,
                                             void *userdata) {}

NPT_Result UpnpChildParing::OnDeviceRemoved(PLT_DeviceDataReference &device) {}

NPT_Result UpnpChildParing::OnDeviceAdded(PLT_DeviceDataReference &device) {
  clog << "UpnpChildParing::OnDeviceAdded()::device->GetFriendlyName="
       << device->GetFriendlyName().GetChars() << endl;
  clog << "UpnpChildParing::OnDeviceAdded()::device->GetType="
       << device->GetType().GetChars() << endl;
  clog << "UpnpChildParing::OnDeviceAdded()::device->GetUUID="
       << device->GetUUID().GetChars() << endl;
  clog << "UpnpChildParing::OnDeviceAdded()::device->GetURLBase()->"
       << device->GetURLBase().ToString().GetChars() << endl;

  PLT_Service *parent_paring_service;
  if (!device->GetType().Compare(UpnpFsmdaUtils::kPpmDeviceType)) {
    device->FindServiceByType(UpnpFsmdaUtils::kPpmServiceType,
                              parent_paring_service);
    return NPT_SUCCESS;
  } else {
    return NPT_FAILURE;
  }
}
/*----------------------------------------------------------------------
 |   UpnpChildParing::StartParingService
 +---------------------------------------------------------------------*/
int UpnpChildParing::StartParingService() {
  clog << "UpnpChildParing::StartService()" << endl;
  if (upnp_instance_ == NULL) {
    upnp_instance_ = UpnpFsmdaUtils::GetRunningUpnpInstance();
  }
  NPT_Result res;
  res = upnp_instance_->AddDevice(*device_host_);
  res = upnp_instance_->AddCtrlPoint(*ctrl_point_);
  (*ctrl_point_)->AddListener(this);
  clog << "UpnpChildParing::StartService()::NPT_Result res="<< NPT_ResultText(res) << endl;
  if (res == NPT_SUCCESS) {
    return 0;
  } else
    return -1;
}

/*----------------------------------------------------------------------
 |   UpnpChildParing::StopParingService
 +---------------------------------------------------------------------*/
int UpnpChildParing::StopParingService() {
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
