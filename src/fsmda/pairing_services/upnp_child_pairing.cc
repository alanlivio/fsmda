/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/
#include <iostream>
#include "fsmda/child_pairing_manager.h"
#include "fsmda/utils/upnp_fsmda_utils.h"

using std::clog;
using std::endl;

/*----------------------------------------------------------------------
 |   UpnpChildPairing::UpnpChildPairing
 +---------------------------------------------------------------------*/
UpnpChildPairing::UpnpChildPairing()
    : PLT_DeviceHost("/", NULL, UpnpFsmdaUtils::kCpmDeviceType,
                     UpnpFsmdaUtils::kCpmDeviceFriendlyName, true, 0, true),
      upnp_instance_(NULL),
      child_pairing_manager_(NULL),
      performed_handshake_(false) {
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
}

/*----------------------------------------------------------------------
 |   UpnpChildPairing::~UpnpChildPairing
 +---------------------------------------------------------------------*/
UpnpChildPairing::~UpnpChildPairing() {
  StopPairingService();
  delete device_service_;
  ctrl_point_->Detach();
  delete ctrl_point_;
  device_host_->Detach();
  delete device_host_;
}

/*----------------------------------------------------------------------
 |   UpnpChildPairing::SetServiceOwner
 +---------------------------------------------------------------------*/
int UpnpChildPairing::SetServiceOwner(ChildPairingManager *service_owner) {
  child_pairing_manager_ = service_owner;
}

/*----------------------------------------------------------------------
 |   UpnpChildPairing::SetDeviceDescription
 +---------------------------------------------------------------------*/
int UpnpChildPairing::SetDeviceDescription(
    DeviceDescription *device_description) {}

/*----------------------------------------------------------------------
 |   UpnpChildPairing::SetupServices
 +---------------------------------------------------------------------*/
NPT_Result UpnpChildPairing::SetupServices() {
  clog << "UpnpChildPairing::SetupServices()" << endl;
  NPT_Result res;
  res = AddService(device_service_);
  return res;
}

/*----------------------------------------------------------------------
 |   UpnpChildPairing::OnAction
 +---------------------------------------------------------------------*/
NPT_Result UpnpChildPairing::OnAction(PLT_ActionReference &action,
                                      const PLT_HttpRequestContext &context) {
  NPT_String name = action->GetActionDesc().GetName();
  clog << "UpnpChildPairing::OnAction()::action.name=" << name.GetChars()
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
    clog << "UpnpChildPairing::OnAction receive classAnnouncement("
         << application_id.GetChars() << "," << class_index << ","
         << class_desc.GetChars() << "," << class_function.GetChars() << ")"
         << endl;
    clog << "UpnpChildPairing::OnAction()::paired_with_parent_= true" << endl;
    performed_handshake_ = true;
    if (child_pairing_manager_ != NULL) {
      child_pairing_manager_->ClassAnnouncement(
          application_id.GetChars(), class_index, class_desc.GetChars(),
          class_function.GetChars());
      return NPT_SUCCESS;
    }
  }
  action->SetError(501, "Action Failed");
  return NPT_FAILURE;
}

NPT_Result UpnpChildPairing::OnEventNotify(
    PLT_Service *service, NPT_List<PLT_StateVariable *> *vars) {}

NPT_Result UpnpChildPairing::OnActionResponse(NPT_Result res,
                                              PLT_ActionReference &action,
                                              void *userdata) {}

NPT_Result UpnpChildPairing::OnDeviceRemoved(PLT_DeviceDataReference &device) {}

NPT_Result UpnpChildPairing::OnDeviceAdded(PLT_DeviceDataReference &device) {
  clog << "UpnpChildPairing::OnDeviceAdded()::device->GetFriendlyName="
       << device->GetFriendlyName().GetChars() << endl;
  clog << "UpnpChildPairing::OnDeviceAdded()::device->GetType="
       << device->GetType().GetChars() << endl;
  clog << "UpnpChildPairing::OnDeviceAdded()::device->GetUUID="
       << device->GetUUID().GetChars() << endl;
  clog << "UpnpChildPairing::OnDeviceAdded()::device->GetURLBase()->"
       << device->GetURLBase().ToString().GetChars() << endl;

  if (!device->GetType().Compare(UpnpFsmdaUtils::kPpmDeviceType)) {
    device->FindServiceByType(UpnpFsmdaUtils::kPpmServiceType,
                              parent_pairing_service_);
    return NPT_SUCCESS;
  } else {
    return NPT_FAILURE;
  }
}
/*----------------------------------------------------------------------
 |   UpnpChildPairing::StartPairingService
 +---------------------------------------------------------------------*/
int UpnpChildPairing::StartPairingService() {
  clog << "UpnpChildPairing::StartService()" << endl;
  if (upnp_instance_ == NULL) {
    upnp_instance_ = UpnpFsmdaUtils::GetRunningInstance();
  }
  NPT_Result res;
  res = upnp_instance_->AddDevice(*device_host_);
  res = upnp_instance_->AddCtrlPoint(*ctrl_point_);
  (*ctrl_point_)->AddListener(this);
  clog << "UpnpChildPairing::StartService()::NPT_Result res="
       << NPT_ResultText(res) << endl;
  if (res == NPT_SUCCESS) {
    return 0;
  } else {
    return -1;
  }
}

/*----------------------------------------------------------------------
 |   UpnpChildPairing::StopPairingService
 +---------------------------------------------------------------------*/
int UpnpChildPairing::StopPairingService() {
  if (upnp_instance_ != NULL) {
    RemoveService(device_service_);
    upnp_instance_->RemoveDevice(*device_host_);
    (*ctrl_point_)->RemoveListener(this);
    upnp_instance_->RemoveCtrlPoint(*ctrl_point_);
    UpnpFsmdaUtils::ReleaseInstance();
    upnp_instance_ = NULL;
  }
  return 0;
}
