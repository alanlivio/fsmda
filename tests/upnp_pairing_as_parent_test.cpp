

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


NPT_SharedVariable upnp_parent_semaphore;
class MockUpnpPpm : public UpnpPpm {
 public:
  NPT_Result OnActionResponse(NPT_Result res, PLT_ActionReference& action,
                              void* userdata) {
    NPT_String name = action->GetActionDesc().GetName();
    clog << "MockUpnpCpm::OnActionResponse()::action.name=" << name.GetChars()
         << endl;
    if (!name.Compare("ClassAnnouncement"))
        upnp_parent_semaphore.SetValue(1);
    return UpnpPpm::OnActionResponse(res, action, userdata);
  }
};

void ClassAnnounceAsParentHelper(bool diferent_processes) {
  UpnpCpm* upnp_cpm;
  MockUpnpPpm* upnp_ppm;
  string app_id;

  // release fake child and parent
  int ret = system("./release_fake_child_parent.sh");

  // test if upnp is running
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
  EXPECT_FALSE(UpnpFsmdaUtils::IsUpnpStarted());
  UpnpFsmdaUtils::GenerateGUID(&app_id);

  // start upnp parent pairing service
  upnp_ppm = new MockUpnpPpm();
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
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 1);

  // start upnp child pairing service
  if (diferent_processes) {
    // configure and start ChildClassHandler
    // start fake_child_helper by system
    string command = "./fake_child_helper";
    command.append(" --device_class=");
    command.append(DeviceClassDescription::GetDeviceClassTypeStringByEnum(
        DeviceClassDescription::kActiveDevice));
    command.append(" > /dev/null");
    int ret = system(command.c_str());
  } else {
    upnp_cpm = new UpnpCpm();
    EXPECT_EQ(upnp_cpm->StartPairingService(), 0);
    EXPECT_TRUE(upnp_cpm->IsPairingServiceStarted());
    EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 2);
  }
  // parent wait for ParentPostSemphoreHelper call
  upnp_parent_semaphore.WaitUntilEquals(1, NPT_TIMEOUT_INFINITE);

  if (diferent_processes == false) {
    // stop child pairing service
    EXPECT_EQ(upnp_cpm->StopPairingService(), 0);
    EXPECT_FALSE(upnp_cpm->IsPairingServiceStarted());
    EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 1);
    delete upnp_cpm;
  }

  // stop parent pairing service
  EXPECT_EQ(upnp_ppm->StopPairingService(), 0);
  EXPECT_FALSE(upnp_ppm->IsPairingServiceStarted());
  EXPECT_EQ(UpnpFsmdaUtils::upnp_references_count(), 0);
  delete upnp_ppm;

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
