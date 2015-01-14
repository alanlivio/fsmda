/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/
#include <iostream>
#include <sstream>
#include "fsmda/child_class_handler.h"
#include "fsmda/upnp/upnp_fsmda_utils.h"

using std::cout;
using std::clog;
using std::stringstream;
using std::endl;

/*----------------------------------------------------------------------
 |   UpnpCpm::UpnpCpm
 +---------------------------------------------------------------------*/
UpnpCpm::UpnpCpm()
    : PLT_DeviceHost("/", NULL, UpnpFsmdaUtils::kChildDeviceType,
                     UpnpFsmdaUtils::kChildDeviceFriendlyName, true, 0, true),
      device_host_(this),
      ctrl_point_(new PLT_CtrlPoint()),
      upnp_instance_(NULL),
      child_class_handler_(NULL) {
  m_ModelDescription = UpnpFsmdaUtils::kChildDeviceModelDescription;
  m_ModelURL = UpnpFsmdaUtils::kChildDeviceModelUrl;
  m_ModelNumber = UpnpFsmdaUtils::kChildDeviceModelNumber;
  m_ModelName = UpnpFsmdaUtils::kChildDeviceModelName;
  m_Manufacturer = UpnpFsmdaUtils::kFsmdaManufacturer;
  m_ManufacturerURL = UpnpFsmdaUtils::kFsmdaManufacturerUrl;

  // create child pairing service
  ppm_service_ = new PLT_Service(this, UpnpFsmdaUtils::kCpmServiceType,
                                 UpnpFsmdaUtils::kCpmServiceId,
                                 UpnpFsmdaUtils::kCpmServiceName);
  ppm_service_->SetSCPDXML((const char *)UpnpFsmdaUtils::kCpmServiceScpdXml);

  // create passive service
  passive_service_ =
      new PLT_Service(this, UpnpFsmdaUtils::kPassiveCcmServiceType,
                      UpnpFsmdaUtils::kPassiveCcmServiceId,
                      UpnpFsmdaUtils::kPassiveCcmServiceName);
  passive_service_->SetSCPDXML(
      (const char *)UpnpFsmdaUtils::kPassiveCcmServiceScpdXml);

  // create active service
  active_service_ = new PLT_Service(this, UpnpFsmdaUtils::kActiveCcmServiceType,
                                    UpnpFsmdaUtils::kActiveCcmServiceId,
                                    UpnpFsmdaUtils::kActiveCcmServiceName);
  active_service_->SetSCPDXML(
      (const char *)UpnpFsmdaUtils::kActiveCcmServiceScpdXml);

  // create ondemand service
  ondemand_service_ =
      new PLT_Service(this, UpnpFsmdaUtils::kOnDemandCcmServiceType,
                      UpnpFsmdaUtils::kOnDemandCcmServiceId,
                      UpnpFsmdaUtils::kOnDemandCcmServiceName);
  ondemand_service_->SetSCPDXML(
      (const char *)UpnpFsmdaUtils::kOnDemandCcmServiceScpdXml);

  // create media catpure service
  mediacapture_service_ =
      new PLT_Service(this, UpnpFsmdaUtils::kMediaCaptureCcmServiceType,
                      UpnpFsmdaUtils::kMediaCaptureCcmServiceId,
                      UpnpFsmdaUtils::kMediaCaptureCcmServiceName);
  mediacapture_service_->SetSCPDXML(
      (const char *)UpnpFsmdaUtils::kMediaCaptureCcmServiceScpdXml);
}

/*----------------------------------------------------------------------
 |   UpnpCpm::~UpnpCpm
 +---------------------------------------------------------------------*/
UpnpCpm::~UpnpCpm() {
  StopPairingService();
  delete ppm_service_;
  ctrl_point_.Detach();
  device_host_.Detach();
}

/*----------------------------------------------------------------------
 |   UpnpCpm::AddDeviceToClass
 +---------------------------------------------------------------------*/
void UpnpCpm::AddDeviceToClass(const string &application_id,
                               const string &device_address,
                               unsigned int class_index,
                               const string &device_desc) {
  clog << "UpnpCpm::AddDeviceToClass " << endl;

  // invoke AddDeviceToClass
  if (last_parent_.IsNull())
    last_parent_semaphore.WaitUntilEquals(1, NPT_TIMEOUT_INFINITE);
  PLT_ActionReference reponse_action;
  ctrl_point_->CreateAction(last_parent_, UpnpFsmdaUtils::kPpmServiceType,
                            "AddDeviceToClass", reponse_action);

  if (reponse_action.IsNull()) {
    clog << "UpnpCpm::OnAction reponse_action.IsNul" << endl;
  }

  reponse_action->SetArgumentValue("application_id", application_id.c_str());
  reponse_action->SetArgumentValue("device_address", "localhost");
  stringstream aux_string;
  aux_string << class_index;
  reponse_action->SetArgumentValue("class_index", aux_string.str().c_str());
  reponse_action->SetArgumentValue("device_description", device_desc.c_str());
  NPT_Result res = ctrl_point_->InvokeAction(reponse_action, 0);
  if (res == NPT_FAILURE)
    clog << "UpnpCpm::AddDeviceToClass calling AddDeviceToClass failed" << endl;
  else
    clog << "UpnpCpm::AddDeviceToClass calling AddDeviceToClass("
         << application_id << "," << class_index << ","
         << " one_rdf_with_size=" << device_desc.size() << ","
         << ")" << endl;
}

/*----------------------------------------------------------------------
 |   UpnpCpm::GetChildIndex
 +---------------------------------------------------------------------*/
void UpnpCpm::GetChildIndex(const string &application_id,
                            const string &device_address,
                            unsigned int class_index) {}

/*----------------------------------------------------------------------
 |   UpnpCpm::SetupServices
 +---------------------------------------------------------------------*/
NPT_Result UpnpCpm::SetupServices() {
  clog << "UpnpCpm::SetupServices()" << endl;

  NPT_Result res;
  res = AddService(ppm_service_);
  if (res == NPT_FAILURE) return NPT_FAILURE;
  res = AddService(passive_service_);
  if (res == NPT_FAILURE) return NPT_FAILURE;
  res = AddService(active_service_);
  if (res == NPT_FAILURE) return NPT_FAILURE;
  res = AddService(ondemand_service_);
  if (res == NPT_FAILURE) return NPT_FAILURE;
  res = AddService(mediacapture_service_);
  if (res == NPT_FAILURE) return NPT_FAILURE;
  return NPT_SUCCESS;
}

/*----------------------------------------------------------------------
 |   UpnpCpm::OnAction
 +---------------------------------------------------------------------*/
NPT_Result UpnpCpm::OnAction(PLT_ActionReference &action,
                             const PLT_HttpRequestContext &context) {
  NPT_String name = action->GetActionDesc().GetName();
  clog << "UpnpCpm::OnAction()::name=" << name.GetChars() << endl;

  if (name.Compare("ClassAnnouncement") == 0) {
    // handling ClassAnnouncement call
    NPT_String application_id;
    action->GetArgumentValue("application_id", application_id);
    NPT_Int32 class_index;
    NPT_String class_index_str;
    action->GetArgumentValue("class_index", class_index);
    action->GetArgumentValue("class_index", class_index_str);
    NPT_String class_desc;
    action->GetArgumentValue("class_desc", class_desc);
    NPT_String class_function;
    action->GetArgumentValue("class_function", class_function);
    clog << "UpnpCpm::OnAction()::ClassAnnouncement("
         << application_id.GetChars() << "," << class_index << ","
         << " one_rdf_with_size=" << class_desc.GetLength() << ","
         << class_function.GetChars() << ")" << endl;

    // call child_class_handler_->ClassAnnouncement
    if (child_class_handler_ != NULL) {
      DeviceClassDescription device_class_description;
      device_class_description.InitializeByRdfContent(class_desc.GetChars());
      bool paired = device_class_description.IsDeviceCompatible(
          child_class_handler_->device_description());
      AddDeviceToClass(application_id.GetChars(), "localhost", class_index,
                       class_desc.GetChars());
    }
  }
  return NPT_SUCCESS;
}

/*----------------------------------------------------------------------
 |   UpnpCpm::OnEventNotify
 +---------------------------------------------------------------------*/
NPT_Result UpnpCpm::OnEventNotify(PLT_Service *service,
                                  NPT_List<PLT_StateVariable *> *vars) {}

/*----------------------------------------------------------------------
 |   UpnpCpm::OnActionResponse
 +---------------------------------------------------------------------*/
NPT_Result UpnpCpm::OnActionResponse(NPT_Result res,
                                     PLT_ActionReference &action,
                                     void *userdata) {
  NPT_String name = action->GetActionDesc().GetName();
  clog << "UpnpCpm::OnActionResponse()::action.name=" << name.GetChars()
       << endl;
  if (name.Compare("AddDeviceToClass") == 0) {
    clog << "UpnpCpm::OnActionResponse()::calling set_paired" << endl;
    child_class_handler_->set_paired(true);
  }
}

/*----------------------------------------------------------------------
 |   UpnpCpm::OnDeviceRemoved
 +---------------------------------------------------------------------*/
NPT_Result UpnpCpm::OnDeviceRemoved(PLT_DeviceDataReference &device) {}

/*----------------------------------------------------------------------
 |   UpnpCpm::OnDeviceAdded
 +---------------------------------------------------------------------*/
NPT_Result UpnpCpm::OnDeviceAdded(PLT_DeviceDataReference &device_data) {
  if (!device_data->GetUUID().Compare(m_UUID)) return NPT_FAILURE;
  if (device_data->GetType().Compare(UpnpFsmdaUtils::kParentDeviceType))
    return NPT_FAILURE;
  clog << "UpnpCpm::OnDeviceAdded() " << endl;
  clog << "UpnpCpm::OnDeviceAdded()::device->GetFriendlyName="
       << device_data->GetFriendlyName().GetChars() << endl;
  clog << "UpnpCpm::OnDeviceAdded()::device->GetType="
       << device_data->GetType().GetChars() << endl;
  clog << "UpnpCpm::OnDeviceAdded()::device->GetUUID="
       << device_data->GetUUID().GetChars() << endl;
  clog << "UpnpCpm::OnDeviceAdded()::device->GetURLBase()->"
       << device_data->GetURLBase().ToString().GetChars() << endl;
  clog << "UpnpCpm::OnDeviceAdded()::last_parent_ = device_data" << endl;
  last_parent_ = device_data;
  last_parent_semaphore.SetValue(1);

  return NPT_SUCCESS;
}
/*----------------------------------------------------------------------
 |   UpnpCpm::StartPairingService
 +---------------------------------------------------------------------*/
int UpnpCpm::StartPairingService() {
  clog << "UpnpCpm::StartPairingService()" << endl;
  if (upnp_instance_ == NULL) {
    upnp_instance_ = UpnpFsmdaUtils::GetRunningInstance();
  }
  NPT_Result res;
  res = upnp_instance_->AddDevice(device_host_);
  res = upnp_instance_->AddCtrlPoint(ctrl_point_);
  ctrl_point_->AddListener(this);
  if (res == NPT_SUCCESS) {
    return 0;
  } else {
    return -1;
  }
}

/*----------------------------------------------------------------------
 |   UpnpCpm::StopPairingService
 +---------------------------------------------------------------------*/
int UpnpCpm::StopPairingService() {
  if (upnp_instance_ != NULL) {
    RemoveService(ppm_service_);
    upnp_instance_->RemoveDevice(device_host_);
    ctrl_point_->RemoveListener(this);
    upnp_instance_->RemoveCtrlPoint(ctrl_point_);
    UpnpFsmdaUtils::ReleaseInstance();
    upnp_instance_ = NULL;
  }
  return 0;
}

/*----------------------------------------------------------------------
 |   UpnpCpm::set_service_owner
 +---------------------------------------------------------------------*/
int UpnpCpm::set_service_owner(ChildClassHandler *service_owner) {
  child_class_handler_ = service_owner;
}

/*----------------------------------------------------------------------
 |   UpnpCpm::IsPairingServiceStarted
 +---------------------------------------------------------------------*/
bool UpnpCpm::IsPairingServiceStarted() { return m_Started; }

/*----------------------------------------------------------------------
 |   UpnpCpm::CreatePassiveCcm
 +---------------------------------------------------------------------*/
PassiveClassInterface *UpnpCpm::CreatePassiveCcm(const string &application_id,
                                                 unsigned int class_index) {
  UpnpPassiveCcm *communication = new UpnpPassiveCcm();
  return communication;
}

/*----------------------------------------------------------------------
 |   UpnpCpm::CreateActiveCcm
 +---------------------------------------------------------------------*/
ActiveClassListenerInterface *UpnpCpm::CreateActiveCcm(
    const string &application_id, unsigned int class_index) {
  UpnpActiveCcm *communication =
      new UpnpActiveCcm(PLT_DeviceHostReference(this), last_parent_,
                        ctrl_point_, application_id, class_index);
  return communication;
}

/*----------------------------------------------------------------------
 |   UpnpCpm::CreateMediaCaptureCcm
 +---------------------------------------------------------------------*/
MediaCaptureClassInterface *UpnpCpm::CreateMediaCaptureCcm(
    const string &application_id, unsigned int class_index) {
  UpnpMediaCaptureCcm *communication = new UpnpMediaCaptureCcm();
  return communication;
}

/*----------------------------------------------------------------------
 |   UpnpCpm::CreateOnDemandCcm
 +---------------------------------------------------------------------*/
OnDemandClassInterface *UpnpCpm::CreateOnDemandCcm(const string &application_id,
                                                   unsigned int class_index) {
  UpnpOnDemandCcm *communication = new UpnpOnDemandCcm();
  return communication;
}
