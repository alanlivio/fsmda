/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include <fsmda/gingancl/communication/ondemand_ccm.h>
#include <cstdlib>
#include <iostream>
#include <cassert>

using namespace std;
/*----------------------------------------------------------------------
 |   main
 +---------------------------------------------------------------------*/
int
main (int argc, char **argv)
{
  // ondemand class description initialize and meet_requirements tests
  OnDemandCCM* onDemandCCM = new OnDemandCCM ();
  onDemandCCM->start_communication_service ();
  assert (onDemandCCM->is_service_started () == true);
  onDemandCCM->stop_communication_service ();
  assert (onDemandCCM->is_service_started () == false);
  return EXIT_SUCCESS;
}
