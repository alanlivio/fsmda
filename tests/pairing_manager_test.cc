/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include "fsmda/device_class_description.h"
#include "fsmda/device_description.h"
#include "fsmda/parent_pairing_manager.h"
#include "fsmda/child_pairing_manager.h"
#include "fsmda/utils/upnp_fsmda_utils.h"
#include "gtest/gtest.h"

using std::string;

class PairingManagerTest : public ::testing::Test {
 public:
  PairingManagerTest() {}
  ~PairingManagerTest() {}
  DeviceDescription* device_description_;
  DeviceDescription* ppm_device_description_;
  DeviceClassDescription* device_class_description_;
  string device_rdf_, device_class_description_rdf_;
  ParentPairingManager* parent_pairing_manager_;

  void SetUp() {
    // test if upnp is running
    EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
    EXPECT_FALSE(UpnpFsmdaUtils::IsUpnpStarted());

    // constructors
    parent_pairing_manager_ = new ParentPairingManager();
    device_description_ = new DeviceDescription();
    device_class_description_ = new DeviceClassDescription();
  }

  void TearDown() {
    // release poniters
    delete device_description_;
    delete device_class_description_;
    delete parent_pairing_manager_;

    // test if upnp is running
    EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
    EXPECT_FALSE(UpnpFsmdaUtils::IsUpnpStarted());
  }
};

TEST_F(PairingManagerTest, DeviceDescriptionMatching) {
  // passive class description initialize and meet_requirements tests
  device_rdf_ = "./files/passive_dev_desc00.xml";
  device_class_description_rdf_ = "./files/passive_class_desc00.xml";
  device_description_->InitializeByRdfFile(device_rdf_);
  EXPECT_EQ(device_description_->device_class_type(),
            DeviceClassDescription::kPassiveDevice);
  EXPECT_EQ(device_class_description_->InitializeByRdfFile(
                device_class_description_rdf_),
            0);
  EXPECT_EQ(device_class_description_->device_class_type(),
            DeviceClassDescription::kPassiveDevice);
  EXPECT_TRUE(
      device_class_description_->DeviceMeetRequirements(device_description_));

  // active class description initialize and meet_requirements tests
  device_rdf_ = "./files/active_dev_desc00.xml";
  device_class_description_rdf_ = "./files/active_class_desc00.xml";
  EXPECT_EQ(device_description_->InitializeByRdfFile(device_rdf_), 0);
  EXPECT_EQ(device_description_->device_class_type(),
            DeviceClassDescription::kActiveDevice);
  EXPECT_EQ(device_class_description_->InitializeByRdfFile(
                device_class_description_rdf_),
            0);
  EXPECT_EQ(device_class_description_->device_class_type(),
            DeviceClassDescription::kActiveDevice);
  EXPECT_TRUE(
      device_class_description_->DeviceMeetRequirements(device_description_));

  // html class description initialize and meet_requirements tests
  device_rdf_ = "./files/html_dev_desc00.xml";
  device_class_description_rdf_ = "./files/html_class_desc00.xml";
  EXPECT_EQ(device_description_->InitializeByRdfFile(device_rdf_), 0);
  EXPECT_EQ(device_description_->device_class_type(),
            DeviceClassDescription::kHtmlDevice);
  EXPECT_EQ(device_class_description_->InitializeByRdfFile(
                device_class_description_rdf_),
            0);
  EXPECT_EQ(device_class_description_->device_class_type(),
            DeviceClassDescription::kHtmlDevice);
  EXPECT_TRUE(
      device_class_description_->DeviceMeetRequirements(device_description_));

  // ondemand class description initialize and meet_requirements tests
  device_class_description_rdf_ = "./files/ondemand_class_desc00.xml";
  device_rdf_ = "./files/ondemand_dev_desc00.xml";
  EXPECT_EQ(device_description_->InitializeByRdfFile(device_rdf_), 0);
  EXPECT_EQ(device_description_->device_class_type(),
            DeviceClassDescription::kOnDemandDevice);
  EXPECT_EQ(device_class_description_->InitializeByRdfFile(
                device_class_description_rdf_),
            0);
  EXPECT_EQ(device_class_description_->device_class_type(),
            DeviceClassDescription::kOnDemandDevice);
  EXPECT_TRUE(
      device_class_description_->DeviceMeetRequirements(device_description_));

  // mediacapture class description initialize and meet_requirements tests
  device_rdf_ = "./files/mediacapture_dev_desc00.xml";
  device_class_description_rdf_ = "./files/mediacapture_class_desc00.xml";
  EXPECT_EQ(device_description_->InitializeByRdfFile(device_rdf_), 0);
  EXPECT_EQ(device_description_->device_class_type(),
            DeviceClassDescription::kMediaCaptureDevice);
  EXPECT_EQ(device_class_description_->InitializeByRdfFile(
                device_class_description_rdf_),
            0);
  EXPECT_EQ(device_class_description_->device_class_type(),
            DeviceClassDescription::kMediaCaptureDevice);
  EXPECT_TRUE(
      device_class_description_->DeviceMeetRequirements(device_description_));
}

TEST_F(PairingManagerTest, PairingWithOneActiveDevice) {
  unsigned int class_index;
  string app_id;

  // add a active class
  UpnpFsmdaUtils::GenerateGUID(&app_id);
  class_index = parent_pairing_manager_->GenerateAvaliableIndex(app_id);
  device_class_description_rdf_ = "./files/active_class_desc00.xml";
  EXPECT_EQ(device_class_description_->InitializeByRdfFile(
                device_class_description_rdf_),
            0);
  parent_pairing_manager_->AddClass(app_id, class_index);
  parent_pairing_manager_->AddClassDescription(app_id, class_index,
                                              device_class_description_);
  EXPECT_EQ(parent_pairing_manager_->GetRegistredClassesSize(app_id), 1);
  EXPECT_EQ(parent_pairing_manager_->StartPairing(), 0);

  // start child pairing service
  DeviceDescription description_aux;
  description_aux.InitializeByDeviceClass(
      DeviceClassDescription::kActiveDevice);
  ChildPairingManager* child_pairing_manager =
      new ChildPairingManager(description_aux);
  EXPECT_EQ(child_pairing_manager->StartPairing(), 0);
  EXPECT_TRUE(child_pairing_manager->IsPairingStarted());
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 2);

  // test if child is paired
  sleep(1);
  EXPECT_TRUE(child_pairing_manager->IsPairingStarted());

  // stop child pairing service
  EXPECT_EQ(child_pairing_manager->StopPairing(), 0);
  EXPECT_FALSE(child_pairing_manager->IsPairingStarted());
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 1);
  delete child_pairing_manager;
  // stop parent pairing service
  EXPECT_EQ(parent_pairing_manager_->StopPairing(), 0);
  EXPECT_FALSE(parent_pairing_manager_->IsPairingStarted());
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
}

TEST_F(PairingManagerTest, PairingWithOnePassiveDevice) {
  unsigned int class_index;
  string app_id;

  // add a active class
  UpnpFsmdaUtils::GenerateGUID(&app_id);
  class_index = parent_pairing_manager_->GenerateAvaliableIndex(app_id);
  device_class_description_rdf_ = "./files/passive_class_desc00.xml";
  EXPECT_EQ(device_class_description_->InitializeByRdfFile(
                device_class_description_rdf_),
            0);
  parent_pairing_manager_->AddClass(app_id, class_index);
  parent_pairing_manager_->AddClassDescription(app_id, class_index,
                                              device_class_description_);
  EXPECT_EQ(parent_pairing_manager_->GetRegistredClassesSize(app_id), 1);
  EXPECT_EQ(parent_pairing_manager_->StartPairing(), 0);

  // start child pairing service
  DeviceDescription description_aux;
  description_aux.InitializeByDeviceClass(
      DeviceClassDescription::kPassiveDevice);
  ChildPairingManager* child_pairing_manager =
      new ChildPairingManager(description_aux);
  EXPECT_EQ(child_pairing_manager->StartPairing(), 0);
  EXPECT_TRUE(child_pairing_manager->IsPairingStarted());
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 2);

  // test if child is paired
  sleep(1);
  EXPECT_TRUE(child_pairing_manager->IsPairingStarted());

  // stop child pairing service
  EXPECT_EQ(child_pairing_manager->StopPairing(), 0);
  EXPECT_FALSE(child_pairing_manager->IsPairingStarted());
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 1);
  delete child_pairing_manager;
  // stop parent pairing service
  EXPECT_EQ(parent_pairing_manager_->StopPairing(), 0);
  EXPECT_FALSE(parent_pairing_manager_->IsPairingStarted());
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
}

TEST_F(PairingManagerTest, PairingWithOneOnDemandDevice) {
  unsigned int class_index;
  string app_id;

  // add a active class
  UpnpFsmdaUtils::GenerateGUID(&app_id);
  class_index = parent_pairing_manager_->GenerateAvaliableIndex(app_id);
  device_class_description_rdf_ = "./files/ondemand_class_desc00.xml";
  EXPECT_EQ(device_class_description_->InitializeByRdfFile(
                device_class_description_rdf_),
            0);
  parent_pairing_manager_->AddClass(app_id, class_index);
  parent_pairing_manager_->AddClassDescription(app_id, class_index,
                                              device_class_description_);
  EXPECT_EQ(parent_pairing_manager_->GetRegistredClassesSize(app_id), 1);
  EXPECT_EQ(parent_pairing_manager_->StartPairing(), 0);

  // start child pairing service
  DeviceDescription description_aux;
  description_aux.InitializeByDeviceClass(
      DeviceClassDescription::kOnDemandDevice);
  ChildPairingManager* child_pairing_manager =
      new ChildPairingManager(description_aux);
  EXPECT_EQ(child_pairing_manager->StartPairing(), 0);
  EXPECT_TRUE(child_pairing_manager->IsPairingStarted());
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 2);

  // test if child is paired
  sleep(1);
  EXPECT_TRUE(child_pairing_manager->IsPairingStarted());

  // stop child pairing service
  EXPECT_EQ(child_pairing_manager->StopPairing(), 0);
  EXPECT_FALSE(child_pairing_manager->IsPairingStarted());
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 1);
  delete child_pairing_manager;
  // stop parent pairing service
  EXPECT_EQ(parent_pairing_manager_->StopPairing(), 0);
  EXPECT_FALSE(parent_pairing_manager_->IsPairingStarted());
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
}

TEST_F(PairingManagerTest, PairingWithOneMediaCapture) {
  unsigned int class_index;
  string app_id;

  // add a active class
  UpnpFsmdaUtils::GenerateGUID(&app_id);
  class_index = parent_pairing_manager_->GenerateAvaliableIndex(app_id);
  device_class_description_rdf_ = "./files/mediacapture_class_desc00.xml";
  EXPECT_EQ(device_class_description_->InitializeByRdfFile(
                device_class_description_rdf_),
            0);
  parent_pairing_manager_->AddClass(app_id, class_index);
  parent_pairing_manager_->AddClassDescription(app_id, class_index,
                                              device_class_description_);
  EXPECT_EQ(parent_pairing_manager_->GetRegistredClassesSize(app_id), 1);
  EXPECT_EQ(parent_pairing_manager_->StartPairing(), 0);

  // start child pairing service
  DeviceDescription description_aux;
  description_aux.InitializeByDeviceClass(
      DeviceClassDescription::kMediaCaptureDevice);
  ChildPairingManager* child_pairing_manager =
      new ChildPairingManager(description_aux);
  EXPECT_EQ(child_pairing_manager->StartPairing(), 0);
  EXPECT_TRUE(child_pairing_manager->IsPairingStarted());
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 2);

  // test if child is paired
  sleep(1);
  EXPECT_TRUE(child_pairing_manager->IsPairingStarted());

  // stop child pairing service
  EXPECT_EQ(child_pairing_manager->StopPairing(), 0);
  EXPECT_FALSE(child_pairing_manager->IsPairingStarted());
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 1);
  delete child_pairing_manager;
  // stop parent pairing service
  EXPECT_EQ(parent_pairing_manager_->StopPairing(), 0);
  EXPECT_FALSE(parent_pairing_manager_->IsPairingStarted());
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
}
