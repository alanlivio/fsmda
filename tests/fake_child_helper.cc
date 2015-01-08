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

DEFINE_string(application_id, "", "uuuid application");
DEFINE_string(device_class, DeviceClassDescription::kInvalidDeviceString,
              "device class name: passive,active,ondemand or medicapture");

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

  clog << "fake_parent_helper.cc::main():: device_class=" << FLAGS_device_class
       << endl;
  clog << "fake_parent_helper.cc::main():: application_id="
       << FLAGS_application_id << endl;

  MockChildPairingManager* child_pairing_manager;
  timeval start_time, end_time;
  double elapsed_time = 0.0;

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

  if (FLAGS_profile_pairing) {
    // wait for pairing
    gettimeofday(&start_time, NULL);
    WaitNamedSemphoreHelper(FLAGS_application_id);
    gettimeofday(&end_time, NULL);
    ReleaseNameSemphoreHelper(FLAGS_application_id);

    elapsed_time = (end_time.tv_sec - start_time.tv_sec) * 1000;
    elapsed_time += (end_time.tv_usec - start_time.tv_usec) / 1000;
    cout << "fsmda_profiling profile_pairing "
         << DeviceClassDescription::GetDeviceClassTypeStringByEnum(device_class)
         << " " << elapsed_time << " ms" << endl;
  } else if (FLAGS_profile_prepare) {
    cout << "fsmda_profiling profile_prepare "
         << DeviceClassDescription::GetDeviceClassTypeStringByEnum(device_class)
         << " " << elapsed_time << " ms" << endl;

  } else if (FLAGS_profile_command) {
    cout << "fsmda_profiling profile_command "
         << DeviceClassDescription::GetDeviceClassTypeStringByEnum(device_class)
         << " " << elapsed_time << " ms" << endl;

  } else if (FLAGS_profile_variable) {
    cout << "fsmda_profiling profile_variable "
         << DeviceClassDescription::GetDeviceClassTypeStringByEnum(device_class)
         << " " << elapsed_time << " ms" << endl;

  } else if (FLAGS_profile_remove_device) {
    cout << "fsmda_profiling profile_remove_device "
         << DeviceClassDescription::GetDeviceClassTypeStringByEnum(device_class)
         << " " << elapsed_time << " ms" << endl;

  } else if (FLAGS_profile_bufferd_command) {
    cout << "fsmda_profiling profile_bufferd_command "
         << DeviceClassDescription::GetDeviceClassTypeStringByEnum(device_class)
         << " " << elapsed_time << " ms" << endl;
  } else {
    WaitNamedSemphoreHelper(FLAGS_application_id);
    ReleaseNameSemphoreHelper(FLAGS_application_id);
  }
  // release child
  child_pairing_manager->StopPairing();
  delete child_pairing_manager;

  return 0;
}
