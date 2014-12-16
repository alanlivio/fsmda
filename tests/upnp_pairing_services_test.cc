/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include "./named_semaphore_helper.h"
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

using std::endl;
using std::clog;
using std::fstream;
using std::ifstream;

class MockUpnpChildPairing : public UpnpChildPairing {
 public:
  string expected_app_id;
  void SetPerformedHandShake(bool performe) {
    clog << "MockUpnpChildPairing::SetPerformedHandShake():: performe = "
         << performe << endl;
    UpnpChildPairing::SetPerformedHandShake(performe);
    PostnamedSemphoreHelper(expected_app_id);
  }
  explicit MockUpnpChildPairing() : UpnpChildPairing() {}
};

void HandShakeWithOneDeviceHelper(bool diferent_processes) {
  UpnpParentPairing* upnp_parent_pairing;
  MockUpnpChildPairing* upnp_child_pairing;
  string app_id = "fake-application-id";

  // test if upnp is running
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
  EXPECT_FALSE(UpnpFsmdaUtils::IsUpnpStarted());

  // start child pairing service
  upnp_child_pairing = new MockUpnpChildPairing();
  EXPECT_EQ(upnp_child_pairing->StartPairingService(), 0);
  EXPECT_TRUE(upnp_child_pairing->IsPairingServiceStarted());
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 1);

  if (diferent_processes) {
    UpnpFsmdaUtils::GenerateGUID(&app_id);
    CreateNamedSemphoreHelper(app_id, true);
    upnp_child_pairing->expected_app_id = app_id;

    // configure and start ParenPaigingManager
    // by open fake_parent_helper and create pipe to its sdtin
    FILE* parent_pipe = popen("./fake_parent_helper", "w");
    ASSERT_TRUE(parent_pipe);

    // send active as device class type
    fprintf(parent_pipe, "%s\n", "active");

    // send app id name to identify semaphore
    fprintf(parent_pipe, "%s\n", app_id.c_str());

    // close pipe
    pclose(parent_pipe);

    // child wait for ParentPostSemphoreHelper call
    WaitNamedSemphoreHelper(app_id);
  } else {
    UpnpFsmdaUtils::GenerateGUID(&app_id);
    CreateNamedSemphoreHelper(app_id, false);
    upnp_child_pairing->expected_app_id = app_id;
    // start parent pairing service with fake discover params
    // only for enable handshake
    upnp_parent_pairing = new UpnpParentPairing();
    unsigned int class_index = 2;
    DeviceClassDescription* device_class_description =
        new DeviceClassDescription();
    device_class_description->InitializeByDeviceClass(
        DeviceClassDescription::kActiveDevice);
    DeviceClassDiscoverParams* dicover_params = new DeviceClassDiscoverParams(
        app_id, class_index, device_class_description);
    upnp_parent_pairing->AddDeviceClassForDiscover(dicover_params);
    EXPECT_EQ(upnp_parent_pairing->StartPairingService(), 0);
    EXPECT_TRUE(upnp_parent_pairing->IsPairingServiceStarted());
    EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 2);

    // child wait for ParentPostSemphoreHelper call
    WaitNamedSemphoreHelper(app_id);
  }
  // test if child is paired
  EXPECT_TRUE(upnp_child_pairing->PerformedHandShake());
  ReleaseNameSemphoreHelper(app_id);

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
