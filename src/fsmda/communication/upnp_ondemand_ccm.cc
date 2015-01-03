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
