#ifndef FSMDA_PARING_DEVICE_CLASS_DESCRIPTION_H_
#define FSMDA_PARING_DEVICE_CLASS_DESCRIPTION_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/
#include "libxml/tree.h"
#include <string>

using std::string;

/*----------------------------------------------------------------------
 |   forward definitions
 +---------------------------------------------------------------------*/
class DeviceDescription;

/*----------------------------------------------------------------------
 |   DeviceClassDescription class
 +---------------------------------------------------------------------*/
class DeviceClassDescription {
 public:
  // class fields and methods
  enum DeviceClassType {
    kFsmdaBaseDevice = 0,
    kFsmdaPassiveDevice = 1,
    kFsmdaActiveDevice = 2,
    kFsmdaHtmlDevice = 3,
    kFsmdaOnDemandDevice = 4,
    kFsmdaMediaCaptureDevice = 5
  };
  enum ParingProtocol { kUpnpParingProcotol = 0, kZeroconfParingProtocol = 1 };
  enum CommunicationProtocol {
    kUpnpCommunicationProcotol = 0,
    kHTTPCommunicationProtocol = 1
  };
  static DeviceClassType GetDeviceClassTypeByString(const string& str);
  static const char* GetDeviceClassTypeStringByEnum(DeviceClassType type);

  // public constructors & destructors
  DeviceClassDescription();
  virtual ~DeviceClassDescription();

  // public fields
  DeviceClassType device_class_type() { return device_class_type_; }
  const string& paring_method() { return paring_protocol_; }
  unsigned int min_devices() { return min_devices_; }
  unsigned int max_devices() { return max_devices_; }
  bool DeviceMeetRequirements(DeviceDescription* device_desc);
  int InitializeByDeviceClass(DeviceClassType type);
  int InitializeByParseRdfFile(const string& rdf_file);

 private:
  DeviceClassType device_class_type_;
  string paring_protocol_;
  unsigned int min_devices_;
  unsigned int max_devices_;
  static const char* device_class_type_strings_[];
  xmlDocPtr doc_;
  bool initialized_;
};

#endif  // FSMDA_PARING_DEVICE_CLASS_DESCRIPTION_H_
