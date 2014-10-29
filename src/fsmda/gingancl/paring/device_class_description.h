#ifndef FSMDA_GINGANCL_PARING_DEVICE_CLASS_DESCRIPTION_H_
#define FSMDA_GINGANCL_PARING_DEVICE_CLASS_DESCRIPTION_H_

#include <fsmda/gingancl/paring/device_description.h>
#include <string>
using namespace std;

class DeviceClassDescription
{
public:
  DeviceClassDescription (DeviceClassType deviceClassType);
  DeviceClassDescription (string rdf_file);
  virtual
  ~DeviceClassDescription ();

  bool
  device_meets_requirements (DeviceDescription device_desc);
};

#endif /* FSMDA_GINGANCL_PARING_DEVICE_CLASS_DESCRIPTION_H_ */
