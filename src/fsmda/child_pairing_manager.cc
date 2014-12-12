#include "fsmda/child_pairing_manager.h"
#include <iostream>
#include <string>
#include <NptConfig.h>
#include <NptResults.h>
#include <NptStrings.h>
#include <PltService.h>
#include <PltStateVariable.h>

using std::clog;
using std::endl;
/*----------------------------------------------------------------------
 |   ChildPairingManager::ChildPairingManager
 +---------------------------------------------------------------------*/
ChildPairingManager::ChildPairingManager(DeviceDescription* device_description)
    : upnp_child_pairing_(NULL) {

  device_description_ = device_description;
}

/*----------------------------------------------------------------------
 |   ChildPairingManager::~ChildPairingManager
 +---------------------------------------------------------------------*/
ChildPairingManager::~ChildPairingManager() {
  if (upnp_child_pairing_ != NULL) delete upnp_child_pairing_;
  delete device_description_;
}

/*----------------------------------------------------------------------
 |   ChildPairingManager::StartPairing
 +---------------------------------------------------------------------*/
int ChildPairingManager::StartPairing() {
  clog << "ChildPairingManager::StartPairing()" << endl;
  if (device_description_->pairing_method() ==
      DeviceClassDescription::kUpnpPairingProcotol) {
    if (upnp_child_pairing_ == NULL) {
      upnp_child_pairing_ = new UpnpChildPairing();
      upnp_child_pairing_->SetServiceOwner(this);
    }
    return upnp_child_pairing_->StartPairingService();
  } else {
    return -1;
  }
}

/*----------------------------------------------------------------------
 |   ChildPairingManager::StopPairing
 +---------------------------------------------------------------------*/
int ChildPairingManager::StopPairing() {
  if (upnp_child_pairing_ != NULL &&
      device_description_->pairing_method() ==
          DeviceClassDescription::kUpnpPairingProcotol) {
    return upnp_child_pairing_->StopPairingService();
  }
  return 0;
}

/*----------------------------------------------------------------------
 |   ChildPairingManager::IsPairingStarted
 +---------------------------------------------------------------------*/
bool ChildPairingManager::IsPairingStarted() {
  if (upnp_child_pairing_ != NULL &&
      device_description_->pairing_method() ==
          DeviceClassDescription::kUpnpPairingProcotol) {
    return upnp_child_pairing_->IsPairingServiceStarted();
  } else {
    return false;
  }
}

bool ChildPairingManager::IsPaired() {
  if (upnp_child_pairing_ != NULL &&
      device_description_->pairing_method() ==
          DeviceClassDescription::kUpnpPairingProcotol) {
    return upnp_child_pairing_->PerformedHandShake();
  } else {
    return false;
  }
}

/*----------------------------------------------------------------------
 |   ChildPairingManager::ClassAnnouncement
 +---------------------------------------------------------------------*/
void ChildPairingManager::ClassAnnouncement(const string& application_id,
                                            unsigned int class_index,
                                            const string& class_desc,
                                            const string& class_function) {}
/*----------------------------------------------------------------------
 |   ChildPairingManager::CreateActiveCc
 +---------------------------------------------------------------------*/
ActiveCcmInterface* ChildPairingManager::CreateActiveCcm(
    unsigned int class_index) {
  if (device_class_description_map_[class_index]->device_class_type() ==
      DeviceClassDescription::kActiveDevice)
    return new UpnpActiveCcm();
  else
    return NULL;
}

/*----------------------------------------------------------------------
 |  ChildPairingManager::CreatePassiveCcm
 +---------------------------------------------------------------------*/
PassiveCcmInterface* ChildPairingManager::CreatePassiveCcm(
    unsigned int class_index) {
  if (device_class_description_map_[class_index]->device_class_type() ==
      DeviceClassDescription::kPassiveDevice)
    return new UpnpPassiveCcm();
  else
    return NULL;
}

/*----------------------------------------------------------------------
 |   ChildPairingManager::CreateOndemandCcm
 +---------------------------------------------------------------------*/
OnDemandCcmInterface* ChildPairingManager::CreateOndemandCcm(
    unsigned int class_index) {
  if (device_class_description_map_[class_index]->device_class_type() ==
      DeviceClassDescription::kOnDemandDevice)
    return new UpnpOnDemandCcm();
  else
    return NULL;
}

/*----------------------------------------------------------------------
 |   ChildPairingManager::CreateMediaCaptureCcm
 +---------------------------------------------------------------------*/
MediaCaptureCcmInterface* ChildPairingManager::CreateMediaCaptureCcm(
    unsigned int class_index) {
  if (device_class_description_map_[class_index]->device_class_type() ==
      DeviceClassDescription::kMediaCaptureDevice)
    return new UpnpMediaCaptureCcm();
  else
    return NULL;
}
