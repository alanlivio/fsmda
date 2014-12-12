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
  UpnpParentPairing* upnp_parent_pairing = new UpnpParentPairing();
  upnp_parent_pairing->StartPairingService();
  char buf[256];
  while (cin.getline(buf, 255)) {
    if (*buf == 'q') break;
  }
  upnp_parent_pairing->StopPairingService();
  delete upnp_parent_pairing;
  return 0;
}
