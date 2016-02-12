
#include <unistd.h>
#include <gflags/gflags.h>
#include <sys/time.h>
#include <signal.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include "fsmda/parent_class_handler.h"
#include "fsmda/upnp/upnp_cpm.h"
#include "fsmda/upnp/upnp_ppm.h"
#include "fsmda/upnp/upnp_fsmda_utils.h"
using std::cin;
using std::cout;
using std::clog;
using std::endl;
using std::getline;
DEFINE_string(application_id, "dc05b236-0cce-4f1d-996b-edd11a66d907",
              "uuuid application");
DEFINE_string(device_class, DeviceClassDescription::kActiveDeviceString,
              "device class name: passive,active,ondemand or medicapture");

// Profile Data Transfer
DEFINE_bool(profile_prepare, false, "enable profile_prepare");
// Profile Command reaction
DEFINE_bool(profile_command, false, "enable profile_command");
// Profile Variable changing
DEFINE_bool(profile_variable, false, "enable profile_variable");
// Profile Fault tolerance (1)
DEFINE_bool(profile_remove_device, false, "enable profile_remove_device");
// Profile Fault tolerance (2)
DEFINE_bool(profile_bufferd_command, false, "enable profile_bufferd_command");

NPT_SharedVariable parent_semaphore;

double CalculateElapsedTime(timeval start_time, timeval end_time) {
  double elapsed_time;
  elapsed_time = (end_time.tv_sec - start_time.tv_sec) * 1000.0;
  elapsed_time += (end_time.tv_usec - start_time.tv_usec) / 1000.0;
  return elapsed_time;
}

class MockParentClassHandler : public ParentClassHandler {
 public:
  virtual void report_add_device_to_class(const string& application_id,
                                          unsigned int class_index) {
    cout << "MockParentClassHandler::ReportAddDeviceToClass()" << endl;
    parent_semaphore.SetValue(1);
  }
};

class MockHpe : public HpeClassHandlingInterface,
                public ActiveClassListenerInterface {
 public:
  // ActiveClassListenerInterface interface
  virtual void report_property_value(const string& object_id,
                                     const string& name, const string& value) {
    clog << "MockParentClassHandler::ReportPropertyValue()" << endl;
  }
  void notify_event_transition(const string& object_id, const string& event_id,
                               const string& transition) {
    clog << "MockParentClassHandler::NotifyEventTransition()" << endl;
  }
  void notify_error(const string& object_id, const string& message) {}

  // HpeClassHandlingInterface interface
  void get_class_variable_value(const string& name, const string& value) {}
  void set_class_variable_value(const string& name, const string& value) {
    clog << "MockParentClassHandler::setClassVariableValue()" << name << "="
         << value << endl;
    if (FLAGS_profile_remove_device)
      parent_semaphore.SetValue(1);
  }
};

int main(int argc, char** argv) {
  google::SetVersionString("0.1");
  google::SetUsageMessage(
      "fake_parent --application_id=<UUID> "
      "--device-class=<passive|active|ondemand|medicapture>");
  google::ParseCommandLineFlags(&argc, &argv, true);

  // redirect clog to /dev/null/
  static std::ofstream logOutput;
  logOutput.open("/dev/null");
  clog.rdbuf(logOutput.rdbuf());

  cout << "fake_parent_helper::device_class=" << FLAGS_device_class
       << ",application_id=" << FLAGS_application_id << endl;

  DeviceClassDescription* device_class_description;
  MockHpe* mock_hpe;
  DeviceClassDescription::DeviceClassType device_class_type;
  timeval start_time, end_time;
  unsigned int class_index;

  // configure parent
  device_class_type =
      DeviceClassDescription::to_device_class_type(FLAGS_device_class);
  MockParentClassHandler* parent_class_handler;
  parent_class_handler     = new MockParentClassHandler();
  mock_hpe                 = new MockHpe();
  device_class_description = new DeviceClassDescription();
  device_class_description->initialize_by_device_class(device_class_type);
  parent_class_handler->add_class_description(FLAGS_application_id, class_index,
                                              device_class_description);
  parent_class_handler->set_class_handling_hpe(FLAGS_application_id, mock_hpe);

  // start parent
  parent_class_handler->start_pairing();

  // waiting for pairing
  cout << "fake_parent_helper:: wait for pairing..." << endl;
  gettimeofday(&start_time, NULL);
  parent_semaphore.SetValue(0);
  parent_semaphore.WaitWhileEquals(0, NPT_TIMEOUT_INFINITE);

  if (FLAGS_profile_prepare) {
    ActiveClassInterface* active_pcm = parent_class_handler->create_active_pcm(
        FLAGS_application_id, class_index);
    active_pcm->registry_active_class_listener(mock_hpe);
    gettimeofday(&start_time, NULL);
    vector<Property> properties;
    vector<Event> events;
    // TODO(alan@telemidia.puc-rio.br): use relative path
    active_pcm->prepare("media01",
                        "/home/alan/development/multidevice-development/"
                        "libfsmda/tests/files/ncl01/",
                        properties, events);
    gettimeofday(&end_time, NULL);
    cout << "fsmda_parent profile_prepare "
         << DeviceClassDescription::to_device_class_string(device_class_type)
         << " " << CalculateElapsedTime(start_time, end_time) << " ms" << endl;
  } else if (FLAGS_profile_command) {
    ActiveClassInterface* active_pcm = parent_class_handler->create_active_pcm(
        FLAGS_application_id, class_index);
    active_pcm->registry_active_class_listener(mock_hpe);
    gettimeofday(&start_time, NULL);
    active_pcm->post_action("media01", "evt01", "start");
    gettimeofday(&end_time, NULL);
    cout << "fsmda_parent profile_command "
         << DeviceClassDescription::to_device_class_string(device_class_type)
         << " " << CalculateElapsedTime(start_time, end_time) << " ms" << endl;
  } else if (FLAGS_profile_variable) {
    ActiveClassInterface* active_pcm = parent_class_handler->create_active_pcm(
        FLAGS_application_id, class_index);
    active_pcm->registry_active_class_listener(mock_hpe);
    gettimeofday(&start_time, NULL);
    active_pcm->set_property_value("media1", "hight", "10%", 0);
    gettimeofday(&end_time, NULL);
    cout << "fsmda_parent profile_variable "
         << DeviceClassDescription::to_device_class_string(
                device_class_type)
         << " " << CalculateElapsedTime(start_time, end_time) << " ms" << endl;
  } else if (FLAGS_profile_remove_device) {
    // wait for pairing
    gettimeofday(&start_time, NULL);
    cout << "fsmda_parent:: wait for profile_remove_device..." << endl;
    parent_semaphore.SetValue(0);
    parent_semaphore.WaitWhileEquals(0, NPT_TIMEOUT_INFINITE);
    gettimeofday(&end_time, NULL);
    cout << "fsmda_parent profile_remove_device "
         << DeviceClassDescription::to_device_class_string(
                device_class_type)
         << " " << CalculateElapsedTime(start_time, end_time) << " ms" << endl;
  } else if (FLAGS_profile_bufferd_command) {
    //    gettimeofday(&end_time, NULL);
    //    cout << "fsmda_parent profile_bufferd_command "
    //         << DeviceClassDescription::GetDeviceClassTypeStringByEnum(
    //                device_class_type) << " "
    //         << CalculateElapsedTime(start_time, end_time) << " ms" << endl;
    //    gettimeofday(&start_time, NULL);
    cout << "fsmda_parent:: wait for second pairing..." << endl;
    parent_semaphore.SetValue(0);
    parent_semaphore.WaitWhileEquals(0, NPT_TIMEOUT_INFINITE);
    //    gettimeofday(&end_time, NULL);
    //    cout << "fsmda_parent profile_bufferd_command "
    //         << DeviceClassDescription::GetDeviceClassTypeStringByEnum(
    //                device_class_type) << " "
    //         << CalculateElapsedTime(start_time, end_time) << " ms" << endl;
  }

  // release parent
  parent_class_handler->stop_pairing();
  delete parent_class_handler;

  return 0;
}
