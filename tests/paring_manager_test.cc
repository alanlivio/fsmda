/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include "fsmda/paring/device_class_description.h"
#include "fsmda/paring/device_description.h"
#include "fsmda/paring/parent_paring_manager.h"
#include "fsmda/paring/child_paring_manager.h"
#include "fsmda/utils/upnp_fsmda_utils.h"
#include "gtest/gtest.h"

class ParingManagerTest : public ::testing::Test {
 public:
  ParingManagerTest() {}
  ~ParingManagerTest() {}
  ParentParingManager* parent_paring_manager_;
  DeviceDescription* device_description_;
  DeviceClassDescription* device_class_description_;

  void SetUp() {
    // test if upnp is running
    EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
    EXPECT_FALSE(UpnpFsmdaUtils::IsUpnpRunning());

    // constructors tests
    parent_paring_manager_ = new ParentParingManager();
    EXPECT_TRUE(parent_paring_manager_);
    device_description_ = new DeviceDescription();
    EXPECT_TRUE(device_description_);
    device_class_description_ = new DeviceClassDescription();
    EXPECT_TRUE(device_class_description_);
  }

  void TearDown() {
    // release poniters
    delete parent_paring_manager_;
    delete device_description_;
    delete device_class_description_;

    // test if upnp is running
    EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
    EXPECT_FALSE(UpnpFsmdaUtils::IsUpnpRunning());
  }
};

TEST_F(ParingManagerTest, DeviceDescriptionMatching) {
  string device_rdf;
  string device_class_description__rdf;

  // passive class description initialize and meet_requirements tests
  device_rdf = "./files/passive_dev_desc00.xml";
  device_description_->InitializeByRdfFile(device_rdf);
  EXPECT_EQ(device_description_->device_class_type(),
            DeviceClassDescription::kFsmdaPassiveDevice);
  device_class_description__rdf = "./files/passive_class_desc00.xml";
  device_class_description_->InitializeByParseRdfFile(
      device_class_description__rdf);
  EXPECT_EQ(device_class_description_->device_class_type(),
            DeviceClassDescription::kFsmdaPassiveDevice);
  EXPECT_TRUE(
      device_class_description_->DeviceMeetRequirements(device_description_));

  // active class description initialize and meet_requirements tests
  device_rdf = "./files/active_dev_desc00.xml";
  device_description_->InitializeByRdfFile(device_rdf);
  EXPECT_EQ(device_description_->device_class_type(),
            DeviceClassDescription::kFsmdaActiveDevice);
  device_class_description__rdf = "./files/active_class_desc00.xml";
  device_class_description_->InitializeByParseRdfFile(
      device_class_description__rdf);
  EXPECT_EQ(device_class_description_->device_class_type(),
            DeviceClassDescription::kFsmdaActiveDevice);
  EXPECT_TRUE(
      device_class_description_->DeviceMeetRequirements(device_description_));

  // html class description initialize and meet_requirements tests
  device_rdf = "./files/html_dev_desc00.xml";
  device_description_->InitializeByRdfFile(device_rdf);
  EXPECT_EQ(device_description_->device_class_type(),
            DeviceClassDescription::kFsmdaHtmlDevice);
  device_class_description__rdf = "./files/html_class_desc00.xml";
  device_class_description_->InitializeByParseRdfFile(
      device_class_description__rdf);
  EXPECT_EQ(device_class_description_->device_class_type(),
            DeviceClassDescription::kFsmdaHtmlDevice);
  EXPECT_TRUE(
      device_class_description_->DeviceMeetRequirements(device_description_));

  // ondemand class description initialize and meet_requirements tests
  device_rdf = "./files/ondemand_dev_desc00.xml";
  device_description_->InitializeByRdfFile(device_rdf);
  EXPECT_EQ(device_description_->device_class_type(),
            DeviceClassDescription::kFsmdaOnDemandDevice);
  device_class_description__rdf = "./files/ondemand_class_desc00.xml";
  device_class_description_->InitializeByParseRdfFile(
      device_class_description__rdf);
  EXPECT_EQ(device_class_description_->device_class_type(),
            DeviceClassDescription::kFsmdaOnDemandDevice);
  EXPECT_TRUE(
      device_class_description_->DeviceMeetRequirements(device_description_));

  // mediacapture class description initialize and meet_requirements tests
  device_rdf = "./files/mediacapture_dev_desc00.xml";
  device_description_->InitializeByRdfFile(device_rdf);
  EXPECT_EQ(device_description_->device_class_type(),
            DeviceClassDescription::kFsmdaMediaCaptureDevice);
  device_class_description__rdf = "./files/mediacapture_class_desc00.xml";
  device_class_description_->InitializeByParseRdfFile(
      device_class_description__rdf);
  EXPECT_EQ(device_class_description_->device_class_type(),
            DeviceClassDescription::kFsmdaMediaCaptureDevice);
  EXPECT_TRUE(
      device_class_description_->DeviceMeetRequirements(device_description_));
}

TEST_F(ParingManagerTest, AddClassDescription) {
  string app_id, class_type;
  unsigned int class_index;

  // Registing one deviceclass for app
  UpnpFsmdaUtils::GenerateGUID(&app_id);
  class_index = parent_paring_manager_->GenerateAvaliableIndex(app_id);
  parent_paring_manager_->AddClass(app_id, class_index);
  EXPECT_EQ(parent_paring_manager_->GetNumberOfRegistredClasses(app_id), 1);

  // test if upnp is running
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 1);
  EXPECT_TRUE(UpnpFsmdaUtils::IsUpnpRunning());

  // Registing one deviceclass for app
  UpnpFsmdaUtils::GenerateGUID(&app_id);
  class_index = parent_paring_manager_->GenerateAvaliableIndex(app_id);
  class_type = DeviceClassDescription::GetDeviceClassTypeStringByEnum(
      DeviceClassDescription::kFsmdaPassiveDevice);
  string network_paremeters, software_parameters, hardware_parameters;
  parent_paring_manager_->AddClassDescription(
      app_id, class_index, class_type, 1, 3, network_paremeters,
      software_parameters, hardware_parameters);
  EXPECT_EQ(parent_paring_manager_->GetNumberOfRegistredClasses(app_id), 2);

  // test if upnp is running
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 1);
  EXPECT_TRUE(UpnpFsmdaUtils::IsUpnpRunning());
}
