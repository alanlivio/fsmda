#include <assert.h>
#include <fsmda/gingancl/paring/device_class_description.h>
#include <fsmda/gingancl/paring/device_description.h>
#include <fsmda/gingancl/paring/device_class_description.h>
#include <fsmda/gingancl/paring/device_description.h>
#include <cstdlib>

int
main (int argc, char **argv)
{
  string device_rdf;
  string device_class_description_rdf;
  bool ret;
  DeviceDescription * device_description = new DeviceDescription ();
  DeviceClassDescription * device_class_description =
      new DeviceClassDescription ();

  /*----------------------------------------------------------------------
   |   passive class description initialize and meet_requirements tests
   +---------------------------------------------------------------------*/
  device_rdf = "./files/test1_passive_dev_desc00.xml";
  device_description->initialize_by_rdf_file (device_rdf);
  assert(device_description != NULL);

  device_class_description_rdf = "./files/test1_passive_class_desc00.xml";
  device_class_description->initialize_by_parse_rdf_file (
      device_class_description_rdf);
  assert(device_class_description != NULL);

  ret = device_class_description->device_meets_requirements (
      device_description);
  assert(ret);

  /*----------------------------------------------------------------------
   |   active class description initialize and meet_requirements tests
   +---------------------------------------------------------------------*/
  device_rdf = "./files/test1_active_dev_desc00.xml";
  device_description->initialize_by_rdf_file (device_rdf);
  assert(device_description != NULL);

  device_class_description_rdf = "./files/test1_active_class_desc00.xml";
  device_class_description->initialize_by_parse_rdf_file (
      device_class_description_rdf);
  assert(device_class_description != NULL);

  ret = device_class_description->device_meets_requirements (
      device_description);
  assert(ret);

  /*----------------------------------------------------------------------
   |   html class description initialize and meet_requirements tests
   +---------------------------------------------------------------------*/
  device_rdf = "./files/test1_html_dev_desc00.xml";
  device_description->initialize_by_rdf_file (device_rdf);
  assert(device_description != NULL);

  device_class_description_rdf = "./files/test1_html_class_desc00.xml";
  device_class_description->initialize_by_parse_rdf_file (
      device_class_description_rdf);
  assert(device_class_description != NULL);

  ret = device_class_description->device_meets_requirements (
      device_description);
  assert(ret);

  /*----------------------------------------------------------------------
   |   ondemand class description initialize and meet_requirements tests
   +---------------------------------------------------------------------*/
  device_rdf = "./files/test1_ondemand_dev_desc00.xml";
  device_description->initialize_by_rdf_file (device_rdf);
  assert(device_description != NULL);

  device_class_description_rdf = "./files/test1_ondemand_class_desc00.xml";
  device_class_description->initialize_by_parse_rdf_file (
      device_class_description_rdf);
  assert(device_class_description != NULL);

  ret = device_class_description->device_meets_requirements (
      device_description);
  assert(ret);

  /*----------------------------------------------------------------------
   |   mediacapture class description initialize and meet_requirements tests
   +---------------------------------------------------------------------*/
  device_rdf = "./files/test1_mediacapture_dev_desc00.xml";
  device_description->initialize_by_rdf_file (device_rdf);
  assert(device_description != NULL);

  device_class_description_rdf = "./files/test1_mediacapture_class_desc00.xml";
  device_class_description->initialize_by_parse_rdf_file (
      device_class_description_rdf);
  assert(device_class_description != NULL);

  ret = device_class_description->device_meets_requirements (
      device_description);
  assert(ret);

  delete device_description;
  delete device_class_description;

  return EXIT_SUCCESS;
}
