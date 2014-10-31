/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include "fsmda/communicationmanager/upnp/upnp_ondemand_ccm.h"
#include <cassert>
#include <cstdlib>

using namespace std;
/*----------------------------------------------------------------------
 |   main
 +---------------------------------------------------------------------*/
int
main (int argc, char **argv)
{
  // ondemand class description initialize and meet_requirements tests
  UpnpOnDemandCcm* onDemandCCM = new UpnpOnDemandCcm ();
  onDemandCCM->start_communication_service ();
  assert (onDemandCCM->is_service_started () == true);
  onDemandCCM->stop_communication_service ();
  assert (onDemandCCM->is_service_started () == false);
  return EXIT_SUCCESS;
}
