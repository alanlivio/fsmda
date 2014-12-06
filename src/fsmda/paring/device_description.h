#ifndef FSMDA_PARING_DEVICE_DESCRIPTION_H_
#define FSMDA_PARING_DEVICE_DESCRIPTION_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include "fsmda/paring/device_class_description.h"
#include "libxml/tree.h"
#include <string>

using std::string;

class DeviceDescription {
 public:
  // public constructors & destructors
  DeviceDescription();
  virtual ~DeviceDescription();

  // public fields
  DeviceClassDescription::DeviceClassType classType_;
  string paringMethod_;

  // public methods
  int InitializeByRdfFile(const string& rdf_file);

 private:
  // private fields
  xmlDocPtr doc_;
  bool initialized_;
};

#endif  // FSMDA_PARING_DEVICE_DESCRIPTION_H_
