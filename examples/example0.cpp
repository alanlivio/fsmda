#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Platinum.h"
#include "PltMediaConnect.h"
#include "PltSyncMediaBrowser.h"

int
main (void)
{
  // setup Neptune logging
  NPT_LogManager::GetDefault ().Configure (
      "plist:.level=INFO;.handlers=ConsoleHandler;.ConsoleHandler.colors=off;.ConsoleHandler.filter=58");

  PLT_UPnP upnp;
  PLT_CtrlPointReference ctrlPoint (new PLT_CtrlPoint ());
  upnp.AddCtrlPoint (ctrlPoint);

  upnp.Start ();

  // extra broadcast discover
  ctrlPoint->Discover (NPT_HttpUrl ("255.255.255.255", 1900, "*"),
		       "upnp:rootdevice", 1);

  char buf[256];
  while (gets (buf))
    {
      if (*buf == 'q')
	break;
    }

  upnp.Stop ();

  return 0;
}
