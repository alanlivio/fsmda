#include "fsmda/services/upnp_service.h"
#include "fsmda/model/communication/ondemand_object_control.h"
#include "fsmda/model/communication/active_object_control.h"
#include "fsmda/model/communication/passive_object_control.h"
#include "fsmda/model/communication/mediacapture_object_control.h"
#include "fsmda/model/paring/class_handling.h"
#include "fsmda/model/paring/device_paring.h"
#include "fsmda/gingancl/parent_paring_manager.h"
#include "fsmda/gingancl/child_paring_manager.h"
#include <cstdlib>

int
main (int argc, char **argv)
{
  ParentParingManager ppm;
  ChildParingManager cpm;
  return EXIT_SUCCESS;
}
