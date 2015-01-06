/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include "./named_semaphore_helper.h"
#include "fsmda/device_class_description.h"
#include "fsmda/device_description.h"
#include "fsmda/parent_pairing_manager.h"
#include "fsmda/child_pairing_manager.h"
#include "fsmda/utils/upnp_fsmda_utils.h"
#include "gtest/gtest.h"

using std::string;
using std::cout;
using std::clog;
using std::endl;

class MockChildPairingManager : public ChildPairingManager {
 public:
  string expected_semaphore;
  void set_paired(bool paired) {
    clog << "MockChildPairingManager::set_paired():: paired = " << paired
         << endl;
    ChildPairingManager::set_paired(paired);
    PostNamedSemphoreHelper(expected_semaphore);
  }
  explicit MockChildPairingManager(const DeviceDescription& device_description)
      : ChildPairingManager(device_description) {}
};

void PairingWithOneDeviceHelper(
    const string& device_rdf, const string& device_class_description_rdf,
    DeviceClassDescription::DeviceClassType expected_device_class_type,
    bool diferent_processes) {
  MockChildPairingManager* child_pairing_manager;
  ParentPairingManager* parent_pairing_manager;
  string app_id;

  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
  EXPECT_FALSE(UpnpFsmdaUtils::IsUpnpStarted());

  // start ChildPairingManager
  DeviceDescription device_description;
  EXPECT_EQ(device_description.InitializeByRdfFile(device_rdf), 0);
  child_pairing_manager = new MockChildPairingManager(device_description);
  EXPECT_EQ(device_description.device_class_type(), expected_device_class_type);
  EXPECT_EQ(child_pairing_manager->StartPairing(), 0);
  EXPECT_TRUE(child_pairing_manager->pairing_started());
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 1);

  UpnpFsmdaUtils::GenerateGUID(&app_id);
  CreateNamedSemphoreHelper(app_id, false);
  child_pairing_manager->expected_semaphore = app_id;

  // start ParentPairingManager
  if (diferent_processes) {
    // configure and start ParenPaigingManager
    // by popen fake_parent_helper
    string command = "./fake_parent_helper";
    command.append(" --device_class=");
    command.append(DeviceClassDescription::GetDeviceClassTypeStringByEnum(
        expected_device_class_type));
    command.append(" --application_id=" + app_id);
    FILE* parent_pipe = popen(command.c_str(), "w");
    ASSERT_TRUE(parent_pipe);
    pclose(parent_pipe);

  } else {
    // configure and start ParenPaigingManager
    DeviceClassDescription* device_class_description;
    device_class_description = new DeviceClassDescription();
    EXPECT_EQ(device_class_description->InitializeByRdfFile(
                  device_class_description_rdf),
              0);
    EXPECT_EQ(device_class_description->device_class_type(),
              expected_device_class_type);
    parent_pairing_manager = new ParentPairingManager();
    unsigned int class_index =
        parent_pairing_manager->GenerateAvaliableIndex(app_id);
    //    parent_pairing_manager->AddClass(app_id, class_index);
    parent_pairing_manager->AddClassDescription(app_id, class_index,
                                                device_class_description);
    EXPECT_EQ(parent_pairing_manager->GetNumberOfRegistredClasses(app_id), 1);
    EXPECT_EQ(parent_pairing_manager->StartPairing(), 0);
    EXPECT_TRUE(parent_pairing_manager->IsPairingStarted());
    EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 2);
  }
  // child wait for ParentPostSemphoreHelper call
  WaitNamedSemphoreHelper(app_id);

  // test if child is paired
  EXPECT_TRUE(child_pairing_manager->paired());
  ReleaseNameSemphoreHelper(app_id);

  if (diferent_processes == false) {
    // stop parent pairing service
    EXPECT_EQ(parent_pairing_manager->StopPairing(), 0);
    EXPECT_FALSE(parent_pairing_manager->IsPairingStarted());
    EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 1);
    delete parent_pairing_manager;
  }

  // stop child pairing service
  EXPECT_EQ(child_pairing_manager->StopPairing(), 0);
  EXPECT_FALSE(child_pairing_manager->pairing_started());
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
  delete child_pairing_manager;

  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
  EXPECT_FALSE(UpnpFsmdaUtils::IsUpnpStarted());
}

TEST(Pairing, PassivePairingWithOneDeviceInSameProcess) {
  PairingWithOneDeviceHelper("./files/passive_dev_desc00.xml",
                             "./files/passive_class_desc00.xml",
                             DeviceClassDescription::kPassiveDevice, false);
}
TEST(Pairing, ActivePairingWithOneDeviceInSameProcess) {
  PairingWithOneDeviceHelper("./files/active_dev_desc00.xml",
                             "./files/active_class_desc00.xml",
                             DeviceClassDescription::kActiveDevice, false);
}
TEST(Pairing, ActiveHtmlPairingWithOneDeviceInSameProcess) {
  PairingWithOneDeviceHelper("./files/html_dev_desc00.xml",
                             "./files/html_class_desc00.xml",
                             DeviceClassDescription::kHtmlDevice, false);
}
TEST(Pairing, OnDemandPairingWithOneDeviceInSameProcess) {
  PairingWithOneDeviceHelper("./files/ondemand_dev_desc00.xml",
                             "./files/ondemand_class_desc00.xml",
                             DeviceClassDescription::kOnDemandDevice, false);
}
TEST(Pairing, MediaCapturePairingWithOneDeviceInSameProcess) {
  PairingWithOneDeviceHelper("./files/mediacapture_dev_desc00.xml",
                             "./files/mediacapture_class_desc00.xml",
                             DeviceClassDescription::kMediaCaptureDevice,
                             false);
}
TEST(Pairing, PassivePairingWithOneDeviceInDiferentProcessess) {
  PairingWithOneDeviceHelper("./files/passive_dev_desc00.xml",
                             "./files/passive_class_desc00.xml",
                             DeviceClassDescription::kPassiveDevice, true);
}
TEST(Pairing, ActivePairingWithOneDeviceInDiferentProcessess) {
  PairingWithOneDeviceHelper("./files/active_dev_desc00.xml",
                             "./files/active_class_desc00.xml",
                             DeviceClassDescription::kActiveDevice, true);
}
TEST(Pairing, ActiveHtmlPairingWithOneDeviceInDiferentProcessess) {
  PairingWithOneDeviceHelper("./files/html_dev_desc00.xml",
                             "./files/html_class_desc00.xml",
                             DeviceClassDescription::kHtmlDevice, true);
}
TEST(Pairing, OnDemandPairingWithOneDeviceInDiferentProcessess) {
  PairingWithOneDeviceHelper("./files/ondemand_dev_desc00.xml",
                             "./files/ondemand_class_desc00.xml",
                             DeviceClassDescription::kOnDemandDevice, true);
}
TEST(Pairing, MediaCapturePairingWithOneDeviceInDiferentProcessess) {
  PairingWithOneDeviceHelper("./files/mediacapture_dev_desc00.xml",
                             "./files/mediacapture_class_desc00.xml",
                             DeviceClassDescription::kMediaCaptureDevice, true);
}
