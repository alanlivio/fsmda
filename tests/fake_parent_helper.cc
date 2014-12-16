/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/
#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include "./named_semaphore_helper.h"
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
  //  read device class type by stdin
  string device_class_command;
  getline(cin, device_class_command);
  clog << "fake_parent_helper.cc::main():: received device_class_command = "
       << device_class_command << endl;

  //  read app id by stdin
  string application_id;
  getline(cin, application_id);
  clog << "fake_parent_helper.cc::main():: received app_id = " << application_id
       << endl;

  // start parent pairing service with fake discover params
  // only for enable handshake
  DeviceClassDescription::DeviceClassType device_class_type;
  device_class_type =
      DeviceClassDescription::GetDeviceClassTypeByString(device_class_command);
  UpnpParentPairing* upnp_parent_pairing = new UpnpParentPairing();
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

  sleep(2);
  //  string parent_named_semaphore = application_id + "_parent";
  //  CreateNamedSemphoreHelper(parent_named_semaphore, true);
  //  WaitNamedSemphoreHelper(parent_named_semaphore);
  upnp_parent_pairing->StopPairingService();
  delete upnp_parent_pairing;

  return 0;
}
