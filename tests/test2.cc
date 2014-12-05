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
  onDemandCCM->start_communication_service();
  EXPECT_TRUE(onDemandCCM->is_service_started());
  onDemandCCM->stop_communication_service();
  EXPECT_FALSE(onDemandCCM->is_service_started());
}

TEST(Paring, UpnpParentParing) {
  // parent paring tests
  cout << "----------------------------------------------------" << endl;
  UpnpParentParing* upnpParentParing = new UpnpParentParing();
  EXPECT_EQ(upnpParentParing->start_service(), 0);
  sleep(2);
  EXPECT_TRUE(upnpParentParing->is_service_started());
  upnpParentParing->stop_service();
  sleep(2);
  EXPECT_FALSE(upnpParentParing->is_service_started());
}

TEST(Paring, UpnpChildParing) {
  // child paring tests
  cout << "----------------------------------------------------" << endl;
  UpnpChildParing* upnpChildParing = new UpnpChildParing();
  EXPECT_EQ(upnpChildParing->start_service(), 0);
  sleep(2);
  EXPECT_TRUE(upnpChildParing->is_service_started());
  sleep(2);
  upnpChildParing->stop_service();
  EXPECT_FALSE(upnpChildParing->is_service_started());
}