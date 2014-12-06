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
  enum DeviceProtocol { kFsmaUpnpProtocol = 0, kFsmdaZeroconfProtocol = 1, };
  static DeviceClassType GetDeviceClassTypeByString(const string& str);

  // public constructors & destructors
  DeviceClassDescription();
  virtual ~DeviceClassDescription();

  // public fields
  DeviceClassType classType_;
  string paringMethod_;
  unsigned int min_devices_;
  unsigned int max_devices_;

  // public methods
  bool DeviceMeetRequirements(DeviceDescription* device_desc);
  int InitializeByDefaultDeviceClass(DeviceClassType type);
  int InitializeByParseRdfFile(const string& rdf_file);

 private:
  static const char* deviceClassTypeMap_[];
  xmlDocPtr doc_;
  bool initialized_;
};

#endif  // FSMDA_PARING_DEVICE_CLASS_DESCRIPTION_H_