/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include "fsmda/communication/upnp_ondemand_ccm.h"
#include "fsmda/paring/upnp_child_paring.h"
#include "fsmda/paring/upnp_parent_paring.h"
#include "gtest/gtest.h"
#include <cstdlib>
#include <iostream>

using std::cout;
using std::endl;

TEST(Communication, UpnpOnDemandCcm) {
  // ondemand class description initialize and meet_requirements tests
  cout << "----------------------------------------------------" << endl;
  UpnpOnDemandCcm* ondemand_ccm = new UpnpOnDemandCcm();
  ondemand_ccm->StartCommunicationService();
  EXPECT_TRUE(ondemand_ccm->IsServiceStartd());
  ondemand_ccm->StopCommunicationService();
  EXPECT_FALSE(ondemand_ccm->IsServiceStartd());
}

TEST(Paring, UpnpParentParing) {
  // parent paring tests
  cout << "----------------------------------------------------" << endl;
  UpnpParentParing* upnp_parent_paring = new UpnpParentParing();
  EXPECT_EQ(upnp_parent_paring->StartService(), 0);
  sleep(2);
  EXPECT_TRUE(upnp_parent_paring->IsServiceStarted());
  upnp_parent_paring->StopService();
  sleep(2);
  EXPECT_FALSE(upnp_parent_paring->IsServiceStarted());
}

TEST(Paring, UpnpChildParing) {
  // child paring tests
  cout << "----------------------------------------------------" << endl;
  UpnpChildParing* upnp_child_paring = new UpnpChildParing();
  EXPECT_EQ(upnp_child_paring->StartService(), 0);
  sleep(2);
  EXPECT_TRUE(upnp_child_paring->IsServiceStarted());
  sleep(2);
  upnp_child_paring->StopService();
  EXPECT_FALSE(upnp_child_paring->IsServiceStarted());
}
