/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include "fsmda/communication/upnp_ondemand_ccm.h"
#include "fsmda/paring/upnp_child_paring.h"
#include "fsmda/paring/upnp_parent_paring.h"
#include "fsmda/utils/upnp_fsmda_utils.h"
#include "gtest/gtest.h"
#include <cstdlib>
#include <iostream>

using std::cout;
using std::endl;
using std::system;

TEST(Paring, ParingServices) {
  EXPECT_FALSE(UpnpFsmdaUtils::IsUpnpRunning());
  // child paring service
  UpnpChildParing* upnp_child_paring = new UpnpChildParing();

  EXPECT_EQ(upnp_child_paring->StartService(), 0);
  sleep(1);
  EXPECT_TRUE(upnp_child_paring->IsServiceStarted());

  // parent paring service
  UpnpParentParing* upnp_parent_paring = new UpnpParentParing();
  EXPECT_EQ(upnp_parent_paring->StartService(), 0);
  sleep(1);
  EXPECT_TRUE(upnp_parent_paring->IsServiceStarted());

  // stop services
  upnp_parent_paring->StopService();
  sleep(2);
  EXPECT_FALSE(upnp_parent_paring->IsServiceStarted());
  sleep(2);
  upnp_child_paring->StopService();
  EXPECT_FALSE(upnp_child_paring->IsServiceStarted());
  EXPECT_FALSE(UpnpFsmdaUtils::IsUpnpRunning());
  EXPECT_EQ(0, UpnpFsmdaUtils::upnp_references_count());
}

TEST(Paring, ChildDiscoverParent) {

  EXPECT_FALSE(UpnpFsmdaUtils::IsUpnpRunning());
  // child paring service
  UpnpChildParing* upnp_child_paring = new UpnpChildParing();
  upnp_child_paring->StartService();

  EXPECT_EQ(1, UpnpFsmdaUtils::upnp_references_count());
  EXPECT_TRUE(UpnpFsmdaUtils::IsUpnpRunning());

  int ret = system("./paring2_test_helper &");
  sleep(3);
  EXPECT_TRUE(upnp_child_paring->IsPaired());

  upnp_child_paring->StopService();
  EXPECT_FALSE(UpnpFsmdaUtils::IsUpnpRunning());
  EXPECT_EQ(0, UpnpFsmdaUtils::upnp_references_count());
}
