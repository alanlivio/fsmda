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
  // constructors tests
  UpnpActivePcm* active_pcm = new UpnpActivePcm();
  EXPECT_TRUE(active_pcm != NULL);
  UpnpActiveCcm* active_ccm = new UpnpActiveCcm();
  EXPECT_TRUE(active_ccm != NULL);
  UpnpMediaCapturePcm* mediacapture_pcm = new UpnpMediaCapturePcm();
  EXPECT_TRUE(mediacapture_pcm != NULL);
  UpnpMediaCaptureCcm* mediacapture_ccm = new UpnpMediaCaptureCcm();
  EXPECT_TRUE(mediacapture_ccm != NULL);
  UpnpOnDemandPcm* ondemand_pcm = new UpnpOnDemandPcm();
  EXPECT_TRUE(ondemand_pcm != NULL);
  UpnpOnDemandCcm* ondemand_ccm = new UpnpOnDemandCcm();
  EXPECT_TRUE(ondemand_ccm != NULL);
  UpnpPassivePcm* passive_pcm = new UpnpPassivePcm();
  EXPECT_TRUE(passive_pcm != NULL);
  UpnpPassiveCcm* passive_ccm = new UpnpPassiveCcm();
  EXPECT_TRUE(passive_ccm != NULL);

  // release poniters
  delete active_pcm;
  delete active_ccm;
  delete mediacapture_pcm;
  delete mediacapture_ccm;
  delete ondemand_pcm;
  delete ondemand_ccm;
  delete passive_pcm;
  delete passive_ccm;
}

TEST(UpnpCommunication, UpnpOnDemandCcm) {
  // ondemand class description initialize and meet_requirements tests
  UpnpOnDemandCcm* ondemand_ccm = new UpnpOnDemandCcm();
  ondemand_ccm->StartCommunicationService();
  EXPECT_TRUE(ondemand_ccm->IsServiceStartd());
  ondemand_ccm->StopCommunicationService();
  EXPECT_FALSE(ondemand_ccm->IsServiceStartd());

  // release poniters
  delete ondemand_ccm;
}
