#include <assert.h>
#include <fsmda/gingancl/paring/device_class_description.h>
#include <fsmda/gingancl/paring/device_description.h>
#include <cstdlib>
#include <string>

int
main (int argc, char **argv)
{
  string device_rdf ("device_description000.xml");
  DeviceDescription * device_description = new DeviceDescription ();
  device_description->parse_rdf_file (device_rdf);
  assert(device_description != NULL);
  string device_class_description_rdf ("device_class_description000.xml");
  DeviceClassDescription * device_class_description = new DeviceClassDescription();
  device_class_description->parse_rdf_file (device_class_description_rdf);
  assert(device_class_description != NULL);

  return EXIT_SUCCESS;
}
