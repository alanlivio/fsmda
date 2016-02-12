#ifndef FSMDA_DEVICE_DESCRIPTION_H_
#define FSMDA_DEVICE_DESCRIPTION_H_

#include <libxml/tree.h>
#include <string>
#include "fsmda/device_class_description.h"

using std::string;

class DeviceDescription {
 public:
  // public constructors & destructors
  DeviceDescription();
  virtual ~DeviceDescription();

  // public methods
  DeviceClassDescription::DeviceClassType device_class_type();
  DeviceClassDescription::PairingProtocol pairing_method();
  const string rdf_content();
  bool initialized();
  int initialize_by_device_class(DeviceClassDescription::DeviceClassType type);
  int initialize_by_rdf_content(const char* content);
  int initialize_by_rdf_file(const string& rdf_file_path);

 private:
  // private methods
  int parse_xml_content(const char* rdf_content);

  // private fields
  bool initialized_;
  string rdf_content_;
  DeviceClassDescription::DeviceClassType device_class_type_;
  DeviceClassDescription::PairingProtocol pairing_protocol_;
  xmlDocPtr doc_;
};

#endif  // FSMDA_DEVICE_DESCRIPTION_H_
