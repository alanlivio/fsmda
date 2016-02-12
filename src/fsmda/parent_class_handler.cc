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

ParentClassHandler::~ParentClassHandler() { delete upnp_ppm_; }

void ParentClassHandler::add_class(const string& application_id,
                                   unsigned int class_index) {}

void ParentClassHandler::add_class_description(
    const string& application_id, unsigned int class_index,
    const string& class_type, unsigned int max_devices,
    unsigned int min_devices, const string& hardware_requirements,
    const string& software_requirements, const string& network_requirements) {
  DeviceClassDescription* device_class_description =
      new DeviceClassDescription();
  device_class_description->initialize_by_device_class(
      DeviceClassDescription::to_device_class_type(class_type));
  add_class_description(application_id, class_index, device_class_description);
}

void ParentClassHandler::add_class_description(
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
    upnp_ppm_->add_device_class_for_discover(dicover_params);
    number_of_registred_classes_++;
  }
}

void ParentClassHandler::set_class_handling_hpe(
    const string& application_id, HpeClassHandlingInterface* hpe) {
  // TODO(alan@telemidia.puc-rio.br): create tests to this
  hpes_map_[application_id] = hpe;
}

HpeClassHandlingInterface* ParentClassHandler::get_class_handling_hpe(
    const string& application_id) {
  return hpes_map_[application_id];
}

void ParentClassHandler::remove_class(const string& application_id,
                                      unsigned int class_index) {
  // TODO(alan@telemidia.puc-rio.br): create tests to this
  device_class_data_map_[application_id].erase(
      device_class_data_map_[application_id].find(class_index));
}

void ParentClassHandler::report_add_device_to_class(
    const string& application_id, unsigned int class_index) {
  // TODO(alan@telemidia.puc-rio.br): create tests to this
  clog << "ParentClassHandler::ReportAddDeviceToClass(" << application_id
       << ",class_index=" << class_index << ")" << endl;
  device_class_data_map_[application_id][class_index]
      ->number_of_registred_children_++;
}

unsigned int ParentClassHandler::get_avaliable_child_index(
    const string& application_id, unsigned int class_index) {
  // TODO(alan@gmail.com): create tests to this
  return 1;
}

int ParentClassHandler::start_pairing() {
  clog << "ParentClassHandler::StartPairing()" << endl;
  if (number_of_registred_classes_ > 0) {
    return upnp_ppm_->start_pairing_service();
  } else {
    return -1;
  }
}

int ParentClassHandler::stop_pairing() {
  return upnp_ppm_->stop_pairing_service();
}

bool ParentClassHandler::is_pairing_started() {
  return upnp_ppm_->is_pairing_service_started();
}

PassiveClassListenerInterface* ParentClassHandler::create_passive_pcm(
    const string& application_id, unsigned int class_index) {
  if (device_class_data_map_[application_id][class_index]
          ->device_class_description_->device_class_type() ==
      DeviceClassDescription::kPassiveDevice) {
    return upnp_ppm_->create_passive_pcm(application_id, class_index);
  }
}

ActiveClassInterface* ParentClassHandler::create_active_pcm(
    const string& application_id, unsigned int class_index) {
  if (device_class_data_map_[application_id][class_index]
          ->device_class_description_->device_class_type() ==
      DeviceClassDescription::kActiveDevice) {
    return upnp_ppm_->create_active_pcm(application_id, class_index);
  }
}

MediaCaptureClassListenerInterface*
ParentClassHandler::create_media_capture_pcm(const string& application_id,
                                             unsigned int class_index) {
  if (device_class_data_map_[application_id][class_index]
          ->device_class_description_->device_class_type() ==
      DeviceClassDescription::kMediaCaptureDevice) {
    return upnp_ppm_->create_mediacapture_pcm(application_id, class_index);
  }
}

OnDemandClassListenerInterface* ParentClassHandler::create_ondemand_pcm(
    const string& application_id, unsigned int class_index) {
  if (device_class_data_map_[application_id][class_index]
          ->device_class_description_->device_class_type() ==
      DeviceClassDescription::kOnDemandDevice) {
    return upnp_ppm_->create_ondemand_pcm(application_id, class_index);
  }
}

unsigned int ParentClassHandler::generate_avaliable_index(
    const string& application_id) {
  for (int i = 5; i < UINT_MAX; i++) {
    if (device_class_data_map_[application_id].find(i) ==
        device_class_data_map_[application_id].end())
      return i;
  }
}

unsigned int ParentClassHandler::number_of_registred_classes(
    const string& application_id) {
  return device_class_data_map_[application_id].size();
}

unsigned int ParentClassHandler::number_of_registred_children(
    const string& application_id, unsigned int class_index) {
  clog << "ParentClassHandler::GetNumberOfRegistredChildren:: "
          "application_id="
       << application_id << ",class_index" << class_index << endl;
  return device_class_data_map_[application_id][class_index]
      ->number_of_registred_children_;
}
