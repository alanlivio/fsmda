/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/
#include <cassert>
#include <iostream>
#include <NptHttp.h>
#include <NptLogging.h>
#include <PltCtrlPoint.h>
#include <PltUPnP.h>
#include "fsmda/parent_pairing_manager.h"
#include "fsmda/upnp/upnp_child_pairing.h"
#include "fsmda/upnp/upnp_parent_pairing.h"
#include "fsmda/upnp/upnp_fsmda_utils.h"

using std::clog;
using std::cin;

/*----------------------------------------------------------------------
 |   main
 +---------------------------------------------------------------------*/
int main(void) {
  ParentPairingManager* parent_pairing_manager_ = new ParentPairingManager();
  UpnpParentPairing* upnp_parent_pairing = new UpnpParentPairing();
  upnp_parent_pairing->set_service_owner(parent_pairing_manager_);
  upnp_parent_pairing->StartPairingService();

  char buf[256];
  while (cin.getline(buf, 255)) {
    if (*buf == 'q') break;
  }
  upnp_parent_pairing->StopPairingService();
  delete upnp_parent_pairing;
  return 0;
}
