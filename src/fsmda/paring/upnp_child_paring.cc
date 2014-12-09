/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include "fsmda/paring/upnp_child_paring.h"
#include "fsmda/utils/upnp_fsmda_utils.h"
#include "NptConfig.h"
#include "NptResults.h"
#include "NptStrings.h"
#include "PltFileMediaServer.h"
#include "PltService.h"
#include "PltStateVariable.h"
#include <iostream>
#include <string>

using std::clog;
using std::endl;

/*----------------------------------------------------------------------
 |   UpnpChildParing::UpnpChildParing
 +---------------------------------------------------------------------*/
UpnpChildParing::UpnpChildParing()
    : PLT_DeviceHost("/", NULL, UpnpFsmdaUtils::kPpmDeviceType,
                     UpnpFsmdaUtils::kCpmDeviceFriendlyName, true, 4445, true),
      device_service_(NULL),
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
  //  (*ctrl_point_)->IgnoreUUID(m_UUID);
  //  (*ctrl_point_)->IgnoreUUID("886ef746-92bf-44f8-bd17-cdc1da03c322");
  //  (*ctrl_point_)->IgnoreUUID("fd264c69-e1d8-483e-9038-a896b65d2c1b");
}

/*----------------------------------------------------------------------
 |   UpnpChildParing::~UpnpChildParing
 +---------------------------------------------------------------------*/
UpnpChildParing::~UpnpChildParing() {
  this->StopService();
  delete device_service_;
  delete ctrl_point_;
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
  clog << "UpnpChildParing::OnAction()" << endl;
  NPT_String name = action->GetActionDesc().GetName();

  // handling classAnnouncement call
  if (name.Compare("classAnnouncement") == 0) {
    NPT_String applicationId;
    action->GetArgumentValue("applicationId", applicationId);
    NPT_Int32 classIndex;
    action->GetArgumentValue("classIndex", classIndex);
    NPT_String classDesc;
    action->GetArgumentValue("classDesc", classDesc);
    NPT_String classFunction;
    action->GetArgumentValue("classFunction", classFunction);
    clog << "--->UpnpChildParing::OnAction receive classAnnouncement("
         << applicationId.GetChars() << "," << classIndex << ","
         << classDesc.GetChars() << "," << classFunction.GetChars() << ")"
         << endl;
    return NPT_SUCCESS;
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
  clog << "UpnpChildParing::OnDeviceAdded()" << endl;
  clog << "UpnpChildParing::OnDeviceAdded()::device->GetFriendlyName="
       << device->GetFriendlyName().GetChars() << endl;
  clog << "UpnpChildParing::OnDeviceAdded()::device->GetType="
       << device->GetType().GetChars() << endl;
  clog << "UpnpChildParing::OnDeviceAdded()::device->GetUUID="
       << device->GetUUID().GetChars() << endl;
  clog << "UpnpChildParing::OnDeviceAdded()::device->GetServices()[0]->"
          "GetSCPDURL=" << device->GetServices()[0]->GetSCPDURL().GetChars()
       << endl;

  PLT_Service *parent_paring_service;
  if (device->GetType().StartsWith(UpnpFsmdaUtils::kPpmDeviceType)) {
    device->FindServiceByType(UpnpFsmdaUtils::kPpmServiceType,
                              parent_paring_service);
//    NPT_String parent_scpdxml;
//    parent_paring_service->GetSCPDXML(parent_scpdxml);
//    clog << "----->parent_scpdxml=" << parent_scpdxml.GetChars() << endl;
    paired_with_parent_ = true;
    return NPT_SUCCESS;
  } else
    return NPT_FAILURE;
}
/*----------------------------------------------------------------------
 |   UpnpChildParing::StartService
 +---------------------------------------------------------------------*/
int UpnpChildParing::StartService() {
  clog << "UpnpChildParing::StartService" << endl;
  if (upnp_instance_ == NULL) {
    upnp_instance_ = UpnpFsmdaUtils::GetRunningUpnpInstance();
  }
  NPT_Result res;
  res = upnp_instance_->AddDevice(*device_host_);
  res = upnp_instance_->AddCtrlPoint(*ctrl_point_);
  (*ctrl_point_)->AddListener(this);
  if (res != NPT_SUCCESS) {
    return -1;
  } else {
    return 0;
  }
}

/*----------------------------------------------------------------------
 |   UpnpChildParing::StopService
 +---------------------------------------------------------------------*/
int UpnpChildParing::StopService() {
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

/*----------------------------------------------------------------------
 |   UpnpChildParing::IsServiceStarted
 +---------------------------------------------------------------------*/
bool UpnpChildParing::IsServiceStarted() { return m_Started; }

/*----------------------------------------------------------------------
 |   UpnpChildParing::IsPaired
 +---------------------------------------------------------------------*/
bool UpnpChildParing::IsPaired() { return paired_with_parent_; }
