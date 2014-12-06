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

TEST(Paring, Constructors) {
  UpnpParentParing* ppm = new UpnpParentParing();
  EXPECT_TRUE(ppm != NULL);
  delete ppm;
  UpnpChildParing* cpm = new UpnpChildParing();
  EXPECT_TRUE(cpm != NULL);
  delete cpm;
  DeviceDescription* dev_description = new DeviceDescription();
  EXPECT_TRUE(dev_description != NULL);
  delete dev_description;
  DeviceClassDescription* dev_class_requirements = new DeviceClassDescription();
  EXPECT_TRUE(dev_class_requirements != NULL);
  delete dev_class_requirements;
}

TEST(Communication, Constructors) {
  UpnpActivePcm* active_pcm = new UpnpActivePcm();
  EXPECT_TRUE(active_pcm != NULL);
  delete active_pcm;
  UpnpActiveCcm* activeCcm = new UpnpActiveCcm();
  EXPECT_TRUE(activeCcm != NULL);
  delete activeCcm;
  UpnpMediaCapturePcm* mediacapture_pcm = new UpnpMediaCapturePcm();
  EXPECT_TRUE(mediacapture_pcm != NULL);
  delete mediacapture_pcm;
  UpnpMediaCaptureCcm* mediacapture_ccm = new UpnpMediaCaptureCcm();
  EXPECT_TRUE(mediacapture_ccm != NULL);
  delete mediacapture_pcm;
  UpnpOnDemandPcm* ondemand_pcm = new UpnpOnDemandPcm();
  EXPECT_TRUE(ondemand_pcm != NULL);
  delete ondemand_pcm;
  UpnpOnDemandCcm* ondemand_ccm = new UpnpOnDemandCcm();
  EXPECT_TRUE(ondemand_ccm != NULL);
  delete ondemand_ccm;
  UpnpPassivePcm* passive_pcm = new UpnpPassivePcm();
  EXPECT_TRUE(passive_pcm != NULL);
  delete passive_pcm;
  UpnpPassiveCcm* passive_ccm = new UpnpPassiveCcm();
  EXPECT_TRUE(passive_ccm != NULL);
  delete passive_ccm;
}

TEST(Utils, UpnpReference) {
  EXPECT_EQ(0, UpnpFsmdaUtils::upnp_references_count());
  PLT_UPnP* upnp = UpnpFsmdaUtils::GetRunningUpnpInstance();
  EXPECT_TRUE(upnp != NULL);
  EXPECT_EQ(1, UpnpFsmdaUtils::upnp_references_count());
  EXPECT_TRUE(upnp->IsRunning());
  UpnpFsmdaUtils::ReleaseUpnpInstance();
  EXPECT_EQ(0, UpnpFsmdaUtils::upnp_references_count());
  UpnpFsmdaUtils::ReleaseUpnpInstance();
  EXPECT_EQ(0, UpnpFsmdaUtils::upnp_references_count());
  EXPECT_FALSE(upnp->IsRunning());
}
