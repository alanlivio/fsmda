/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include <cstdlib>
#include <iostream>
#include <fstream>
#include "./named_semaphore_helper.h"
#include "fsmda//device_description.h"
#include "fsmda//device_class_description.h"
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

class MockUpnpCpm : public UpnpCpm {
 public:
  string expected_semaphore;
  MockUpnpCpm() : UpnpCpm() {}

  NPT_Result OnAction(PLT_ActionReference& action,
                      const PLT_HttpRequestContext& context) {
    clog << "MockUpnpCpm::OnAction()::name="
         << action->GetActionDesc().GetName().GetChars() << endl;
    NPT_String name = action->GetActionDesc().GetName();
    if (!name.Compare("ClassAnnouncement"))
      PostNamedSemphoreHelper(expected_semaphore);
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
  EXPECT_EQ(upnp_cpm->StartPairingService(), 0);
  EXPECT_TRUE(upnp_cpm->IsPairingServiceStarted());
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 1);

  UpnpFsmdaUtils::GenerateGUID(&app_id);
  CreateNamedSemphoreHelper(app_id, false);
  upnp_cpm->expected_semaphore = app_id;

  if (different_processes) {
    // configure and start ParentClassHandlher
    // start fake_parent_helper by system
    string command = "./fake_parent_helper";
    command.append(" --device_class=");
    command.append(DeviceClassDescription::GetDeviceClassTypeStringByEnum(
        DeviceClassDescription::kActiveDevice));
    command.append(" --application_id=" + app_id);
    command.append(" > /dev/null");
    int ret = system(command.c_str());

  } else {
    // start parent pairing service with fake discover params
    // only for enable handshake
    upnp_ppm = new UpnpPpm();
    unsigned int class_index = DeviceClassDescription::kActiveDevice;
    DeviceClassDescription* device_class_description =
        new DeviceClassDescription();
    device_class_description->InitializeByDeviceClass(
        DeviceClassDescription::kActiveDevice);
    DeviceClassDiscoverParams* dicover_params = new DeviceClassDiscoverParams(
        app_id, class_index, device_class_description);
    upnp_ppm->AddDeviceClassForDiscover(dicover_params);
    EXPECT_EQ(upnp_ppm->StartPairingService(), 0);
    EXPECT_TRUE(upnp_ppm->IsPairingServiceStarted());
    EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 2);
  }

  // child wait for ParentPostSemphoreHelper call
  WaitNamedSemphoreHelper(app_id);
  ReleaseNameSemphoreHelper(app_id);

  if (different_processes == false) {
    // stop parent pairing service
    EXPECT_EQ(upnp_ppm->StopPairingService(), 0);
    EXPECT_FALSE(upnp_ppm->IsPairingServiceStarted());
    EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 1);
    delete upnp_ppm;
  }

  // stop child pairing service
  EXPECT_EQ(upnp_cpm->StopPairingService(), 0);
  EXPECT_FALSE(upnp_cpm->IsPairingServiceStarted());
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
