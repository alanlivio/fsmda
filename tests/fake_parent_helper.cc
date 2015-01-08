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
#include "fsmda/parent_pairing_manager.h"
#include "fsmda/pairing/upnp_child_pairing.h"
#include "fsmda/pairing/upnp_parent_pairing.h"
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

class MockParentPairingManager : public ParentPairingManager {
 public:
  string expected_semaphore;
  virtual void AddDeviceToClass(const string& application_id,
                                const string& device_address,
                                unsigned int class_index,
                                const string& device_desc) {
    clog << "MockParentPairingManager::AddDeviceToClass()" << endl;
    PostNamedSemphoreHelper(expected_semaphore);
  }
};

class MockHpe : public ClassHandlingHpeInterface {
 public:
  string expected_semaphore;
  // public pure virtual methods
  virtual void getClassVariableValue(const string& name, const string& value) {}
  virtual void setClassVariableValue(const string& name, const string& value) {
    clog << "MockParentPairingManager::setClassVariableValue()" << endl;
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

  clog << "fake_parent_helper.cc::main():: device_class=" << FLAGS_device_class
       << endl;
  clog << "fake_parent_helper.cc::main():: application_id="
       << FLAGS_application_id << endl;

  DeviceClassDescription* device_class_description;
  MockParentPairingManager* parent_pairing_manager;
  DeviceClassDescription::DeviceClassType device_class_type;
  timeval start_time, end_time;
  double elapsed_time = 0.0;
  unsigned int class_index = 2;

  // configure parent
  device_class_type =
      DeviceClassDescription::GetDeviceClassTypeByString(FLAGS_device_class);
  parent_pairing_manager = new MockParentPairingManager();
  device_class_description = new DeviceClassDescription();
  device_class_description->InitializeByDeviceClass(device_class_type);
  parent_pairing_manager->AddClassDescription(FLAGS_application_id, class_index,
                                              device_class_description);

  // start parent
  string parent_named_semaphore = FLAGS_application_id + "_parent";
  parent_pairing_manager->expected_semaphore = parent_named_semaphore;
  CreateNamedSemphoreHelper(parent_named_semaphore, false);
  parent_pairing_manager->StartPairing();

  if (FLAGS_profile_pairing) {
    // wait for pairing
    gettimeofday(&start_time, NULL);
    WaitNamedSemphoreHelper(parent_named_semaphore);
    gettimeofday(&end_time, NULL);
    ReleaseNameSemphoreHelper(parent_named_semaphore);
    elapsed_time = (end_time.tv_sec - start_time.tv_sec) * 1000;
    elapsed_time += (end_time.tv_usec - start_time.tv_usec) / 1000;
    cout << "fsmda_profiling_parent profile_pairing "
         << DeviceClassDescription::GetDeviceClassTypeStringByEnum(
                device_class_type) << " " << elapsed_time << " ms" << endl;
  } else if (FLAGS_profile_prepare) {
    cout << "fsmda_profiling_parent profile_prepare "
         << DeviceClassDescription::GetDeviceClassTypeStringByEnum(
                device_class_type) << " " << elapsed_time << " ms" << endl;
  } else if (FLAGS_profile_command) {
    cout << "fsmda_profiling_parent profile_command "
         << DeviceClassDescription::GetDeviceClassTypeStringByEnum(
                device_class_type) << " " << elapsed_time << " ms" << endl;
  } else if (FLAGS_profile_variable) {
    cout << "fsmda_profiling_parent profile_variable "
         << DeviceClassDescription::GetDeviceClassTypeStringByEnum(
                device_class_type) << " " << elapsed_time << " ms" << endl;
  } else if (FLAGS_profile_remove_device) {
    cout << "fsmda_profiling_parent profile_remove_device "
         << DeviceClassDescription::GetDeviceClassTypeStringByEnum(
                device_class_type) << " " << elapsed_time << " ms" << endl;
  } else if (FLAGS_profile_bufferd_command) {
    cout << "fsmda_profiling_parent profile_bufferd_command "
         << DeviceClassDescription::GetDeviceClassTypeStringByEnum(
                device_class_type) << " " << elapsed_time << " ms" << endl;
  } else {
    WaitNamedSemphoreHelper(parent_named_semaphore);
    ReleaseNameSemphoreHelper(parent_named_semaphore);
  }
  // release parent
  parent_pairing_manager->StopPairing();
  delete parent_pairing_manager;

  return 0;
}
