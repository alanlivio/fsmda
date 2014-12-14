/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/
#include <iostream>
#include "fsmda/parent_pairing_manager.h"
#include "fsmda/pairing_services/upnp_child_pairing.h"
#include "fsmda/pairing_services/upnp_parent_pairing.h"
#include "fsmda/utils/upnp_fsmda_utils.h"

using std::cin;

/*----------------------------------------------------------------------
 |   main
 +---------------------------------------------------------------------*/
int main(void) {
  // start parent pairing service with fake discover params
  // only for enable handshake
  UpnpParentPairing* upnp_parent_pairing = new UpnpParentPairing();
  string application_id = "fake-application-id";
  unsigned int class_index = 2;
  DeviceClassDescription* device_class_description =
      new DeviceClassDescription();
  device_class_description->InitializeByDeviceClass(
      DeviceClassDescription::kActiveDevice);
  DeviceClassDiscoverParams* dicover_params = new DeviceClassDiscoverParams(
      application_id, class_index, device_class_description);
  upnp_parent_pairing->AddDeviceClassForDiscover(dicover_params);

  // start parent pairing service
  upnp_parent_pairing->StartPairingService(), 0;
  upnp_parent_pairing->IsPairingServiceStarted();

  //  wait for a q char
  string command;
  while (cin >> command) {
    if (command == "stop") break;
  }
  upnp_parent_pairing->StopPairingService();
  delete upnp_parent_pairing;

  return 0;
}
