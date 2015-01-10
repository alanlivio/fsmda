#ifndef FSMDA_UTILS_UPNP_FSMDA_UTILS_H_
#define FSMDA_UTILS_UPNP_FSMDA_UTILS_H_

/*----------------------------------------------------------------------
 |   include
 +---------------------------------------------------------------------*/

#include <string>
#include <NptList.h>
#include <NptLogging.h>
#include <PltUPnP.h>

using std::string;

/*----------------------------------------------------------------------
 |   UpnpFsmdaUtils class
 +---------------------------------------------------------------------*/
class UpnpFsmdaUtils {
 public:
  // public class fields: fsmda manufacturer upnp strings
  static const char* kFsmdaManufacturer;
  static const char* kFsmdaManufacturerUrl;

  // public class fields: ppm upnp strings
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

  // public class fields: ppm upnp strings
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

  // public class fields: active pcm upnp strings
  static const char* kActivePcmDeviceType;
  static const char* kActivePcmDeviceFriendlyName;
  static const char* kActivePcmDeviceModelDescription;
  static const char* kActivePcmDeviceModelUrl;
  static const char* kActivePcmDeviceModelNumber;
  static const char* kActivePcmDeviceModelName;
  static const char* kActivePcmServiceType;
  static const char* kActivePcmServiceId;
  static const char* kActivePcmServiceName;
  static const char* kActivePcmServiceScpdXml;

  // public class fields: active ccm upnp strings
  static const char* kActiveCcmDeviceType;
  static const char* kActiveCcmDeviceFriendlyName;
  static const char* kActiveCcmDeviceModelDescription;
  static const char* kActiveCcmDeviceModelUrl;
  static const char* kActiveCcmDeviceModelNumber;
  static const char* kActiveCcmDeviceModelName;
  static const char* kActiveCcmServiceType;
  static const char* kActiveCcmServiceId;
  static const char* kActiveCcmServiceName;
  static const char* kActiveCcmServiceScpdXml;

  // public class fields: passive pcm upnp strings
  static const char* kPassivePcmDeviceType;
  static const char* kPassivePcmDeviceFriendlyName;
  static const char* kPassivePcmDeviceModelName;
  static const char* kPassivePcmDeviceModelDescription;
  static const char* kPassivePcmDeviceModelUrl;
  static const char* kPassivePcmDeviceModelNumber;
  static const char* kPassivePcmServiceType;
  static const char* kPassivePcmServiceId;
  static const char* kPassivePcmServiceName;
  static const char* kPassivePcmServiceScpdXml;

  // public class fields: passive ccm upnp strings
  static const char* kPassiveCcmDeviceType;
  static const char* kPassiveCcmDeviceFriendlyName;
  static const char* kPassiveCcmDeviceModelName;
  static const char* kPassiveCcmDeviceModelDescription;
  static const char* kPassiveCcmDeviceModelUrl;
  static const char* kPassiveCcmDeviceModelNumber;
  static const char* kPassiveCcmServiceType;
  static const char* kPassiveCcmServiceId;
  static const char* kPassiveCcmServiceName;
  static const char* kPassiveCcmServiceScpdXml;

  // public class fields: medicapture ccm upnp strings
  static const char* kMediaCapturePcmDeviceType;
  static const char* kMediaCapturePcmDeviceFriendlyName;
  static const char* kMediaCapturePcmDeviceModelName;
  static const char* kMediaCapturePcmDeviceModelDescription;
  static const char* kMediaCapturePcmDeviceModelUrl;
  static const char* kMediaCapturePcmDeviceModelNumber;
  static const char* kMediaCapturePcmServiceType;
  static const char* kMediaCapturePcmServiceId;
  static const char* kMediaCapturePcmServiceName;
  static const char* kMediaCapturePcmServiceScpdXml;

  // public class fields: medicapture ccm upnp strings
  static const char* kMediaCaptureCcmDeviceType;
  static const char* kMediaCaptureCcmDeviceFriendlyName;
  static const char* kMediaCaptureCcmDeviceModelName;
  static const char* kMediaCaptureCcmDeviceModelDescription;
  static const char* kMediaCaptureCcmDeviceModelUrl;
  static const char* kMediaCaptureCcmDeviceModelNumber;
  static const char* kMediaCaptureCcmServiceType;
  static const char* kMediaCaptureCcmServiceId;
  static const char* kMediaCaptureCcmServiceName;
  static const char* kMediaCaptureCcmServiceScpdXml;

  // public class fields: ondemand pcm upnp strings
  static const char* kOnDemandPcmDeviceType;
  static const char* kOnDemandPcmDeviceFriendlyName;
  static const char* kOnDemandPcmDeviceModelName;
  static const char* kOnDemandPcmDeviceModelDescription;
  static const char* kOnDemandPcmDeviceModelUrl;
  static const char* kOnDemandPcmDeviceModelNumber;
  static const char* kOnDemandPcmServiceType;
  static const char* kOnDemandPcmServiceId;
  static const char* kOnDemandPcmServiceName;
  static const char* kOnDemandPcmServiceScpdXml;

  // public class fields: ondemand ccm upnp strings
  static const char* kOnDemandCcmDeviceType;
  static const char* kOnDemandCcmDeviceFriendlyName;
  static const char* kOnDemandCcmDeviceModelName;
  static const char* kOnDemandCcmDeviceModelDescription;
  static const char* kOnDemandCcmDeviceModelUrl;
  static const char* kOnDemandCcmDeviceModelNumber;
  static const char* kOnDemandCcmServiceType;
  static const char* kOnDemandCcmServiceId;
  static const char* kOnDemandCcmServiceName;
  static const char* kOnDemandCcmServiceScpdXml;

  // public class methods
  static void GenerateGUID(string* guid);
  static PLT_UPnP* GetRunningInstance();
  static void ReleaseInstance();
  static bool IsUpnpStarted();
  static unsigned int upnp_references_count() {
    return UpnpFsmdaUtils::upnp_references_count_;
  }

 private:
  // private constructors & destructors
  UpnpFsmdaUtils() {}
  ~UpnpFsmdaUtils() {}

  // private class fields
  static PLT_UPnP* upnp_singleton_;
  static unsigned int upnp_references_count_;
};

#endif  // FSMDA_UTILS_UPNP_FSMDA_UTILS_H_
