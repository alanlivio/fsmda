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

class MockParentClassHandler : public ParentClassHandler {
 public:
  string expected_semaphore;
  virtual void ReportAddDeviceToClass(const string& application_id,
                                      unsigned int class_index) {
    clog << "MockParentClassHandler::AddDeviceToClass()" << endl;
    ParentClassHandler::ReportAddDeviceToClass(application_id, class_index);
    PostNamedSemphoreHelper(expected_semaphore);
  }
};

class MockHpe : public HpeClassHandlingInterface,
                public ActiveClassListenerInterface {
 public:
  string expected_semaphore;

  // ActiveClassListenerInterface interface
  virtual void ReportPropertyValue(const string& object_id, const string& name,
                                   const string& value) {
    cout << "MockParentClassHandler::ReportPropertyValue()" << endl;
  }
  void NotifyEventTransition(const std::string& object_id,
                             const std::string& event_id,
                             const std::string& transition) {
    cout << "MockParentClassHandler::NotifyEventTransition()" << endl;
  }
  void NotifyError(const std::string& object_id, const std::string& message) {}

  // HpeClassHandlingInterface interface
  void getClassVariableValue(const std::string& name,
                             const std::string& value) {}
  void setClassVariableValue(const std::string& name,
                             const std::string& value) {
    cout << "MockParentClassHandler::setClassVariableValue()" << endl;
  }
};

void PairingAsParentHelper(
    const string& device_rdf, const string& device_class_description_rdf,
    DeviceClassDescription::DeviceClassType expected_device_class_type,
    bool diferent_processes) {
  ChildClassHandler* child_class_handler;
  MockParentClassHandler* parent_class_handler;
  MockHpe* mock_hpe;
  string app_id;

  // release fake child and parent
  int ret = system("./release_fake_child_parent.sh");

  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
  EXPECT_FALSE(UpnpFsmdaUtils::IsUpnpStarted());

  // genereate a app_id
  UpnpFsmdaUtils::GenerateGUID(&app_id);
  string parent_named_semaphore = app_id + "_parent";
  CreateNamedSemphoreHelper(parent_named_semaphore, false);

  // configure ParenPaigingManager
  DeviceClassDescription* device_class_description;
  device_class_description = new DeviceClassDescription();
  EXPECT_EQ(device_class_description->InitializeByRdfFile(
                device_class_description_rdf),
            0);
  EXPECT_EQ(device_class_description->device_class_type(),
            expected_device_class_type);
  parent_class_handler = new MockParentClassHandler();
  mock_hpe = new MockHpe();
  unsigned int class_index =
      parent_class_handler->GenerateAvaliableIndex(app_id);
  parent_class_handler->expected_semaphore = parent_named_semaphore;
  parent_class_handler->AddClassDescription(app_id, class_index,
                                            device_class_description);
  parent_class_handler->SetClassHandlingHpe(app_id, mock_hpe);
  EXPECT_EQ(parent_class_handler->number_of_registred_classes(app_id), 1);

  // start ParenPaigingManager
  EXPECT_EQ(parent_class_handler->StartPairing(), 0);
  EXPECT_TRUE(parent_class_handler->IsPairingStarted());
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 1);

  // start ParentClassHandler
  if (diferent_processes) {
    // configure and start ParenPaigingManager
    // by popen fake_parent_helper
    string command = "./fake_child_helper";
    command.append(" --device_class=");
    command.append(DeviceClassDescription::GetDeviceClassTypeStringByEnum(
        expected_device_class_type));
    command.append(" --application_id=" + app_id);
    FILE* parent_pipe = popen(command.c_str(), "w");
    ASSERT_TRUE(parent_pipe);
    pclose(parent_pipe);

  } else {
    DeviceDescription device_description;
    EXPECT_EQ(device_description.InitializeByRdfFile(device_rdf), 0);
    child_class_handler = new ChildClassHandler(device_description);
    EXPECT_EQ(device_description.device_class_type(),
              expected_device_class_type);
    EXPECT_EQ(child_class_handler->StartPairing(), 0);
    EXPECT_TRUE(child_class_handler->IsPairingStarted());
    EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 2);
  }
  // parent wait for ParentPostSemphoreHelper call
  cout << "parent wait" << endl;
  WaitNamedSemphoreHelper(parent_named_semaphore);

  // test if child is paired
  EXPECT_EQ(
      parent_class_handler->number_of_registred_children(app_id, class_index),
      1);
  if (device_class_description->device_class_type() ==
      DeviceClassDescription::kPassiveDevice) {
    PassiveClassListenerInterface* passive_pcm =
        parent_class_handler->CreatePassivePcm(app_id, class_index);
    EXPECT_TRUE(passive_pcm);
    delete passive_pcm;
  } else if (device_class_description->device_class_type() ==
             DeviceClassDescription::kActiveDevice) {
    ActiveClassInterface* active_pcm =
        parent_class_handler->CreateActivePcm(app_id, class_index);
    active_pcm->RegistryActiveClassListener(mock_hpe);
    active_pcm->PostAction("media01", "evt01", "start");
    EXPECT_TRUE(active_pcm);
    cout << "PostAction wait" << endl;
    delete active_pcm;
  } else if (device_class_description->device_class_type() ==
             DeviceClassDescription::kOnDemandDevice) {
    OnDemandClassListenerInterface* ondemand_pcm =
        parent_class_handler->CreateOnDemandPcm(app_id, class_index);
    EXPECT_TRUE(ondemand_pcm);
    delete ondemand_pcm;
  } else if (device_class_description->device_class_type() ==
             DeviceClassDescription::kMediaCaptureDevice) {
    MediaCaptureClassListenerInterface* medicapture_pcm =
        parent_class_handler->CreateMediaCapturePcm(app_id, class_index);
    EXPECT_TRUE(medicapture_pcm);
    delete medicapture_pcm;
  } else {
    FAIL();
  }

  if (diferent_processes == false) {
    // stop child pairing service
    EXPECT_EQ(child_class_handler->StopPairing(), 0);
    EXPECT_FALSE(child_class_handler->IsPairingStarted());
    EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 1);
    delete child_class_handler;
  }

  // stop parent pairing service
  EXPECT_EQ(parent_class_handler->StopPairing(), 0);
  EXPECT_FALSE(parent_class_handler->IsPairingStarted());
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
  delete parent_class_handler;
  ReleaseNameSemphoreHelper(parent_named_semaphore);

  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
  EXPECT_FALSE(UpnpFsmdaUtils::IsUpnpStarted());
}

TEST(PairingAsParent, PassiveInSameProcess) {
  PairingAsParentHelper("./files/passive_dev_desc00.xml",
                        "./files/passive_class_desc00.xml",
                        DeviceClassDescription::kPassiveDevice, false);
}
TEST(PairingAsParent, ActiveInSameProcess) {
  PairingAsParentHelper("./files/active_dev_desc00.xml",
                        "./files/active_class_desc00.xml",
                        DeviceClassDescription::kActiveDevice, false);
}
TEST(PairingAsParent, OnDemandInSameProcess) {
  PairingAsParentHelper("./files/ondemand_dev_desc00.xml",
                        "./files/ondemand_class_desc00.xml",
                        DeviceClassDescription::kOnDemandDevice, false);
}
TEST(PairingAsParent, MediaCaptureInSameProcess) {
  PairingAsParentHelper("./files/mediacapture_dev_desc00.xml",
                        "./files/mediacapture_class_desc00.xml",
                        DeviceClassDescription::kMediaCaptureDevice, false);
}
TEST(PairingAsParent, PassiveInDifferentProcesses) {
  PairingAsParentHelper("./files/passive_dev_desc00.xml",
                        "./files/passive_class_desc00.xml",
                        DeviceClassDescription::kPassiveDevice, true);
}
TEST(PairingAsParent, ActiveInDifferentProcesses) {
  PairingAsParentHelper("./files/active_dev_desc00.xml",
                        "./files/active_class_desc00.xml",
                        DeviceClassDescription::kActiveDevice, true);
}
TEST(PairingAsParent, OnDemandInDifferentProcesses) {
  PairingAsParentHelper("./files/ondemand_dev_desc00.xml",
                        "./files/ondemand_class_desc00.xml",
                        DeviceClassDescription::kOnDemandDevice, true);
}
TEST(PairingAsParent, MediaCaptureInDifferentProcesses) {
  PairingAsParentHelper("./files/mediacapture_dev_desc00.xml",
                        "./files/mediacapture_class_desc00.xml",
                        DeviceClassDescription::kMediaCaptureDevice, true);
}
