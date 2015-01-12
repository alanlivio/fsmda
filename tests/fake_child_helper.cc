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
#include "fsmda//device_class_description.h"
#include "fsmda//device_description.h"
#include "fsmda/parent_class_handler.h"
#include "fsmda/child_class_handler.h"
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

// Profile Pairing
DEFINE_bool(profile_pairing, false, "enable profile_pairing");
// Profile Fault tolerance (2)
DEFINE_bool(profile_bufferd_command, false, "enable profile_bufferd_command");

double CalculateElapsedTime(timeval start_time, timeval end_time) {
  double elapsed_time;
  elapsed_time = (end_time.tv_sec - start_time.tv_sec) * 1000.0;
  elapsed_time += (end_time.tv_usec - start_time.tv_usec) / 1000.0;
  return elapsed_time;
}

class MockChildClassHandler : public ChildClassHandler {
 public:
  string expected_semaphore;
  void set_paired(bool paired) {
    clog << "MockChildClassHandler::SetPaired():: paired = " << paired << endl;
    ChildClassHandler::set_paired(paired);
    PostNamedSemphoreHelper(expected_semaphore);
  }
  explicit MockChildClassHandler(const DeviceDescription& device_description)
      : ChildClassHandler(device_description) {}
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

  cout << "fake_child_helper::device_class=" << FLAGS_device_class
       << ",application_id=" << FLAGS_application_id << endl;

  MockChildClassHandler* child_class_handler;
  timeval start_time, end_time;

  // configure child
  DeviceClassDescription::DeviceClassType device_class =
      DeviceClassDescription::GetDeviceClassTypeByString(FLAGS_device_class);
  DeviceDescription device_description;
  const char* rdf_content =
      DeviceClassDescription::GetDeviceClassRdfDefaultContentByType(
          device_class);
  device_description.InitializeByRdfContent(rdf_content);
  child_class_handler = new MockChildClassHandler(device_description);

  // start child
  child_class_handler->expected_semaphore = FLAGS_application_id;
  CreateNamedSemphoreHelper(FLAGS_application_id, false);
  child_class_handler->StartPairing();

  gettimeofday(&start_time, NULL);
  cout << "fake_child_helper:: wait for pairing..." << endl;
  WaitNamedSemphoreHelper(FLAGS_application_id);

  if (FLAGS_profile_pairing) {
    // wait for pairing
    gettimeofday(&end_time, NULL);
    cout << "fsmda_child profile_pairing "
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
  child_class_handler->StopPairing();
  delete child_class_handler;

  return 0;
}
