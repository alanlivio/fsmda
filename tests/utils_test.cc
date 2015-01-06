/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/
#include <cstdlib>
#include <iostream>
#include "fsmda/utils/upnp_fsmda_utils.h"
#include "gtest/gtest.h"

TEST(Utils, GetRunningUpnpInstance) {
  // test if upnp is running
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
  EXPECT_FALSE(UpnpFsmdaUtils::IsUpnpStarted());

  // test upnp references counter
  PLT_UPnP* upnp_reference_ = UpnpFsmdaUtils::GetRunningInstance();
  EXPECT_TRUE(upnp_reference_);
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 1);
  UpnpFsmdaUtils::ReleaseInstance();
  EXPECT_FALSE(UpnpFsmdaUtils::IsUpnpStarted());
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
  UpnpFsmdaUtils::ReleaseInstance();
  EXPECT_FALSE(UpnpFsmdaUtils::IsUpnpStarted());

  // test if upnp is running
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
  EXPECT_FALSE(UpnpFsmdaUtils::IsUpnpStarted());
}
