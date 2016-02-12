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

ChildClassHandler::ChildClassHandler(
    const DeviceDescription& device_description)
    : upnp_cpm_(NULL), paired_(false) {
  device_description_ = new DeviceDescription(device_description);
  clog << "ChildClassHandler::ChildClassHandler(device_class_type="
       << device_description_->device_class_type() << ")" << endl;
  upnp_cpm_ = new UpnpCpm();
  upnp_cpm_->set_service_owner(this);
  passive_player_      = NULL;
  active_player_       = NULL;
  ondemand_player_     = NULL;
  mediacapture_player_ = NULL;
}

ChildClassHandler::~ChildClassHandler() {
  delete device_description_;
  delete upnp_cpm_;
}

int ChildClassHandler::StartPairing() {
  clog << "ChildClassHandler::StartPairing()" << endl;
  if (device_description_->pairing_method() ==
      DeviceClassDescription::kUpnpPairingProcotol) {
    return upnp_cpm_->StartPairingService();
  } else {
    return -1;
  }
}

int ChildClassHandler::StopPairing() {
  if (device_description_->pairing_method() ==
      DeviceClassDescription::kUpnpPairingProcotol) {
    return upnp_cpm_->StopPairingService();
  }
  return 0;
}

bool ChildClassHandler::IsPairingStarted() {
  if (device_description_->pairing_method() ==
      DeviceClassDescription::kUpnpPairingProcotol) {
    return upnp_cpm_->IsPairingServiceStarted();
  } else {
    return false;
  }
}

bool ChildClassHandler::paired() { return paired_; }

void ChildClassHandler::set_paired(bool paired) { paired_ = paired; }

DeviceDescription* ChildClassHandler::device_description() {
  return device_description_;
}

void ChildClassHandler::set_active_player(ActivePlayerInterface* player) {
  active_player_ = player;
}

void ChildClassHandler::set_passive_player(PassiveClassInterface* player) {
  passive_player_ = player;
}

void ChildClassHandler::set_ondemand_player(OnDemandClassInterface* player) {
  ondemand_player_ = player;
}

void ChildClassHandler::set_mediacapture_player(
    MediaCaptureClassInterface* player) {
  mediacapture_player_ = player;
}

PassiveClassInterface* ChildClassHandler::passive_player() {
  return passive_player_;
}

ActivePlayerInterface* ChildClassHandler::active_player() {
  return active_player_;
}

OnDemandClassInterface* ChildClassHandler::ondemand_player() {
  return ondemand_player_;
}

MediaCaptureClassInterface* ChildClassHandler::mediacapture_player() {
  return mediacapture_player_;
}
