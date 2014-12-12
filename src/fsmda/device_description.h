#ifndef FSMDA_DEVICE_DESCRIPTION_H_
#define FSMDA_DEVICE_DESCRIPTION_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/
#include <libxml/tree.h>
#include <string>
#include "fsmda/device_class_description.h"

using std::string;

/*----------------------------------------------------------------------
 |   DeviceDescription class
 +---------------------------------------------------------------------*/
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

#endif  // FSMDA_DEVICE_DESCRIPTION_H_
