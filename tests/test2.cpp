/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include "fsmda/communicationmanager/upnp/upnp_ondemand_ccm.h"
#include "fsmda/paringmanager/upnp/upnp_child_paring.h"
#include "fsmda/paringmanager/upnp/upnp_parent_paring.h"
#include "unistd.h"
#include <cassert>
#include <cstdlib>
#include <iostream>

using namespace std;
/*----------------------------------------------------------------------
 |   main
 +---------------------------------------------------------------------*/
int
main (int argc, char **argv)
{
  // parent paring tests
  cout << "----------------------------------------------------" << endl;
  UpnpParentParing* upnpParentParing = new UpnpParentParing ();
  assert(upnpParentParing->start_service () == 0);
  sleep (1);
  assert(upnpParentParing->is_service_started () == true);
  upnpParentParing->stop_service ();
  assert(upnpParentParing->is_service_started () == false);

  // child paring tests
  cout << "----------------------------------------------------" << endl;
  UpnpChildParing* upnpChildParing = new UpnpChildParing ();
  assert(upnpChildParing->start_service () == 0);
  sleep (1);
  assert(upnpChildParing->is_service_started () == true);
  upnpChildParing->stop_service ();
  assert(upnpChildParing->is_service_started () == false);

  // ondemand class description initialize and meet_requirements tests
  cout << "----------------------------------------------------" << endl;
  UpnpOnDemandCcm* onDemandCCM = new UpnpOnDemandCcm ();
  onDemandCCM->start_communication_service ();
  assert(onDemandCCM->is_service_started () == true);
  onDemandCCM->stop_communication_service ();
  assert(onDemandCCM->is_service_started () == false);

  return EXIT_SUCCESS;
}
