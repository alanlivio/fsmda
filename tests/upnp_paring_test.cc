/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/
#include <cstdlib>
#include <iostream>
#include "fsmda/communication/upnp_ondemand_ccm.h"
#include "fsmda/paring/upnp_child_paring.h"
#include "fsmda/paring/upnp_parent_paring.h"
#include "fsmda/utils/upnp_fsmda_utils.h"
#include "gtest/gtest.h"

using std::cout;
using std::endl;
using std::system;

TEST(UpnpParing, Constructors) {
  // test if upnp is running
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
  EXPECT_FALSE(UpnpFsmdaUtils::IsUpnpRunning());

  UpnpParentParing* upnp_parent_paring = new UpnpParentParing();
  EXPECT_TRUE(upnp_parent_paring);
  UpnpChildParing* upnp_child_paring = new UpnpChildParing();
  EXPECT_TRUE(upnp_child_paring);

  delete upnp_parent_paring;
  delete upnp_child_paring;

  // test if upnp is running
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
  EXPECT_FALSE(UpnpFsmdaUtils::IsUpnpRunning());
}

TEST(UpnpParing, SameProcessParing) {
  // test if upnp is running
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
  EXPECT_FALSE(UpnpFsmdaUtils::IsUpnpRunning());

  // start child paring service
  UpnpChildParing* upnp_child_paring = new UpnpChildParing();

  EXPECT_EQ(upnp_child_paring->StartService(), 0);
  EXPECT_TRUE(upnp_child_paring->IsServiceStarted());
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 1);

  // start parent paring service
  UpnpParentParing* upnp_parent_paring = new UpnpParentParing();
  EXPECT_EQ(upnp_parent_paring->StartService(), 0);
  EXPECT_TRUE(upnp_parent_paring->IsServiceStarted());
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 2);

  // test if child is paired
  sleep(1);
  EXPECT_TRUE(upnp_child_paring->IsPaired());

  // stop child paring service
  upnp_child_paring->StopService();
  EXPECT_FALSE(upnp_child_paring->IsServiceStarted());
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 1);

  // stop parent paring service
  upnp_parent_paring->StopService();
  EXPECT_FALSE(upnp_parent_paring->IsServiceStarted());

  // release poniters
  delete upnp_child_paring;
  delete upnp_parent_paring;

  // test if upnp is running
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
  EXPECT_FALSE(UpnpFsmdaUtils::IsUpnpRunning());
}

TEST(UpnpParing, DiferentProcessesParing) {
  // test if upnp is running
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
  EXPECT_FALSE(UpnpFsmdaUtils::IsUpnpRunning());

  // start child paring service
  UpnpChildParing* upnp_child_paring = new UpnpChildParing();

  EXPECT_EQ(upnp_child_paring->StartService(), 0);
  EXPECT_TRUE(upnp_child_paring->IsServiceStarted());
  EXPECT_EQ(1, UpnpFsmdaUtils::upnp_references_count());

  // start parent paring service
  sleep(1);
  ASSERT_TRUE(popen("./upnp_paring_test_helper", "r"));
  sleep(1);

  EXPECT_TRUE(upnp_child_paring->IsPaired());

  // stop child paring service
  upnp_child_paring->StopService();
  EXPECT_FALSE(upnp_child_paring->IsServiceStarted());

  // release poniters
  delete upnp_child_paring;

  // test if upnp is running
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
  EXPECT_FALSE(UpnpFsmdaUtils::IsUpnpRunning());
}
