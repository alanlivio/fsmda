#ifndef FSMDA_DEVICE_DESCRIPTION_H_
#define FSMDA_DEVICE_DESCRIPTION_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/
#include <libxml/tree.h>
#include <string>
#include "fsmda//device_class_description.h"

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
  DeviceClassDescription::DeviceClassType device_class_type();
  DeviceClassDescription::PairingProtocol pairing_method();
  const string rdf_content();
  bool initialized();
  int InitializeByDeviceClass(DeviceClassDescription::DeviceClassType type);
  int InitializeByRdfContent(const char* content);
  int InitializeByRdfFile(const string& rdf_file_path);

 private:
  // private methods
  int ParseXmlContent(const char* rdf_conten);

  // private fields
  bool initialized_;
  string rdf_content_;
  DeviceClassDescription::DeviceClassType device_class_type_;
  DeviceClassDescription::PairingProtocol pairing_protocol_;
  xmlDocPtr doc_;
};

#endif  // FSMDA_DEVICE_DESCRIPTION_H_
