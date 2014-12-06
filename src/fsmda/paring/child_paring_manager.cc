#include "fsmda/communication/model/passive_object_interfaces.h"
#include "fsmda/communication/upnp_active_ccm.h"
#include "fsmda/communication/upnp_mediacapture_ccm.h"
#include "fsmda/communication/upnp_passive_ccm.h"
#include "fsmda/paring/child_paring_manager.h"
#include "fsmda/paring/device_class_description.h"
#include <string>

ChildParingManager::ChildParingManager() {
}

ChildParingManager::~ChildParingManager() {
}

/*----------------------------------------------------------------------
 |   ChildParingManager::CreateActiveCc
 +---------------------------------------------------------------------*/
ActiveCcmInterface* ChildParingManager::CreateActiveCcm(
    unsigned int class_index) {
  if (map_classDescription_[class_index]->classType_
      == DeviceClassDescription::kFsmdaActiveDevice)
    return new UpnpActiveCcm();
  else
    return NULL;
}

/*----------------------------------------------------------------------
 |   ChildParingManager::CreateMediaCaptureCcm
 +---------------------------------------------------------------------*/
MediaCaptureCcmInterface* ChildParingManager::CreateMediaCaptureCcm(
    unsigned int class_index) {
  if (map_classDescription_[class_index]->classType_
      == DeviceClassDescription::kFsmdaMediaCaptureDevice)
    return new UpnpMediaCaptureCcm();
  else
    return NULL;
}

/*----------------------------------------------------------------------
 |  ChildParingManager::CreatePassiveCcm
 +---------------------------------------------------------------------*/
PassiveCcmInterface* ChildParingManager::CreatePassiveCcm(
    unsigned int class_index) {
  if (map_classDescription_[class_index]->classType_
      == DeviceClassDescription::kFsmdaPassiveDevice)
    return new UpnpPassiveCcm();
  else
    return NULL;
}

void ChildParingManager::ClassAnnouncement(const string& application_id,
                                           unsigned int class_index,
                                           const string& class_desc,
                                           const string& class_function) {
}