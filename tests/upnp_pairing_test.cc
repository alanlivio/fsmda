/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/
#include "fsmda/communication_services/upnp_ondemand_ccm.h"
#include <cstdlib>
#include <iostream>
#include "fsmda/device_description.h"
#include "fsmda/device_class_description.h"
#include "fsmda/parent_pairing_manager.h"
#include "fsmda/child_pairing_manager.h"
#include "fsmda/pairing_services/upnp_child_pairing.h"
#include "fsmda/pairing_services/upnp_parent_pairing.h"
#include "fsmda/utils/upnp_fsmda_utils.h"
#include "gtest/gtest.h"

using std::cout;
using std::endl;
using std::system;

class UpnpPairingTest : public ::testing::Test {
 public:
  UpnpPairingTest() {}
  ~UpnpPairingTest() {}
  ParentPairingManager* parent_pairing_manager_;
  UpnpParentPairing* upnp_parent_pairing_;
  ChildPairingManager* child_pairing_manager_;
  UpnpChildPairing* upnp_child_pairing_;

  void SetUp() {
    // test if upnp is running
    EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
    EXPECT_FALSE(UpnpFsmdaUtils::IsUpnpStarted());

    // constructors
    parent_pairing_manager_ = new ParentPairingManager();
    DeviceDescription description_aux;
    description_aux.InitializeByDeviceClass(
        DeviceClassDescription::kActiveDevice);
    child_pairing_manager_ = new ChildPairingManager(description_aux);
    upnp_parent_pairing_ = new UpnpParentPairing(parent_pairing_manager_);
    upnp_child_pairing_ = new UpnpChildPairing(child_pairing_manager_);
  }

  void TearDown() {
    // release poniters
    delete parent_pairing_manager_;
    delete child_pairing_manager_;

    // test if upnp is running
    EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
    EXPECT_FALSE(UpnpFsmdaUtils::IsUpnpStarted());
  }
};

TEST_F(UpnpPairingTest, SameProcessPairing) {
  // start child pairing service
  EXPECT_EQ(upnp_child_pairing_->StartPairingService(), 0);
  EXPECT_TRUE(upnp_child_pairing_->IsPairingServiceStarted());
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 1);

  // start parent pairing service
  EXPECT_EQ(upnp_parent_pairing_->StartPairingService(), 0);
  EXPECT_TRUE(upnp_parent_pairing_->IsPairingServiceStarted());
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 2);

  // test if child is paired
  sleep(1);
  EXPECT_TRUE(upnp_child_pairing_->IsPaired());

  // stop child pairing service
  EXPECT_EQ(upnp_child_pairing_->StopPairingService(), 0);
  EXPECT_FALSE(upnp_child_pairing_->IsPairingServiceStarted());
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 1);

  // stop parent pairing service
  EXPECT_EQ(upnp_parent_pairing_->StopPairingService(), 0);
  EXPECT_FALSE(upnp_parent_pairing_->IsPairingServiceStarted());
}

TEST_F(UpnpPairingTest, DiferentProcessesPairing) {
  // start child pairing service
  EXPECT_EQ(upnp_child_pairing_->StartPairingService(), 0);
  EXPECT_TRUE(upnp_child_pairing_->IsPairingServiceStarted());
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 1);

  // start parent pairing service
  ASSERT_TRUE(popen("./upnp_pairing_test_helper", "r"));

  // test if child is paired
  sleep(1);
  EXPECT_TRUE(upnp_child_pairing_->IsPaired());

  // stop child pairing service
  EXPECT_EQ(upnp_child_pairing_->StopPairingService(), 0);
  EXPECT_FALSE(upnp_child_pairing_->IsPairingServiceStarted());
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
}
