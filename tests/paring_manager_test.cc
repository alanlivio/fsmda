/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include "fsmda/paring/device_class_description.h"
#include "fsmda/paring/device_description.h"
#include "fsmda/paring/parent_paring_manager.h"
#include "fsmda/paring/child_paring_manager.h"
#include "fsmda/utils/upnp_fsmda_utils.h"
#include "gtest/gtest.h"

TEST(ParingManager, Constructors) {
  // test if upnp is running
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
  EXPECT_FALSE(UpnpFsmdaUtils::IsUpnpRunning());

  // constructors tests
  ParentParingManager* parent_paring_manager = new ParentParingManager();
  EXPECT_TRUE(parent_paring_manager);
  DeviceDescription* dev_description = new DeviceDescription();
  EXPECT_TRUE(dev_description);
  DeviceClassDescription* dev_class_requirements = new DeviceClassDescription();
  EXPECT_TRUE(dev_class_requirements);

  // release poniters
  delete parent_paring_manager;
  delete dev_class_requirements;
  delete dev_description;

  // test if upnp is running
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
  EXPECT_FALSE(UpnpFsmdaUtils::IsUpnpRunning());
}

TEST(ParingManager, AddClassDescription) {
  string app_id, class_type;
  unsigned int class_index;

  // test if upnp is running
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
  EXPECT_FALSE(UpnpFsmdaUtils::IsUpnpRunning());

  // constructors
  DeviceDescription* dev_description = new DeviceDescription();
  EXPECT_TRUE(dev_description);
  DeviceClassDescription* dev_class_requirements = new DeviceClassDescription();
  EXPECT_TRUE(dev_class_requirements);
  ParentParingManager* parent_paring_manager = new ParentParingManager();
  EXPECT_TRUE(parent_paring_manager);
  ChildParingManager* child_paring_manager = new ChildParingManager();
  EXPECT_TRUE(child_paring_manager);

  // Registing one deviceclass for app
  UpnpFsmdaUtils::GenerateGUID(&app_id);
  class_index = parent_paring_manager->GenerateAvaliableIndex(app_id);
  parent_paring_manager->AddClass(app_id, class_index);
  EXPECT_EQ(parent_paring_manager->GetNumberOfRegistredClasses(app_id), 1);

  // test if upnp is running
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 1);
  EXPECT_TRUE(UpnpFsmdaUtils::IsUpnpRunning());

  // Registing one deviceclass for app
  UpnpFsmdaUtils::GenerateGUID(&app_id);
  class_index = parent_paring_manager->GenerateAvaliableIndex(app_id);
  class_type = DeviceClassDescription::GetDeviceClassTypeStringByEnum(
      DeviceClassDescription::kFsmdaPassiveDevice);
  string network_paremeters, software_parameters, hardware_parameters;
  parent_paring_manager->AddClassDescription(
      app_id, class_index, class_type, 1, 3, network_paremeters,
      software_parameters, hardware_parameters);
  EXPECT_EQ(parent_paring_manager->GetNumberOfRegistredClasses(app_id), 2);

  // test if upnp is running
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 1);
  EXPECT_TRUE(UpnpFsmdaUtils::IsUpnpRunning());

  // release poniters
  delete dev_description;
  delete dev_class_requirements;
  delete parent_paring_manager;
  delete child_paring_manager;

  // test if upnp is running
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
  EXPECT_FALSE(UpnpFsmdaUtils::IsUpnpRunning());
}

TEST(ParingManager, DeviceDescriptionMatching) {
  string device_rdf;
  string device_class_description_rdf;
  bool ret;

  // test if upnp is running
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
  EXPECT_FALSE(UpnpFsmdaUtils::IsUpnpRunning());

  // constructors tests
  DeviceDescription* device_description = new DeviceDescription();
  EXPECT_TRUE(device_description);
  DeviceClassDescription* device_class_description =
      new DeviceClassDescription();
  EXPECT_TRUE(device_class_description);

  // passive class description initialize and meet_requirements tests
  device_rdf = "./files/passive_dev_desc00.xml";
  device_description->InitializeByRdfFile(device_rdf);
  EXPECT_EQ(device_description->device_class_type(),
            DeviceClassDescription::kFsmdaPassiveDevice);
  device_class_description_rdf = "./files/passive_class_desc00.xml";
  device_class_description->InitializeByParseRdfFile(
      device_class_description_rdf);
  EXPECT_EQ(device_class_description->device_class_type(),
            DeviceClassDescription::kFsmdaPassiveDevice);
  EXPECT_TRUE(
      device_class_description->DeviceMeetRequirements(device_description));

  // active class description initialize and meet_requirements tests
  device_rdf = "./files/active_dev_desc00.xml";
  device_description->InitializeByRdfFile(device_rdf);
  EXPECT_EQ(device_description->device_class_type(),
            DeviceClassDescription::kFsmdaActiveDevice);
  device_class_description_rdf = "./files/active_class_desc00.xml";
  device_class_description->InitializeByParseRdfFile(
      device_class_description_rdf);
  EXPECT_EQ(device_class_description->device_class_type(),
            DeviceClassDescription::kFsmdaActiveDevice);
  EXPECT_TRUE(
      device_class_description->DeviceMeetRequirements(device_description));

  // html class description initialize and meet_requirements tests
  device_rdf = "./files/html_dev_desc00.xml";
  device_description->InitializeByRdfFile(device_rdf);
  EXPECT_EQ(device_description->device_class_type(),
            DeviceClassDescription::kFsmdaHtmlDevice);
  device_class_description_rdf = "./files/html_class_desc00.xml";
  device_class_description->InitializeByParseRdfFile(
      device_class_description_rdf);
  EXPECT_EQ(device_class_description->device_class_type(),
            DeviceClassDescription::kFsmdaHtmlDevice);
  EXPECT_TRUE(
      device_class_description->DeviceMeetRequirements(device_description));

  // ondemand class description initialize and meet_requirements tests
  device_rdf = "./files/ondemand_dev_desc00.xml";
  device_description->InitializeByRdfFile(device_rdf);
  EXPECT_EQ(device_description->device_class_type(),
            DeviceClassDescription::kFsmdaOnDemandDevice);
  device_class_description_rdf = "./files/ondemand_class_desc00.xml";
  device_class_description->InitializeByParseRdfFile(
      device_class_description_rdf);
  EXPECT_EQ(device_class_description->device_class_type(),
            DeviceClassDescription::kFsmdaOnDemandDevice);
  EXPECT_TRUE(
      device_class_description->DeviceMeetRequirements(device_description));

  // mediacapture class description initialize and meet_requirements tests
  device_rdf = "./files/mediacapture_dev_desc00.xml";
  device_description->InitializeByRdfFile(device_rdf);
  EXPECT_EQ(device_description->device_class_type(),
            DeviceClassDescription::kFsmdaMediaCaptureDevice);
  device_class_description_rdf = "./files/mediacapture_class_desc00.xml";
  device_class_description->InitializeByParseRdfFile(
      device_class_description_rdf);
  EXPECT_EQ(device_class_description->device_class_type(),
            DeviceClassDescription::kFsmdaMediaCaptureDevice);
  EXPECT_TRUE(
      device_class_description->DeviceMeetRequirements(device_description));

  // release poniters
  delete device_description;
  delete device_class_description;

  // test if upnp is running
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
  EXPECT_FALSE(UpnpFsmdaUtils::IsUpnpRunning());
}
