/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include "gtest/gtest.h"
#include "fsmda/paring/device_class_description.h"
#include "fsmda/paring/device_description.h"
#include "fsmda/paring/parent_paring_manager.h"
#include "fsmda/paring/child_paring_manager.h"
#include "fsmda/utils/upnp_fsmda_utils.h"

using std::cout;
using std::endl;
using std::system;
using std::string;

TEST(ParingManager, ClassHandling) {
  // constructors
  DeviceDescription* dev_description = new DeviceDescription();
  EXPECT_TRUE(dev_description);
  DeviceClassDescription* dev_class_requirements = new DeviceClassDescription();
  EXPECT_TRUE(dev_class_requirements);
  ParentParingManager* parent_paring_manager = new ParentParingManager();
  EXPECT_TRUE(parent_paring_manager);
  ChildParingManager* child_paring_manager = new ChildParingManager();
  EXPECT_TRUE(child_paring_manager);

  string app_id;
  UpnpFsmdaUtils::GenerateGUID(app_id);

  // Registing one deviceclass for app
  parent_paring_manager->AddClass(
      app_id, parent_paring_manager->GenerateAvaliableIndex());
  EXPECT_EQ(parent_paring_manager->GetNumberOfRegistredClasses(), 1);

  // Registing one deviceclass for app
  UpnpFsmdaUtils::GenerateGUID(app_id);
  string network_paremeters, software_parameters, hardware_parameters;
  parent_paring_manager->AddClassDescription(
      app_id, parent_paring_manager->GenerateAvaliableIndex(),
      DeviceClassDescription::GetDeviceClassTypeStringByEnum(
          DeviceClassDescription::kFsmdaPassiveDevice),
      1, 3, network_paremeters, software_parameters, hardware_parameters);

  EXPECT_EQ(parent_paring_manager->GetNumberOfRegistredClasses(), 2);

  // release poniters
  delete dev_description;
  delete dev_class_requirements;
  delete parent_paring_manager;
  delete child_paring_manager;
}
