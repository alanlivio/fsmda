/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include <iostream>
#include <sstream>
#include "fsmda/communication/upnp_active_pcm.h"
#include "fsmda/utils/upnp_fsmda_utils.h"

using std::cout;
using std::clog;
using std::stringstream;
using std::endl;

/*----------------------------------------------------------------------
 |   UpnpActivePcm::UpnpActivePcm
 +---------------------------------------------------------------------*/
UpnpActivePcm::UpnpActivePcm()
    : PLT_DeviceHost("/", NULL, UpnpFsmdaUtils::kActivePcmDeviceType,
                     UpnpFsmdaUtils::kActivePcmDeviceFriendlyName, true, 0,
                     true),
      device_host_(this),
      ctrl_point_(new PLT_CtrlPoint()),
      upnp_instance_(NULL) {
  m_ModelDescription = UpnpFsmdaUtils::kActivePcmDeviceModelDescription;
  m_ModelURL = UpnpFsmdaUtils::kActivePcmDeviceModelUrl;
  m_ModelNumber = UpnpFsmdaUtils::kActivePcmDeviceModelNumber;
  m_ModelName = UpnpFsmdaUtils::kActivePcmDeviceModelName;
  m_Manufacturer = UpnpFsmdaUtils::kFsmdaManufacturer;
  m_ManufacturerURL = UpnpFsmdaUtils::kFsmdaManufacturerUrl;
  device_service_ = new PLT_Service(this, UpnpFsmdaUtils::kActivePcmServiceType,
                                    UpnpFsmdaUtils::kActivePcmServiceId,
                                    UpnpFsmdaUtils::kActivePcmServiceName);
  device_service_->SetSCPDXML(
      (const char *)UpnpFsmdaUtils::kActivePcmServiceScpdXml);
}

/*----------------------------------------------------------------------
 |   UpnpActivePcm::~UpnpActivePcm
 +---------------------------------------------------------------------*/
UpnpActivePcm::~UpnpActivePcm() {
  StopCommunicationService();
  delete device_service_;
  ctrl_point_.Detach();
  device_host_.Detach();
}

/*----------------------------------------------------------------------
 |   UpnpActivePcm::StartCommunicationService
 +---------------------------------------------------------------------*/
int UpnpActivePcm::StartCommunicationService() {
  clog << "UpnpActiveCcm::StartCommunicationService()" << endl;
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
 |   UpnpActivePcm::StopCommunicationService
 +---------------------------------------------------------------------*/
int UpnpActivePcm::StopCommunicationService() {
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
 |   UpnpActivePcm::IsCommunicationServiceStarted
 +---------------------------------------------------------------------*/
bool UpnpActivePcm::IsCommunicationServiceStarted() { return m_Started; }

/*----------------------------------------------------------------------
 |   UpnpActivePcm::RequestPropertyValue
 +---------------------------------------------------------------------*/
void UpnpActivePcm::RequestPropertyValue(const string &object_id,
                                         const string &name) {}

/*----------------------------------------------------------------------
 |   UpnpActivePcm::NotifyEventTransition
 +---------------------------------------------------------------------*/
void UpnpActivePcm::NotifyEventTransition(const string &object_id,
                                          const string &event_id,
                                          const string &transition) {}

/*----------------------------------------------------------------------
 |   UpnpActivePcm::NotifyError
 +---------------------------------------------------------------------*/
void UpnpActivePcm::NotifyError(const string &object_id,
                                const string &message) {}

/*----------------------------------------------------------------------
 |   UpnpActivePcm::SetupServices
 +---------------------------------------------------------------------*/
NPT_Result UpnpActivePcm::SetupServices() {}

/*----------------------------------------------------------------------
 |   UpnpActivePcm::OnAction
 +---------------------------------------------------------------------*/
NPT_Result UpnpActivePcm::OnAction(PLT_ActionReference &action,
                                   const PLT_HttpRequestContext &context) {}

/*----------------------------------------------------------------------
 |   UpnpActivePcm::OnDeviceAdded
 +---------------------------------------------------------------------*/
NPT_Result UpnpActivePcm::OnDeviceAdded(PLT_DeviceDataReference &device) {}

/*----------------------------------------------------------------------
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
