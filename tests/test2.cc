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
  UpnpOnDemandCcm* onDemandCCM = new UpnpOnDemandCcm();
  onDemandCCM->StartCommunicationService();
  EXPECT_TRUE(onDemandCCM->IsServiceStartd());
  onDemandCCM->StopCommunicationService();
  EXPECT_FALSE(onDemandCCM->IsServiceStartd());
}

TEST(Paring, UpnpParentParing) {
  // parent paring tests
  cout << "----------------------------------------------------" << endl;
  UpnpParentParing* upnpParentParing = new UpnpParentParing();
  EXPECT_EQ(upnpParentParing->StartService(), 0);
  sleep(2);
  EXPECT_TRUE(upnpParentParing->IsServiceStarted());
  upnpParentParing->StopService();
  sleep(2);
  EXPECT_FALSE(upnpParentParing->IsServiceStarted());
}

TEST(Paring, UpnpChildParing) {
  // child paring tests
  cout << "----------------------------------------------------" << endl;
  UpnpChildParing* upnpChildParing = new UpnpChildParing();
  EXPECT_EQ(upnpChildParing->StartService(), 0);
  sleep(2);
  EXPECT_TRUE(upnpChildParing->IsServiceStarted());
  sleep(2);
  upnpChildParing->StopService();
  EXPECT_FALSE(upnpChildParing->IsServiceStarted());
}
