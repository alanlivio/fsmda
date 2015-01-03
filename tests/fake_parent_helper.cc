/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/
#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <gflags/gflags.h>
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

  // start parent pairing service with fake discover params
  // only for enable handshake
  DeviceClassDescription::DeviceClassType device_class_type;
  device_class_type =
      DeviceClassDescription::GetDeviceClassTypeByString(FLAGS_device_class);
  UpnpParentPairing* upnp_parent_pairing = new UpnpParentPairing();
  unsigned int class_index = 2;
  DeviceClassDescription* device_class_description =
      new DeviceClassDescription();
  device_class_description->InitializeByDeviceClass(device_class_type);
  DeviceClassDiscoverParams* dicover_params = new DeviceClassDiscoverParams(
      FLAGS_application_id, class_index, device_class_description);
  upnp_parent_pairing->AddDeviceClassForDiscover(dicover_params);

  // start parent pairing service
  upnp_parent_pairing->StartPairingService(), 0;
  upnp_parent_pairing->IsPairingServiceStarted();

  sleep(2);
  //  string parent_named_semaphore = application_id + "_parent";
  //  CreateNamedSemphoreHelper(parent_named_semaphore, true);
  //  WaitNamedSemphoreHelper(parent_named_semaphore);
  upnp_parent_pairing->StopPairingService();
  delete upnp_parent_pairing;

  return 0;
}
