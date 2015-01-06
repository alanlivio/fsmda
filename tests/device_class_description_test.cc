/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include "fsmda/class_handling/device_class_description.h"
#include "fsmda/class_handling/device_description.h"
#include "fsmda/parent_pairing_manager.h"
#include "fsmda/child_pairing_manager.h"
#include "fsmda/utils/upnp_fsmda_utils.h"
#include "gtest/gtest.h"

using std::string;

void DeviceDescriptionMatchingHelper(
    const string& device_rdf, const string& device_class_description_rdf,
    DeviceClassDescription::DeviceClassType expected_device_class_type) {
  DeviceDescription device_description;
  DeviceClassDescription device_class_description;

  EXPECT_EQ(device_description.InitializeByRdfFile(device_rdf), 0);
  EXPECT_EQ(device_class_description.InitializeByRdfFile(
                device_class_description_rdf),
            0);

  EXPECT_EQ(device_description.device_class_type(), expected_device_class_type);
  EXPECT_EQ(device_class_description.device_class_type(),
            expected_device_class_type);

  EXPECT_TRUE(device_class_description.IsDeviceCompatible(&device_description));
}

TEST(DeviceClassDescription, PassiveDeviceDescriptionMatching) {
  // passive class description initialize and meet_requirements tests
  DeviceDescriptionMatchingHelper("./files/passive_dev_desc00.xml",
                                  "./files/passive_class_desc00.xml",
                                  DeviceClassDescription::kPassiveDevice);
}
TEST(DeviceClassDescription, ActiveDeviceDescriptionMatching) {
  // active class description initialize and meet_requirements tests
  DeviceDescriptionMatchingHelper("./files/active_dev_desc00.xml",
                                  "./files/active_class_desc00.xml",
                                  DeviceClassDescription::kActiveDevice);
}
TEST(DeviceClassDescription, ActiveHtmlDeviceDescriptionMatching) {
  // html class description initialize and meet_requirements tests
  DeviceDescriptionMatchingHelper("./files/html_dev_desc00.xml",
                                  "./files/html_class_desc00.xml",
                                  DeviceClassDescription::kHtmlDevice);
}
TEST(DeviceClassDescription, OnDemandDeviceDescriptionMatching) {
  // ondemand class description initialize and meet_requirements tests
  DeviceDescriptionMatchingHelper("./files/ondemand_dev_desc00.xml",
                                  "./files/ondemand_class_desc00.xml",
                                  DeviceClassDescription::kOnDemandDevice);
}
TEST(DeviceClassDescription, MediaCatpureDeviceDescriptionMatching) {
  // mediacapture class description initialize and meet_requirements tests
  DeviceDescriptionMatchingHelper("./files/mediacapture_dev_desc00.xml",
                                  "./files/mediacapture_class_desc00.xml",
                                  DeviceClassDescription::kMediaCaptureDevice);
}
