/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/
#include <cassert>
#include <iostream>
#include <NptHttp.h>
#include <NptLogging.h>
#include <PltCtrlPoint.h>
#include <PltUPnP.h>
#include "fsmda/paring_services/upnp_child_paring.h"
#include "fsmda/paring_services/upnp_parent_paring.h"
#include "fsmda/parent_paring_manager.h"
#include "fsmda/utils/upnp_fsmda_utils.h"

using std::clog;
using std::cin;

/*----------------------------------------------------------------------
 |   main
 +---------------------------------------------------------------------*/
int main(void) {
  ParentParingManager* parent_paring_manager_ = new ParentParingManager();
  UpnpParentParing* upnp_parent_paring =
      new UpnpParentParing(parent_paring_manager_);
  upnp_parent_paring->StartParingService();

  char buf[256];
  while (cin.getline(buf, 255)) {
    if (*buf == 'q') break;
  }
  upnp_parent_paring->StopParingService();
  delete upnp_parent_paring;
  return 0;
}
