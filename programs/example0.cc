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

using namespace std;
/*----------------------------------------------------------------------
 |   main
 +---------------------------------------------------------------------*/
int
main (void)
{
  UpnpParentParing* upnpParentParing = new UpnpParentParing ();
  upnpParentParing->start_service ();

  UpnpChildParing* upnpChildParing = new UpnpChildParing ();
  upnpChildParing->start_service ();
  char buf[256];
  while (gets (buf))
    {
      if (*buf == 'q')
	break;
    }
  return 0;
}
