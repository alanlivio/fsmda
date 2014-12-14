/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/
#include <iostream>
#include "fsmda/parent_pairing_manager.h"
#include "fsmda/pairing_services/upnp_child_pairing.h"
#include "fsmda/pairing_services/upnp_parent_pairing.h"
#include "fsmda/utils/upnp_fsmda_utils.h"

using std::clog;
using std::cin;

/*----------------------------------------------------------------------
 |   main
 +---------------------------------------------------------------------*/
int main(void) {
  // create parent pairing service
  UpnpParentPairing* upnp_parent_pairing = new UpnpParentPairing();
  DeviceClassDescription* device_class_description =
      new DeviceClassDescription();
  device_class_description->InitializeByDeviceClass(
      DeviceClassDescription::kActiveDevice);
  string application_id;
  UpnpFsmdaUtils::GenerateGUID(&application_id);
  unsigned int class_index = 2;
  DeviceClassDiscoverParams* dicover_params = new DeviceClassDiscoverParams(
      application_id, class_index, device_class_description);
  upnp_parent_pairing->AddDeviceClassForDiscover(dicover_params);

  // start parent pairing service
  upnp_parent_pairing->StartPairingService(), 0;
  upnp_parent_pairing->IsPairingServiceStarted();

  //  wait for a q char
  char buf[256];
  while (cin.getline(buf, 255)) {
    if (*buf == 'q') break;
  }
  upnp_parent_pairing->StopPairingService();
  delete upnp_parent_pairing;
  return 0;
}
