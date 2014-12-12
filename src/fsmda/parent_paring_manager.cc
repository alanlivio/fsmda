#include <string>
#include <climits>
#include <iostream>
#include "fsmda/communication_services/upnp_active_pcm.h"
#include "fsmda/communication_services/upnp_mediacapture_pcm.h"
#include "fsmda/communication_services/upnp_ondemand_pcm.h"
#include "fsmda/communication_services/upnp_passive_pcm.h"
#include "fsmda/model/passive_object_interfaces.h"
#include "fsmda/paring_services/upnp_parent_paring.h"
#include "fsmda/device_class_description.h"
#include "fsmda/parent_paring_manager.h"

using std::clog;
using std::endl;

ParentParingManager::ParentParingManager()
    : upnp_parent_paring_(NULL), upnp_registred_classes_size(0) {}

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
      DeviceClassDescription::kActiveDevice);
  AddClassDescription(application_id, class_index, device_class_description);
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
  // TODO(alanlivio@gmail.com): change  to Initialize passing paremeters
  AddClassDescription(application_id, class_index, device_class_description);
}

/*----------------------------------------------------------------------
 |   ParentParingManager::AddClassDescription
 +---------------------------------------------------------------------*/
void ParentParingManager::AddClassDescription(
    const std::string& application_id, unsigned int class_index,
    DeviceClassDescription* device_class_description) {
  device_class_description_map_[application_id][class_index] =
      device_class_description;
  if (device_class_description->paring_protocol() ==
      DeviceClassDescription::kUpnpParingProcotol) {
    upnp_registred_classes_size++;
  }
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
 |   ParentParingManager::StartParing
 +---------------------------------------------------------------------*/
int ParentParingManager::StartParing() {
  clog << "ParentParingManager::StartParing()" << endl;
  if (upnp_registred_classes_size > 0) {
    if (upnp_parent_paring_ == NULL)
      upnp_parent_paring_ = new UpnpParentParing(this);
    return upnp_parent_paring_->StartParingService();
  } else {
    return -1;
  }
}

/*----------------------------------------------------------------------
 |   ParentParingManager::StopParing
 +---------------------------------------------------------------------*/
int ParentParingManager::StopParing() {
  if (upnp_parent_paring_ != NULL) {
    return upnp_parent_paring_->StopParingService();
  }
  return 0;
}

/*----------------------------------------------------------------------
 |   ParentParingManager::IsParingStarted
 +---------------------------------------------------------------------*/
bool ParentParingManager::IsParingStarted() {
  if (upnp_parent_paring_ != NULL) {
    return upnp_parent_paring_->IsParingServiceStarted();
  } else {
    return false;
  }
}

/*----------------------------------------------------------------------
 |   ParentParingManager::CreateActivePcm
 +---------------------------------------------------------------------*/
ActivePcmInterface* ParentParingManager::CreateActivePcm(
    const string& application_id, unsigned int class_index) {
  if (device_class_description_map_[application_id][class_index]
          ->device_class_type() == DeviceClassDescription::kActiveDevice)
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
      DeviceClassDescription::kMediaCaptureDevice)
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
          ->device_class_type() == DeviceClassDescription::kOnDemandDevice)
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
          ->device_class_type() == DeviceClassDescription::kPassiveDevice)
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
 |   ParentParingManager::GetRegistredClassesSize
 +---------------------------------------------------------------------*/
unsigned int ParentParingManager::GetRegistredClassesSize(
    const string& application_id) {
  return device_class_description_map_[application_id].size();
}
