/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include "./named_semaphore_helper.h"
#include "fsmda/class_handling/device_class_description.h"
#include "fsmda/class_handling/device_description.h"
#include "fsmda/parent_pairing_manager.h"
#include "fsmda/child_pairing_manager.h"
#include "fsmda/utils/upnp_fsmda_utils.h"
#include "gtest/gtest.h"

using std::string;
using std::cout;
using std::clog;
using std::endl;

class MockParentPairingManager : public ParentPairingManager {
 public:
  string expected_semaphore;
  virtual void AddDeviceToClass(const string& application_id,
                                const string& device_address,
                                unsigned int class_index,
                                const string& device_desc) {
    clog << "MockParentPairingManager::AddDeviceToClass()" << endl;
    ParentPairingManager::AddDeviceToClass(application_id, device_address,
                                           class_index, device_desc);
    PostNamedSemphoreHelper(expected_semaphore);
  }
};

void CallPrepareWithOneDeviceHelper(
    const string& device_rdf, const string& device_class_description_rdf,
    DeviceClassDescription::DeviceClassType expected_device_class_type,
    bool diferent_processes) {
  ChildPairingManager* child_pairing_manager;
  MockParentPairingManager* parent_pairing_manager;
  string app_id;

  // release fake child and parent
  int ret = system("./release_fake_child_parent.sh");

  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
  EXPECT_FALSE(UpnpFsmdaUtils::IsUpnpStarted());

  // genereate a app_id
  UpnpFsmdaUtils::GenerateGUID(&app_id);
  string parent_named_semaphore = app_id + "_parent";
  CreateNamedSemphoreHelper(parent_named_semaphore, false);

  // configure ParenPaigingManager
  DeviceClassDescription* device_class_description;
  device_class_description = new DeviceClassDescription();
  EXPECT_EQ(device_class_description->InitializeByRdfFile(
                device_class_description_rdf),
            0);
  EXPECT_EQ(device_class_description->device_class_type(),
            expected_device_class_type);
  parent_pairing_manager = new MockParentPairingManager();
  unsigned int class_index =
      parent_pairing_manager->GenerateAvaliableIndex(app_id);
  parent_pairing_manager->expected_semaphore = parent_named_semaphore;
  parent_pairing_manager->AddClassDescription(app_id, class_index,
                                              device_class_description);
  EXPECT_EQ(parent_pairing_manager->GetNumberOfRegistredClasses(app_id), 1);

  // start ParenPaigingManager
  EXPECT_EQ(parent_pairing_manager->StartPairing(), 0);
  EXPECT_TRUE(parent_pairing_manager->IsPairingStarted());
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 1);

  // start ParentPairingManager
  if (diferent_processes) {
    // configure and start ParenPaigingManager
    // by popen fake_parent_helper
    string command = "./fake_child_helper";
    command.append(" --device_class=");
    command.append(DeviceClassDescription::GetDeviceClassTypeStringByEnum(
        expected_device_class_type));
    command.append(" --application_id=" + app_id);
    FILE* parent_pipe = popen(command.c_str(), "w");
    ASSERT_TRUE(parent_pipe);
    pclose(parent_pipe);

  } else {
    DeviceDescription device_description;
    EXPECT_EQ(device_description.InitializeByRdfFile(device_rdf), 0);
    child_pairing_manager = new ChildPairingManager(device_description);
    EXPECT_EQ(device_description.device_class_type(),
              expected_device_class_type);
    EXPECT_EQ(child_pairing_manager->StartPairing(), 0);
    EXPECT_TRUE(child_pairing_manager->IsPairingStarted());
    EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 2);
  }
  // parent wait for ParentPostSemphoreHelper call
  WaitNamedSemphoreHelper(parent_named_semaphore);

  //   test if child is paired
  EXPECT_EQ(
      parent_pairing_manager->GetNumberOfRegistredChildren(app_id, class_index),
      1);
  ReleaseNameSemphoreHelper(parent_named_semaphore);
  if (device_class_description->device_class_type() ==
      DeviceClassDescription::kPassiveDevice) {
    PassivePcmInterface* passive_pcm =
        parent_pairing_manager->CreatePassivePcm(app_id, class_index);
    EXPECT_TRUE(passive_pcm);
  } else if (device_class_description->device_class_type() ==
             DeviceClassDescription::kActiveDevice) {
    ActivePcmInterface* active_pcm =
        parent_pairing_manager->CreateActivePcm(app_id, class_index);
    EXPECT_TRUE(active_pcm);
  } else if (device_class_description->device_class_type() ==
             DeviceClassDescription::kOnDemandDevice) {
    OnDemandPcmInterface* ondemand_pcm =
        parent_pairing_manager->CreateOnDemandPcm(app_id, class_index);
    EXPECT_TRUE(ondemand_pcm);
  } else if (device_class_description->device_class_type() ==
             DeviceClassDescription::kMediaCaptureDevice) {
    MediaCapturePcmInterface* medicapture_pcm =
        parent_pairing_manager->CreateMediaCapturePcm(app_id, class_index);
    EXPECT_TRUE(medicapture_pcm);
  } else {
    FAIL();
  }

  if (diferent_processes == false) {
    // stop child pairing service
    EXPECT_EQ(child_pairing_manager->StopPairing(), 0);
    EXPECT_FALSE(child_pairing_manager->IsPairingStarted());
    EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 1);
    delete child_pairing_manager;
  }

  // stop parent pairing service
  EXPECT_EQ(parent_pairing_manager->StopPairing(), 0);
  EXPECT_FALSE(parent_pairing_manager->IsPairingStarted());
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
  delete parent_pairing_manager;

  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
  EXPECT_FALSE(UpnpFsmdaUtils::IsUpnpStarted());
}

TEST(Communication, PassiveCallPrepareInSameProcess) {
  CallPrepareWithOneDeviceHelper("./files/passive_dev_desc00.xml",
                                 "./files/passive_class_desc00.xml",
                                 DeviceClassDescription::kPassiveDevice, false);
}
TEST(Communication, ActiveCallPrepareInSameProcess) {
  CallPrepareWithOneDeviceHelper("./files/active_dev_desc00.xml",
                                 "./files/active_class_desc00.xml",
                                 DeviceClassDescription::kActiveDevice, false);
}
TEST(Communication, OnDemandCallPrepareInSameProcess) {
  CallPrepareWithOneDeviceHelper(
      "./files/ondemand_dev_desc00.xml", "./files/ondemand_class_desc00.xml",
      DeviceClassDescription::kOnDemandDevice, false);
}
TEST(Communication, MediaCaptureCallPrepareInSameProcess) {
  CallPrepareWithOneDeviceHelper("./files/mediacapture_dev_desc00.xml",
                                 "./files/mediacapture_class_desc00.xml",
                                 DeviceClassDescription::kMediaCaptureDevice,
                                 false);
}
TEST(Communication, PassiveCallPrepareInDiferentProcessess) {
  CallPrepareWithOneDeviceHelper("./files/passive_dev_desc00.xml",
                                 "./files/passive_class_desc00.xml",
                                 DeviceClassDescription::kPassiveDevice, true);
}
TEST(Communication, ActiveCallPrepareInDiferentProcessess) {
  CallPrepareWithOneDeviceHelper("./files/active_dev_desc00.xml",
                                 "./files/active_class_desc00.xml",
                                 DeviceClassDescription::kActiveDevice, true);
}
TEST(Communication, OnDemandCallPrepareInDiferentProcessess) {
  CallPrepareWithOneDeviceHelper("./files/ondemand_dev_desc00.xml",
                                 "./files/ondemand_class_desc00.xml",
                                 DeviceClassDescription::kOnDemandDevice, true);
}
TEST(Communication, MediaCaptureCallPrepareInDiferentProcessess) {
  CallPrepareWithOneDeviceHelper("./files/mediacapture_dev_desc00.xml",
                                 "./files/mediacapture_class_desc00.xml",
                                 DeviceClassDescription::kMediaCaptureDevice,
                                 true);
}
