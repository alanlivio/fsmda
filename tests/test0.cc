/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include "fsmda/communication/upnp_active_ccm.h"
#include "fsmda/communication/upnp_active_pcm.h"
#include "fsmda/communication/upnp_mediacapture_ccm.h"
#include "fsmda/communication/upnp_mediacapture_pcm.h"
#include "fsmda/communication/upnp_ondemand_ccm.h"
#include "fsmda/communication/upnp_ondemand_pcm.h"
#include "fsmda/communication/upnp_passive_ccm.h"
#include "fsmda/communication/upnp_passive_pcm.h"
#include "fsmda/paring/device_class_description.h"
#include "fsmda/paring/device_description.h"
#include "fsmda/paring/upnp_child_paring.h"
#include "fsmda/paring/upnp_parent_paring.h"
#include "fsmda/utils/upnp_fsmda_utils.h"
#include "gtest/gtest.h"
#include "gtest/internal/gtest-linked_ptr.h"
#include "PltUPnP.h"
#include <cstdlib>

/*----------------------------------------------------------------------
 |   main
 +---------------------------------------------------------------------*/

TEST(Paring, Constructors)
{
  UpnpParentParing * ppm = new UpnpParentParing ();
  EXPECT_TRUE(ppm != NULL);
  delete ppm;
  UpnpChildParing * cpm = new UpnpChildParing ();
  EXPECT_TRUE(cpm != NULL);
  delete cpm;
  DeviceDescription * dev_description = new DeviceDescription ();
  EXPECT_TRUE(dev_description != NULL);
  delete dev_description;
  DeviceClassDescription * dev_class_requirements =
      new DeviceClassDescription ();
  EXPECT_TRUE(dev_class_requirements != NULL);
  delete dev_class_requirements;
}

TEST(Communication, Constructors)
{
  UpnpActivePcm * activePcm = new UpnpActivePcm ();
  EXPECT_TRUE(activePcm != NULL);
  delete activePcm;
  UpnpActiveCcm * activeCcm = new UpnpActiveCcm ();
  EXPECT_TRUE(activeCcm != NULL);
  delete activeCcm;
  UpnpMediaCapturePcm * mediacapturePcm = new UpnpMediaCapturePcm ();
  EXPECT_TRUE(mediacapturePcm != NULL);
  delete mediacapturePcm;
  UpnpMediaCaptureCcm * mediacaptureCcm = new UpnpMediaCaptureCcm ();
  EXPECT_TRUE(mediacaptureCcm != NULL);
  delete mediacapturePcm;
  UpnpOnDemandPcm * onDemandPcm = new UpnpOnDemandPcm ();
  EXPECT_TRUE(onDemandPcm != NULL);
  delete onDemandPcm;
  UpnpOnDemandCcm * onDemandCcm = new UpnpOnDemandCcm ();
  EXPECT_TRUE(onDemandCcm != NULL);
  delete onDemandCcm;
  UpnpPassivePcm * passivePcm = new UpnpPassivePcm ();
  EXPECT_TRUE(passivePcm != NULL);
  delete passivePcm;
  UpnpPassiveCcm * passiveCcm = new UpnpPassiveCcm ();
  EXPECT_TRUE(passiveCcm != NULL);
  delete passiveCcm;
}

TEST(Utils, Upnp)
{
  EXPECT_EQ(0, UpnpFsmdaUtils::references_count_);
  PLT_UPnP * upnp = UpnpFsmdaUtils::requestUpnpReference ();
  EXPECT_TRUE(upnp != NULL);
  EXPECT_EQ(1, UpnpFsmdaUtils::references_count_);
  UpnpFsmdaUtils::releaseUpnpReference ();
  EXPECT_EQ(0, UpnpFsmdaUtils::references_count_);
  UpnpFsmdaUtils::releaseUpnpReference ();
  EXPECT_EQ(0, UpnpFsmdaUtils::references_count_);
}
