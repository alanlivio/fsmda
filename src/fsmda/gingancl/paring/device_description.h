#ifndef FSMDA_GINGANCL_PARING_DEVICE_DESCRIPTION_H_
#define FSMDA_GINGANCL_PARING_DEVICE_DESCRIPTION_H_

#include <string>
#include "device_class_description.h"

using namespace std;

class DeviceDescription
{
// public fields
public:
  DeviceClassDescription::DeviceClassType classType_;
  string paringMethod_;

// public methods
public:
  DeviceDescription ();
  virtual
  ~DeviceDescription ();
  int
  initialize_by_rdf_file (const string& rdf_file);

// private fields
private:
  xmlDocPtr doc_;
  bool initialized_;

// private methods
private:

};

#endif /* FSMDA_GINGANCL_PARING_DEVICE_DESCRIPTION_H_ */
