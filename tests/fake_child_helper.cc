
#include <unistd.h>
#include <gflags/gflags.h>
#include <sys/time.h>
#include <signal.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include "fsmda/device_class_description.h"
#include "fsmda/device_description.h"
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
// Profile Variable changing
DEFINE_bool(profile_variable, false, "enable profile_variable");

NPT_SharedVariable child_semaphore;
double CalculateElapsedTime(timeval start_time, timeval end_time) {
  double elapsed_time;
  elapsed_time = (end_time.tv_sec - start_time.tv_sec) * 1000.0;
  elapsed_time += (end_time.tv_usec - start_time.tv_usec) / 1000.0;
  return elapsed_time;
}

class MockChildClassHandler : public ChildClassHandler {
 public:
  void set_paired(bool paired) {
    cout << "MockChildClassHandler::SetPaired():: paired = " << paired << endl;
    ChildClassHandler::set_paired(paired);
    child_semaphore.SetValue(1);
  }
  explicit MockChildClassHandler(const DeviceDescription& device_description)
      : ChildClassHandler(device_description) {}
};

class MockActivePlayer : public ActivePlayerInterface {
 public:
  MockActivePlayer() { ccm = NULL; }
  ActivePlayerListenerInterface* ccm;
  virtual void Prepare(const string& object_src, vector<Property> properties,
                       vector<Event> events) {}
  virtual void AddEvent(Event evt) {}
  virtual void RemoveEvent(const string& event_id) {}
  virtual void PostAction(const string& event_id, const string& action) {}
  virtual void RequestPropertyValue(const string& property_name) {
    cout << "MockActivePlayer::RequestPropertyValue()::" << endl;
    if (ccm != NULL)
      ccm->ReportPropertyValue(property_name, "RequestPropertyValue return");
    child_semaphore.SetValue(1);
  }

  virtual void SetPropertyValue(const string& property_name,
                                const string& property_value,
                                unsigned int property_uration) {
    cout << "MockActivePlayer::SetPropertyValue()::" << endl;
    if (ccm != NULL)
      ccm->ReportPropertyValue(property_name, "SetPropertyValue return");
    child_semaphore.SetValue(1);
  }
  virtual void RegistryPlayerListener(ActivePlayerListenerInterface* listener) {
    ccm = listener;
  }
};

int main(int argc, char** argv) {
  google::SetVersionString("0.1");
  google::SetUsageMessage(
      "fake_child_helper --device-class=<passive|active|ondemand|medicapture>");
  google::ParseCommandLineFlags(&argc, &argv, true);

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
  MockChildClassHandler* child_class_handler;
  child_class_handler = new MockChildClassHandler(device_description);
  // Set Player if is a active device
  MockActivePlayer* active_player;
  active_player = new MockActivePlayer();
  child_class_handler->set_active_player(active_player);

  // start child
  child_class_handler->StartPairing();

  cout << "fake_child_helper:: wait for pairing..." << endl;
  gettimeofday(&start_time, NULL);
  child_semaphore.SetValue(0);
  child_semaphore.WaitWhileEquals(0, NPT_TIMEOUT_INFINITE);

  if (FLAGS_profile_pairing) {
    gettimeofday(&end_time, NULL);
    cout << "fsmda_child profile_pairing "
         << DeviceClassDescription::GetDeviceClassTypeStringByEnum(device_class)
         << " " << CalculateElapsedTime(start_time, end_time) << " ms" << endl;
  } else if (FLAGS_profile_variable) {
    cout << "waiting for SetPropertyValue" << endl;
    child_semaphore.SetValue(0);
    child_semaphore.WaitWhileEquals(0, NPT_TIMEOUT_INFINITE);
  } else if (FLAGS_profile_bufferd_command) {
    //    gettimeofday(&end_time, NULL);
    //    cout << "fsmda_child profile_bufferd_command "
    //         <<
    //         DeviceClassDescription::GetDeviceClassTypeStringByEnum(device_class)
    //         << " " << CalculateElapsedTime(start_time, end_time) << " ms" <<
    //         endl;
    child_class_handler->StopPairing();
    delete child_class_handler;
    gettimeofday(&start_time, NULL);
    child_class_handler = new MockChildClassHandler(device_description);
    child_class_handler->StartPairing();
    cout << "fake_child_helper:: wait for second pairing..." << endl;
    child_semaphore.SetValue(0);
    child_semaphore.WaitWhileEquals(0, NPT_TIMEOUT_INFINITE);
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
