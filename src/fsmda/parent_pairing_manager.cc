#include <string>
#include <climits>
#include <iostream>
#include "fsmda/device_class_description.h"
#include "fsmda/parent_pairing_manager.h"
#include "fsmda/communication_services/upnp_active_pcm.h"
#include "fsmda/communication_services/upnp_mediacapture_pcm.h"
#include "fsmda/communication_services/upnp_ondemand_pcm.h"
#include "fsmda/communication_services/upnp_passive_pcm.h"
#include "fsmda/model/passive_object_interfaces.h"
#include "fsmda/pairing_services/upnp_parent_pairing.h"

using std::clog;
using std::endl;

ParentPairingManager::ParentPairingManager()
    : upnp_parent_pairing_(NULL), upnp_registred_classes_size(0) {}

ParentPairingManager::~ParentPairingManager() {
  if (upnp_parent_pairing_ != NULL) delete upnp_parent_pairing_;
  // TODO(alan@telemidia.puc-rio.br): delete  device_class_description_map_
  // content
}

/*----------------------------------------------------------------------
 |   ParentPairingManager::AddClass
 +---------------------------------------------------------------------*/
void ParentPairingManager::AddClass(const string& application_id,
                                    unsigned int class_index) {
  DeviceClassDescription* device_class_description =
      new DeviceClassDescription();
  device_class_description->InitializeByDeviceClass(
      DeviceClassDescription::kActiveDevice);
  AddClassDescription(application_id, class_index, device_class_description);
}

/*----------------------------------------------------------------------
 |   ParentPairingManager::AddClassDescription
 +---------------------------------------------------------------------*/
void ParentPairingManager::AddClassDescription(
    const string& application_id, unsigned int class_index,
    const string& class_type, unsigned int max_devices,
    unsigned int min_devices, const string& hardware_requirements,
    const string& software_requirements, const string& network_requirements) {
  DeviceClassDescription* device_class_description =
      new DeviceClassDescription();
  device_class_description->InitializeByDeviceClass(
      DeviceClassDescription::GetDeviceClassTypeByString(class_type));
  // TODO(alan@telemidia.puc-rio.br): change  to Initialize using given
  // paremeters
  AddClassDescription(application_id, class_index, device_class_description);
}

/*----------------------------------------------------------------------
 |   ParentPairingManager::AddClassDescription
 +---------------------------------------------------------------------*/
void ParentPairingManager::AddClassDescription(
    const std::string& application_id, unsigned int class_index,
    DeviceClassDescription* device_class_description) {
  device_class_description_map_[application_id][class_index] =
      device_class_description;
  if (device_class_description->pairing_protocol() ==
      DeviceClassDescription::kUpnpPairingProcotol) {
    upnp_registred_classes_size++;
  }
}

/*----------------------------------------------------------------------
 |   ParentPairingManager::RemoveClass
 +---------------------------------------------------------------------*/
void ParentPairingManager::RemoveClass(const string& application_id,
                                       unsigned int class_index) {
  // TODO(alan@telemidia.puc-rio.br): create tests to this
  device_class_description_map_.at(application_id).erase(
      device_class_description_map_.at(application_id).find(class_index));
}

/*----------------------------------------------------------------------
 |   ParentPairingManager::AddDeviceToClass
 +---------------------------------------------------------------------*/
void ParentPairingManager::AddDeviceToClass(const string& application_id,
                                            const string& device_address,
                                            unsigned int class_index,
                                            const string& device_desc) {
  // TODO(alan@telemidia.puc-rio.br): create tests to this
}
/*----------------------------------------------------------------------
 |   ParentPairingManager::GetChildIndex
 +---------------------------------------------------------------------*/
void ParentPairingManager::GetChildIndex(const string& application_id,
                                         const string& device_address,
                                         unsigned int class_index) {
  // TODO(alan@gmail.com): create tests to this
}

/*----------------------------------------------------------------------
 |   ParentPairingManager::StartPairing
 +---------------------------------------------------------------------*/
int ParentPairingManager::StartPairing() {
  clog << "ParentPairingManager::StartPairing()" << endl;
  if (upnp_registred_classes_size > 0) {
    if (upnp_parent_pairing_ == NULL)
      upnp_parent_pairing_ = new UpnpParentPairing(this);
    return upnp_parent_pairing_->StartPairingService();
  } else {
    return -1;
  }
}

/*----------------------------------------------------------------------
 |   ParentPairingManager::StopPairing
 +---------------------------------------------------------------------*/
int ParentPairingManager::StopPairing() {
  if (upnp_parent_pairing_ != NULL) {
    return upnp_parent_pairing_->StopPairingService();
  }
  return 0;
}

/*----------------------------------------------------------------------
 |   ParentPairingManager::IsPairingStarted
 +---------------------------------------------------------------------*/
bool ParentPairingManager::IsPairingStarted() {
  if (upnp_parent_pairing_ != NULL) {
    return upnp_parent_pairing_->IsPairingServiceStarted();
  } else {
    return false;
  }
}

/*----------------------------------------------------------------------
 |   ParentPairingManager::CreateActivePcm
 +---------------------------------------------------------------------*/
ActivePcmInterface* ParentPairingManager::CreateActivePcm(
    const string& application_id, unsigned int class_index) {
  if (device_class_description_map_[application_id][class_index]
          ->device_class_type() == DeviceClassDescription::kActiveDevice)
    return new UpnpActivePcm();
  else
    return NULL;
}

/*----------------------------------------------------------------------
 |   ParentPairingManager::CreateActivePcm
 +---------------------------------------------------------------------*/
MediaCapturePcmInterface* ParentPairingManager::CreateMediaCapturePcm(
    const string& application_id, unsigned int class_index) {
  if (device_class_description_map_[application_id][class_index]
          ->device_class_type() == DeviceClassDescription::kMediaCaptureDevice)
    return new UpnpMediaCapturePcm();
  else
    return NULL;
}

/*----------------------------------------------------------------------
 |   ParentPairingManager::CreateOnDemandPcm
 +---------------------------------------------------------------------*/
OnDemandPcmInterface* ParentPairingManager::CreateOnDemandPcm(
    const string& application_id, unsigned int class_index) {
  if (device_class_description_map_[application_id][class_index]
          ->device_class_type() == DeviceClassDescription::kOnDemandDevice)
    return new UpnpOnDemandPcm();
  else
    return NULL;
}

/*----------------------------------------------------------------------
 |   ParentPairingManager::CreatePassivePcm
 +---------------------------------------------------------------------*/
PassivePcmInterface* ParentPairingManager::CreatePassivePcm(
    const string& application_id, unsigned int class_index) {
  if (device_class_description_map_[application_id][class_index]
          ->device_class_type() == DeviceClassDescription::kPassiveDevice)
    return new UpnpPassivePcm();
  else
    return NULL;
}

/*----------------------------------------------------------------------
 |   ParentPairingManager::GenerateAvaliableIndex
 +---------------------------------------------------------------------*/
unsigned int ParentPairingManager::GenerateAvaliableIndex(
    const string& application_id) {
  for (int i = 0; i < UINT_MAX; i++) {
    if (device_class_description_map_[application_id].find(i) ==
        device_class_description_map_[application_id].end())
      return i;
  }
}

/*----------------------------------------------------------------------
 |   ParentPairingManager::GetRegistredClassesSize
 +---------------------------------------------------------------------*/
unsigned int ParentPairingManager::GetRegistredClassesSize(
    const string& application_id) {
  return device_class_description_map_[application_id].size();
}
