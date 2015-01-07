/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include <iostream>
#include <sstream>
#include "fsmda/communication/upnp_active_ccm.h"
#include "fsmda/utils/upnp_fsmda_utils.h"

using std::cout;
using std::clog;
using std::stringstream;
using std::endl;

/*----------------------------------------------------------------------
 |   UpnpActiveCcm::UpnpActiveCcm
 +---------------------------------------------------------------------*/
UpnpActiveCcm::UpnpActiveCcm()
    : PLT_DeviceHost("/", NULL, UpnpFsmdaUtils::kActiveCcmDeviceType,
                     UpnpFsmdaUtils::kActiveCcmDeviceFriendlyName, true, 0,
                     true),
      device_host_(this),
      ctrl_point_(new PLT_CtrlPoint()),
      upnp_instance_(NULL) {
  m_ModelDescription = UpnpFsmdaUtils::kActiveCcmDeviceModelDescription;
  m_ModelURL = UpnpFsmdaUtils::kActiveCcmDeviceModelUrl;
  m_ModelNumber = UpnpFsmdaUtils::kActiveCcmDeviceModelNumber;
  m_ModelName = UpnpFsmdaUtils::kActiveCcmDeviceModelName;
  m_Manufacturer = UpnpFsmdaUtils::kFsmdaManufacturer;
  m_ManufacturerURL = UpnpFsmdaUtils::kFsmdaManufacturerUrl;
  device_service_ = new PLT_Service(this, UpnpFsmdaUtils::kActiveCcmServiceType,
                                    UpnpFsmdaUtils::kActiveCcmServiceId,
                                    UpnpFsmdaUtils::kActiveCcmServiceName);
  device_service_->SetSCPDXML(
      (const char*)UpnpFsmdaUtils::kActiveCcmServiceScpdXml);
}

/*----------------------------------------------------------------------
 |   UpnpActiveCcm::~UpnpActiveCcm
 +---------------------------------------------------------------------*/
UpnpActiveCcm::~UpnpActiveCcm() {
  StopCommunicationService();
  delete device_service_;
  ctrl_point_.Detach();
  device_host_.Detach();
}

/*----------------------------------------------------------------------
 |   UpnpActiveCcm::StartCommunicationService
 +---------------------------------------------------------------------*/
int UpnpActiveCcm::StartCommunicationService() {
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
 |   UpnpActiveCcm::StopCommunicationService
 +---------------------------------------------------------------------*/
int UpnpActiveCcm::StopCommunicationService() {
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
 |   UpnpActiveCcm::IsCommunicationServiceStarted
 +---------------------------------------------------------------------*/
bool UpnpActiveCcm::IsCommunicationServiceStarted() { return m_Started; }

/*----------------------------------------------------------------------
 |   UpnpActiveCcm::Prepare
 +---------------------------------------------------------------------*/
void UpnpActiveCcm::Prepare(const string& object_id, const string& object_src,
                            vector<Property> properties, vector<Event> evts) {}

/*----------------------------------------------------------------------
 |   UpnpActiveCcm::AddEvent
 +---------------------------------------------------------------------*/
void UpnpActiveCcm::AddEvent(const string& object_id, Event evt) {}

/*----------------------------------------------------------------------
 |   UpnpActiveCcm::RemoveEvent
 +---------------------------------------------------------------------*/
void UpnpActiveCcm::RemoveEvent(const string& object_id,
                                const string& event_id) {}

/*----------------------------------------------------------------------
 |   UpnpActiveCcm::PostAction
 +---------------------------------------------------------------------*/
void UpnpActiveCcm::PostAction(const string& object_id, const string& event_id,
                               const string& action) {}

/*----------------------------------------------------------------------
 |   UpnpActiveCcm::ReportPropertyValue
 +---------------------------------------------------------------------*/
void UpnpActiveCcm::ReportPropertyValue(const string& object_id,
                                        const string& name,
                                        const string& value) {}

/*----------------------------------------------------------------------
 |   UpnpActiveCcm::SetPropertyValue
 +---------------------------------------------------------------------*/
void UpnpActiveCcm::SetPropertyValue(const string& object_id,
                                     const string& name, const string& value,
                                     unsigned int duration) {}

/*----------------------------------------------------------------------
 |   UpnpActiveCcm::SetupServices
 +---------------------------------------------------------------------*/
NPT_Result UpnpActiveCcm::SetupServices() {}

/*----------------------------------------------------------------------
 |   UpnpActiveCcm::OnAction
 +---------------------------------------------------------------------*/
NPT_Result UpnpActiveCcm::OnAction(PLT_ActionReference& action,
                                   const PLT_HttpRequestContext& context) {}
/*----------------------------------------------------------------------
 |   UpnpActiveCcm::OnDeviceAdded
 +---------------------------------------------------------------------*/
NPT_Result UpnpActiveCcm::OnDeviceAdded(PLT_DeviceDataReference& device) {}

/*----------------------------------------------------------------------
 |   UpnpActiveCcm::OnDeviceRemoved
 +---------------------------------------------------------------------*/
NPT_Result UpnpActiveCcm::OnDeviceRemoved(PLT_DeviceDataReference& device) {}

/*----------------------------------------------------------------------
 |   UpnpActiveCcm::OnActionResponse
 +---------------------------------------------------------------------*/
NPT_Result UpnpActiveCcm::OnActionResponse(NPT_Result res,
                                           PLT_ActionReference& action,
                                           void* userdata) {}

/*----------------------------------------------------------------------
 |   UpnpActiveCcm::OnEventNotify
 +---------------------------------------------------------------------*/
NPT_Result UpnpActiveCcm::OnEventNotify(PLT_Service* service,
                                        NPT_List<PLT_StateVariable*>* vars) {}
