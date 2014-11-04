/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include "assert.h"
#include "fsmda/communicationmanager/upnp/upnp_active_ccm.h"
#include "fsmda/communicationmanager/upnp/upnp_active_pcm.h"
#include "fsmda/communicationmanager/upnp/upnp_mediacapture_ccm.h"
#include "fsmda/communicationmanager/upnp/upnp_mediacapture_pcm.h"
#include "fsmda/communicationmanager/upnp/upnp_ondemand_ccm.h"
#include "fsmda/communicationmanager/upnp/upnp_ondemand_pcm.h"
#include "fsmda/communicationmanager/upnp/upnp_passive_ccm.h"
#include "fsmda/communicationmanager/upnp/upnp_passive_pcm.h"
#include "fsmda/paringmanager/device_class_description.h"
#include "fsmda/paringmanager/device_description.h"
#include "fsmda/paringmanager/upnp/upnp_child_paring.h"
#include "fsmda/paringmanager/upnp/upnp_parent_paring.h"
#include "fsmda/utils/upnp_fsmda_utils.h"
#include "PltUPnP.h"
#include <cstdlib>

/*----------------------------------------------------------------------
 |   main
 +---------------------------------------------------------------------*/
int
main (int argc, char **argv)
{
  // fsmda/model and fsmda/gingancl constructor tests
  UpnpParentParing * ppm = new UpnpParentParing ();
  assert(ppm != NULL);
  delete ppm;
  UpnpChildParing * cpm = new UpnpChildParing ();
  assert(cpm != NULL);
  delete cpm;
  UpnpActivePcm * activePcm = new UpnpActivePcm ();
  assert(activePcm != NULL);
  delete activePcm;
  UpnpActiveCcm * activeCcm = new UpnpActiveCcm ();
  assert(activeCcm != NULL);
  delete activeCcm;
  UpnpMediaCapturePcm * mediacapturePcm = new UpnpMediaCapturePcm ();
  assert(mediacapturePcm != NULL);
  delete mediacapturePcm;
  UpnpMediaCaptureCcm * mediacaptureCcm = new UpnpMediaCaptureCcm ();
  assert(mediacaptureCcm != NULL);
  delete mediacapturePcm;
  UpnpOnDemandPcm * onDemandPcm = new UpnpOnDemandPcm ();
  assert(onDemandPcm != NULL);
  delete onDemandPcm;
  UpnpOnDemandCcm * onDemandCcm = new UpnpOnDemandCcm ();
  assert(onDemandCcm != NULL);
  delete onDemandCcm;
  UpnpPassivePcm * passivePcm = new UpnpPassivePcm ();
  assert(passivePcm != NULL);
  delete passivePcm;
  UpnpPassiveCcm * passiveCcm = new UpnpPassiveCcm ();
  assert(passiveCcm != NULL);
  delete passiveCcm;
  DeviceDescription * dev_description = new DeviceDescription ();
  assert(dev_description != NULL);
  delete dev_description;
  DeviceClassDescription * dev_class_requirements =
      new DeviceClassDescription ();
  assert(dev_class_requirements != NULL);
  delete dev_class_requirements;

  // fsmda/protocol constructor tests
  PLT_UPnP * upnp = UpnpFsmdaUtils::requestUpnpReference();
  assert(upnp != NULL);
  UpnpFsmdaUtils::releaseUpnpReference();

  return EXIT_SUCCESS;
}
