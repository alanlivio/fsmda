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

ActiveCcmInterface*
ChildParingManager::createActiveCcm(unsigned int classIndex) {
  if (map_classDescription_[classIndex]->classType_
      == DeviceClassDescription::kFsmdaActiveDevice)
    return new UpnpActiveCcm();
  else
    return NULL;
}
MediaCaptureCcmInterface*
ChildParingManager::createMediaCaptureCcm(unsigned int classIndex) {
  if (map_classDescription_[classIndex]->classType_
      == DeviceClassDescription::kFsmdaMediaCaptureDevice)
    return new UpnpMediaCaptureCcm();
  else
    return NULL;
}

PassiveCcmInterface*
ChildParingManager::createPassiveCcm(unsigned int classIndex) {
  if (map_classDescription_[classIndex]->classType_
      == DeviceClassDescription::kFsmdaPassiveDevice)
    return new UpnpPassiveCcm();
  else
    return NULL;
}

void ChildParingManager::classAnnouncement(const string& applicationID,
                                           unsigned int classIndex,
                                           const string& classDesc,
                                           const string& classFunction) {

}

