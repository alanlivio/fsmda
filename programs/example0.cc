/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/
#include <cassert>
#include <iostream>
#include <NptHttp.h>
#include <NptLogging.h>
#include <PltCtrlPoint.h>
#include <PltUPnP.h>
#include "fsmda/parent_class_handler.h"
#include "fsmda/upnp/upnp_cpm.h"
#include "fsmda/upnp/upnp_ppm.h"
#include "fsmda/upnp/upnp_fsmda_utils.h"

using std::clog;
using std::cin;

/*----------------------------------------------------------------------
 |   main
 +---------------------------------------------------------------------*/
int main(void) {
  ParentClassHandler* parent_class_handler_ = new ParentClassHandler();
  UpnpPpm* upnp_ppm = new UpnpPpm();
  upnp_ppm->set_service_owner(parent_class_handler_);
  upnp_ppm->StartPairingService();

  char buf[256];
  while (cin.getline(buf, 255)) {
    if (*buf == 'q') break;
  }
  upnp_ppm->StopPairingService();
  delete upnp_ppm;
  return 0;
}
