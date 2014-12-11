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
    EXPECT_FALSE(UpnpFsmdaUtils::IsUpnpRunning());

    // constructors tests
    active_pcm_ = new UpnpActivePcm();
    EXPECT_TRUE(active_pcm_ != NULL);
    active_ccm_ = new UpnpActiveCcm();
    EXPECT_TRUE(active_ccm_ != NULL);
    mediacapture_pcm_ = new UpnpMediaCapturePcm();
    EXPECT_TRUE(mediacapture_pcm_ != NULL);
    mediacapture_ccm_ = new UpnpMediaCaptureCcm();
    EXPECT_TRUE(mediacapture_ccm_ != NULL);
    ondemand_pcm_ = new UpnpOnDemandPcm();
    EXPECT_TRUE(ondemand_pcm_ != NULL);
    ondemand_ccm_ = new UpnpOnDemandCcm();
    EXPECT_TRUE(ondemand_ccm_ != NULL);
    passive_pcm_ = new UpnpPassivePcm();
    EXPECT_TRUE(passive_pcm_ != NULL);
    passive_ccm_ = new UpnpPassiveCcm();
    EXPECT_TRUE(passive_ccm_ != NULL);
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
    EXPECT_FALSE(UpnpFsmdaUtils::IsUpnpRunning());
  }
};

TEST_F(UpnpCommunicationTest, UpnpOnDemandCcm) {
  // ondemand class description initialize and meet_requirements tests
  ondemand_ccm_->StartCommunicationService();
  EXPECT_TRUE(ondemand_ccm_->IsServiceStartd());
  ondemand_ccm_->StopCommunicationService();
  EXPECT_FALSE(ondemand_ccm_->IsServiceStartd());
}
