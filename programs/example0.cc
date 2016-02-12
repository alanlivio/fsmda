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

int main(void) {
  ParentClassHandler* parent_class_handler_ = new ParentClassHandler();
  UpnpPpm* upnp_ppm = new UpnpPpm();
  upnp_ppm->set_service_owner(parent_class_handler_);
  upnp_ppm->start_pairing_service();

  char buf[256];
  while (cin.getline(buf, 255)) {
    if (*buf == 'q')
      break;
  }
  upnp_ppm->stop_pairing_service();
  delete upnp_ppm;
  return 0;
}
