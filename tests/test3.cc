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
  UpnpOnDemandCcm* ondemand_ccm = new UpnpOnDemandCcm();
  ondemand_ccm->StartCommunicationService();
  EXPECT_TRUE(ondemand_ccm->IsServiceStartd());
  ondemand_ccm->StopCommunicationService();
  EXPECT_FALSE(ondemand_ccm->IsServiceStartd());
}
