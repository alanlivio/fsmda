#ifndef FSMDA_UPNP_UPNP_FSMDA_UTILS_H_
#define FSMDA_UPNP_UPNP_FSMDA_UTILS_H_

#include <string>
#include <NptList.h>
#include <NptLogging.h>
#include <PltUPnP.h>

using std::string;


class UpnpFsmdaUtils {
 public:
  // public class fields: fsmda manufacturer upnp strings
  static const char* kFsmdaManufacturer;
  static const char* kFsmdaManufacturerUrl;

  // public class fields: parent device upnp strings
  static const char* kParentDeviceType;
  static const char* kParentDeviceFriendlyName;
  static const char* kParentDeviceModelDescription;
  static const char* kParentDeviceModelUrl;
  static const char* kParentDeviceNumber;
  static const char* kParentDeviceModelName;

  // public class fields: child device upnp strings
  static const char* kChildDeviceType;
  static const char* kChildDeviceFriendlyName;
  static const char* kChildDeviceModelDescription;
  static const char* kChildDeviceModelUrl;
  static const char* kChildDeviceModelNumber;
  static const char* kChildDeviceModelName;

  // public class fields: ppm upnp strings
  static const char* kPpmServiceType;
  static const char* kPpmServiceId;
  static const char* kPpmServiceName;
  static const char* kPpmServiceScpdXml;

  // public class fields: ppm upnp strings
  static const char* kCpmServiceType;
  static const char* kCpmServiceId;
  static const char* kCpmServiceName;
  static const char* kCpmServiceScpdXml;

  // public class fields: passive pcm upnp strings
  static const char* kPassivePcmServiceType;
  static const char* kPassivePcmServiceId;
  static const char* kPassivePcmServiceName;
  static const char* kPassivePcmServiceScpdXml;

  // public class fields: active pcm upnp strings
  static const char* kActivePcmServiceType;
  static const char* kActivePcmServiceId;
  static const char* kActivePcmServiceName;
  static const char* kActivePcmServiceScpdXml;

  // public class fields: active ccm upnp strings
  static const char* kActiveCcmServiceType;
  static const char* kActiveCcmServiceId;
  static const char* kActiveCcmServiceName;
  static const char* kActiveCcmServiceScpdXml;

  // public class fields: passive ccm upnp strings
  static const char* kPassiveCcmServiceType;
  static const char* kPassiveCcmServiceId;
  static const char* kPassiveCcmServiceName;
  static const char* kPassiveCcmServiceScpdXml;

  // public class fields: medicapture ccm upnp strings
  static const char* kMediaCapturePcmServiceType;
  static const char* kMediaCapturePcmServiceId;
  static const char* kMediaCapturePcmServiceName;
  static const char* kMediaCapturePcmServiceScpdXml;

  // public class fields: medicapture ccm upnp strings
  static const char* kMediaCaptureCcmServiceType;
  static const char* kMediaCaptureCcmServiceId;
  static const char* kMediaCaptureCcmServiceName;
  static const char* kMediaCaptureCcmServiceScpdXml;

  // public class fields: ondemand pcm upnp strings
  static const char* kOnDemandPcmServiceType;
  static const char* kOnDemandPcmServiceId;
  static const char* kOnDemandPcmServiceName;
  static const char* kOnDemandPcmServiceScpdXml;

  // public class fields: ondemand ccm upnp strings
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

#endif  // FSMDA_UPNP_UPNP_FSMDA_UTILS_H_
