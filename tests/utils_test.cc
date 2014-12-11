/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/
#include <cstdlib>
#include <iostream>
#include "fsmda/utils/upnp_fsmda_utils.h"
#include "gtest/gtest.h"

class UpnpUtilsTest : public ::testing::Test {
 public:
  UpnpUtilsTest() {}
  ~UpnpUtilsTest() {}
  PLT_UPnP* upnp_reference_;

  void SetUp() {
    // test if upnp is running
    EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
    EXPECT_FALSE(UpnpFsmdaUtils::IsUpnpRunning());
  }

  void TearDown() {
    // test if upnp is running
    EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
    EXPECT_FALSE(UpnpFsmdaUtils::IsUpnpRunning());
  }
};

TEST(UpnpUtilsTest, GetRunningUpnpInstance) {
  // test upnp references counter
  PLT_UPnP* upnp_reference_ = UpnpFsmdaUtils::GetRunningUpnpInstance();
  EXPECT_TRUE(upnp_reference_);
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 1);
  EXPECT_TRUE(UpnpFsmdaUtils::IsUpnpRunning());
  UpnpFsmdaUtils::ReleaseUpnpInstance();
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
  UpnpFsmdaUtils::ReleaseUpnpInstance();
}
