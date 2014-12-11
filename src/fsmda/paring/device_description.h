#ifndef FSMDA_PARING_DEVICE_DESCRIPTION_H_
#define FSMDA_PARING_DEVICE_DESCRIPTION_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/
#include <string>
#include "fsmda/paring/device_class_description.h"
#include "libxml/tree.h"

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
  DeviceClassDescription::ParingProtocol paring_method() {
    return paring_method_;
  }
  bool IsInitialize() { return initialized_; }
  int InitializeByRdfFile(const string& rdf_file);
  int InitializeByDeviceClass(
      DeviceClassDescription::DeviceClassType device_class_type);

 private:
  // private fields
  bool initialized_;
  DeviceClassDescription::DeviceClassType class_type_;
  DeviceClassDescription::ParingProtocol paring_method_;
  xmlDocPtr doc_;
};

#endif  // FSMDA_PARING_DEVICE_DESCRIPTION_H_
