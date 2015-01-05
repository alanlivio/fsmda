/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/
#include <unistd.h>
#include <gflags/gflags.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include "./named_semaphore_helper.h"
#include "fsmda/parent_pairing_manager.h"
#include "fsmda/pairing/upnp_child_pairing.h"
#include "fsmda/pairing/upnp_parent_pairing.h"
#include "fsmda/utils/upnp_fsmda_utils.h"

DEFINE_string(application_id, "", "uuuid application");
DEFINE_string(device_class, DeviceClassDescription::kInvalidDeviceString,
              "device class name: passive,active,ondemand or medicapture");

using std::cin;
using std::cout;
using std::clog;
using std::endl;
using std::getline;

class MockParentPairingManager : public ParentPairingManager {
 public:
  string expected_semaphore;
  virtual void AddDeviceToClass(const string& application_id,
                                const string& device_address,
                                unsigned int class_index,
                                const string& device_desc) {
    clog << "MockParentPairingManager::AddDeviceToClass()" << endl;
    ParentPairingManager::AddDeviceToClass(application_id, device_address,
                                           class_index, device_desc);
    string parent_named_semaphore = FLAGS_application_id + "_parent";
    PostNamedSemphoreHelper(parent_named_semaphore);
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

  // create device_class description
  DeviceClassDescription::DeviceClassType device_class_type;
  device_class_type =
      DeviceClassDescription::GetDeviceClassTypeByString(FLAGS_device_class);
  MockParentPairingManager* parent_pairing_manager =
      new MockParentPairingManager();
  unsigned int class_index = 2;
  DeviceClassDescription* device_class_description =
      new DeviceClassDescription();
  device_class_description->InitializeByDeviceClass(device_class_type);
  parent_pairing_manager->AddClassDescription(FLAGS_application_id, class_index,
                                              device_class_description);

  // wait for parent prepared and start
  string parent_named_semaphore = FLAGS_application_id + "_parent";
  parent_pairing_manager->expected_semaphore = parent_named_semaphore;
  CreateNamedSemphoreHelper(parent_named_semaphore, false);
  parent_pairing_manager->StartPairing();
  WaitNamedSemphoreHelper(parent_named_semaphore);
  ReleaseNameSemphoreHelper(parent_named_semaphore);

  // release parent
  parent_pairing_manager->StopPairing();
  delete parent_pairing_manager;

  return 0;
}
