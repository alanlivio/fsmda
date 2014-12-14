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

void PairingWithOneDeviceHelper(
    const string& device_rdf, const string& device_class_description_rdf,
    DeviceClassDescription::DeviceClassType expected_device_class_type,
    bool diferent_processes) {
  ChildPairingManager* child_pairing_manager;
  ParentPairingManager* parent_pairing_manager;

  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
  EXPECT_FALSE(UpnpFsmdaUtils::IsUpnpStarted());

  // start ChildPairingManager
  DeviceDescription device_description;
  EXPECT_EQ(device_description.InitializeByRdfFile(device_rdf), 0);
  child_pairing_manager = new ChildPairingManager(device_description);
  EXPECT_EQ(device_description.device_class_type(), expected_device_class_type);
  EXPECT_EQ(child_pairing_manager->StartPairing(), 0);
  EXPECT_TRUE(child_pairing_manager->IsPairingStarted());
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 1);

  // start ParentPairingManager
  if (diferent_processes) {
    FILE* parent_pipe = popen("./fake_parent_helper", "w");
    ASSERT_TRUE(parent_pipe);
    fprintf(parent_pipe, "%s\n",
            DeviceClassDescription::GetDeviceClassTypeStringByEnum(
                expected_device_class_type));
    fclose(parent_pipe);
  } else {
    DeviceClassDescription* device_class_description =
        new DeviceClassDescription();
    EXPECT_EQ(device_class_description->InitializeByRdfFile(
                  device_class_description_rdf),
              0);
    EXPECT_EQ(device_class_description->device_class_type(),
              expected_device_class_type);
    string app_id;
    UpnpFsmdaUtils::GenerateGUID(&app_id);
    parent_pairing_manager = new ParentPairingManager();
    unsigned int class_index =
        parent_pairing_manager->GenerateAvaliableIndex(app_id);
    //    parent_pairing_manager->AddClass(app_id, class_index);
    parent_pairing_manager->AddClassDescription(app_id, class_index,
                                                device_class_description);
    EXPECT_EQ(parent_pairing_manager->GetNumberOfRegistredClasses(app_id), 1);
    EXPECT_EQ(parent_pairing_manager->StartPairing(), 0);
    EXPECT_TRUE(parent_pairing_manager->IsPairingStarted());
    EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 2);
  }
  // test if child is paired
  sleep(1);
  EXPECT_TRUE(child_pairing_manager->IsPaired());

  if (diferent_processes == false) {
    // stop parent pairing service
    EXPECT_EQ(parent_pairing_manager->StopPairing(), 0);
    EXPECT_FALSE(parent_pairing_manager->IsPairingStarted());
    EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 1);
    delete parent_pairing_manager;
  }

  // stop child pairing service
  EXPECT_EQ(child_pairing_manager->StopPairing(), 0);
  EXPECT_FALSE(child_pairing_manager->IsPairingStarted());
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
  delete child_pairing_manager;

  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
  EXPECT_FALSE(UpnpFsmdaUtils::IsUpnpStarted());
}

TEST(PairingManagersTest, PairingWithOneDeviceInSameProcess) {
  PairingWithOneDeviceHelper("./files/active_dev_desc00.xml",
                             "./files/active_class_desc00.xml",
                             DeviceClassDescription::kActiveDevice, false);
//  PairingWithOneDeviceHelper("./files/passive_dev_desc00.xml",
//                             "./files/passive_class_desc00.xml",
//                             DeviceClassDescription::kPassiveDevice, false);
//  PairingWithOneDeviceHelper("./files/html_dev_desc00.xml",
//                             "./files/html_class_desc00.xml",
//                             DeviceClassDescription::kHtmlDevice, false);
//  PairingWithOneDeviceHelper("./files/ondemand_dev_desc00.xml",
//                             "./files/ondemand_class_desc00.xml",
//                             DeviceClassDescription::kOnDemandDevice, false);
//  PairingWithOneDeviceHelper("./files/mediacapture_dev_desc00.xml",
//                             "./files/mediacapture_class_desc00.xml",
//                             DeviceClassDescription::kMediaCaptureDevice,
//                             false);
}
TEST(PairingManagersTest, PairingWithOneDeviceInDiferentProcess) {
  PairingWithOneDeviceHelper("./files/active_dev_desc00.xml",
                             "./files/active_class_desc00.xml",
                             DeviceClassDescription::kActiveDevice, true);
//  PairingWithOneDeviceHelper("./files/passive_dev_desc00.xml",
//                             "./files/passive_class_desc00.xml",
//                             DeviceClassDescription::kPassiveDevice, true);
//  PairingWithOneDeviceHelper("./files/html_dev_desc00.xml",
//                             "./files/html_class_desc00.xml",
//                             DeviceClassDescription::kHtmlDevice, true);
//  PairingWithOneDeviceHelper("./files/ondemand_dev_desc00.xml",
//                             "./files/ondemand_class_desc00.xml",
//                             DeviceClassDescription::kOnDemandDevice, true);
//  PairingWithOneDeviceHelper("./files/mediacapture_dev_desc00.xml",
//                             "./files/mediacapture_class_desc00.xml",
//                             DeviceClassDescription::kMediaCaptureDevice, true);
}
