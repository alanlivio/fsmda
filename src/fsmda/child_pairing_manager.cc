#include "fsmda/child_pairing_manager.h"
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
 |   ChildPairingManager::ChildPairingManager
 +---------------------------------------------------------------------*/
ChildPairingManager::ChildPairingManager(
    const DeviceDescription& device_description)
    : upnp_child_pairing_(NULL), paired_(false) {
  device_description_ = new DeviceDescription(device_description);
  clog << "ChildPairingManager::ChildPairingManager(device_class_type="
       << device_description_->device_class_type() << ")" << endl;
  upnp_child_pairing_ = new UpnpChildPairing();
  upnp_child_pairing_->set_service_owner(this);
}

/*----------------------------------------------------------------------
 |   ChildPairingManager::~ChildPairingManager
 +---------------------------------------------------------------------*/
ChildPairingManager::~ChildPairingManager() {
  delete device_description_;
  delete upnp_child_pairing_;
}

/*----------------------------------------------------------------------
 |   ChildPairingManager::StartPairing
 +---------------------------------------------------------------------*/
int ChildPairingManager::StartPairing() {
  clog << "ChildPairingManager::StartPairing()" << endl;
  if (device_description_->pairing_method() ==
      DeviceClassDescription::kUpnpPairingProcotol) {
    return upnp_child_pairing_->StartPairingService();
  } else {
    return -1;
  }
}

/*----------------------------------------------------------------------
 |   ChildPairingManager::StopPairing
 +---------------------------------------------------------------------*/
int ChildPairingManager::StopPairing() {
  if (device_description_->pairing_method() ==
      DeviceClassDescription::kUpnpPairingProcotol) {
    return upnp_child_pairing_->StopPairingService();
  }
  return 0;
}

/*----------------------------------------------------------------------
 |   ChildPairingManager::ClassAnnouncement
 +---------------------------------------------------------------------*/
void ChildPairingManager::ClassAnnouncement(const string& application_id,
                                            unsigned int class_index,
                                            const string& class_desc,
                                            const string& class_function) {
  clog << "ChildPairingManager::ClassAnnouncement" << endl;
  DeviceClassDescription device_class_description;
  device_class_description.InitializeByRdfContent(class_desc.c_str());
  bool paired =
      device_class_description.IsDeviceCompatible(device_description_);
  //  set_paired(paired);
  upnp_child_pairing_->AddDeviceToClass(application_id, "locahost", class_index,
                                        class_desc);
}

/*----------------------------------------------------------------------
 |  ChildPairingManager::CreatePassiveCcm
 +---------------------------------------------------------------------*/
PassiveClassInterface* ChildPairingManager::CreatePassiveCcm(
    const string& application_id, unsigned int class_index) {
  if (device_class_description_map_[class_index]->device_class_type() ==
      DeviceClassDescription::kPassiveDevice) {
    return upnp_child_pairing_->CreatePassiveCcm(application_id, class_index);
  }
}

/*----------------------------------------------------------------------
 |   ChildPairingManager::CreateActiveCc
 +---------------------------------------------------------------------*/
ActiveClassInterface* ChildPairingManager::CreateActiveCcm(
    const string& application_id, unsigned int class_index) {
  if (device_class_description_map_[class_index]->device_class_type() ==
      DeviceClassDescription::kActiveDevice) {
    return upnp_child_pairing_->CreateActiveCcm(application_id, class_index);
  }
}

/*----------------------------------------------------------------------
 |   ChildPairingManager::CreateOndemandCcm
 +---------------------------------------------------------------------*/
OnDemandClassInterface* ChildPairingManager::CreateOndemandCcm(
    const string& application_id, unsigned int class_index) {
  if (device_class_description_map_[class_index]->device_class_type() ==
      DeviceClassDescription::kOnDemandDevice) {
    return upnp_child_pairing_->CreateOnDemandCcm(application_id, class_index);
  }
}

/*----------------------------------------------------------------------
 |   ChildPairingManager::CreateMediaCaptureCcm
 +---------------------------------------------------------------------*/
MediaCaptureClassInterface* ChildPairingManager::CreateMediaCaptureCcm(
    const string& application_id, unsigned int class_index) {
  if (device_class_description_map_[class_index]->device_class_type() ==
      DeviceClassDescription::kMediaCaptureDevice) {
    return upnp_child_pairing_->CreateMediaCaptureCcm(application_id,
                                                      class_index);
  }
}

/*----------------------------------------------------------------------
 |   ChildPairingManager::pairing_started
 +---------------------------------------------------------------------*/
bool ChildPairingManager::IsPairingStarted() {
  if (device_description_->pairing_method() ==
      DeviceClassDescription::kUpnpPairingProcotol) {
    return upnp_child_pairing_->IsPairingServiceStarted();
  } else {
    return false;
  }
}

/*----------------------------------------------------------------------
 |   ChildPairingManager::paired
 +---------------------------------------------------------------------*/
bool ChildPairingManager::paired() {
  if (device_description_->pairing_method() ==
      DeviceClassDescription::kUpnpPairingProcotol) {
    return paired_;
  } else {
    return false;
  }
}

/*----------------------------------------------------------------------
 |   ChildPairingManager::set_paired
 +---------------------------------------------------------------------*/
void ChildPairingManager::set_paired(bool paired) { paired_ = paired; }

/*----------------------------------------------------------------------
 |   ChildPairingManager::device_description
 +---------------------------------------------------------------------*/
DeviceDescription* ChildPairingManager::device_description() {
  return device_description_;
}
