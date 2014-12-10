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

  // public methods
  DeviceClassDescription::DeviceClassType device_class_type() {
    return class_type_;
  }
  string& paring_method() { return paring_method_; }
  int InitializeByRdfFile(const string& rdf_file);

 private:
  // private fields
  DeviceClassDescription::DeviceClassType class_type_;
  string paring_method_;
  xmlDocPtr doc_;
  bool initialized_;
};

#endif  // FSMDA_PARING_DEVICE_DESCRIPTION_H_
