#include <string>
#include <climits>
#include <iostream>
#include "fsmda/device_class_description.h"
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

ParentClassHandler::ParentClassHandler() : number_of_registred_classes_(0) {
  upnp_ppm_ = new UpnpPpm();
  upnp_ppm_->set_service_owner(this);
}

ParentClassHandler::~ParentClassHandler() {
  delete upnp_ppm_;
  // TODO(alan@telemidia.puc-rio.br): delete device_class_description_map_
}

/*----------------------------------------------------------------------
 |   ParentClassHandler::AddClass
 +---------------------------------------------------------------------*/
void ParentClassHandler::AddClass(const string& application_id,
                                  unsigned int class_index) {
  // TODO(alan@telemidia.puc-rio.br): implemet this
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
    const string& application_id, unsigned int class_index,
    DeviceClassDescription* device_class_description) {
  clog << "ParentClassHandler::AddClassDescription(" << application_id
       << ",class_index=" << class_index
       << ",device_class_type=" << device_class_description->device_class_type()
       << ")" << endl;
  device_class_data_map_[application_id][class_index] = new DeviceClassData();
  device_class_data_map_[application_id][class_index]
      ->device_class_description_ = device_class_description;
  if (device_class_description->pairing_protocol() ==
      DeviceClassDescription::kUpnpPairingProcotol) {
    DeviceClassDiscoverParams* dicover_params = new DeviceClassDiscoverParams(
        application_id, class_index, device_class_description);
    upnp_ppm_->AddDeviceClassForDiscover(dicover_params);
    number_of_registred_classes_++;
  }
}

/*----------------------------------------------------------------------
 |   ParentClassHandler::SetClassHandlingHPE
 +---------------------------------------------------------------------*/
void ParentClassHandler::SetClassHandlingHpe(const string& application_id,
                                             HpeClassHandlingInterface* hpe) {
  // TODO(alan@telemidia.puc-rio.br): create tests to this
  hpes_map_[application_id] = hpe;
}

/*----------------------------------------------------------------------
 |   ParentClassHandler::SetClassHandlingHPE
 +---------------------------------------------------------------------*/
HpeClassHandlingInterface* ParentClassHandler::GetClassHandlingHpe(
    const string& application_id) {
  return hpes_map_[application_id];
}

/*----------------------------------------------------------------------
 |   ParentClassHandler::RemoveClass
 +---------------------------------------------------------------------*/
void ParentClassHandler::RemoveClass(const string& application_id,
                                     unsigned int class_index) {
  // TODO(alan@telemidia.puc-rio.br): create tests to this
  device_class_data_map_[application_id].erase(
      device_class_data_map_[application_id].find(class_index));
}

/*----------------------------------------------------------------------
 |   ParentClassHandler::AddDeviceToClass
 +---------------------------------------------------------------------*/
void ParentClassHandler::ReportAddDeviceToClass(const string& application_id,
                                                unsigned int class_index) {
  // TODO(alan@telemidia.puc-rio.br): create tests to this
  clog << "ParentClassHandler::ReportAddDeviceToClass(" << application_id
       << ",class_index=" << class_index
       << ")" << endl;
  device_class_data_map_[application_id][class_index]
      ->number_of_registred_children_++;
}
/*----------------------------------------------------------------------
 |   ParentClassHandler::GetAvaliableChildIndex
 +---------------------------------------------------------------------*/
unsigned int ParentClassHandler::GetAvaliableChildIndex(
    const string& application_id, unsigned int class_index) {
  // TODO(alan@gmail.com): create tests to this
  return 1;
}

/*----------------------------------------------------------------------
 |   ParentClassHandler::StartPairing
 +---------------------------------------------------------------------*/
int ParentClassHandler::StartPairing() {
  clog << "ParentClassHandler::StartPairing()" << endl;
  if (number_of_registred_classes_ > 0) {
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
  if (device_class_data_map_[application_id][class_index]
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
  if (device_class_data_map_[application_id][class_index]
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
  if (device_class_data_map_[application_id][class_index]
          ->device_class_description_->device_class_type() ==
      DeviceClassDescription::kMediaCaptureDevice) {
    return upnp_ppm_->CreateMediaCapturePcm(application_id, class_index);
  }
}

/*----------------------------------------------------------------------
 |   ParentClassHandler::CreateOnDemandPcm
 +---------------------------------------------------------------------*/
OnDemandClassListenerInterface* ParentClassHandler::CreateOnDemandPcm(
    const string& application_id, unsigned int class_index) {
  if (device_class_data_map_[application_id][class_index]
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
  for (int i = 5; i < UINT_MAX; i++) {
    if (device_class_data_map_[application_id].find(i) ==
        device_class_data_map_[application_id].end())
      return i;
  }
}

/*----------------------------------------------------------------------
 |   ParentClassHandler::number_of_registred_classes
 +---------------------------------------------------------------------*/
unsigned int ParentClassHandler::number_of_registred_classes(
    const string& application_id) {
  return device_class_data_map_[application_id].size();
}

/*----------------------------------------------------------------------
 |   ParentClassHandler::number_of_registred_children
 +---------------------------------------------------------------------*/
unsigned int ParentClassHandler::number_of_registred_children(
    const string& application_id, unsigned int class_index) {
  clog << "ParentClassHandler::GetNumberOfRegistredChildren:: "
          "application_id=" << application_id << ",class_index" << class_index
       << endl;
  return device_class_data_map_[application_id][class_index]
      ->number_of_registred_children_;
}
