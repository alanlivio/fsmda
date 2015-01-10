#include "fsmda/child_class_handler.h"
#include <iostream>
#include <string>
#include <NptConfig.h>
#include <NptResults.h>
#include <NptStrings.h>
#include <PltService.h>
#include <PltStateVariable.h>

using std::clog;
using std::cout;
using std::endl;
/*----------------------------------------------------------------------
 |   ChildClassHandler::ChildClassHandler
 +---------------------------------------------------------------------*/
ChildClassHandler::ChildClassHandler(
    const DeviceDescription& device_description)
    : upnp_cpm_(NULL), paired_(false) {
  device_description_ = new DeviceDescription(device_description);
  clog << "ChildClassHandler::ChildClassHandler(device_class_type="
       << device_description_->device_class_type() << ")" << endl;
  upnp_cpm_ = new UpnpCpm();
  upnp_cpm_->set_service_owner(this);
}

/*----------------------------------------------------------------------
 |   ChildClassHandler::~ChildClassHandler
 +---------------------------------------------------------------------*/
ChildClassHandler::~ChildClassHandler() {
  delete device_description_;
  delete upnp_cpm_;
}

/*----------------------------------------------------------------------
 |   ChildClassHandler::StartPairing
 +---------------------------------------------------------------------*/
int ChildClassHandler::StartPairing() {
  clog << "ChildClassHandler::StartPairing()" << endl;
  if (device_description_->pairing_method() ==
      DeviceClassDescription::kUpnpPairingProcotol) {
    return upnp_cpm_->StartPairingService();
  } else {
    return -1;
  }
}

/*----------------------------------------------------------------------
 |   ChildClassHandler::StopPairing
 +---------------------------------------------------------------------*/
int ChildClassHandler::StopPairing() {
  if (device_description_->pairing_method() ==
      DeviceClassDescription::kUpnpPairingProcotol) {
    return upnp_cpm_->StopPairingService();
  }
  return 0;
}

/*----------------------------------------------------------------------
 |  ChildClassHandler::CreatePassiveCcm
 +---------------------------------------------------------------------*/
PassiveClassInterface* ChildClassHandler::CreatePassiveCcm(
    const string& application_id, unsigned int class_index) {
  if (device_class_description_map_[class_index]->device_class_type() ==
      DeviceClassDescription::kPassiveDevice) {
    return upnp_cpm_->CreatePassiveCcm(application_id, class_index);
  }
}

/*----------------------------------------------------------------------
 |   ChildClassHandler::CreateActiveCc
 +---------------------------------------------------------------------*/
ActiveClassListenerInterface* ChildClassHandler::CreateActiveCcm(
    const string& application_id, unsigned int class_index) {
  if (device_class_description_map_[class_index]->device_class_type() ==
      DeviceClassDescription::kActiveDevice) {
    return upnp_cpm_->CreateActiveCcm(application_id, class_index);
  }
}

/*----------------------------------------------------------------------
 |   ChildClassHandler::CreateOndemandCcm
 +---------------------------------------------------------------------*/
OnDemandClassInterface* ChildClassHandler::CreateOndemandCcm(
    const string& application_id, unsigned int class_index) {
  if (device_class_description_map_[class_index]->device_class_type() ==
      DeviceClassDescription::kOnDemandDevice) {
    return upnp_cpm_->CreateOnDemandCcm(application_id, class_index);
  }
}

/*----------------------------------------------------------------------
 |   ChildClassHandler::CreateMediaCaptureCcm
 +---------------------------------------------------------------------*/
MediaCaptureClassInterface* ChildClassHandler::CreateMediaCaptureCcm(
    const string& application_id, unsigned int class_index) {
  if (device_class_description_map_[class_index]->device_class_type() ==
      DeviceClassDescription::kMediaCaptureDevice) {
    return upnp_cpm_->CreateMediaCaptureCcm(application_id, class_index);
  }
}

/*----------------------------------------------------------------------
 |   ChildClassHandler::pairing_started
 +---------------------------------------------------------------------*/
bool ChildClassHandler::IsPairingStarted() {
  if (device_description_->pairing_method() ==
      DeviceClassDescription::kUpnpPairingProcotol) {
    return upnp_cpm_->IsPairingServiceStarted();
  } else {
    return false;
  }
}

/*----------------------------------------------------------------------
 |   ChildClassHandler::paired
 +---------------------------------------------------------------------*/
bool ChildClassHandler::paired() {
  if (device_description_->pairing_method() ==
      DeviceClassDescription::kUpnpPairingProcotol) {
    return paired_;
  } else {
    return false;
  }
}

/*----------------------------------------------------------------------
 |   ChildClassHandler::set_paired
 +---------------------------------------------------------------------*/
void ChildClassHandler::set_paired(bool paired) { paired_ = paired; }

/*----------------------------------------------------------------------
 |   ChildClassHandler::device_description
 +---------------------------------------------------------------------*/
DeviceDescription* ChildClassHandler::device_description() {
  return device_description_;
}
