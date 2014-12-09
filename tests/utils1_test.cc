/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include "fsmda/utils/upnp_fsmda_utils.h"
#include "gtest/gtest.h"
#include <cstdlib>
#include <iostream>

TEST(Utils, UpnpReference) {
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
  PLT_UPnP* upnp = UpnpFsmdaUtils::GetRunningUpnpInstance();
  EXPECT_TRUE(upnp != NULL);
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 1);
  EXPECT_TRUE(upnp->IsRunning());
  UpnpFsmdaUtils::ReleaseUpnpInstance();
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
  UpnpFsmdaUtils::ReleaseUpnpInstance();
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
  EXPECT_FALSE(upnp->IsRunning());
}
