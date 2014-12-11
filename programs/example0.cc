/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/
#include <cassert>
#include <iostream>
#include <NptHttp.h>
#include <NptLogging.h>
#include <PltCtrlPoint.h>
#include <PltUPnP.h>
#include "fsmda/paring/child_paring_manager.h"
#include "fsmda/paring/parent_paring_manager.h"
#include "fsmda/paring/upnp_child_paring.h"
#include "fsmda/paring/upnp_parent_paring.h"
#include "fsmda/utils/upnp_fsmda_utils.h"

using std::clog;
using std::cin;

/*----------------------------------------------------------------------
 |   main
 +---------------------------------------------------------------------*/
int main(void) {
  ChildParingManager* parent_paring_manager = new ChildParingManager();
  UpnpChildParing* upnp_child_paring =
      new UpnpChildParing(parent_paring_manager);
  upnp_child_paring->StartParingService();

  char buf[256];
  while (cin.getline(buf, 255)) {
    if (*buf == 'q') break;
  }

  upnp_child_paring->StopParingService();
  delete upnp_child_paring;
  delete parent_paring_manager;

  return 0;
}
