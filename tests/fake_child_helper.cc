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
#include "fsmda/class_handling/device_class_description.h"
#include "fsmda/class_handling/device_description.h"
#include "fsmda/parent_pairing_manager.h"
#include "fsmda/child_pairing_manager.h"
#include "fsmda/utils/upnp_fsmda_utils.h"

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

class MockChildPairingManager : public ChildPairingManager {
 public:
  string expected_semaphore;
  void set_paired(bool paired) {
    clog << "MockChildPairingManager::SetPaired():: paired = " << paired
         << endl;
    ChildPairingManager::set_paired(paired);
    PostNamedSemphoreHelper(expected_semaphore);
  }
  explicit MockChildPairingManager(const DeviceDescription& device_description)
      : ChildPairingManager(device_description) {}
};

/*----------------------------------------------------------------------
 |   main
 +---------------------------------------------------------------------*/
int main(int argc, char** argv) {
  google::SetVersionString("0.1");
  google::SetUsageMessage(
      "fake_child_helper --application_id=<UUID> "
      "--device-class=<passive|active|ondemand|medicapture>");
  google::ParseCommandLineFlags(&argc, &argv, true);

  // redirect clog to /dev/null/
  static std::ofstream logOutput;
  logOutput.open("/dev/null");
  clog.rdbuf(logOutput.rdbuf());

  clog << "Running fake_child_helper with device_class=" << FLAGS_device_class
       << " and application_id=" << FLAGS_application_id << endl;

  MockChildPairingManager* child_pairing_manager;
  timeval start_time, end_time;

  // configure child
  DeviceClassDescription::DeviceClassType device_class =
      DeviceClassDescription::GetDeviceClassTypeByString(FLAGS_device_class);
  DeviceDescription device_description;
  const char* rdf_content =
      DeviceClassDescription::GetDeviceClassRdfDefaultContentByType(
          device_class);
  device_description.InitializeByRdfContent(rdf_content);
  child_pairing_manager = new MockChildPairingManager(device_description);

  // start child
  child_pairing_manager->expected_semaphore = FLAGS_application_id;
  CreateNamedSemphoreHelper(FLAGS_application_id, false);
  child_pairing_manager->StartPairing();

  gettimeofday(&start_time, NULL);
  WaitNamedSemphoreHelper(FLAGS_application_id);

  if (FLAGS_profile_pairing) {
    // wait for pairing
    gettimeofday(&end_time, NULL);
    cout << "fsmda_child profile_pairing "
         << DeviceClassDescription::GetDeviceClassTypeStringByEnum(device_class)
         << " " << CalculateElapsedTime(start_time, end_time) << " ms" << endl;
  } else if (FLAGS_profile_prepare) {
    gettimeofday(&start_time, NULL);
    gettimeofday(&end_time, NULL);
    cout << "fsmda_child profile_prepare "
         << DeviceClassDescription::GetDeviceClassTypeStringByEnum(device_class)
         << " " << CalculateElapsedTime(start_time, end_time) << " ms" << endl;

  } else if (FLAGS_profile_command) {
    gettimeofday(&start_time, NULL);
    gettimeofday(&end_time, NULL);
    cout << "fsmda_child profile_command "
         << DeviceClassDescription::GetDeviceClassTypeStringByEnum(device_class)
         << " " << CalculateElapsedTime(start_time, end_time) << " ms" << endl;

  } else if (FLAGS_profile_variable) {
    gettimeofday(&start_time, NULL);
    gettimeofday(&end_time, NULL);
    cout << "fsmda_child profile_variable "
         << DeviceClassDescription::GetDeviceClassTypeStringByEnum(device_class)
         << " " << CalculateElapsedTime(start_time, end_time) << " ms" << endl;

  } else if (FLAGS_profile_remove_device) {
    gettimeofday(&start_time, NULL);
    gettimeofday(&end_time, NULL);
    cout << "fsmda_child profile_remove_device "
         << DeviceClassDescription::GetDeviceClassTypeStringByEnum(device_class)
         << " " << CalculateElapsedTime(start_time, end_time) << " ms" << endl;

  } else if (FLAGS_profile_bufferd_command) {
    gettimeofday(&start_time, NULL);
    gettimeofday(&end_time, NULL);
    cout << "fsmda_child profile_bufferd_command "
         << DeviceClassDescription::GetDeviceClassTypeStringByEnum(device_class)
         << " " << CalculateElapsedTime(start_time, end_time) << " ms" << endl;
  }

  // release child
  ReleaseNameSemphoreHelper(FLAGS_application_id);
  child_pairing_manager->StopPairing();
  delete child_pairing_manager;

  return 0;
}
