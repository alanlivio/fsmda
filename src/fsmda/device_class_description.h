#ifndef FSMDA_DEVICE_CLASS_DESCRIPTION_H_
#define FSMDA_DEVICE_CLASS_DESCRIPTION_H_


#include <libxml/tree.h>
#include <string>

using std::string;


class DeviceDescription;


class DeviceClassDescription {
 public:
  //  public enums and constants
  enum DeviceClassType {
    kInvalidDevice = -1,
    kBaseDevice = 0,
    kPassiveDevice = 1,
    kActiveDevice = 2,
    kHtmlDevice = 3,
    kOnDemandDevice = 4,
    kMediaCaptureDevice = 5
  };
  enum PairingProtocol {
    kPairingProtocolInvalid = -1,
    kUpnpPairingProcotol = 0,
    kZeroconfPairingProtocol = 1
  };
  enum CommunicationProtocol {
    kCommunicationProtocolInvalid = -1,
    kUpnpCommunicationProcotol = 0,
    kHTTPCommunicationProtocol = 1,
    kAdHocSocketCommunicationProtocol = 2
  };

  static const char* kInvalidDeviceString;
  static const char* kBaseDeviceString;
  static const char* kPassiveDeviceString;
  static const char* kActiveDeviceString;
  static const char* kHtmlDeviceString;
  static const char* kOnDemandDeviceString;
  static const char* kMediaCaptureDeviceString;

  static const char* kInvalidPairingProtocolString;
  static const char* kUpnpPairingProcotolString;
  static const char* kZeroconfPairingProtocolString;

  static const char* kInvalidCommunicationProtocolString;
  static const char* kUpnpCommunicationProcotolString;
  static const char* kHTTPCommunicationProtocolString;
  static const char* kAdHocSocketCommunicationProtocolString;

  static const char* kInvalidDeviceDefaultRdfContent;
  static const char* kPassiveDeviceDefaultRdfContent;
  static const char* kActiveDeviceDefaultRdfContent;
  static const char* kHtmlDeviceDefaultRdfContent;
  static const char* kOnDemandDeviceDefaultRdfContent;
  static const char* kMediCaptureDeviceDefaultRdfContent;

  // public static methods
  static DeviceClassType GetDeviceClassTypeByString(const string& str);
  static PairingProtocol GetPairingProtocolByString(const string& str);
  static CommunicationProtocol GetCommunicationProtocoByString(
      const string& str);
  static const char* GetDeviceClassRdfDefaultContentByType(
      DeviceClassType type);
  static const char* GetDeviceClassTypeStringByEnum(DeviceClassType type);
  static const char* GetPairingProtocolStringByEnum(PairingProtocol type);
  static const char* GetCommunicationProtocolStringByEnum(
      CommunicationProtocol type);

  // public constructors & destructors
  DeviceClassDescription();
  virtual ~DeviceClassDescription();

  // public methods
  bool IsDeviceCompatible(DeviceDescription* device_desc);
  int InitializeByDeviceClass(DeviceClassType type);
  int InitializeByRdfContent(const char* content);
  int InitializeByRdfFile(const string& rdf_file_path);
  DeviceClassType device_class_type();
  PairingProtocol pairing_protocol();
  CommunicationProtocol communication_protocol();
  const string& rdf_content();
  unsigned int min_devices();
  unsigned int max_devices();

 private:
  // private methods
  int ParseXmlContent(const char* rdf_conten);

  // private fields
  unsigned int min_devices_;
  unsigned int max_devices_;
  string rdf_content_;
  bool initialized_;
  DeviceClassType device_class_type_;
  PairingProtocol pairing_protocol_;
  CommunicationProtocol communication_protocol_;
};

#endif  // FSMDA_DEVICE_CLASS_DESCRIPTION_H_
