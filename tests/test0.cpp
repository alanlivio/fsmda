#include <fsmda/gingancl/communication/active_ccm.h>
#include <fsmda/gingancl/communication/active_pcm.h>
#include <fsmda/gingancl/communication/mediacapture_ccm.h>
#include <fsmda/gingancl/communication/mediacapture_pcm.h>
#include <fsmda/gingancl/communication/ondemand_pcm.h>
#include <fsmda/gingancl/communication/passive_ccm.h>
#include <fsmda/gingancl/communication/passive_pcm.h>
#include <fsmda/gingancl/paring/child_paring_manager.h>
#include <fsmda/gingancl/paring/device_description.h>
#include <fsmda/gingancl/paring/parent_paring_manager.h>
#include <cstdlib>
#include <string>
#include <vector>
#include <assert.h>
#include <fsmda/gingancl/paring/device_class_description.h>

int
main (int argc, char **argv)
{
  vector<void*> ptr_vector;
  ParentParingManager * ppm = new ParentParingManager ();
  assert(ppm != NULL);
  ChildParingManager * cpm = new ChildParingManager ();
  assert(cpm != NULL);
  ActivePCM * activePCM = new ActivePCM ();
  assert(activePCM != NULL);
  ActiveCCM * activeCCM = new ActiveCCM ();
  assert(activeCCM != NULL);
  MediaCapturePCM * mediacapturePCM = new MediaCapturePCM ();
  assert(mediacapturePCM != NULL);
  MediaCaptureCCM * mediacaptureCCM = new MediaCaptureCCM ();
  assert(mediacaptureCCM != NULL);
  OnDemandPCM * onDemandPCM = new OnDemandPCM ();
  assert(onDemandPCM != NULL);
  PassivePCM * passivePCM = new PassivePCM ();
  assert(passivePCM != NULL);
  PassiveCCM * passiveCCM = new PassiveCCM ();
  assert(passiveCCM != NULL);
  string device_rdf ("./device.rdf");
  DeviceDescription * device_description = new DeviceDescription (device_rdf);
  assert(device_description != NULL);
  string equirements_rdf ("./requiments.rdf");
  DeviceClassDescription * device_requirements = new DeviceClassDescription (
      equirements_rdf);
  assert(device_requirements != NULL);

  return EXIT_SUCCESS;
}
