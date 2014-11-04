/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include "fsmda/communicationmanager/upnp/upnp_ondemand_ccm.h"
#include "fsmda/paringmanager/upnp/upnp_child_paring.h"
#include "fsmda/paringmanager/upnp/upnp_parent_paring.h"
#include <cassert>
#include <cstdlib>

using namespace std;
/*----------------------------------------------------------------------
 |   main
 +---------------------------------------------------------------------*/
int
main (int argc, char **argv)
{
  // parent paring tests
  UpnpParentParing* upnpParentParing = new UpnpParentParing ();
  upnpParentParing->start_service ();
  assert(upnpParentParing->is_service_started () == true);
  upnpParentParing->stop_service ();
  assert(upnpParentParing->is_service_started () == false);

  // child paring tests
  UpnpChildParing* upnpChildParing = new UpnpChildParing ();
  upnpChildParing->start_service ();
  assert(upnpChildParing->is_service_started () == true);
  upnpChildParing->stop_service ();
  assert(upnpChildParing->is_service_started () == false);

  // ondemand class description initialize and meet_requirements tests
  UpnpOnDemandCcm* onDemandCCM = new UpnpOnDemandCcm ();
  onDemandCCM->start_communication_service ();
  assert(onDemandCCM->is_service_started () == true);
  onDemandCCM->stop_communication_service ();
  assert(onDemandCCM->is_service_started () == false);

  return EXIT_SUCCESS;
}
