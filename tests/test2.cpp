/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include <fsmda/gingancl/communication/ondemand_ccm.h>
#include <cstdlib>

/*----------------------------------------------------------------------
 |   main
 +---------------------------------------------------------------------*/
int
main (int argc, char **argv)
{
  // ondemand class description initialize and meet_requirements tests
  OnDemandCCM*  onDemandCCM = new OnDemandCCM();
  onDemandCCM->start_communication_service();
  return EXIT_SUCCESS;
}
