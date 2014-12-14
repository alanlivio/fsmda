/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include "fsmda/parent_pairing_manager.h"
#include "fsmda/pairing_services/upnp_child_pairing.h"
#include "fsmda/pairing_services/upnp_parent_pairing.h"
#include "fsmda/utils/upnp_fsmda_utils.h"

using std::cin;
using std::clog;
using std::endl;
using std::getline;
/*----------------------------------------------------------------------
 |   main
 +---------------------------------------------------------------------*/
int main(void) {
  //  wait for a stop
  string device_class_command;
  getline(cin, device_class_command);
  clog << "fake_parent_helper.cc::main():: received a " << device_class_command
       << " commnad" << endl;
  DeviceClassDescription::DeviceClassType device_class_type;
  device_class_type =
      DeviceClassDescription::GetDeviceClassTypeByString(device_class_command);

  // start parent pairing service with fake discover params
  // only for enable handshake
  UpnpParentPairing* upnp_parent_pairing = new UpnpParentPairing();
  string application_id = "fake-application-id";
  unsigned int class_index = 2;
  DeviceClassDescription* device_class_description =
      new DeviceClassDescription();
  device_class_description->InitializeByDeviceClass(device_class_type);
  DeviceClassDiscoverParams* dicover_params = new DeviceClassDiscoverParams(
      application_id, class_index, device_class_description);
  upnp_parent_pairing->AddDeviceClassForDiscover(dicover_params);

  // start parent pairing service
  upnp_parent_pairing->StartPairingService(), 0;
  upnp_parent_pairing->IsPairingServiceStarted();

  sleep(3);
  upnp_parent_pairing->StopPairingService();
  delete upnp_parent_pairing;

  return 0;
}
