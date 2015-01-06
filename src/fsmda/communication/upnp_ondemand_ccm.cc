/*----------------------------------------------------------------------
 |   include
 +---------------------------------------------------------------------*/

#include "fsmda/communication/upnp_ondemand_ccm.h"
#include "fsmda/utils/upnp_fsmda_utils.h"
#include "NptStrings.h"
#include "PltDeviceHost.h"
#include "PltFileMediaServer.h"
#include "PltUPnP.h"
#include <iostream>
#include <string>

using std::clog;
using std::endl;

/*----------------------------------------------------------------------
 |   UpnpOnDemandCcm::UpnpOnDemandCcm
 +---------------------------------------------------------------------*/
UpnpOnDemandCcm::UpnpOnDemandCcm()
    : ondemand_folder_("/tmp/fsmda/ondemand/"),
      uuid_("fsmda-0000"),
      service_start_(false),
      upnp_reference_(NULL) {}

/*----------------------------------------------------------------------
 |   UpnpOnDemandCcm::~UpnpOnDemandCcm
 +---------------------------------------------------------------------*/
UpnpOnDemandCcm::~UpnpOnDemandCcm() {
  if (upnp_reference_ != NULL)
    upnp_reference_ = UpnpFsmdaUtils::GetRunningInstance();
}

/*----------------------------------------------------------------------
 |   UpnpOnDemandCcm::~NotifyError
 +---------------------------------------------------------------------*/
void UpnpOnDemandCcm::NotifyError(const std::string& message,
                                  const std::string& object_id) {}

/*----------------------------------------------------------------------
 |   UpnpOnDemandCcm::Start
 +---------------------------------------------------------------------*/
int UpnpOnDemandCcm::StartCommunicationService() {
  if (upnp_reference_ == NULL)
    upnp_reference_ = UpnpFsmdaUtils::GetRunningInstance();

  clog << "OnDemandCCM::start_communication" << endl;
  PLT_DeviceHostReference device(new PLT_FileMediaServer(
      ondemand_folder_.c_str(), UpnpFsmdaUtils::kOnDemandCcmDeviceFriendlyName,
      true, uuid_.c_str()));
  device->m_ModelDescription =
      UpnpFsmdaUtils::kOnDemandCcmDeviceModelDescription;
  device->m_ModelURL = UpnpFsmdaUtils::kOnDemandCcmDeviceModelUrl;
  device->m_ModelNumber = UpnpFsmdaUtils::kOnDemandCcmDeviceModelNumber;
  device->m_ModelName = UpnpFsmdaUtils::kOnDemandCcmDeviceModelName;
  device->m_Manufacturer = UpnpFsmdaUtils::kFsmdaManufacturer;
  device->m_ManufacturerURL = UpnpFsmdaUtils::kFsmdaManufacturerUrl;
  upnp_reference_->AddDevice(device);
  service_start_ = true;
  return 0;
}

/*----------------------------------------------------------------------
 |   UpnpOnDemandCcm::Stop
 +---------------------------------------------------------------------*/
int UpnpOnDemandCcm::StopCommunicationService() {
  UpnpFsmdaUtils::ReleaseInstance();
  upnp_reference_ = NULL;
  service_start_ = false;
  return 0;
}
/*----------------------------------------------------------------------
 |   UpnpOnDemandCcm::IsCommunicationServiceStarted
 +---------------------------------------------------------------------*/
bool UpnpOnDemandCcm::IsCommunicationServiceStarted() { return service_start_; }

/*----------------------------------------------------------------------
 |   UpnpOnDemandCcm::SetupServices
 +---------------------------------------------------------------------*/
NPT_Result UpnpOnDemandCcm::SetupServices() {}

/*----------------------------------------------------------------------
 |   UpnpOnDemandCcm::OnAction
 +---------------------------------------------------------------------*/
NPT_Result UpnpOnDemandCcm::OnAction(PLT_ActionReference& action,
                                     const PLT_HttpRequestContext& context) {}
/*----------------------------------------------------------------------
 |   UpnpOnDemandCcm::OnDeviceAdded
 +---------------------------------------------------------------------*/
NPT_Result UpnpOnDemandCcm::OnDeviceAdded(PLT_DeviceDataReference& device) {}

/*----------------------------------------------------------------------
 |   UpnpOnDemandCcm::OnDeviceRemoved
 +---------------------------------------------------------------------*/
NPT_Result UpnpOnDemandCcm::OnDeviceRemoved(PLT_DeviceDataReference& device) {}

/*----------------------------------------------------------------------
 |   UpnpOnDemandCcm::OnActionResponse
 +---------------------------------------------------------------------*/
NPT_Result UpnpOnDemandCcm::OnActionResponse(NPT_Result res,
                                             PLT_ActionReference& action,
                                             void* userdata) {}

/*----------------------------------------------------------------------
 |   UpnpOnDemandCcm::OnEventNotify
 +---------------------------------------------------------------------*/
NPT_Result UpnpOnDemandCcm::OnEventNotify(PLT_Service* service,
                                          NPT_List<PLT_StateVariable*>* vars) {}
