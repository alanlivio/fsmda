/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include "./named_semaphore_helper.h"
#include "fsmda//device_class_description.h"
#include "fsmda//device_description.h"
#include "fsmda/parent_class_handler.h"
#include "fsmda/child_class_handler.h"
#include "fsmda/upnp/upnp_fsmda_utils.h"
#include "gtest/gtest.h"

using std::string;
using std::cout;
using std::clog;
using std::endl;

class MockChildClassHandler : public ChildClassHandler {
 public:
  string expected_semaphore;
  void set_paired(bool paired) {
    clog << "MockChildClassHandler::set_paired():: paired = " << paired << endl;
    ChildClassHandler::set_paired(paired);
    PostNamedSemphoreHelper(expected_semaphore);
  }
  explicit MockChildClassHandler(const DeviceDescription& device_description)
      : ChildClassHandler(device_description) {}
};
class MockHpe : public HpeClassHandlingInterface {
 public:
  string expected_semaphore;

  // public methods
  void getClassVariableValue(const string& name, const string& value) {}
  void setClassVariableValue(const string& name, const string& value) {}
};

void PairingAsChildHelper(
    const string& device_rdf, const string& device_class_description_rdf,
    DeviceClassDescription::DeviceClassType expected_device_class_type,
    bool diferent_processes) {
  MockChildClassHandler* child_class_handler;
  ParentClassHandler* parent_class_handler;
  string app_id;

  // release fake child and parent
  int ret = system("./release_fake_child_parent.sh > /dev/null");

  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
  EXPECT_FALSE(UpnpFsmdaUtils::IsUpnpStarted());

  // start ChildClassHandler
  DeviceDescription device_description;
  EXPECT_EQ(device_description.InitializeByRdfFile(device_rdf), 0);
  child_class_handler = new MockChildClassHandler(device_description);
  EXPECT_EQ(device_description.device_class_type(), expected_device_class_type);
  EXPECT_EQ(child_class_handler->StartPairing(), 0);
  EXPECT_TRUE(child_class_handler->IsPairingStarted());
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 1);

  UpnpFsmdaUtils::GenerateGUID(&app_id);
  CreateNamedSemphoreHelper(app_id, false);
  child_class_handler->expected_semaphore = app_id;

  // start ParentClassHandler
  if (diferent_processes) {
    // configure and start ParenPaigingManager
    // by popen fake_parent_helper
    string command = "./fake_parent_helper";
    command.append(" --device_class=");
    command.append(DeviceClassDescription::GetDeviceClassTypeStringByEnum(
        expected_device_class_type));
    command.append(" --application_id=" + app_id);
    command.append(" > /dev/null");
    int ret = system(command.c_str());
  } else {
    // configure and start ParenPaigingManager
    DeviceClassDescription* device_class_description;
    MockHpe* mock_hpe;
    device_class_description = new DeviceClassDescription();
    EXPECT_EQ(device_class_description->InitializeByRdfFile(
                  device_class_description_rdf),
              0);
    mock_hpe = new MockHpe();
    EXPECT_EQ(device_class_description->device_class_type(),
              expected_device_class_type);
    parent_class_handler = new ParentClassHandler();
    unsigned int class_index =
        parent_class_handler->GenerateAvaliableIndex(app_id);
    //    parent_class_handler->AddClass(app_id, class_index);
    parent_class_handler->AddClassDescription(app_id, class_index,
                                              device_class_description);
    parent_class_handler->SetClassHandlingHpe(app_id, mock_hpe);
    EXPECT_EQ(parent_class_handler->number_of_registred_classes(app_id), 1);
    EXPECT_EQ(parent_class_handler->StartPairing(), 0);
    EXPECT_TRUE(parent_class_handler->IsPairingStarted());
    EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 2);
  }
  // child wait for ParentPostSemphoreHelper call
  WaitNamedSemphoreHelper(app_id);

  // test if child is paired
  EXPECT_TRUE(child_class_handler->paired());
  ReleaseNameSemphoreHelper(app_id);

  if (diferent_processes == false) {
    // stop parent pairing service
    EXPECT_EQ(parent_class_handler->StopPairing(), 0);
    EXPECT_FALSE(parent_class_handler->IsPairingStarted());
    EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 1);
    delete parent_class_handler;
  }

  // stop child pairing service
  EXPECT_EQ(child_class_handler->StopPairing(), 0);
  EXPECT_FALSE(child_class_handler->IsPairingStarted());
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
  delete child_class_handler;

  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
  EXPECT_FALSE(UpnpFsmdaUtils::IsUpnpStarted());
}

TEST(PairingAsChild, PassiveInSameProcess) {
  PairingAsChildHelper("./files/passive_dev_desc00.xml",
                       "./files/passive_class_desc00.xml",
                       DeviceClassDescription::kPassiveDevice, false);
}
TEST(PairingAsChild, ActiveInSameProcess) {
  PairingAsChildHelper("./files/active_dev_desc00.xml",
                       "./files/active_class_desc00.xml",
                       DeviceClassDescription::kActiveDevice, false);
}

TEST(PairingAsChild, OnDemandInSameProcess) {
  PairingAsChildHelper("./files/ondemand_dev_desc00.xml",
                       "./files/ondemand_class_desc00.xml",
                       DeviceClassDescription::kOnDemandDevice, false);
}
TEST(PairingAsChild, MediaCaptureInSameProcess) {
  PairingAsChildHelper("./files/mediacapture_dev_desc00.xml",
                       "./files/mediacapture_class_desc00.xml",
                       DeviceClassDescription::kMediaCaptureDevice, false);
}
TEST(PairingAsChild, PassiveInDifferentProcesses) {
  PairingAsChildHelper("./files/passive_dev_desc00.xml",
                       "./files/passive_class_desc00.xml",
                       DeviceClassDescription::kPassiveDevice, true);
}
TEST(PairingAsChild, ActiveInDifferentProcesses) {
  PairingAsChildHelper("./files/active_dev_desc00.xml",
                       "./files/active_class_desc00.xml",
                       DeviceClassDescription::kActiveDevice, true);
}

TEST(PairingAsChild, OnDemandInDifferentProcesses) {
  PairingAsChildHelper("./files/ondemand_dev_desc00.xml",
                       "./files/ondemand_class_desc00.xml",
                       DeviceClassDescription::kOnDemandDevice, true);
}
TEST(PairingAsChild, MediaCaptureInDifferentProcesses) {
  PairingAsChildHelper("./files/mediacapture_dev_desc00.xml",
                       "./files/mediacapture_class_desc00.xml",
                       DeviceClassDescription::kMediaCaptureDevice, true);
}
