/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/
#include <unistd.h>
#include <gflags/gflags.h>
#include <sys/time.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include "./named_semaphore_helper.h"
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

// Waiting pairing
DEFINE_bool(waiting_pairing, false, "just waiting for pairing");
// Profile Pairing
DEFINE_bool(profile_pairing, false, "enable profile_pairing");
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

double CalculateElapsedTime(timeval start_time, timeval end_time) {
  double elapsed_time;
  elapsed_time = (end_time.tv_sec - start_time.tv_sec) * 1000.0;
  elapsed_time += (end_time.tv_usec - start_time.tv_usec) / 1000.0;
  return elapsed_time;
}

class MockParentClassHandler : public ParentClassHandler {
 public:
  string expected_semaphore;
  virtual void AddDeviceToClass(const string& application_id,
                                const string& device_address,
                                unsigned int class_index,
                                const string& device_desc) {
    clog << "MockParentClassHandler::AddDeviceToClass()" << endl;
    PostNamedSemphoreHelper(expected_semaphore);
  }
};

class MockHpe : public HpeClassHandlingInterface {
 public:
  string expected_semaphore;

  // public methods
  void getClassVariableValue(const string& name, const string& value) {}
  void setClassVariableValue(const string& name, const string& value) {
    clog << "MockParentClassHandler::setClassVariableValue()" << endl;
    if (FLAGS_profile_remove_device)
      PostNamedSemphoreHelper(expected_semaphore);
  }
};

/*----------------------------------------------------------------------
 |   main
 +---------------------------------------------------------------------*/
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

  clog << "Running parent_helper with device_class=" << FLAGS_device_class
       << " and application_id=" << FLAGS_application_id << endl;

  DeviceClassDescription* device_class_description;
  MockParentClassHandler* parent_class_handler;
  MockHpe* mock_hpe;
  DeviceClassDescription::DeviceClassType device_class_type;
  timeval start_time, end_time;
  unsigned int class_index;

  // configure parent
  device_class_type =
      DeviceClassDescription::GetDeviceClassTypeByString(FLAGS_device_class);
  parent_class_handler = new MockParentClassHandler();
  mock_hpe = new MockHpe();
  device_class_description = new DeviceClassDescription();
  device_class_description->InitializeByDeviceClass(device_class_type);
  parent_class_handler->AddClassDescription(FLAGS_application_id, class_index,
                                              device_class_description);
  parent_class_handler->SetClassHandlingHpe(FLAGS_application_id, mock_hpe);

  // start parent
  string parent_named_semaphore = FLAGS_application_id + "_parent";
  parent_class_handler->expected_semaphore = parent_named_semaphore;
  mock_hpe->expected_semaphore = parent_named_semaphore;
  CreateNamedSemphoreHelper(parent_named_semaphore, false);
  parent_class_handler->StartPairing();

  gettimeofday(&start_time, NULL);
  WaitNamedSemphoreHelper(parent_named_semaphore);

  if (FLAGS_profile_pairing) {
    // wait for pairing
    gettimeofday(&end_time, NULL);
    cout << "fsmda_parent profile_pairing "
         << DeviceClassDescription::GetDeviceClassTypeStringByEnum(
                device_class_type) << " "
         << CalculateElapsedTime(start_time, end_time) << " ms" << endl;

  } else if (FLAGS_profile_prepare) {
    gettimeofday(&start_time, NULL);
    gettimeofday(&end_time, NULL);
    cout << "fsmda_parent profile_prepare "
         << DeviceClassDescription::GetDeviceClassTypeStringByEnum(
                device_class_type) << " "
         << CalculateElapsedTime(start_time, end_time) << " ms" << endl;

  } else if (FLAGS_profile_command) {
    gettimeofday(&start_time, NULL);
    gettimeofday(&end_time, NULL);
    cout << "fsmda_parent profile_command "
         << DeviceClassDescription::GetDeviceClassTypeStringByEnum(
                device_class_type) << " "
         << CalculateElapsedTime(start_time, end_time) << " ms" << endl;

  } else if (FLAGS_profile_variable) {
    gettimeofday(&start_time, NULL);
    gettimeofday(&end_time, NULL);
    cout << "fsmda_parent profile_variable "
         << DeviceClassDescription::GetDeviceClassTypeStringByEnum(
                device_class_type) << " "
         << CalculateElapsedTime(start_time, end_time) << " ms" << endl;

  } else if (FLAGS_profile_remove_device) {
    // wait for pairing
    gettimeofday(&start_time, NULL);
    cout << "fsmda_parent profile_remove_device waiting for second post"
         << endl;
    WaitNamedSemphoreHelper(parent_named_semaphore);
    gettimeofday(&end_time, NULL);
    cout << "fsmda_parent profile_remove_device "
         << DeviceClassDescription::GetDeviceClassTypeStringByEnum(
                device_class_type) << " "
         << CalculateElapsedTime(start_time, end_time) << " ms" << endl;

  } else if (FLAGS_profile_bufferd_command) {
    gettimeofday(&start_time, NULL);
    gettimeofday(&end_time, NULL);
    cout << "fsmda_parent profile_bufferd_command "
         << DeviceClassDescription::GetDeviceClassTypeStringByEnum(
                device_class_type) << " "
         << CalculateElapsedTime(start_time, end_time) << " ms" << endl;
  }

  // release parent
  ReleaseNameSemphoreHelper(parent_named_semaphore);
  parent_class_handler->StopPairing();
  delete parent_class_handler;

  return 0;
}
