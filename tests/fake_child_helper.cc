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
#include "fsmda/device_class_description.h"
#include "fsmda/device_description.h"
#include "fsmda/parent_pairing_manager.h"
#include "fsmda/child_pairing_manager.h"
#include "fsmda/utils/upnp_fsmda_utils.h"

DEFINE_string(application_id, "", "uuuid application");
DEFINE_string(device_class, DeviceClassDescription::kInvalidDeviceString,
              "device class name: passive,active,ondemand or medicapture");

using std::cin;
using std::cout;
using std::clog;
using std::endl;
using std::getline;

class MockChildPairingManager : public ChildPairingManager {
 public:
  string expected_app_id;
  void SetPaired(bool paired) {
    clog << "MockChildPairingManager::SetPaired():: paired = " << paired
         << endl;
    ChildPairingManager::SetPaired(paired);
    PostNamedSemphoreHelper(expected_app_id);
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
//  static std::ofstream logOutput;
//  logOutput.open("/dev/null");
//  clog.rdbuf(logOutput.rdbuf());

  clog << "fake_parent_helper.cc::main():: device_class=" << FLAGS_device_class
       << endl;
  clog << "fake_parent_helper.cc::main():: application_id="
       << FLAGS_application_id << endl;

  MockChildPairingManager* child_pairing_manager;
  timeval start_time, end_time;
  double elapsed_time;
  CreateNamedSemphoreHelper(FLAGS_application_id, true);

  // create description for device_class
  DeviceClassDescription::DeviceClassType device_class =
      DeviceClassDescription::GetDeviceClassTypeByString(FLAGS_device_class);
  DeviceDescription device_description;
  const char* rdf_content =
      DeviceClassDescription::GetDeviceClassRdfDefaultContentByType(
          device_class);
  device_description.InitializeByRdfContent(rdf_content);

  // start ChildPairingManager
  child_pairing_manager = new MockChildPairingManager(device_description);
  child_pairing_manager->expected_app_id = FLAGS_application_id;
  child_pairing_manager->StartPairing();
  gettimeofday(&start_time, NULL);

  // child wait for ParentPostSemphoreHelper call
  WaitNamedSemphoreHelper(FLAGS_application_id);
  gettimeofday(&end_time, NULL);

  // sec to ms
  elapsed_time = (end_time.tv_sec - start_time.tv_sec) * 1000;
  // us to ms
  elapsed_time += (end_time.tv_usec - start_time.tv_usec) / 1000;

  cout << "PairingWithOneDeviceHelper(diferent_processes="
       << "yes"
       << ", device_class_type=" << device_class
       << ")::elapsed_time=" << elapsed_time << " ms" << endl;

  // release child
  child_pairing_manager->StopPairing();
  delete child_pairing_manager;

  return 0;
}
