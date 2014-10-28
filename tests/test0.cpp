#include <cassert>
#include <cstring>
#include <cstdlib>

#include "fsmda/services/upnp_service.h"
#include "fsmda/model/communication/ondemand_object_control.h"
#include "fsmda/model/communication/active_object_control.h"
#include "fsmda/model/communication/passive_object_control.h"
#include "fsmda/model/communication/mediacapture_object_control.h"
#include "fsmda/model/paring/class_handling.h"
#include "fsmda/model/paring/device_paring.h"
#include "fsmda/gingancl/paring/parent_paring_manager.h"
#include "fsmda/gingancl/paring/child_paring_manager.h"
#include "fsmda/gingancl/communication/active_pcm.h"
#include "fsmda/gingancl/communication/active_ccm.h"
#include "fsmda/gingancl/communication/mediacapture_pcm.h"
#include "fsmda/gingancl/communication/mediacapture_ccm.h"
#include "fsmda/gingancl/communication/ondemand_pcm.h"
#include "fsmda/gingancl/communication/passive_pcm.h"
#include "fsmda/gingancl/communication/passive_ccm.h"

int
main (int argc, char **argv)
{
  ParentParingManager * ppm = new ParentParingManager ();
  assert(ppm != NULL);
  ChildParingManager * cpm = new ChildParingManager ();
  assert(cpm != NULL);
  delete ppm;
  delete cpm;

  ActivePCM * activePCM = new ActivePCM();
  ActiveCCM * activeCCM = new ActiveCCM();
  MediaCapturePCM * mediacapturePCM = new MediaCapturePCM();
  MediaCaptureCCM * mediacaptureCCM = new MediaCaptureCCM();
  OnDemandPCM * onDemandPCM = new OnDemandPCM();
  PassivePCM * passivePCM = new PassivePCM();
  PassiveCCM * passiveCCM = new PassiveCCM();


  return EXIT_SUCCESS;
}
