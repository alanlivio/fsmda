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
    upnp_reference_ = UpnpFsmdaUtils::GetRunningUpnpInstance();
}

/*----------------------------------------------------------------------
 |   UpnpOnDemandCcm::StartCommunicationService
 +---------------------------------------------------------------------*/
int UpnpOnDemandCcm::StartCommunicationService() {
  if (upnp_reference_ == NULL)
    upnp_reference_ = UpnpFsmdaUtils::GetRunningUpnpInstance();

  clog << "OnDemandCCM::start_communication_service" << endl;
  PLT_DeviceHostReference device(
      new PLT_FileMediaServer(this->ondemand_folder_.c_str(),
                              UpnpFsmdaUtils::kOnDemandCcmDeviceFriendlyName,
                              true, this->uuid_.c_str()));
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
 |   UpnpOnDemandCcm::StopCommunicationService
 +---------------------------------------------------------------------*/
int UpnpOnDemandCcm::StopCommunicationService() {
  UpnpFsmdaUtils::ReleaseUpnpInstance();
  upnp_reference_ = NULL;
  service_start_ = false;
  return 0;
}
/*----------------------------------------------------------------------
 |   UpnpOnDemandCcm::IsServiceStartd
 +---------------------------------------------------------------------*/
bool UpnpOnDemandCcm::IsServiceStartd() { return service_start_; }
