/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/
#include <cstdlib>
#include <iostream>
#include "fsmda/utils/upnp_fsmda_utils.h"
#include "gtest/gtest.h"

TEST(UpnpUtils, UpnpReference) {
  // test if upnp is running
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
  EXPECT_FALSE(UpnpFsmdaUtils::IsUpnpRunning());

  // test upnp references counter
  PLT_UPnP* upnp = UpnpFsmdaUtils::GetRunningUpnpInstance();
  EXPECT_TRUE(upnp != NULL);
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 1);
  EXPECT_TRUE(upnp->IsRunning());
  UpnpFsmdaUtils::ReleaseUpnpInstance();
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
  UpnpFsmdaUtils::ReleaseUpnpInstance();

  // test if upnp is running
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
  EXPECT_FALSE(UpnpFsmdaUtils::IsUpnpRunning());
}
