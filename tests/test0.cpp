#include <cassert>
#include <cstring>
#include <cstdlib>

#include "fsmda/services/upnp_service.h"
#include "fsmda/model/communication/ondemand_object_control.h"
#include "fsmda/model/communication/active_object_control.h"
#include "fsmda/model/communication/passive_object_control.h"
#include "fsmda/model/communication/mediacapture_object_control.h"
#include "fsmda/model/paring/class_handling.h"
#include "fsmda/model/paring/device_paring.h"
#include "fsmda/gingancl/paring/parent_paring_manager.h"
#include "fsmda/gingancl/paring/child_paring_manager.h"

int
main (int argc, char **argv)
{
  ParentParingManager * ppm = new ParentParingManager ();
  assert(ppm != NULL);
  ChildParingManager * cpm = new ChildParingManager ();
  assert(cpm != NULL);
  delete ppm;
  delete cpm;

  return EXIT_SUCCESS;
}
