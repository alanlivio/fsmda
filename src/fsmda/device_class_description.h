#ifndef FSMDA_DEVICE_CLASS_DESCRIPTION_H_
#define FSMDA_DEVICE_CLASS_DESCRIPTION_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/
#include <libxml/tree.h>
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
  // class fields
  enum DeviceClassType {
    kDeviceClassTypeInvalid = -1,
    kFsmdaBaseDevice = 0,
    kFsmdaPassiveDevice = 1,
    kFsmdaActiveDevice = 2,
    kFsmdaHtmlDevice = 3,
    kFsmdaOnDemandDevice = 4,
    kFsmdaMediaCaptureDevice = 5
  };
  enum ParingProtocol {
    kParingProtocolInvalid = -1,
    kUpnpParingProcotol = 0,
    kZeroconfParingProtocol = 1
  };
  enum CommunicationProtocol {
    kCommunicationProtocolInvalid = -1,
    kUpnpCommunicationProcotol = 0,
    kHTTPCommunicationProtocol = 1
  };

  // class methods
  static DeviceClassType GetDeviceClassTypeByString(const string& str);
  static ParingProtocol GetParingProtocolByString(const string& str);
  static CommunicationProtocol GetCommunicationProtocoByString(
      const string& str);
  static const char* GetDeviceClassTypeStringByEnum(DeviceClassType type);
  static const char* GetParingProtocolStringByEnum(ParingProtocol type);
  static const char* GetCommunicationProtocolStringByEnum(
      CommunicationProtocol type);

  // public constructors & destructors
  DeviceClassDescription();
  virtual ~DeviceClassDescription();

  // public fields
  DeviceClassType device_class_type() { return device_class_type_; }
  ParingProtocol paring_protocol() { return paring_protocol_; }
  CommunicationProtocol communication_protocol() {
    return communication_protocol_;
  }
  unsigned int min_devices() { return min_devices_; }
  unsigned int max_devices() { return max_devices_; }
  bool DeviceMeetRequirements(DeviceDescription* device_desc);
  int InitializeByDeviceClass(DeviceClassType type);
  int InitializeByRdfFile(const string& rdf_file);

 private:
  // private fields
  unsigned int min_devices_;
  unsigned int max_devices_;
  bool initialized_;
  static const char* device_class_type_strings_[];
  static const char* paring_protocol_strings_[];
  static const char* communication_protocol_strings_[];
  xmlDocPtr doc_;
  DeviceClassType device_class_type_;
  ParingProtocol paring_protocol_;
  CommunicationProtocol communication_protocol_;
};

#endif  // FSMDA_DEVICE_CLASS_DESCRIPTION_H_
