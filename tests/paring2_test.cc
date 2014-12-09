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

 TEST(Paring, SameProcessParing) {
  EXPECT_FALSE(UpnpFsmdaUtils::IsUpnpRunning());
  EXPECT_EQ(0, UpnpFsmdaUtils::upnp_references_count());

  // start child paring service
  UpnpChildParing* upnp_child_paring = new UpnpChildParing();

  EXPECT_EQ(upnp_child_paring->StartService(), 0);
  EXPECT_TRUE(upnp_child_paring->IsServiceStarted());
  EXPECT_EQ(1, UpnpFsmdaUtils::upnp_references_count());

  // start parent paring service
  UpnpParentParing* upnp_parent_paring = new UpnpParentParing();
  EXPECT_EQ(upnp_parent_paring->StartService(), 0);
  EXPECT_TRUE(upnp_parent_paring->IsServiceStarted());
  EXPECT_EQ(2, UpnpFsmdaUtils::upnp_references_count());

  sleep(1);
  EXPECT_TRUE(upnp_child_paring->IsPaired());

  // stop child paring service
  upnp_child_paring->StopService();
  EXPECT_FALSE(upnp_child_paring->IsServiceStarted());
  EXPECT_EQ(1, UpnpFsmdaUtils::upnp_references_count());

  // stop parent paring service
  upnp_parent_paring->StopService();
  EXPECT_FALSE(upnp_parent_paring->IsServiceStarted());

  EXPECT_FALSE(UpnpFsmdaUtils::IsUpnpRunning());
  EXPECT_EQ(0, UpnpFsmdaUtils::upnp_references_count());
}

TEST(Paring, DiferentProcessesParing) {

  EXPECT_FALSE(UpnpFsmdaUtils::IsUpnpRunning());
  EXPECT_EQ(0, UpnpFsmdaUtils::upnp_references_count());

  // start child paring service
  UpnpChildParing* upnp_child_paring = new UpnpChildParing();

  EXPECT_EQ(upnp_child_paring->StartService(), 0);
  EXPECT_TRUE(upnp_child_paring->IsServiceStarted());
  EXPECT_EQ(1, UpnpFsmdaUtils::upnp_references_count());

  // start parent paring service
  sleep(1);
  ASSERT_TRUE(popen("./paring2_test_helper", "r") != NULL);
  sleep(1);

  EXPECT_TRUE(upnp_child_paring->IsPaired());

  // stop child paring service
  upnp_child_paring->StopService();
  EXPECT_FALSE(upnp_child_paring->IsServiceStarted());

  EXPECT_FALSE(UpnpFsmdaUtils::IsUpnpRunning());
  EXPECT_EQ(0, UpnpFsmdaUtils::upnp_references_count());
}
