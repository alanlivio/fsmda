#include <string>
#include <iostream>
#include "fsmda/communication_services/upnp_active_ccm.h"
#include "fsmda/communication_services/upnp_mediacapture_ccm.h"
#include "fsmda/communication_services/upnp_ondemand_ccm.h"
#include "fsmda/communication_services/upnp_passive_ccm.h"
#include "fsmda/model/passive_object_interfaces.h"
#include "fsmda/child_paring_manager.h"
#include "fsmda/device_description.h"
#include "fsmda/device_class_description.h"

using std::clog;
using std::endl;
/*----------------------------------------------------------------------
 |   ChildParingManager::ChildParingManager
 +---------------------------------------------------------------------*/
ChildParingManager::ChildParingManager(
    const DeviceDescription& device_description)
    : upnp_child_paring_(NULL) {

  device_description_ = new DeviceDescription(device_description);
}

/*----------------------------------------------------------------------
 |   ChildParingManager::~ChildParingManager
 +---------------------------------------------------------------------*/
ChildParingManager::~ChildParingManager() {
  if (upnp_child_paring_ != NULL) delete upnp_child_paring_;
  delete device_description_;
}

/*----------------------------------------------------------------------
 |   ChildParingManager::StartParing
 +---------------------------------------------------------------------*/
int ChildParingManager::StartParing() {
  clog << "ChildParingManager::StartParing()::" << endl;
  if (device_description_->paring_method() ==
      DeviceClassDescription::kUpnpParingProcotol) {
    if (upnp_child_paring_ == NULL) {
      upnp_child_paring_ = new UpnpChildParing(this);
    }
    return upnp_child_paring_->StartParingService();
  } else {
    return -1;
  }
}

/*----------------------------------------------------------------------
 |   ChildParingManager::StopParing
 +---------------------------------------------------------------------*/
int ChildParingManager::StopParing() {
  if (upnp_child_paring_ != NULL &&
      device_description_->paring_method() ==
          DeviceClassDescription::kUpnpParingProcotol) {
    return upnp_child_paring_->StopParingService();
  }
  return 0;
}

/*----------------------------------------------------------------------
 |   ChildParingManager::IsParingStarted
 +---------------------------------------------------------------------*/
bool ChildParingManager::IsParingStarted() {
  if (upnp_child_paring_ != NULL &&
      device_description_->paring_method() ==
          DeviceClassDescription::kUpnpParingProcotol) {
    return upnp_child_paring_->IsParingServiceStarted();
  } else {
    return false;
  }
}

/*----------------------------------------------------------------------
 |   ChildParingManager::ClassAnnouncement
 +---------------------------------------------------------------------*/
void ChildParingManager::ClassAnnouncement(const string& application_id,
                                           unsigned int class_index,
                                           const string& class_desc,
                                           const string& class_function) {}
/*----------------------------------------------------------------------
 |   ChildParingManager::CreateActiveCc
 +---------------------------------------------------------------------*/
ActiveCcmInterface* ChildParingManager::CreateActiveCcm(
    unsigned int class_index) {
  if (device_class_description_map_[class_index]->device_class_type() ==
      DeviceClassDescription::kFsmdaActiveDevice)
    return new UpnpActiveCcm();
  else
    return NULL;
}

/*----------------------------------------------------------------------
 |  ChildParingManager::CreatePassiveCcm
 +---------------------------------------------------------------------*/
PassiveCcmInterface* ChildParingManager::CreatePassiveCcm(
    unsigned int class_index) {
  if (device_class_description_map_[class_index]->device_class_type() ==
      DeviceClassDescription::kFsmdaPassiveDevice)
    return new UpnpPassiveCcm();
  else
    return NULL;
}

/*----------------------------------------------------------------------
 |   ChildParingManager::CreateOndemandCcm
 +---------------------------------------------------------------------*/
OnDemandCcmInterface* ChildParingManager::CreateOndemandCcm(
    unsigned int class_index) {
  if (device_class_description_map_[class_index]->device_class_type() ==
      DeviceClassDescription::kFsmdaOnDemandDevice)
    return new UpnpOnDemandCcm();
  else
    return NULL;
}

/*----------------------------------------------------------------------
 |   ChildParingManager::CreateMediaCaptureCcm
 +---------------------------------------------------------------------*/
MediaCaptureCcmInterface* ChildParingManager::CreateMediaCaptureCcm(
    unsigned int class_index) {
  if (device_class_description_map_[class_index]->device_class_type() ==
      DeviceClassDescription::kFsmdaMediaCaptureDevice)
    return new UpnpMediaCaptureCcm();
  else
    return NULL;
}
