/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include "fsmda/paring/device_class_description.h"
#include "fsmda/paring/device_description.h"
#include "fsmda/paring/upnp_child_paring.h"
#include "fsmda/paring/upnp_parent_paring.h"
#include "fsmda/utils/upnp_fsmda_utils.h"
#include "gtest/gtest.h"
#include "gtest/internal/gtest-linked_ptr.h"
#include "PltUPnP.h"
#include <cstdlib>
#include <string>

TEST(ParingManager, Constructors) {

  DeviceDescription* dev_description = new DeviceDescription();
  EXPECT_TRUE(dev_description);
  delete dev_description;
  DeviceClassDescription* dev_class_requirements = new DeviceClassDescription();
  EXPECT_TRUE(dev_class_requirements);
  delete dev_class_requirements;
}

TEST(ParingManager, DeviceDescriptionMatching) {
  string device_rdf;
  string device_class_description_rdf;
  bool ret;
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

  delete device_description;
  delete device_class_description;
}
