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

  EXPECT_TRUE(
      device_class_description.DeviceMeetRequirements(&device_description));
}

void PairingWithOneDeviceHelper(
    const string& device_rdf, const string& device_class_description_rdf,
    DeviceClassDescription::DeviceClassType expected_device_class_type) {

  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
  EXPECT_FALSE(UpnpFsmdaUtils::IsUpnpStarted());

  // add a device class
  DeviceClassDescription* device_class_description =
      new DeviceClassDescription();
  EXPECT_EQ(device_class_description->InitializeByRdfFile(
                device_class_description_rdf),
            0);
  string app_id;
  UpnpFsmdaUtils::GenerateGUID(&app_id);
  ParentPairingManager* parent_pairing_manager = new ParentPairingManager();
  unsigned int class_index =
      parent_pairing_manager->GenerateAvaliableIndex(app_id);
  parent_pairing_manager->AddClass(app_id, class_index);
  parent_pairing_manager->AddClassDescription(app_id, class_index,
                                              device_class_description);
  EXPECT_EQ(parent_pairing_manager->GetNumberOfRegistredClasses(app_id), 1);

  // add a device
  DeviceDescription device_description;
  EXPECT_EQ(device_description.InitializeByRdfFile(device_rdf), 0);
  ChildPairingManager* child_pairing_manager =
      new ChildPairingManager(device_description);

  EXPECT_EQ(device_description.device_class_type(),
            expected_device_class_type);
  EXPECT_EQ(device_class_description->device_class_type(),
            expected_device_class_type);

  // start parent pairing service
  EXPECT_EQ(parent_pairing_manager->StartPairing(), 0);
  EXPECT_TRUE(parent_pairing_manager->IsPairingStarted());
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 1);

  // start child pairing service
  EXPECT_EQ(child_pairing_manager->StartPairing(), 0);
  EXPECT_TRUE(child_pairing_manager->IsPairingStarted());
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 2);

  // test if child is paired
  sleep(1);
  EXPECT_TRUE(child_pairing_manager->IsPaired());

  // stop child pairing service
  EXPECT_EQ(child_pairing_manager->StopPairing(), 0);
  EXPECT_FALSE(child_pairing_manager->IsPairingStarted());
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 1);
  delete child_pairing_manager;

  // stop parent pairing service
  EXPECT_EQ(parent_pairing_manager->StopPairing(), 0);
  EXPECT_FALSE(parent_pairing_manager->IsPairingStarted());
  delete parent_pairing_manager;

  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
  EXPECT_FALSE(UpnpFsmdaUtils::IsUpnpStarted());
}

TEST(PairingManagersTest, DeviceDescriptionMatching) {
  // active class description initialize and meet_requirements tests
  DeviceDescriptionMatchingHelper("./files/active_dev_desc00.xml",
                                  "./files/active_class_desc00.xml",
                                  DeviceClassDescription::kActiveDevice);

  // passive class description initialize and meet_requirements tests
  DeviceDescriptionMatchingHelper("./files/passive_dev_desc00.xml",
                                  "./files/passive_class_desc00.xml",
                                  DeviceClassDescription::kPassiveDevice);

  // html class description initialize and meet_requirements tests
  DeviceDescriptionMatchingHelper("./files/html_dev_desc00.xml",
                                  "./files/html_class_desc00.xml",
                                  DeviceClassDescription::kHtmlDevice);

  // ondemand class description initialize and meet_requirements tests
  DeviceDescriptionMatchingHelper("./files/ondemand_dev_desc00.xml",
                                  "./files/ondemand_class_desc00.xml",
                                  DeviceClassDescription::kOnDemandDevice);

  // mediacapture class description initialize and meet_requirements tests
  DeviceDescriptionMatchingHelper("./files/mediacapture_dev_desc00.xml",
                                  "./files/mediacapture_class_desc00.xml",
                                  DeviceClassDescription::kMediaCaptureDevice);
}

TEST(PairingManagersTest, PairingWithOneDevice) {
  // active class description initialize and meet_requirements tests
  PairingWithOneDeviceHelper("./files/active_dev_desc00.xml",
                             "./files/active_class_desc00.xml",
                             DeviceClassDescription::kActiveDevice);

  //  // active class description initialize and meet_requirements tests
  //  PairingWithOneDeviceHelper("./files/passive_dev_desc00.xml",
  //                             "./files/passive_class_desc00.xml",
  //                             DeviceClassDescription::kPassiveDevice);

  //  // active class description initialize and meet_requirements tests
  //  PairingWithOneDeviceHelper("./files/html_dev_desc00.xml",
  //                             "./files/html_class_desc00.xml",
  //                             DeviceClassDescription::kHtmlDevice);

  //  // active class description initialize and meet_requirements tests
  //  PairingWithOneDeviceHelper("./files/ondemand_dev_desc00.xml",
  //                             "./files/ondemand_class_desc00.xml",
  //                             DeviceClassDescription::kOnDemandDevice);

  //  // active class description initialize and meet_requirements tests
  //  PairingWithOneDeviceHelper("./files/mediacapture_dev_desc00.xml",
  //                             "./files/mediacapture_class_desc00.xml",
  //                             DeviceClassDescription::kMediaCaptureDevice);
}
