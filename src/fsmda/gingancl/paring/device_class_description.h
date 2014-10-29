#ifndef FSMDA_GINGANCL_PARING_DEVICE_CLASS_DESCRIPTION_H_
#define FSMDA_GINGANCL_PARING_DEVICE_CLASS_DESCRIPTION_H_

#include <map>
#include <string>
#include <libxml/parser.h>

#include "device_description.h"

using namespace std;
class DeviceClassDescription
{
public:
  // static fields and methods
  enum DeviceClassType
  {
    FSDMA_BASE = 0,
    FSDMA_PASSIVE = 1,
    FSDMA_ACTIVE = 2,
    FSDMA_HTML = 3,
    FSDMA_ONDEMAND = 4,
    FSDMA_MEDIACAPTURE = 5
  };
  static DeviceClassType
  get_device_class_type_by_string (const string& str);

// public methods
public:
  DeviceClassDescription (DeviceClassType deviceClassType);
  DeviceClassDescription (const string& rdf_file);
  virtual
  ~DeviceClassDescription ();
  bool
  device_meets_requirements (DeviceDescription device_desc);

// private fields
private:
  DeviceClassType classType_;
  xmlDocPtr doc_;
  static string deviceClassTypeMap[];

// private methods
private:
  void
  parse_rdf_file (const string& rdf_file);

};

#endif /* FSMDA_GINGANCL_PARING_DEVICE_CLASS_DESCRIPTION_H_ */
