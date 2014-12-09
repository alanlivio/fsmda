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

TEST(Paring, ParentAndChildParing) {
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

  //  sleep(3);
  //  EXPECT_TRUE(upnp_child_paring->IsPaired());

  // stop services
  upnp_parent_paring->StopService();
  sleep(2);
  EXPECT_FALSE(upnp_parent_paring->IsServiceStarted());
  sleep(2);
  upnp_child_paring->StopService();
  EXPECT_FALSE(upnp_child_paring->IsServiceStarted());
}
