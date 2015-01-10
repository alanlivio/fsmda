#include <string>
#include <climits>
#include <iostream>
#include "fsmda//device_class_description.h"
#include "fsmda/parent_class_handler.h"
#include "fsmda/upnp/upnp_active_pcm.h"
#include "fsmda/upnp/upnp_mediacapture_pcm.h"
#include "fsmda/upnp/upnp_ondemand_pcm.h"
#include "fsmda/upnp/upnp_passive_pcm.h"
#include "fsmda/model/passive_objects_api.h"
#include "fsmda/upnp/upnp_ppm.h"

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

ParentClassHandler::ParentClassHandler() : upnp_registred_classes_size(0) {
  upnp_ppm_ = new UpnpPpm();
  upnp_ppm_->set_service_owner(this);
}

ParentClassHandler::~ParentClassHandler() {
  delete upnp_ppm_;
  // TODO(alan@telemidia.puc-rio.br): delete  device_class_description_map_
  // contents
}

/*----------------------------------------------------------------------
 |   ParentClassHandler::AddClass
 +---------------------------------------------------------------------*/
void ParentClassHandler::AddClass(const string& application_id,
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
 |   ParentClassHandler::AddClassDescription
 +---------------------------------------------------------------------*/
void ParentClassHandler::AddClassDescription(
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
 |   ParentClassHandler::AddClassDescription
 +---------------------------------------------------------------------*/
void ParentClassHandler::AddClassDescription(
    const std::string& application_id, unsigned int class_index,
    DeviceClassDescription* device_class_description) {
  clog << "ParentClassHandler::AddClassDescription(" << application_id
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
    upnp_ppm_->AddDeviceClassForDiscover(dicover_params);
    upnp_registred_classes_size++;
  }
}

/*----------------------------------------------------------------------
 |   ParentClassHandler::SetClassHandlingHPE
 +---------------------------------------------------------------------*/
void ParentClassHandler::SetClassHandlingHpe(
    const std::string& application_id, HpeClassHandlingInterface* hpe) {
  // TODO(alan@telemidia.puc-rio.br): create tests to this
  hpes_map_[application_id] = hpe;
}

/*----------------------------------------------------------------------
 |   ParentClassHandler::RemoveClass
 +---------------------------------------------------------------------*/
void ParentClassHandler::RemoveClass(const string& application_id,
                                       unsigned int class_index) {
  // TODO(alan@telemidia.puc-rio.br): create tests to this
  application_class_data_map_[application_id].erase(
      application_class_data_map_[application_id].find(class_index));
}

/*----------------------------------------------------------------------
 |   ParentClassHandler::AddDeviceToClass
 +---------------------------------------------------------------------*/
void ParentClassHandler::AddDeviceToClass(const string& application_id,
                                            const string& device_address,
                                            unsigned int class_index,
                                            const string& device_desc) {
  // TODO(alan@telemidia.puc-rio.br): create tests to this
  clog << "ParentClassHandler::AddDeviceToClass" << endl;
  if (application_class_data_map_[application_id].find(class_index) !=
      application_class_data_map_[application_id].end())
    application_class_data_map_[application_id][class_index]
        ->registred_devices_.push_back(device_address);
}
/*----------------------------------------------------------------------
 |   ParentClassHandler::GetChildIndex
 +---------------------------------------------------------------------*/
void ParentClassHandler::GetChildIndex(const string& application_id,
                                         const string& device_address,
                                         unsigned int class_index) {
  // TODO(alan@gmail.com): create tests to this
}

/*----------------------------------------------------------------------
 |   ParentClassHandler::StartPairing
 +---------------------------------------------------------------------*/
int ParentClassHandler::StartPairing() {
  clog << "ParentClassHandler::StartPairing()" << endl;
  if (upnp_registred_classes_size > 0) {
    return upnp_ppm_->StartPairingService();
  } else {
    return -1;
  }
}

/*----------------------------------------------------------------------
 |   ParentClassHandler::StopPairing
 +---------------------------------------------------------------------*/
int ParentClassHandler::StopPairing() {
  return upnp_ppm_->StopPairingService();
}

/*----------------------------------------------------------------------
 |   ParentClassHandler::IsPairingStarted
 +---------------------------------------------------------------------*/
bool ParentClassHandler::IsPairingStarted() {
  return upnp_ppm_->IsPairingServiceStarted();
}

/*----------------------------------------------------------------------
 |   ParentClassHandler::CreatePassivePcm
 +---------------------------------------------------------------------*/
PassiveClassListenerInterface* ParentClassHandler::CreatePassivePcm(
    const string& application_id, unsigned int class_index) {
  if (application_class_data_map_[application_id][class_index]
          ->device_class_description_->device_class_type() ==
      DeviceClassDescription::kPassiveDevice) {
    return upnp_ppm_->CreatePassivePcm(application_id, class_index);
  }
}

/*----------------------------------------------------------------------
 |   ParentClassHandler::CreateActivePcm
 +---------------------------------------------------------------------*/
ActiveClassInterface* ParentClassHandler::CreateActivePcm(
    const string& application_id, unsigned int class_index) {
  if (application_class_data_map_[application_id][class_index]
          ->device_class_description_->device_class_type() ==
      DeviceClassDescription::kActiveDevice) {
    return upnp_ppm_->CreateActivePcm(application_id, class_index);
  }
}

/*----------------------------------------------------------------------
 |   ParentClassHandler::CreateMediaCapturePcm
 +---------------------------------------------------------------------*/
MediaCaptureClassListenerInterface* ParentClassHandler::CreateMediaCapturePcm(
    const string& application_id, unsigned int class_index) {
  if (application_class_data_map_[application_id][class_index]
          ->device_class_description_->device_class_type() ==
      DeviceClassDescription::kMediaCaptureDevice) {
    return upnp_ppm_->CreateMediaCapturePcm(application_id,
                                                       class_index);
  }
}

/*----------------------------------------------------------------------
 |   ParentClassHandler::CreateOnDemandPcm
 +---------------------------------------------------------------------*/
OnDemandClassListenerInterface* ParentClassHandler::CreateOnDemandPcm(
    const string& application_id, unsigned int class_index) {
  if (application_class_data_map_[application_id][class_index]
          ->device_class_description_->device_class_type() ==
      DeviceClassDescription::kOnDemandDevice) {
    return upnp_ppm_->CreateOnDemandPcm(application_id, class_index);
  }
}

/*----------------------------------------------------------------------
 |   ParentClassHandler::GenerateAvaliableIndex
 +---------------------------------------------------------------------*/
unsigned int ParentClassHandler::GenerateAvaliableIndex(
    const string& application_id) {
  for (int i = 0; i < UINT_MAX; i++) {
    if (application_class_data_map_[application_id].find(i) ==
        application_class_data_map_[application_id].end())
      return i;
  }
}

/*----------------------------------------------------------------------
 |   ParentClassHandler::GetNumberOfRegistredClasses
 +---------------------------------------------------------------------*/
unsigned int ParentClassHandler::GetNumberOfRegistredClasses(
    const string& application_id) {
  return application_class_data_map_[application_id].size();
}

/*----------------------------------------------------------------------
 |   ParentClassHandler::GetNumberOfRegistredChildren
 +---------------------------------------------------------------------*/
unsigned int ParentClassHandler::GetNumberOfRegistredChildren(
    const std::string& application_id, unsigned int class_index) {
  clog << "ParentClassHandler::GetNumberOfRegistredChildren:: "
          "application_id=" << application_id << ",class_index" << class_index
       << endl;
  if (application_class_data_map_[application_id].find(class_index) !=
      application_class_data_map_[application_id].end())
    return application_class_data_map_[application_id][class_index]
        ->registred_devices_.size();
  else
    return 0;
}
