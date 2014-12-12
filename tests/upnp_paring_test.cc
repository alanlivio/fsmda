/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/
#include "fsmda/communication_services/upnp_ondemand_ccm.h"
#include <cstdlib>
#include <iostream>
#include "fsmda/device_description.h"
#include "fsmda/device_class_description.h"
#include "fsmda/parent_paring_manager.h"
#include "fsmda/child_paring_manager.h"
#include "fsmda/paring_services/upnp_child_paring.h"
#include "fsmda/paring_services/upnp_parent_paring.h"
#include "fsmda/utils/upnp_fsmda_utils.h"
#include "gtest/gtest.h"

using std::cout;
using std::endl;
using std::system;

class UpnpParingTest : public ::testing::Test {
 public:
  UpnpParingTest() {}
  ~UpnpParingTest() {}
  ParentParingManager* parent_paring_manager_;
  UpnpParentParing* upnp_parent_paring_;
  ChildParingManager* child_paring_manager_;
  UpnpChildParing* upnp_child_paring_;

  void SetUp() {
    // test if upnp is running
    EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
    EXPECT_FALSE(UpnpFsmdaUtils::IsUpnpStarted());

    // constructors
    parent_paring_manager_ = new ParentParingManager();
    DeviceDescription description_aux;
    description_aux.InitializeByDeviceClass(
        DeviceClassDescription::kFsmdaActiveDevice);
    child_paring_manager_ = new ChildParingManager(description_aux);
    upnp_parent_paring_ = new UpnpParentParing(parent_paring_manager_);
    upnp_child_paring_ = new UpnpChildParing(child_paring_manager_);
  }

  void TearDown() {
    // release poniters
    delete parent_paring_manager_;
    delete child_paring_manager_;

    // test if upnp is running
    EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
    EXPECT_FALSE(UpnpFsmdaUtils::IsUpnpStarted());
  }
};

TEST_F(UpnpParingTest, SameProcessParing) {
  // start child paring service
  EXPECT_EQ(upnp_child_paring_->StartParingService(), 0);
  EXPECT_TRUE(upnp_child_paring_->IsParingServiceStarted());
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 1);

  // start parent paring service
  EXPECT_EQ(upnp_parent_paring_->StartParingService(), 0);
  EXPECT_TRUE(upnp_parent_paring_->IsParingServiceStarted());
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 2);

  // test if child is paired
  sleep(1);
  EXPECT_TRUE(upnp_child_paring_->IsPaired());

  // stop child paring service
  EXPECT_EQ(upnp_child_paring_->StopParingService(), 0);
  EXPECT_FALSE(upnp_child_paring_->IsParingServiceStarted());
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 1);

  // stop parent paring service
  EXPECT_EQ(upnp_parent_paring_->StopParingService(), 0);
  EXPECT_FALSE(upnp_parent_paring_->IsParingServiceStarted());
}

TEST_F(UpnpParingTest, DiferentProcessesParing) {
  // start child paring service
  EXPECT_EQ(upnp_child_paring_->StartParingService(), 0);
  EXPECT_TRUE(upnp_child_paring_->IsParingServiceStarted());
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 1);

  // start parent paring service
  ASSERT_TRUE(popen("./upnp_paring_test_helper", "r"));

  // test if child is paired
  sleep(1);
  EXPECT_TRUE(upnp_child_paring_->IsPaired());

  // stop child paring service
  EXPECT_EQ(upnp_child_paring_->StopParingService(), 0);
  EXPECT_FALSE(upnp_child_paring_->IsParingServiceStarted());
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
}
