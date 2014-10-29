#ifndef FSMDA_GINGANCL_PARING_DEVICE_CLASS_DESCRIPTION_H_
#define FSMDA_GINGANCL_PARING_DEVICE_CLASS_DESCRIPTION_H_

#include <libxml/tree.h>
#include <string>

class DeviceDescription;

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
  DeviceClassDescription ();
  virtual
  ~DeviceClassDescription ();
  bool
  device_meets_requirements (DeviceDescription device_desc);
  int
  initialize_by_default_device_class (DeviceClassType);
  int
  initialize_by_parse_rdf_file (const string& rdf_file);

// private fields
private:
  static string deviceClassTypeMap[];
  xmlDocPtr doc_;
  DeviceClassType classType_;
  string paringMethod_;
  unsigned int min_devices_;
  unsigned int max_devices_;
  bool is_configured_;

// private methods
private:

};

#endif /* FSMDA_GINGANCL_PARING_DEVICE_CLASS_DESCRIPTION_H_ */
