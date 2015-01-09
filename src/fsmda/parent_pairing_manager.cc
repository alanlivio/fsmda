#include <string>
#include <climits>
#include <iostream>
#include "fsmda/class_handling/device_class_description.h"
#include "fsmda/parent_pairing_manager.h"
#include "fsmda/communication/upnp_active_pcm.h"
#include "fsmda/communication/upnp_mediacapture_pcm.h"
#include "fsmda/communication/upnp_ondemand_pcm.h"
#include "fsmda/communication/upnp_passive_pcm.h"
#include "fsmda/model/passive_objects_api.h"
#include "fsmda/pairing/upnp_parent_pairing.h"

using std::clog;
using std::cout;
using std::endl;

class MockHpe : public HpeClassHandlingInterface {
 public:
  string expected_semaphore;

  // public methods
  void getClassVariableValue(const string& name, const string& value) {}
  void setClassVariableValue(const string& name, const string& value) {}
};

ParentPairingManager::ParentPairingManager() : upnp_registred_classes_size(0) {
  upnp_parent_pairing_ = new UpnpParentPairing();
  upnp_parent_pairing_->set_service_owner(this);
}

ParentPairingManager::~ParentPairingManager() {
  delete upnp_parent_pairing_;
  // TODO(alan@telemidia.puc-rio.br): delete  device_class_description_map_
  // contents
}

/*----------------------------------------------------------------------
 |   ParentPairingManager::AddClass
 +---------------------------------------------------------------------*/
void ParentPairingManager::AddClass(const string& application_id,
                                    unsigned int class_index) {
  // TODO(alan@telemidia.puc-rio.br): implemet this
  //  DeviceClassDescription* device_class_description =
  //      new DeviceClassDescription();
  //  device_class_description->InitializeByDeviceClass(
  //      DeviceClassDescription::kActiveDevice);
  //  AddClassDescription(application_id, class_index,
  // device_class_description);
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
  AddClassDescription(application_id, class_index, device_class_description);
}

/*----------------------------------------------------------------------
 |   ParentPairingManager::AddClassDescription
 +---------------------------------------------------------------------*/
void ParentPairingManager::AddClassDescription(
    const std::string& application_id, unsigned int class_index,
    DeviceClassDescription* device_class_description) {
  clog << "ParentPairingManager::AddClassDescription(" << application_id
       << ",class_index" << class_index
       << ",device_class_type=" << device_class_description->device_class_type()
       << ")" << endl;
  application_class_data_map_[application_id][class_index] =
      new ApplicationClassData();
  application_class_data_map_[application_id][class_index]
      ->device_class_description_ = device_class_description;
  if (device_class_description->pairing_protocol() ==
      DeviceClassDescription::kUpnpPairingProcotol) {
    DeviceClassDiscoverParams* dicover_params = new DeviceClassDiscoverParams(
        application_id, class_index, device_class_description);
    upnp_parent_pairing_->AddDeviceClassForDiscover(dicover_params);
    upnp_registred_classes_size++;
  }
}

/*----------------------------------------------------------------------
 |   ParentPairingManager::SetClassHandlingHPE
 +---------------------------------------------------------------------*/
void ParentPairingManager::SetClassHandlingHPE(
    const std::string& application_id, HpeClassHandlingInterface* hpe) {
  // TODO(alan@telemidia.puc-rio.br): create tests to this
  hpes_map_[application_id] = hpe;
}

/*----------------------------------------------------------------------
 |   ParentPairingManager::RemoveClass
 +---------------------------------------------------------------------*/
void ParentPairingManager::RemoveClass(const string& application_id,
                                       unsigned int class_index) {
  // TODO(alan@telemidia.puc-rio.br): create tests to this
  application_class_data_map_[application_id].erase(
      application_class_data_map_[application_id].find(class_index));
}

/*----------------------------------------------------------------------
 |   ParentPairingManager::AddDeviceToClass
 +---------------------------------------------------------------------*/
void ParentPairingManager::AddDeviceToClass(const string& application_id,
                                            const string& device_address,
                                            unsigned int class_index,
                                            const string& device_desc) {
  // TODO(alan@telemidia.puc-rio.br): create tests to this
  clog << "ParentPairingManager::AddDeviceToClass" << endl;
  if (application_class_data_map_[application_id].find(class_index) !=
      application_class_data_map_[application_id].end())
    application_class_data_map_[application_id][class_index]
        ->registred_devices_.push_back(device_address);
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
    return upnp_parent_pairing_->StartPairingService();
  } else {
    return -1;
  }
}

/*----------------------------------------------------------------------
 |   ParentPairingManager::StopPairing
 +---------------------------------------------------------------------*/
int ParentPairingManager::StopPairing() {
  return upnp_parent_pairing_->StopPairingService();
}

/*----------------------------------------------------------------------
 |   ParentPairingManager::IsPairingStarted
 +---------------------------------------------------------------------*/
bool ParentPairingManager::IsPairingStarted() {
  return upnp_parent_pairing_->IsPairingServiceStarted();
}

/*----------------------------------------------------------------------
 |   ParentPairingManager::CreatePassivePcm
 +---------------------------------------------------------------------*/
PassiveClassListenerInterface* ParentPairingManager::CreatePassivePcm(
    const string& application_id, unsigned int class_index) {
  if (application_class_data_map_[application_id][class_index]
          ->device_class_description_->device_class_type() ==
      DeviceClassDescription::kPassiveDevice) {
    return upnp_parent_pairing_->CreatePassivePcm(application_id, class_index);
  }
}

/*----------------------------------------------------------------------
 |   ParentPairingManager::CreateActivePcm
 +---------------------------------------------------------------------*/
ActiveClassListenerInterface* ParentPairingManager::CreateActivePcm(
    const string& application_id, unsigned int class_index) {
  if (application_class_data_map_[application_id][class_index]
          ->device_class_description_->device_class_type() ==
      DeviceClassDescription::kActiveDevice) {
    return upnp_parent_pairing_->CreateActivePcm(application_id, class_index);
  }
}

/*----------------------------------------------------------------------
 |   ParentPairingManager::CreateMediaCapturePcm
 +---------------------------------------------------------------------*/
MediaCaptureClassListenerInterface* ParentPairingManager::CreateMediaCapturePcm(
    const string& application_id, unsigned int class_index) {
  if (application_class_data_map_[application_id][class_index]
          ->device_class_description_->device_class_type() ==
      DeviceClassDescription::kMediaCaptureDevice) {
    return upnp_parent_pairing_->CreateMediaCapturePcm(application_id,
                                                       class_index);
  }
}

/*----------------------------------------------------------------------
 |   ParentPairingManager::CreateOnDemandPcm
 +---------------------------------------------------------------------*/
OnDemandClassListenerInterface* ParentPairingManager::CreateOnDemandPcm(
    const string& application_id, unsigned int class_index) {
  if (application_class_data_map_[application_id][class_index]
          ->device_class_description_->device_class_type() ==
      DeviceClassDescription::kOnDemandDevice) {
    return upnp_parent_pairing_->CreateOnDemandPcm(application_id, class_index);
  }
}

/*----------------------------------------------------------------------
 |   ParentPairingManager::GenerateAvaliableIndex
 +---------------------------------------------------------------------*/
unsigned int ParentPairingManager::GenerateAvaliableIndex(
    const string& application_id) {
  for (int i = 0; i < UINT_MAX; i++) {
    if (application_class_data_map_[application_id].find(i) ==
        application_class_data_map_[application_id].end())
      return i;
  }
}

/*----------------------------------------------------------------------
 |   ParentPairingManager::GetNumberOfRegistredClasses
 +---------------------------------------------------------------------*/
unsigned int ParentPairingManager::GetNumberOfRegistredClasses(
    const string& application_id) {
  return application_class_data_map_[application_id].size();
}

/*----------------------------------------------------------------------
 |   ParentPairingManager::GetNumberOfRegistredChildren
 +---------------------------------------------------------------------*/
unsigned int ParentPairingManager::GetNumberOfRegistredChildren(
    const std::string& application_id, unsigned int class_index) {
  clog << "ParentPairingManager::GetNumberOfRegistredChildren:: "
          "application_id=" << application_id << ",class_index" << class_index
       << endl;
  if (application_class_data_map_[application_id].find(class_index) !=
      application_class_data_map_[application_id].end())
    return application_class_data_map_[application_id][class_index]
        ->registred_devices_.size();
  else
    return 0;
}
