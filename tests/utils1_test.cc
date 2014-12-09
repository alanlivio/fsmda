/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include "fsmda/utils/upnp_fsmda_utils.h"
#include "gtest/gtest.h"
#include <cstdlib>
#include <iostream>

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
