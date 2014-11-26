#ifndef PARING_DEVICE_DESCRIPTION_H_
#define PARING_DEVICE_DESCRIPTION_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include "fsmda/paringmanager/device_class_description.h"
#include "libxml/tree.h"
#include <string>

using namespace std;

class DeviceDescription {
 public:
  // public constructors & destructors
  DeviceDescription();
  virtual
  ~DeviceDescription();

  // public fields
  DeviceClassDescription::DeviceClassType classType_;
  string paringMethod_;

  // public methods
  int
  initialize_by_rdf_file(const string& rdf_file);

 private:
  // private fields
  xmlDocPtr doc_;
  bool initialized_;

};

#endif /* PARING_DEVICE_DESCRIPTION_H_ */
