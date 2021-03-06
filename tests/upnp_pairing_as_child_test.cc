

#include <cstdlib>
#include <iostream>
#include <fstream>
#include "fsmda/device_description.h"
#include "fsmda/device_class_description.h"
#include "fsmda/parent_class_handler.h"
#include "fsmda/child_class_handler.h"
#include "fsmda/upnp/upnp_cpm.h"
#include "fsmda/upnp/upnp_ppm.h"
#include "fsmda/upnp/upnp_fsmda_utils.h"
#include "gtest/gtest.h"

using std::string;
using std::cout;
using std::clog;
using std::endl;

NPT_SharedVariable upnp_child_semaphore;
class MockUpnpCpm : public UpnpCpm {
 public:
  MockUpnpCpm() : UpnpCpm() {}
  NPT_Result OnAction(PLT_ActionReference& action,
                      const PLT_HttpRequestContext& context) {
    clog << "MockUpnpCpm::OnAction()::name="
         << action->GetActionDesc().GetName().GetChars() << endl;
    NPT_String name = action->GetActionDesc().GetName();
    if (!name.Compare("ClassAnnouncement"))
      upnp_child_semaphore.SetValue(1);
    return UpnpCpm::OnAction(action, context);
  }
};

void ClassAnnounceAsChildHelper(bool different_processes) {
  UpnpPpm* upnp_ppm;
  MockUpnpCpm* upnp_cpm;
  string app_id;

  // release fake child and parent
  int ret = system("./release_fake_child_parent.sh");

  // test if upnp is running
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
  EXPECT_FALSE(UpnpFsmdaUtils::IsUpnpStarted());

  // start upnp child pairing service
  upnp_cpm = new MockUpnpCpm();
  EXPECT_EQ(upnp_cpm->start_pairing_service(), 0);
  EXPECT_TRUE(upnp_cpm->is_pairing_service_started());
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 1);
  UpnpFsmdaUtils::GenerateGUID(&app_id);

  if (different_processes) {
    // configure and start ParentClassHandlher
    // start fake_parent_helper by system
    string command = "./fake_parent_helper";
    command.append(" --device_class=");
    command.append(DeviceClassDescription::to_device_class_string(
        DeviceClassDescription::kActiveDevice));
    command.append(" --application_id=" + app_id);
    command.append(" > /dev/null");
    int ret = system(command.c_str());

  } else {
    // start parent pairing service with fake discover params
    // only for enable handshake
    upnp_ppm                 = new UpnpPpm();
    unsigned int class_index = DeviceClassDescription::kActiveDevice;
    DeviceClassDescription* device_class_description =
        new DeviceClassDescription();
    device_class_description->initialize_by_device_class(
        DeviceClassDescription::kActiveDevice);
    DeviceClassDiscoverParams* dicover_params = new DeviceClassDiscoverParams(
        app_id, class_index, device_class_description);
    upnp_ppm->add_device_class_for_discover(dicover_params);
    EXPECT_EQ(upnp_ppm->start_pairing_service(), 0);
    EXPECT_TRUE(upnp_ppm->is_pairing_service_started());
    EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 2);
  }

  // child wait for ParentPostSemphoreHelper call
  upnp_child_semaphore.WaitUntilEquals(1, NPT_TIMEOUT_INFINITE);

  if (different_processes == false) {
    // stop parent pairing service
    EXPECT_EQ(upnp_ppm->stop_pairing_service(), 0);
    EXPECT_FALSE(upnp_ppm->is_pairing_service_started());
    EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 1);
    delete upnp_ppm;
  }

  // stop child pairing service
  EXPECT_EQ(upnp_cpm->stop_pairing_service(), 0);
  EXPECT_FALSE(upnp_cpm->is_pairing_service_started());
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
  delete upnp_cpm;

  // test if upnp is running
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
  EXPECT_FALSE(UpnpFsmdaUtils::IsUpnpStarted());
}

TEST(UpnpPairingAsChild, ClassAnnounceInSameProcess) {
  ClassAnnounceAsChildHelper(false);
}

TEST(UpnpPairingAsChild, ClassAnnounceInDifferentProcesses) {
  // TODO(alan@telemidia.puc-rio.br)
  //  ClassAnnounceHelper(true);
}
