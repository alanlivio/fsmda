/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/
#include "fsmda/communication_services/upnp_ondemand_ccm.h"
#include <cstdlib>
#include <iostream>
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

void PairingWithOnDeviceInSameProcessHelper(
    DeviceClassDescription::DeviceClassType device_class_type) {
  UpnpParentPairing* upnp_parent_pairing;
  UpnpChildPairing* upnp_child_pairing;

  // test if upnp is running
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
  EXPECT_FALSE(UpnpFsmdaUtils::IsUpnpStarted());

  // start parent pairing service
  upnp_parent_pairing = new UpnpParentPairing();
  EXPECT_EQ(upnp_parent_pairing->StartPairingService(), 0);
  EXPECT_TRUE(upnp_parent_pairing->IsPairingServiceStarted());
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 1);

  // start child pairing service
  DeviceDescription* description_aux = new DeviceDescription();
  description_aux->InitializeByDeviceClass(device_class_type);
  upnp_child_pairing = new UpnpChildPairing();
  EXPECT_EQ(upnp_child_pairing->StartPairingService(), 0);
  EXPECT_TRUE(upnp_child_pairing->IsPairingServiceStarted());
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 2);

  // test if child is paired
  sleep(1);
  EXPECT_TRUE(upnp_child_pairing->PerformedHandShake());

  // stop parent pairing service
  EXPECT_EQ(upnp_parent_pairing->StopPairingService(), 0);
  EXPECT_FALSE(upnp_parent_pairing->IsPairingServiceStarted());
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 1);
  delete upnp_parent_pairing;

  // stop child pairing service
  EXPECT_EQ(upnp_child_pairing->StopPairingService(), 0);
  EXPECT_FALSE(upnp_child_pairing->IsPairingServiceStarted());
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
  delete upnp_child_pairing;

  // test if upnp is running
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
  EXPECT_FALSE(UpnpFsmdaUtils::IsUpnpStarted());
}

void PairingWithOnDeviceInDiferentProcessesHelper(
    DeviceClassDescription::DeviceClassType device_class_type) {
  UpnpChildPairing* upnp_child_pairing;

  // test if upnp is running
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
  EXPECT_FALSE(UpnpFsmdaUtils::IsUpnpStarted());

  // start child pairing service
  DeviceDescription* description_aux = new DeviceDescription();
  description_aux->InitializeByDeviceClass(device_class_type);
  upnp_child_pairing = new UpnpChildPairing();
  EXPECT_EQ(upnp_child_pairing->StartPairingService(), 0);
  EXPECT_TRUE(upnp_child_pairing->IsPairingServiceStarted());
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 1);

  // start parent pairing service
  ASSERT_TRUE(popen("./upnp_pairing_services_test_helper", "r"));

  // test if child is paired
  sleep(1);
  EXPECT_TRUE(upnp_child_pairing->PerformedHandShake());
  // TODO(alan@telemidia.puc-rio.br): use class_type as program parameter

  // stop child pairing service
  EXPECT_EQ(upnp_child_pairing->StopPairingService(), 0);
  EXPECT_FALSE(upnp_child_pairing->IsPairingServiceStarted());
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
  delete upnp_child_pairing;

  // test if upnp is running
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
  EXPECT_FALSE(UpnpFsmdaUtils::IsUpnpStarted());
}

TEST(UpnpPairingServicesTest, PairingWithOnDeviceInSameProcess) {
  //  PairingWithOnDeviceInSameProcessHelper
  // (DeviceClassDescription::kActiveDevice);
  //  PairingWithOnDeviceInSameProcess(DeviceClassDescription::kHtmlDevice);
  //  PairingWithOnDeviceInSameProcess(DeviceClassDescription::kPassiveDevice);
  //  PairingWithOnDeviceInSameProcess(DeviceClassDescription::kOnDemandDevice);
  //  PairingWithOnDeviceInSameProcess
  // (DeviceClassDescription::kMediaCaptureDevice);
}

TEST(UpnpPairingServicesTest, PairingWithOnDeviceInDiferentProcesses) {
  //  PairingWithOnDeviceInDiferentProcessesHelper(
  //      DeviceClassDescription::kActiveDevice);
  //  PairingWithOnDeviceInSameProcess(DeviceClassDescription::kPassiveDevice);
  //  PairingWithOnDeviceInSameProcess(DeviceClassDescription::kHtmlDevice);
  //  PairingWithOnDeviceInSameProcess(DeviceClassDescription::kOnDemandDevice);
  //  PairingWithOnDeviceInSameProcess
  // (DeviceClassDescription::kMediaCaptureDevice);
}
