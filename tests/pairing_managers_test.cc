/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include <ctime>
#include <sys/time.h>
#include "./named_semaphore_helper.h"
#include "fsmda/device_class_description.h"
#include "fsmda/device_description.h"
#include "fsmda/parent_pairing_manager.h"
#include "fsmda/child_pairing_manager.h"
#include "fsmda/utils/upnp_fsmda_utils.h"
#include "gtest/gtest.h"

using std::string;
using std::cout;
using std::clog;
using std::endl;
using std::clock_t;
using std::clock;

class MockChildPairingManager : public ChildPairingManager {
 public:
  string expected_app_id;
  void SetPaired(bool paired) {
    clog << "MockChildPairingManager::SetPaired():: paired = " << paired
         << endl;
    ChildPairingManager::SetPaired(paired);
    PostNamedSemphoreHelper(expected_app_id);
  }
  explicit MockChildPairingManager(const DeviceDescription& device_description)
      : ChildPairingManager(device_description) {}
};

void PairingWithOneDeviceHelper(
    const string& device_rdf, const string& device_class_description_rdf,
    DeviceClassDescription::DeviceClassType expected_device_class_type,
    bool diferent_processes) {
  MockChildPairingManager* child_pairing_manager;
  ParentPairingManager* parent_pairing_manager;
  string app_id;
  timeval start_time, end_time;
  unsigned long long elapsed_time;

  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
  EXPECT_FALSE(UpnpFsmdaUtils::IsUpnpStarted());

  // start ChildPairingManager
  DeviceDescription device_description;
  EXPECT_EQ(device_description.InitializeByRdfFile(device_rdf), 0);
  child_pairing_manager = new MockChildPairingManager(device_description);
  EXPECT_EQ(device_description.device_class_type(), expected_device_class_type);
  EXPECT_EQ(child_pairing_manager->StartPairing(), 0);
  EXPECT_TRUE(child_pairing_manager->IsPairingStarted());
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 1);
  gettimeofday(&start_time, NULL);

  // start ParentPairingManager
  if (diferent_processes) {
    UpnpFsmdaUtils::GenerateGUID(&app_id);
    CreateNamedSemphoreHelper(app_id, true);
    child_pairing_manager->expected_app_id = app_id;

    // configure and start ParenPaigingManager
    // by open fake_parent_helper and create pipe to its sdtin
    FILE* parent_pipe = popen("./fake_parent_helper", "w");
    ASSERT_TRUE(parent_pipe);

    // send active as device class type
    fprintf(parent_pipe, "%s\n",
            DeviceClassDescription::GetDeviceClassTypeStringByEnum(
                expected_device_class_type));

    // send app id name to identify semaphore
    fprintf(parent_pipe, "%s\n", app_id.c_str());

    // close pipe
    pclose(parent_pipe);

    // child wait for ParentPostSemphoreHelper call
    WaitNamedSemphoreHelper(app_id);
  } else {
    UpnpFsmdaUtils::GenerateGUID(&app_id);
    CreateNamedSemphoreHelper(app_id, false);
    child_pairing_manager->expected_app_id = app_id;

    // configure and start ParenPaigingManager
    DeviceClassDescription* device_class_description;
    device_class_description = new DeviceClassDescription();
    EXPECT_EQ(device_class_description->InitializeByRdfFile(
                  device_class_description_rdf),
              0);
    EXPECT_EQ(device_class_description->device_class_type(),
              expected_device_class_type);
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

    // child wait for ParentPostSemphoreHelper call
    WaitNamedSemphoreHelper(app_id);
  }
  gettimeofday(&end_time, NULL);

  // sec to ms
  elapsed_time = (end_time.tv_sec - start_time.tv_sec) * 1000;
  // us to ms
  elapsed_time += (end_time.tv_usec - start_time.tv_usec) / 1000;

  cout << "PairingWithOneDeviceHelper(diferent_processes=" << diferent_processes
       << ", device_class_type=" << expected_device_class_type
       << ")::elapsed_time=" << elapsed_time << " ms" << endl;

  // test if child is paired
  EXPECT_TRUE(child_pairing_manager->IsPaired());
  ReleaseNameSemphoreHelper(app_id);

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
  PairingWithOneDeviceHelper("./files/passive_dev_desc00.xml",
                             "./files/passive_class_desc00.xml",
                             DeviceClassDescription::kPassiveDevice, false);
  PairingWithOneDeviceHelper("./files/active_dev_desc00.xml",
                             "./files/active_class_desc00.xml",
                             DeviceClassDescription::kActiveDevice, false);
  PairingWithOneDeviceHelper("./files/html_dev_desc00.xml",
                             "./files/html_class_desc00.xml",
                             DeviceClassDescription::kHtmlDevice, false);
  PairingWithOneDeviceHelper("./files/ondemand_dev_desc00.xml",
                             "./files/ondemand_class_desc00.xml",
                             DeviceClassDescription::kOnDemandDevice, false);
  PairingWithOneDeviceHelper("./files/mediacapture_dev_desc00.xml",
                             "./files/mediacapture_class_desc00.xml",
                             DeviceClassDescription::kMediaCaptureDevice,
                             false);
}
TEST(PairingManagersTest, PairingWithOneDeviceInDiferentProcessess) {
  PairingWithOneDeviceHelper("./files/passive_dev_desc00.xml",
                             "./files/passive_class_desc00.xml",
                             DeviceClassDescription::kPassiveDevice, true);
  PairingWithOneDeviceHelper("./files/active_dev_desc00.xml",
                             "./files/active_class_desc00.xml",
                             DeviceClassDescription::kActiveDevice, true);
  PairingWithOneDeviceHelper("./files/html_dev_desc00.xml",
                             "./files/html_class_desc00.xml",
                             DeviceClassDescription::kHtmlDevice, true);
  PairingWithOneDeviceHelper("./files/ondemand_dev_desc00.xml",
                             "./files/ondemand_class_desc00.xml",
                             DeviceClassDescription::kOnDemandDevice, true);
  PairingWithOneDeviceHelper("./files/mediacapture_dev_desc00.xml",
                             "./files/mediacapture_class_desc00.xml",
                             DeviceClassDescription::kMediaCaptureDevice, true);
}
