#include <assert.h>
#include <fsmda/gingancl/communication/active_ccm.h>
#include <fsmda/gingancl/communication/active_pcm.h>
#include <fsmda/gingancl/communication/mediacapture_ccm.h>
#include <fsmda/gingancl/communication/mediacapture_pcm.h>
#include <fsmda/gingancl/communication/ondemand_pcm.h>
#include <fsmda/gingancl/communication/passive_ccm.h>
#include <fsmda/gingancl/communication/passive_pcm.h>
#include <fsmda/gingancl/paring/child_paring_manager.h>
#include <fsmda/gingancl/paring/device_class_description.h>
#include <fsmda/gingancl/paring/device_description.h>
#include <fsmda/gingancl/paring/parent_paring_manager.h>
#include <cstdlib>
#include <vector>

int
main (int argc, char **argv)
{
  vector<void*> ptr_vector;
  ParentParingManager * ppm = new ParentParingManager ();
  assert(ppm != NULL);
  delete ppm;

  ChildParingManager * cpm = new ChildParingManager ();
  assert(cpm != NULL);
  delete cpm;

  ActivePCM * activePCM = new ActivePCM ();
  assert(activePCM != NULL);
  delete activePCM;

  ActiveCCM * activeCCM = new ActiveCCM ();
  assert(activeCCM != NULL);
  delete activeCCM;

  MediaCapturePCM * mediacapturePCM = new MediaCapturePCM ();
  assert(mediacapturePCM != NULL);
  delete mediacapturePCM;

  MediaCaptureCCM * mediacaptureCCM = new MediaCaptureCCM ();
  assert(mediacaptureCCM != NULL);
  delete mediacapturePCM;

  OnDemandPCM * onDemandPCM = new OnDemandPCM ();
  assert(onDemandPCM != NULL);
  delete onDemandPCM;

  PassivePCM * passivePCM = new PassivePCM ();
  assert(passivePCM != NULL);
  delete passivePCM;

  PassiveCCM * passiveCCM = new PassiveCCM ();
  assert(passiveCCM != NULL);
  delete passiveCCM;

  DeviceDescription * dev_description = new DeviceDescription ();
  assert(dev_description != NULL);
  delete dev_description;

  DeviceClassDescription * dev_class_requirements = new DeviceClassDescription ();
  assert(dev_class_requirements != NULL);
  delete dev_class_requirements;

  return EXIT_SUCCESS;
}
