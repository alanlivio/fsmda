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
}

TEST(ParingManager, ClassHandling) {
  // constructors
  DeviceDescription* dev_description = new DeviceDescription();
  EXPECT_TRUE(dev_description);
  DeviceClassDescription* dev_class_requirements = new DeviceClassDescription();
  EXPECT_TRUE(dev_class_requirements);
  ParentParingManager* parent_paring_manager = new ParentParingManager();
  EXPECT_TRUE(parent_paring_manager);
  ChildParingManager* child_paring_manager = new ChildParingManager();
  EXPECT_TRUE(child_paring_manager);

  string app_id;
  UpnpFsmdaUtils::GenerateGUID(app_id);

  // Registing one deviceclass for app
  parent_paring_manager->AddClass(
      app_id, parent_paring_manager->GenerateAvaliableIndex());
  EXPECT_EQ(parent_paring_manager->GetNumberOfRegistredClasses(), 1);

  // Registing one deviceclass for app
  UpnpFsmdaUtils::GenerateGUID(app_id);
  string network_paremeters, software_parameters, hardware_parameters;
  parent_paring_manager->AddClassDescription(
      app_id, parent_paring_manager->GenerateAvaliableIndex(),
      DeviceClassDescription::GetDeviceClassTypeStringByEnum(
          DeviceClassDescription::kFsmdaPassiveDevice),
      1, 3, network_paremeters, software_parameters, hardware_parameters);

  EXPECT_EQ(parent_paring_manager->GetNumberOfRegistredClasses(), 2);

  // release poniters
  delete dev_description;
  delete dev_class_requirements;
  delete parent_paring_manager;
  delete child_paring_manager;
}


TEST(ParingManager, DeviceDescriptionMatching) {
  string device_rdf;
  string device_class_description_rdf;
  bool ret;

  // constructors tests
  DeviceDescription* device_description = new DeviceDescription();
  EXPECT_TRUE(device_description);
  DeviceClassDescription* device_class_description =
      new DeviceClassDescription();
  EXPECT_TRUE(device_class_description);

  // passive class description initialize and meet_requirements tests
  device_rdf = "./files/test1_passive_dev_desc00.xml";
  device_description->InitializeByRdfFile(device_rdf);
  device_class_description_rdf = "./files/test1_passive_class_desc00.xml";
  device_class_description->InitializeByParseRdfFile(
      device_class_description_rdf);

  ret = device_class_description->DeviceMeetRequirements(device_description);
  EXPECT_TRUE(ret);

  // active class description initialize and meet_requirements tests
  device_rdf = "./files/test1_active_dev_desc00.xml";
  device_description->InitializeByRdfFile(device_rdf);
  device_class_description_rdf = "./files/test1_active_class_desc00.xml";
  device_class_description->InitializeByParseRdfFile(
      device_class_description_rdf);
  ret = device_class_description->DeviceMeetRequirements(device_description);
  EXPECT_TRUE(ret);

  // html class description initialize and meet_requirements tests
  device_rdf = "./files/test1_html_dev_desc00.xml";
  device_description->InitializeByRdfFile(device_rdf);
  device_class_description_rdf = "./files/test1_html_class_desc00.xml";
  device_class_description->InitializeByParseRdfFile(
      device_class_description_rdf);
  ret = device_class_description->DeviceMeetRequirements(device_description);
  EXPECT_TRUE(ret);

  // ondemand class description initialize and meet_requirements tests
  device_rdf = "./files/test1_ondemand_dev_desc00.xml";
  device_description->InitializeByRdfFile(device_rdf);
  device_class_description_rdf = "./files/test1_ondemand_class_desc00.xml";
  device_class_description->InitializeByParseRdfFile(
      device_class_description_rdf);
  ret = device_class_description->DeviceMeetRequirements(device_description);
  EXPECT_TRUE(ret);

  // mediacapture class description initialize and meet_requirements tests
  device_rdf = "./files/test1_mediacapture_dev_desc00.xml";
  device_description->InitializeByRdfFile(device_rdf);
  device_class_description_rdf = "./files/test1_mediacapture_class_desc00.xml";
  device_class_description->InitializeByParseRdfFile(
      device_class_description_rdf);
  ret = device_class_description->DeviceMeetRequirements(device_description);
  EXPECT_TRUE(ret);

  // release poniters
  delete device_description;
  delete device_class_description;
}
