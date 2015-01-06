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
      device_host_(this),
      ctrl_point_(new PLT_CtrlPoint()),
      upnp_instance_(NULL),
      child_pairing_manager_(NULL),
      handshake_performed_(false) {
  m_ModelDescription = UpnpFsmdaUtils::kCpmDeviceModelDescription;
  m_ModelURL = UpnpFsmdaUtils::kCpmDeviceModelUrl;
  m_ModelNumber = UpnpFsmdaUtils::kCpmDeviceModelNumber;
  m_ModelName = UpnpFsmdaUtils::kCpmDeviceModelName;
  m_Manufacturer = UpnpFsmdaUtils::kFsmdaManufacturer;
  m_ManufacturerURL = UpnpFsmdaUtils::kFsmdaManufacturerUrl;
  device_service_ = new PLT_Service(this, UpnpFsmdaUtils::kCpmServiceType,
                                    UpnpFsmdaUtils::kCpmServiceId,
                                    UpnpFsmdaUtils::kCpmServiceName);
  device_service_->SetSCPDXML((const char *)UpnpFsmdaUtils::kCpmServiceScpdXml);
}

/*----------------------------------------------------------------------
 |   UpnpChildPairing::~UpnpChildPairing
 +---------------------------------------------------------------------*/
UpnpChildPairing::~UpnpChildPairing() {
  StopPairingService();
  delete device_service_;
  ctrl_point_.Detach();
  device_host_.Detach();
}

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

  if (name.Compare("classAnnouncement") == 0) {
    // handling classAnnouncement call
    NPT_String application_id;
    action->GetArgumentValue("applicationId", application_id);
    NPT_Int32 class_index;
    NPT_String class_index_str;
    action->GetArgumentValue("classIndex", class_index);
    action->GetArgumentValue("classIndex", class_index_str);
    NPT_String class_desc;
    action->GetArgumentValue("classDesc", class_desc);
    NPT_String class_function;
    action->GetArgumentValue("classFunction", class_function);
    clog << "UpnpChildPairing::OnAction receive classAnnouncement("
         << application_id.GetChars() << "," << class_index << ","
         << " one_rdf_with_size=" << class_desc.GetLength() << ","
         << class_function.GetChars() << ")" << endl;

    // call child_pairing_manager_->ClassAnnouncement
    if (child_pairing_manager_ != NULL) {
      child_pairing_manager_->ClassAnnouncement(
          application_id.GetChars(), class_index, class_desc.GetChars(),
          class_function.GetChars());
    }

    // invoke addDeviceToClass
    //    clog << "UpnpChildPairing::OnAction "
    //            "last_parent_->GetFriendlyName()="
    //         << data->GetFriendlyName().GetChars() << endl;
    //    PLT_ActionReference reponse_action;
    //    ctrl_point_->CreateAction(data, UpnpFsmdaUtils::kPpmServiceType,
    //                              "addDeviceToClass", reponse_action);
    //    if (reponse_action.IsNull()) {
    //      clog << "UpnpChildPairing::OnAction reponse_action.IsNul" << endl;
    //      return NPT_FAILURE;
    //    }
    //    reponse_action->SetArgumentValue("applicationId", application_id);
    //    reponse_action->SetArgumentValue("deviceAddr", "localhost");
    //    reponse_action->SetArgumentValue("classIndex", class_index_str);
    //    reponse_action->SetArgumentValue("deviceDesc", class_desc);
    //    ctrl_point_->InvokeAction(reponse_action, 0);
    //    clog << "UpnpChildPairing::OnAction calling addDeviceToClass("
    //         << application_id.GetChars() << "," << class_index << ","
    //         << " one_rdf_with_size=" << class_desc.GetLength() << ","
    //         << ")" << endl;

    // set pareid
    set_handshake_performed(true);
    return NPT_SUCCESS;
  }
  action->SetError(501, "Action Failed");
  return NPT_FAILURE;
}

/*----------------------------------------------------------------------
 |   UpnpChildPairing::OnEventNotify
 +---------------------------------------------------------------------*/
NPT_Result UpnpChildPairing::OnEventNotify(
    PLT_Service *service, NPT_List<PLT_StateVariable *> *vars) {}

/*----------------------------------------------------------------------
 |   UpnpChildPairing::OnActionResponse
 +---------------------------------------------------------------------*/
NPT_Result UpnpChildPairing::OnActionResponse(NPT_Result res,
                                              PLT_ActionReference &action,
                                              void *userdata) {}

/*----------------------------------------------------------------------
 |   UpnpChildPairing::OnDeviceRemoved
 +---------------------------------------------------------------------*/
NPT_Result UpnpChildPairing::OnDeviceRemoved(PLT_DeviceDataReference &device) {}

/*----------------------------------------------------------------------
 |   UpnpChildPairing::OnDeviceAdded
 +---------------------------------------------------------------------*/
NPT_Result UpnpChildPairing::OnDeviceAdded(
    PLT_DeviceDataReference &device_data) {
  if (device_data->GetType().Compare(
          "urn:schemas-upnp-org:device:fsmda-parent-pairing-device:1"))
    return NPT_FAILURE;
  clog << "UpnpChildPairing::OnDeviceAdded() " << endl;
  clog << "UpnpChildPairing::OnDeviceAdded()::device->GetFriendlyName="
       << device_data->GetFriendlyName().GetChars() << endl;
  clog << "UpnpChildPairing::OnDeviceAdded()::device->GetType="
       << device_data->GetType().GetChars() << endl;
  clog << "UpnpChildPairing::OnDeviceAdded()::device->GetUUID="
       << device_data->GetUUID().GetChars() << endl;
  clog << "UpnpChildPairing::OnDeviceAdded()::device->GetURLBase()->"
       << device_data->GetURLBase().ToString().GetChars() << endl;

  //  last_parent_ = PLT_DeviceDataFinder(device_data);
  //  registred_parents_.Add(device_data);
  //  last_parent_uuid = device_data->GetUUID();

  if (!device_data->GetType().Compare(UpnpFsmdaUtils::kPpmDeviceType)) {
    device_data->FindServiceByType(UpnpFsmdaUtils::kPpmServiceType,
                                   parent_pairing_);
    return NPT_SUCCESS;
  } else {
    return NPT_FAILURE;
  }
}
/*----------------------------------------------------------------------
 |   UpnpChildPairing::StartPairingService
 +---------------------------------------------------------------------*/
int UpnpChildPairing::StartPairingService() {
  clog << "UpnpChildPairing::StartPairingService()" << endl;
  if (upnp_instance_ == NULL) {
    upnp_instance_ = UpnpFsmdaUtils::GetRunningInstance();
  }
  NPT_Result res;
  res = upnp_instance_->AddDevice(device_host_);
  res = upnp_instance_->AddCtrlPoint(ctrl_point_);
  ctrl_point_->AddListener(this);
  clog << "UpnpChildPairing::StartPairingService()::NPT_Result res="
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
    upnp_instance_->RemoveDevice(device_host_);
    ctrl_point_->RemoveListener(this);
    upnp_instance_->RemoveCtrlPoint(ctrl_point_);
    UpnpFsmdaUtils::ReleaseInstance();
    upnp_instance_ = NULL;
  }
  return 0;
}

/*----------------------------------------------------------------------
 |   UpnpChildPairing::set_service_owner
 +---------------------------------------------------------------------*/
int UpnpChildPairing::set_service_owner(ChildPairingManager *service_owner) {
  child_pairing_manager_ = service_owner;
}

/*----------------------------------------------------------------------
 |   UpnpChildPairing::pairing_service_started
 +---------------------------------------------------------------------*/
bool UpnpChildPairing::pairing_service_started() { return m_Started; }

/*----------------------------------------------------------------------
 |   UpnpChildPairing::handshak_performed
 +---------------------------------------------------------------------*/
bool UpnpChildPairing::handshak_performed() { return handshake_performed_; }

/*----------------------------------------------------------------------
 |   UpnpChildPairing::set_handshake_performed
 +---------------------------------------------------------------------*/
void UpnpChildPairing::set_handshake_performed(bool performed) {
  handshake_performed_ = performed;
}
