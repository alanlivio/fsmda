#include "fsmda/communication/model/passive_object_interfaces.h"
#include "fsmda/communication/upnp_active_pcm.h"
#include "fsmda/communication/upnp_mediacapture_pcm.h"
#include "fsmda/communication/upnp_ondemand_pcm.h"
#include "fsmda/communication/upnp_passive_pcm.h"
#include "fsmda/paring/device_class_description.h"
#include "fsmda/paring/parent_paring_manager.h"
#include <string>
#include <climits>

ParentParingManager::ParentParingManager() {}

ParentParingManager::~ParentParingManager() {}

/*----------------------------------------------------------------------
 |   ParentParingManager::AddClass
 +---------------------------------------------------------------------*/
void ParentParingManager::AddClass(const string& application_id,
                                   unsigned int class_index) {
  DeviceClassDescription* device_class_description =
      new DeviceClassDescription();
  device_class_description->InitializeByDeviceClass(
      DeviceClassDescription::kFsmdaActiveDevice);
  device_class_description_map_[class_index] = device_class_description;
}
/*----------------------------------------------------------------------
 |   ParentParingManager::RemoveClass
 +---------------------------------------------------------------------*/
void ParentParingManager::RemoveClass(const string& application_id,
                                      unsigned int class_index) {}
/*----------------------------------------------------------------------
 |   ParentParingManager::AddClassDescription
 +---------------------------------------------------------------------*/
void ParentParingManager::AddClassDescription(
    const string& application_id, unsigned int class_index,
    const string& class_type, unsigned int max_devices,
    unsigned int min_devices, const string& hardware_requirements,
    const string& software_requirements, const string& network_requirements) {
  DeviceClassDescription* device_class_description =
      new DeviceClassDescription();
  device_class_description->InitializeByDeviceClass(
      DeviceClassDescription::GetDeviceClassTypeByString(class_type));
  device_class_description_map_[class_index] = device_class_description;
}

/*----------------------------------------------------------------------
 |   ParentParingManager::AddDeviceToClass
 +---------------------------------------------------------------------*/
void ParentParingManager::AddDeviceToClass(const string& application_id,
                                           const string& device_address,
                                           unsigned int class_index,
                                           const string& device_desc) {}
/*----------------------------------------------------------------------
 |   ParentParingManager::GetChildIndex
 +---------------------------------------------------------------------*/
void ParentParingManager::GetChildIndex(const string& application_id,
                                        const string& device_address,
                                        unsigned int class_index) {}

/*----------------------------------------------------------------------
 |   ParentParingManager::CreateActivePcm
 +---------------------------------------------------------------------*/
ActivePcmInterface* ParentParingManager::CreateActivePcm(
    unsigned int class_index) {
  if (device_class_description_map_[class_index]->device_class_type_ ==
      DeviceClassDescription::kFsmdaActiveDevice)
    return new UpnpActivePcm();
  else
    return NULL;
}

/*----------------------------------------------------------------------
 |   ParentParingManager::CreateActivePcm
 +---------------------------------------------------------------------*/
MediaCapturePcmInterface* ParentParingManager::CreateMediaCapturePcm(
    unsigned int class_index) {
  if (device_class_description_map_[class_index]->device_class_type_ ==
      DeviceClassDescription::kFsmdaMediaCaptureDevice)
    return new UpnpMediaCapturePcm();
  else
    return NULL;
}

/*----------------------------------------------------------------------
 |   ParentParingManager::CreateOnDemandPcm
 +---------------------------------------------------------------------*/
OnDemandPcmInterface* ParentParingManager::CreateOnDemandPcm(
    unsigned int class_index) {
  if (device_class_description_map_[class_index]->device_class_type_ ==
      DeviceClassDescription::kFsmdaOnDemandDevice)
    return new UpnpOnDemandPcm();
  else
    return NULL;
}

/*----------------------------------------------------------------------
 |   ParentParingManager::CreatePassivePcm
 +---------------------------------------------------------------------*/
PassivePcmInterface* ParentParingManager::CreatePassivePcm(
    unsigned int class_index) {
  if (device_class_description_map_[class_index]->device_class_type_ ==
      DeviceClassDescription::kFsmdaPassiveDevice)
    return new UpnpPassivePcm();
  else
    return NULL;
}

/*----------------------------------------------------------------------
 |   ParentParingManager::CreatePassivePcm
 +---------------------------------------------------------------------*/
unsigned int ParentParingManager::GenerateAvaliableIndex() {
  for (int i = 0; i < UINT_MAX; i++) {
    if (device_class_description_map_.find(i) ==
        device_class_description_map_.end())
      return i;
  }
}

/*----------------------------------------------------------------------
 |   ParentParingManager::CreatePassivePcm
 +---------------------------------------------------------------------*/
unsigned int ParentParingManager::GetNumberOfRegistredClasses() {
  return device_class_description_map_.size();
}
