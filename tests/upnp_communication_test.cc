/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include "gtest/gtest.h"
#include "fsmda/communication/upnp_active_ccm.h"
#include "fsmda/communication/upnp_active_pcm.h"
#include "fsmda/communication/upnp_mediacapture_ccm.h"
#include "fsmda/communication/upnp_mediacapture_pcm.h"
#include "fsmda/communication/upnp_ondemand_ccm.h"
#include "fsmda/communication/upnp_ondemand_pcm.h"
#include "fsmda/communication/upnp_passive_ccm.h"
#include "fsmda/communication/upnp_passive_pcm.h"
#include "fsmda/utils/upnp_fsmda_utils.h"

using std::cout;
using std::endl;

class UpnpCommunicationTest : public ::testing::Test {
 public:
  UpnpCommunicationTest() {}
  ~UpnpCommunicationTest() {}
  UpnpActivePcm* active_pcm_;
  UpnpActiveCcm* active_ccm_;
  UpnpMediaCapturePcm* mediacapture_pcm_;
  UpnpMediaCaptureCcm* mediacapture_ccm_;
  UpnpOnDemandPcm* ondemand_pcm_;
  UpnpOnDemandCcm* ondemand_ccm_;
  UpnpPassivePcm* passive_pcm_;
  UpnpPassiveCcm* passive_ccm_;

  void SetUp() {
    // test if upnp is running
    EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
    EXPECT_FALSE(UpnpFsmdaUtils::IsUpnpStarted());

    // constructors
    active_pcm_ = new UpnpActivePcm();
    active_ccm_ = new UpnpActiveCcm();
    mediacapture_pcm_ = new UpnpMediaCapturePcm();
    mediacapture_ccm_ = new UpnpMediaCaptureCcm();
    ondemand_pcm_ = new UpnpOnDemandPcm();
    ondemand_ccm_ = new UpnpOnDemandCcm();
    passive_pcm_ = new UpnpPassivePcm();
    passive_ccm_ = new UpnpPassiveCcm();
  }

  void TearDown() {
    // release poniters
    delete active_pcm_;
    delete active_ccm_;
    delete mediacapture_pcm_;
    delete mediacapture_ccm_;
    delete ondemand_pcm_;
    delete ondemand_ccm_;
    delete passive_pcm_;
    delete passive_ccm_;

    // test if upnp is running
    EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
    EXPECT_FALSE(UpnpFsmdaUtils::IsUpnpStarted());
  }
};

TEST_F(UpnpCommunicationTest, UpnpOnDemandCcm) {
  // ondemand class description initialize and meet_requirements tests
  EXPECT_EQ(ondemand_ccm_->StartCommunicationService(), 0);
  EXPECT_TRUE(ondemand_ccm_->IsCommunicationServiceStarted());
  EXPECT_EQ(ondemand_ccm_->StopCommunicationService(), 0);
  EXPECT_FALSE(ondemand_ccm_->IsCommunicationServiceStarted());
}
