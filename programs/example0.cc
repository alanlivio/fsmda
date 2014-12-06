/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include <NptHttp.h>
#include <NptLogging.h>
#include <PltCtrlPoint.h>
#include <PltUPnP.h>
#include "fsmda/paring/upnp_child_paring.h"
#include "fsmda/paring/upnp_parent_paring.h"
#include "fsmda/utils/upnp_fsmda_utils.h"
#include <cassert>
#include <cstdio>
#include <iostream>

using std::clog;
/*----------------------------------------------------------------------
 |   main
 +---------------------------------------------------------------------*/
int main(void) {
  UpnpParentParing* upnp_parent_paring = new UpnpParentParing();
  upnp_parent_paring->StartService();

  //  UpnpChildParing* upnp_child_paring = new
  // UpnpChildParing("UpnpChildParing");
  //  upnp_child_paring->StartService();
  char buf[256];
  while (gets(buf)) {
    if (*buf == 'q') break;
  }
  return 0;
}
