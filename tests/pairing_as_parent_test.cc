

#include "fsmda/device_class_description.h"
#include "fsmda/device_description.h"
#include "fsmda/parent_class_handler.h"
#include "fsmda/child_class_handler.h"
#include "fsmda/upnp/upnp_fsmda_utils.h"
#include "gtest/gtest.h"

using std::string;
using std::cout;
using std::clog;
using std::endl;

NPT_SharedVariable parent_semaphore;
class MockParentClassHandler : public ParentClassHandler {
 public:
  virtual void report_add_device_to_class(const string& application_id,
                                          unsigned int class_index) {
    clog << "MockParentClassHandler::AddDeviceToClass()" << endl;
    ParentClassHandler::report_add_device_to_class(application_id, class_index);
    parent_semaphore.SetValue(1);
  }
};

class MockHpe : public HpeClassHandlingInterface,
                public ActiveClassListenerInterface {
 public:
  string expected_semaphore;

  // ActiveClassListenerInterface interface
  virtual void report_property_value(const string& object_id,
                                     const string& name, const string& value) {
    cout << "MockParentClassHandler::ReportPropertyValue()" << endl;
  }
  void notify_event_transition(const string& object_id, const string& event_id,
                               const string& transition) {
    cout << "MockParentClassHandler::NotifyEventTransition()" << endl;
  }
  void notify_error(const string& object_id, const string& message) {}

  // HpeClassHandlingInterface interface
  void get_class_variable_value(const string& name, const string& value) {}
  void set_class_variable_value(const string& name, const string& value) {
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
  int ret = system("./release_fake_child_parent.sh > /dev/null");

  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
  EXPECT_FALSE(UpnpFsmdaUtils::IsUpnpStarted());

  // genereate a app_id
  UpnpFsmdaUtils::GenerateGUID(&app_id);

  // configure ParentClassHandlher
  DeviceClassDescription* device_class_description;
  device_class_description = new DeviceClassDescription();
  EXPECT_EQ(device_class_description->initialize_by_rdf_file(
                device_class_description_rdf),
            0);
  EXPECT_EQ(device_class_description->device_class_type(),
            expected_device_class_type);
  parent_class_handler = new MockParentClassHandler();
  mock_hpe = new MockHpe();
  unsigned int class_index =
      parent_class_handler->generate_avaliable_index(app_id);
  parent_class_handler->add_class_description(app_id, class_index,
                                              device_class_description);
  parent_class_handler->set_class_handling_hpe(app_id, mock_hpe);
  EXPECT_EQ(parent_class_handler->number_of_registred_classes(app_id), 1);

  // start ParentClassHandlher
  EXPECT_EQ(parent_class_handler->start_pairing(), 0);
  EXPECT_TRUE(parent_class_handler->is_pairing_started());
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 1);

  // start ChildClassHandler
  if (diferent_processes) {
    // configure and start ChildClassHandler
    // start fake_child_helper by system
    string command = "./fake_child_helper";
    command.append(" --device_class=");
    command.append(DeviceClassDescription::to_device_class_string(
        expected_device_class_type));
    command.append(" > /dev/null");
    int ret = system(command.c_str());
  } else {
    DeviceDescription device_description;
    EXPECT_EQ(device_description.initialize_by_rdf_file(device_rdf), 0);
    child_class_handler = new ChildClassHandler(device_description);
    EXPECT_EQ(device_description.device_class_type(),
              expected_device_class_type);
    EXPECT_EQ(child_class_handler->start_pairing(), 0);
    EXPECT_TRUE(child_class_handler->is_pairing_started());
    EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 2);
  }
  // parent wait for ParentPostSemphoreHelper call
  parent_semaphore.WaitUntilEquals(1, NPT_TIMEOUT_INFINITE);
  EXPECT_EQ(
      parent_class_handler->number_of_registred_children(app_id, class_index),
      1);
  if (device_class_description->device_class_type() ==
      DeviceClassDescription::kPassiveDevice) {
    PassiveClassListenerInterface* passive_pcm =
        parent_class_handler->create_passive_pcm(app_id, class_index);
    EXPECT_TRUE(passive_pcm);
    delete passive_pcm;
  } else if (device_class_description->device_class_type() ==
             DeviceClassDescription::kActiveDevice) {
    ActiveClassInterface* active_pcm =
        parent_class_handler->create_active_pcm(app_id, class_index);
    active_pcm->registry_active_class_listener(mock_hpe);
    active_pcm->post_action("media01", "evt01", "start");
    EXPECT_TRUE(active_pcm);
    delete active_pcm;
  } else if (device_class_description->device_class_type() ==
             DeviceClassDescription::kOnDemandDevice) {
    OnDemandClassListenerInterface* ondemand_pcm =
        parent_class_handler->create_ondemand_pcm(app_id, class_index);
    EXPECT_TRUE(ondemand_pcm);
    delete ondemand_pcm;
  } else if (device_class_description->device_class_type() ==
             DeviceClassDescription::kMediaCaptureDevice) {
    MediaCaptureClassListenerInterface* medicapture_pcm =
        parent_class_handler->create_media_capture_pcm(app_id, class_index);
    EXPECT_TRUE(medicapture_pcm);
    delete medicapture_pcm;
  } else {
    FAIL();
  }

  if (diferent_processes == false) {
    // stop child pairing service
    EXPECT_EQ(child_class_handler->stop_pairing(), 0);
    EXPECT_FALSE(child_class_handler->is_pairing_started());
    EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 1);
    delete child_class_handler;
  }

  // stop parent pairing service
  EXPECT_EQ(parent_class_handler->stop_pairing(), 0);
  EXPECT_FALSE(parent_class_handler->is_pairing_started());
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
  delete parent_class_handler;

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
