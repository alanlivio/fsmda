/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include "fsmda/paring/device_class_description.h"
#include "fsmda/paring/device_description.h"
#include "fsmda/paring/parent_paring_manager.h"
#include "fsmda/paring/child_paring_manager.h"
#include "fsmda/utils/upnp_fsmda_utils.h"
#include "gtest/gtest.h"

using std::string;

class ParingManagerTest : public ::testing::Test {
 public:
  ParingManagerTest() {}
  ~ParingManagerTest() {}
  DeviceDescription* device_description_;
  DeviceDescription* ppm_device_description_;
  DeviceClassDescription* device_class_description_;
  string device_rdf_, device_class_description_rdf_;
  ParentParingManager* parent_paring_manager_;
  ChildParingManager* child_paring_manager_;

  void SetUp() {
    // test if upnp is running
    EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
    EXPECT_FALSE(UpnpFsmdaUtils::IsUpnpStarted());

    // constructors
    parent_paring_manager_ = new ParentParingManager();
    device_description_ = new DeviceDescription();
    DeviceDescription description_aux;
    description_aux.InitializeByDeviceClass(
        DeviceClassDescription::kFsmdaActiveDevice);
    child_paring_manager_ = new ChildParingManager(description_aux);
    device_class_description_ = new DeviceClassDescription();
  }

  void TearDown() {
    // release poniters
    delete device_description_;
    delete device_class_description_;
    delete parent_paring_manager_;
    delete child_paring_manager_;

    // test if upnp is running
    EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
    EXPECT_FALSE(UpnpFsmdaUtils::IsUpnpStarted());
  }
};

TEST_F(ParingManagerTest, DeviceDescriptionMatching) {
  // passive class description initialize and meet_requirements tests
  device_rdf_ = "./files/passive_dev_desc00.xml";
  device_class_description_rdf_ = "./files/passive_class_desc00.xml";
  device_description_->InitializeByRdfFile(device_rdf_);
  EXPECT_EQ(device_description_->device_class_type(),
            DeviceClassDescription::kFsmdaPassiveDevice);
  EXPECT_EQ(device_class_description_->InitializeByRdfFile(
                device_class_description_rdf_),
            0);
  EXPECT_EQ(device_class_description_->device_class_type(),
            DeviceClassDescription::kFsmdaPassiveDevice);
  EXPECT_TRUE(
      device_class_description_->DeviceMeetRequirements(device_description_));

  // active class description initialize and meet_requirements tests
  device_rdf_ = "./files/active_dev_desc00.xml";
  device_class_description_rdf_ = "./files/active_class_desc00.xml";
  EXPECT_EQ(device_description_->InitializeByRdfFile(device_rdf_), 0);
  EXPECT_EQ(device_description_->device_class_type(),
            DeviceClassDescription::kFsmdaActiveDevice);
  EXPECT_EQ(device_class_description_->InitializeByRdfFile(
                device_class_description_rdf_),
            0);
  EXPECT_EQ(device_class_description_->device_class_type(),
            DeviceClassDescription::kFsmdaActiveDevice);
  EXPECT_TRUE(
      device_class_description_->DeviceMeetRequirements(device_description_));

  // html class description initialize and meet_requirements tests
  device_rdf_ = "./files/html_dev_desc00.xml";
  device_class_description_rdf_ = "./files/html_class_desc00.xml";
  EXPECT_EQ(device_description_->InitializeByRdfFile(device_rdf_), 0);
  EXPECT_EQ(device_description_->device_class_type(),
            DeviceClassDescription::kFsmdaHtmlDevice);
  EXPECT_EQ(device_class_description_->InitializeByRdfFile(
                device_class_description_rdf_),
            0);
  EXPECT_EQ(device_class_description_->device_class_type(),
            DeviceClassDescription::kFsmdaHtmlDevice);
  EXPECT_TRUE(
      device_class_description_->DeviceMeetRequirements(device_description_));

  // ondemand class description initialize and meet_requirements tests
  device_class_description_rdf_ = "./files/ondemand_class_desc00.xml";
  device_rdf_ = "./files/ondemand_dev_desc00.xml";
  EXPECT_EQ(device_description_->InitializeByRdfFile(device_rdf_), 0);
  EXPECT_EQ(device_description_->device_class_type(),
            DeviceClassDescription::kFsmdaOnDemandDevice);
  EXPECT_EQ(device_class_description_->InitializeByRdfFile(
                device_class_description_rdf_),
            0);
  EXPECT_EQ(device_class_description_->device_class_type(),
            DeviceClassDescription::kFsmdaOnDemandDevice);
  EXPECT_TRUE(
      device_class_description_->DeviceMeetRequirements(device_description_));

  // mediacapture class description initialize and meet_requirements tests
  device_rdf_ = "./files/mediacapture_dev_desc00.xml";
  device_class_description_rdf_ = "./files/mediacapture_class_desc00.xml";
  EXPECT_EQ(device_description_->InitializeByRdfFile(device_rdf_), 0);
  EXPECT_EQ(device_description_->device_class_type(),
            DeviceClassDescription::kFsmdaMediaCaptureDevice);
  EXPECT_EQ(device_class_description_->InitializeByRdfFile(
                device_class_description_rdf_),
            0);
  EXPECT_EQ(device_class_description_->device_class_type(),
            DeviceClassDescription::kFsmdaMediaCaptureDevice);
  EXPECT_TRUE(
      device_class_description_->DeviceMeetRequirements(device_description_));
}

TEST_F(ParingManagerTest, AddClassDescription) {
  string app_id, class_type;
  unsigned int class_index;

  // add a active class
  UpnpFsmdaUtils::GenerateGUID(&app_id);
  class_index = parent_paring_manager_->GenerateAvaliableIndex(app_id);
  device_class_description_rdf_ = "./files/active_class_desc00.xml";
  EXPECT_EQ(device_class_description_->InitializeByRdfFile(
                device_class_description_rdf_),
            0);
  parent_paring_manager_->AddClass(app_id, class_index);
  parent_paring_manager_->AddClassDescription(app_id, class_index,
                                              device_class_description_);
  EXPECT_EQ(parent_paring_manager_->GetRegistredClassesSize(app_id), 1);

  // start child paring service
  EXPECT_EQ(child_paring_manager_->StartParing(), 0);
  //  EXPECT_TRUE(child_paring_manager_->IsParingStarted());
  //  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 2);

  //  // test if child is paired
  //  sleep(1);
  //  EXPECT_TRUE(child_paring_manager_->IsParingStarted());

  //  // stop child paring service
  //  EXPECT_EQ(child_paring_manager_->StopParing(), 0);
  //  EXPECT_FALSE(child_paring_manager_->IsParingStarted());
  //  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 1);

  //  // test if upnp is running
  //  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 1);
  //  EXPECT_TRUE(UpnpFsmdaUtils::IsUpnpStarted());
}
