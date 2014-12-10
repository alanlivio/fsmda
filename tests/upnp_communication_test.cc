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
#include "gtest/gtest.h"
#include <cstdlib>
#include <iostream>

using std::cout;
using std::endl;

TEST(UpnpCommunication, Constructors) {
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

TEST(UpnpCommunication, UpnpOnDemandCcm) {
  // ondemand class description initialize and meet_requirements tests
  UpnpOnDemandCcm* ondemand_ccm = new UpnpOnDemandCcm();
  ondemand_ccm->StartCommunicationService();
  EXPECT_TRUE(ondemand_ccm->IsServiceStartd());
  ondemand_ccm->StopCommunicationService();
  EXPECT_FALSE(ondemand_ccm->IsServiceStartd());
}
