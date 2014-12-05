/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include "fsmda/paring/device_class_description.h"
#include "fsmda/paring/device_description.h"
#include "gtest/gtest.h"
#include <cstdlib>
#include <string>

TEST(Paring, DeviceMeetRequirements) {
  string device_rdf;
  string device_class_description_rdf;
  bool ret;
  DeviceDescription * device_description = new DeviceDescription();
  EXPECT_TRUE(device_description != NULL);
  DeviceClassDescription * device_class_description =
      new DeviceClassDescription();
  EXPECT_TRUE(device_class_description != NULL);

  // passive class description initialize and meet_requirements tests
  device_rdf = "./files/test1_passive_dev_desc00.xml";
  device_description->initialize_by_rdf_file(device_rdf);
  device_class_description_rdf = "./files/test1_passive_class_desc00.xml";
  device_class_description->initialize_by_parse_rdf_file(
      device_class_description_rdf);

  ret = device_class_description->device_meets_requirements(device_description);
  EXPECT_TRUE(ret);

  // active class description initialize and meet_requirements tests
  device_rdf = "./files/test1_active_dev_desc00.xml";
  device_description->initialize_by_rdf_file(device_rdf);
  device_class_description_rdf = "./files/test1_active_class_desc00.xml";
  device_class_description->initialize_by_parse_rdf_file(
      device_class_description_rdf);
  ret = device_class_description->device_meets_requirements(device_description);
  EXPECT_TRUE(ret);

  // html class description initialize and meet_requirements tests
  device_rdf = "./files/test1_html_dev_desc00.xml";
  device_description->initialize_by_rdf_file(device_rdf);
  device_class_description_rdf = "./files/test1_html_class_desc00.xml";
  device_class_description->initialize_by_parse_rdf_file(
      device_class_description_rdf);
  ret = device_class_description->device_meets_requirements(device_description);
  EXPECT_TRUE(ret);

  // ondemand class description initialize and meet_requirements tests
  device_rdf = "./files/test1_ondemand_dev_desc00.xml";
  device_description->initialize_by_rdf_file(device_rdf);
  device_class_description_rdf = "./files/test1_ondemand_class_desc00.xml";
  device_class_description->initialize_by_parse_rdf_file(
      device_class_description_rdf);
  ret = device_class_description->device_meets_requirements(device_description);
  EXPECT_TRUE(ret);

  // mediacapture class description initialize and meet_requirements tests
  device_rdf = "./files/test1_mediacapture_dev_desc00.xml";
  device_description->initialize_by_rdf_file(device_rdf);
  device_class_description_rdf = "./files/test1_mediacapture_class_desc00.xml";
  device_class_description->initialize_by_parse_rdf_file(
      device_class_description_rdf);
  ret = device_class_description->device_meets_requirements(device_description);
  EXPECT_TRUE(ret);

  delete device_description;
  delete device_class_description;
}
