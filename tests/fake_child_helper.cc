/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/
#include <unistd.h>
#include <gflags/gflags.h>
#include <sys/time.h>
#include <signal.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
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

DEFINE_string(device_class, DeviceClassDescription::kActiveDeviceString,
              "device class name: passive,active,ondemand or medicapture");

// Profile Pairing
DEFINE_bool(profile_pairing, false, "enable profile_pairing");
// Profile Fault tolerance (2)
DEFINE_bool(profile_bufferd_command, false, "enable profile_bufferd_command");

/*----------------------------------------------------------------------
 |   Auxiliary variables
 +---------------------------------------------------------------------*/
NPT_SharedVariable child_semaphore;

class MockChildClassHandler : public ChildClassHandler {
 public:
  void set_paired(bool paired) {
    clog << "MockChildClassHandler::SetPaired():: paired = " << paired << endl;
    ChildClassHandler::set_paired(paired);
    child_semaphore.SetValue(1);
  }
  explicit MockChildClassHandler(const DeviceDescription& device_description)
      : ChildClassHandler(device_description) {}
};

MockChildClassHandler* child_class_handler = NULL;

/*----------------------------------------------------------------------
 |   global function
 +---------------------------------------------------------------------*/
void HandleInterrupt(int sig) {
  if (child_class_handler != NULL) {
    cout << "fake_child_helper::releasing after receive INT" << endl;
    child_semaphore.SetValue(1);
    child_class_handler->StopPairing();
  }
}

double CalculateElapsedTime(timeval start_time, timeval end_time) {
  double elapsed_time;
  elapsed_time = (end_time.tv_sec - start_time.tv_sec) * 1000.0;
  elapsed_time += (end_time.tv_usec - start_time.tv_usec) / 1000.0;
  return elapsed_time;
}

/*----------------------------------------------------------------------
 |   main
 +---------------------------------------------------------------------*/
int main(int argc, char** argv) {
  google::SetVersionString("0.1");
  google::SetUsageMessage(
      "fake_child_helper --device-class=<passive|active|ondemand|medicapture>");
  google::ParseCommandLineFlags(&argc, &argv, true);

  signal(SIGINT, HandleInterrupt);
  signal(SIGSTOP, HandleInterrupt);
  signal(SIGTERM, HandleInterrupt);
  signal(SIGTSTP, HandleInterrupt);

  // redirect clog to /dev/null/
  static std::ofstream logOutput;
  logOutput.open("/dev/null");
  clog.rdbuf(logOutput.rdbuf());

  cout << "fake_child_helper::device_class=" << FLAGS_device_class << endl;

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
  child_class_handler->StartPairing();

  cout << "fake_child_helper:: wait for pairing..." << endl;
  gettimeofday(&start_time, NULL);
  child_semaphore.WaitUntilEquals(1, NPT_TIMEOUT_INFINITE);
  child_semaphore.SetValue(0);

  if (FLAGS_profile_pairing) {
    // wait for pairing
    gettimeofday(&end_time, NULL);
    cout << "fsmda_child profile_pairing "
         << DeviceClassDescription::GetDeviceClassTypeStringByEnum(device_class)
         << " " << CalculateElapsedTime(start_time, end_time) << " ms" << endl;
  } else if (FLAGS_profile_bufferd_command) {
    child_class_handler->StopPairing();
    delete child_class_handler;
    gettimeofday(&start_time, NULL);
    child_class_handler = new MockChildClassHandler(device_description);
    child_class_handler->StartPairing();
    cout << "fake_child_helper:: wait for second pairing..." << endl;
    child_semaphore.WaitWhileEquals(1, NPT_TIMEOUT_INFINITE);
    gettimeofday(&end_time, NULL);
    cout << "fsmda_child profile_bufferd_command "
         << DeviceClassDescription::GetDeviceClassTypeStringByEnum(device_class)
         << " " << CalculateElapsedTime(start_time, end_time) << " ms" << endl;
  }

  // release child
  child_class_handler->StopPairing();
  delete child_class_handler;

  return 0;
}
