/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/
#include "fsmda/communication_services/upnp_ondemand_ccm.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include "fsmda/device_description.h"
#include "fsmda/device_class_description.h"
#include "fsmda/parent_pairing_manager.h"
#include "fsmda/child_pairing_manager.h"
#include "fsmda/pairing_services/upnp_child_pairing.h"
#include "fsmda/pairing_services/upnp_parent_pairing.h"
#include "fsmda/utils/upnp_fsmda_utils.h"
#include "gtest/gtest.h"

using std::cout;
using std::endl;
using std::fstream;
using std::ifstream;

void HandShakeWithOneDeviceHelper(bool diferent_processes) {
  UpnpParentPairing* upnp_parent_pairing;
  UpnpChildPairing* upnp_child_pairing;

  // test if upnp is running
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
  EXPECT_FALSE(UpnpFsmdaUtils::IsUpnpStarted());

  // start child pairing service
  upnp_child_pairing = new UpnpChildPairing();
  EXPECT_EQ(upnp_child_pairing->StartPairingService(), 0);
  EXPECT_TRUE(upnp_child_pairing->IsPairingServiceStarted());
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 1);

  if (diferent_processes) {
    // start parent pairing service
    FILE* parent_pipe = popen("./fake_parent_helper", "w");
    ASSERT_TRUE(parent_pipe);
    fprintf(parent_pipe, "%s\n", "active");
    fclose(parent_pipe);
  } else {
    // start parent pairing service with fake discover params
    // only for enable handshake
    upnp_parent_pairing = new UpnpParentPairing();
    string application_id = "fake-application-id";
    unsigned int class_index = 2;
    DeviceClassDescription* device_class_description =
        new DeviceClassDescription();
    device_class_description->InitializeByDeviceClass(
        DeviceClassDescription::kActiveDevice);
    DeviceClassDiscoverParams* dicover_params = new DeviceClassDiscoverParams(
        application_id, class_index, device_class_description);
    upnp_parent_pairing->AddDeviceClassForDiscover(dicover_params);
    EXPECT_EQ(upnp_parent_pairing->StartPairingService(), 0);
    EXPECT_TRUE(upnp_parent_pairing->IsPairingServiceStarted());
    EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 2);
  }
  // test if child is paired
  sleep(1);
  EXPECT_TRUE(upnp_child_pairing->PerformedHandShake());

  if (diferent_processes == false) {
    // stop parent pairing service
    EXPECT_EQ(upnp_parent_pairing->StopPairingService(), 0);
    EXPECT_FALSE(upnp_parent_pairing->IsPairingServiceStarted());
    EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 1);
    delete upnp_parent_pairing;
  }

  // stop child pairing service
  EXPECT_EQ(upnp_child_pairing->StopPairingService(), 0);
  EXPECT_FALSE(upnp_child_pairing->IsPairingServiceStarted());
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
  delete upnp_child_pairing;

  // test if upnp is running
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
  EXPECT_FALSE(UpnpFsmdaUtils::IsUpnpStarted());
}

TEST(UpnpPairingServicesTest, HandShakeWithOneDeviceInSameProcess) {
  HandShakeWithOneDeviceHelper(false);
}

TEST(UpnpPairingServicesTest, HandShakeWithOneDeviceInDiferentProcesses) {
  HandShakeWithOneDeviceHelper(true);
}
