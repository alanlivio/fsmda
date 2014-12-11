#include <string>
#include <climits>
#include "fsmda/communication/model/passive_object_interfaces.h"
#include "fsmda/communication/upnp_active_pcm.h"
#include "fsmda/communication/upnp_mediacapture_pcm.h"
#include "fsmda/communication/upnp_ondemand_pcm.h"
#include "fsmda/communication/upnp_passive_pcm.h"
#include "fsmda/paring/upnp_parent_paring.h"
#include "fsmda/paring/device_class_description.h"
#include "fsmda/paring/parent_paring_manager.h"

ParentParingManager::ParentParingManager()
    : upnp_parent_paring_(NULL), registred_classes_size_(0) {}

ParentParingManager::~ParentParingManager() {
  if (upnp_parent_paring_ != NULL) delete upnp_parent_paring_;
}

/*----------------------------------------------------------------------
 |   ParentParingManager::AddClass
 +---------------------------------------------------------------------*/
void ParentParingManager::AddClass(const string& application_id,
                                   unsigned int class_index) {
  DeviceClassDescription* device_class_description =
      new DeviceClassDescription();
  device_class_description->InitializeByDeviceClass(
      DeviceClassDescription::kFsmdaActiveDevice);
  device_class_description_map_[application_id][class_index] =
      device_class_description;
  StartParingService(device_class_description);
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
  device_class_description_map_[application_id][class_index] =
      device_class_description;
  // TODO(alan@telemidia.puc-rio.br): Start UpnpParing Service.
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
    const string& application_id, unsigned int class_index) {
  if (device_class_description_map_[application_id][class_index]
          ->device_class_type() == DeviceClassDescription::kFsmdaActiveDevice)
    return new UpnpActivePcm();
  else
    return NULL;
}

/*----------------------------------------------------------------------
 |   ParentParingManager::CreateActivePcm
 +---------------------------------------------------------------------*/
MediaCapturePcmInterface* ParentParingManager::CreateMediaCapturePcm(
    const string& application_id, unsigned int class_index) {
  if (device_class_description_map_[application_id][class_index]
          ->device_class_type() ==
      DeviceClassDescription::kFsmdaMediaCaptureDevice)
    return new UpnpMediaCapturePcm();
  else
    return NULL;
}

/*----------------------------------------------------------------------
 |   ParentParingManager::CreateOnDemandPcm
 +---------------------------------------------------------------------*/
OnDemandPcmInterface* ParentParingManager::CreateOnDemandPcm(
    const string& application_id, unsigned int class_index) {
  if (device_class_description_map_[application_id][class_index]
          ->device_class_type() == DeviceClassDescription::kFsmdaOnDemandDevice)
    return new UpnpOnDemandPcm();
  else
    return NULL;
}

/*----------------------------------------------------------------------
 |   ParentParingManager::CreatePassivePcm
 +---------------------------------------------------------------------*/
PassivePcmInterface* ParentParingManager::CreatePassivePcm(
    const string& application_id, unsigned int class_index) {
  if (device_class_description_map_[application_id][class_index]
          ->device_class_type() == DeviceClassDescription::kFsmdaPassiveDevice)
    return new UpnpPassivePcm();
  else
    return NULL;
}

/*----------------------------------------------------------------------
 |   ParentParingManager::GenerateAvaliableIndex
 +---------------------------------------------------------------------*/
unsigned int ParentParingManager::GenerateAvaliableIndex(
    const string& application_id) {
  for (int i = 0; i < UINT_MAX; i++) {
    if (device_class_description_map_[application_id].find(i) ==
        device_class_description_map_[application_id].end())
      return i;
  }
}

/*----------------------------------------------------------------------
 |   ParentParingManager::GetNumberOfRegistredClasses
 +---------------------------------------------------------------------*/
unsigned int ParentParingManager::GetNumberOfRegistredClasses(
    const string& application_id) {
  return device_class_description_map_.size();
}

/*----------------------------------------------------------------------
 |   ParentParingManager::StartParingByDeviceClassDescription
 +---------------------------------------------------------------------*/
int ParentParingManager::StartParingService(
    DeviceClassDescription* device_class_description) {

  if (device_class_description->paring_protocol() ==
      DeviceClassDescription::kUpnpParingProcotol) {
    if (upnp_parent_paring_ == NULL) {
      upnp_parent_paring_ = new UpnpParentParing();
      upnp_parent_paring_->SetParentParingManager(this);
      upnp_parent_paring_->StartService();
      return 0;
    }
  } else {
    return -1;
  }
}
/*----------------------------------------------------------------------
 |   ParentParingManager::StopParingService
 +---------------------------------------------------------------------*/
int ParentParingManager::StopParingService(
    DeviceClassDescription* device_class_description) {
  if (upnp_parent_paring_ != NULL) {
    upnp_parent_paring_->StopService();
    return 0;
  }
}
