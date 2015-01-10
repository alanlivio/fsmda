/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include <cstdlib>
#include <iostream>
#include <fstream>
#include "./named_semaphore_helper.h"
#include "fsmda//device_description.h"
#include "fsmda//device_class_description.h"
#include "fsmda/parent_pairing_manager.h"
#include "fsmda/child_pairing_manager.h"
#include "fsmda/upnp/upnp_child_pairing.h"
#include "fsmda/upnp/upnp_parent_pairing.h"
#include "fsmda/upnp/upnp_fsmda_utils.h"
#include "gtest/gtest.h"

using std::string;
using std::cout;
using std::clog;
using std::endl;

class MockUpnpParentPairing : public UpnpParentPairing {
 public:
  string expected_semaphore;
  NPT_Result OnActionResponse(NPT_Result res, PLT_ActionReference& action,
                              void* userdata) {
    NPT_String name = action->GetActionDesc().GetName();
    clog << "MockUpnpChildPairing::OnActionResponse()::action.name="
         << name.GetChars() << endl;
    if (!name.Compare("classAnnouncement"))
      PostNamedSemphoreHelper(expected_semaphore);
    return UpnpParentPairing::OnActionResponse(res, action, userdata);
  }
};

void ClassAnnounceAsParentHelper(bool diferent_processes) {
  UpnpChildPairing* upnp_child_pairing;
  MockUpnpParentPairing* upnp_parent_pairing;
  string app_id;

  // release fake child and parent
  int ret = system("./release_fake_child_parent.sh");

  // test if upnp is running
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
  EXPECT_FALSE(UpnpFsmdaUtils::IsUpnpStarted());

  // genereate a app_id
  UpnpFsmdaUtils::GenerateGUID(&app_id);
  string parent_named_semaphore = app_id + "_parent";
  CreateNamedSemphoreHelper(parent_named_semaphore, false);

  // start upnp parent pairing service
  upnp_parent_pairing = new MockUpnpParentPairing();
  upnp_parent_pairing->expected_semaphore = parent_named_semaphore;
  unsigned int class_index = DeviceClassDescription::kActiveDevice;
  DeviceClassDescription* device_class_description =
      new DeviceClassDescription();
  device_class_description->InitializeByDeviceClass(
      DeviceClassDescription::kActiveDevice);
  DeviceClassDiscoverParams* dicover_params = new DeviceClassDiscoverParams(
      app_id, class_index, device_class_description);
  upnp_parent_pairing->AddDeviceClassForDiscover(dicover_params);
  EXPECT_EQ(upnp_parent_pairing->StartPairingService(), 0);
  EXPECT_TRUE(upnp_parent_pairing->IsPairingServiceStarted());
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 1);

  // start upnp child pairing service
  if (diferent_processes) {
    // configure and start ParenPaigingManager
    // by popen fake_parent_helper
    string command = "./fake_child_helper";
    command.append(" --device_class=");
    command.append(DeviceClassDescription::GetDeviceClassTypeStringByEnum(
        DeviceClassDescription::kActiveDevice));
    command.append(" --application_id=" + app_id);
    command.append(" --waiting_pairing");
    FILE* parent_pipe = popen(command.c_str(), "w");
    ASSERT_TRUE(parent_pipe);
    pclose(parent_pipe);

  } else {
    upnp_child_pairing = new UpnpChildPairing();
    EXPECT_EQ(upnp_child_pairing->StartPairingService(), 0);
    EXPECT_TRUE(upnp_child_pairing->IsPairingServiceStarted());
    EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 2);
  }
  // parent wait for ParentPostSemphoreHelper call
  WaitNamedSemphoreHelper(parent_named_semaphore);
  ReleaseNameSemphoreHelper(app_id);

  if (diferent_processes == false) {
    // stop child pairing service
    EXPECT_EQ(upnp_child_pairing->StopPairingService(), 0);
    EXPECT_FALSE(upnp_child_pairing->IsPairingServiceStarted());
    EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 1);
    delete upnp_child_pairing;
  }

  // stop parent pairing service
  EXPECT_EQ(upnp_parent_pairing->StopPairingService(), 0);
  EXPECT_FALSE(upnp_parent_pairing->IsPairingServiceStarted());
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
  delete upnp_parent_pairing;

  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
  EXPECT_FALSE(UpnpFsmdaUtils::IsUpnpStarted());
}

TEST(UpnpPairingAsParent, ClassAnnounceInSameProcess) {
  ClassAnnounceAsParentHelper(false);
}

TEST(UpnpPairingAsParent, ClassAnnounceInDifferentProcesses) {
  // TODO(alan@telemidia.puc-rio.br)
  //  ClassAnnounceHelper(true);
}
