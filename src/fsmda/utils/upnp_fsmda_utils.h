#ifndef UPNP_FSMDA_UTILS_H
#define UPNP_FSMDA_UTILS_H

/*----------------------------------------------------------------------
 |   include
 +---------------------------------------------------------------------*/

#include "PltUPnP.h"

using namespace std;

/*----------------------------------------------------------------------
 |   UpnpFsmdaUtils class
 +---------------------------------------------------------------------*/
class UpnpFsmdaUtils {
 public:
  // class fields
  static const char* kPpmDeviceType;
  static const char* kPpmDeviceFriendlyName;
  static const char* kPpmDeviceModelDescription;
  static const char* kPpmDeviceModelUrl;
  static const char* kPpmDeviceNumber;
  static const char* kPpmDeviceModelName;
  static const char* kPpmServiceType;
  static const char* kPpmServiceId;
  static const char* kPpmServiceName;
  static const char* kPpmServiceScpdXml;
  static const char* kCpmDeviceType;
  static const char* kCpmDeviceFriendlyName;
  static const char* kCpmDeviceModelDescription;
  static const char* kCpmDeviceModelUrl;
  static const char* kCpmDeviceModelNumber;
  static const char* kCpmDeviceModelName;
  static const char* kCpmServiceType;
  static const char* kCpmServiceId;
  static const char* kCpmServiceName;
  static const char* kCpmServiceScpdXml;

  static const char* kFsmdaManufacturer;
  static const char* kFsmdaManufacturerUrl;

  static const char* kOnDemandCcmDeviceFriendlyName;
  static const char* kOnDemandCcmDeviceModelDescription;
  static const char* kOnDemandCcmDeviceModelUrl;
  static const char* kOnDemandCcmDeviceModelNumber;
  static const char* kOnDemandCcmDeviceModelName;

  // class methods
  static PLT_UPnP*
  requestUpnpReference();
  static void
  releaseUpnpReference();
  static unsigned int references_count_;

 private:
  // private constructors & destructors
  UpnpFsmdaUtils() {
  }
  ~UpnpFsmdaUtils() {
  }

  // private class fields
  static PLT_UPnP * upnp_singleton_;
  static bool upnp_running_;
};

#endif /* UPNP_FSMDA_UTILS_H */
