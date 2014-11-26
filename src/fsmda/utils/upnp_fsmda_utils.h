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
  static const char* UPNP_FSMDA_PPM_DEVICE_TYPE;
  static const char* UPNP_FSMDA_PPM_DEVICE_FRIENDLY_NAME;
  static const char* UPNP_FSMDA_PPM_DEVICE_MODEL_DESCRIPTION;
  static const char* UPNP_FSMDA_PPM_DEVICE_MODEL_URL;
  static const char* UPNP_FSMDA_PPM_DEVICE_MODEL_NUMBER;
  static const char* UPNP_FSMDA_PPM_DEVICE_MODEL_NAME;
  static const char* UPNP_FSMDA_PPM_SERVICE_TYPE;
  static const char* UPNP_FSMDA_PPM_SERVICE_ID;
  static const char* UPNP_FSMDA_PPM_SERVICE_NAME;
  static const char* UPNP_FSMDA_PPM_SERVICE_SCPDXML;
  static const char* UPNP_FSMDA_CPM_DEVICE_TYPE;
  static const char* UPNP_FSMDA_CPM_DEVICE_FRIENDLY_NAME;
  static const char* UPNP_FSMDA_CPM_DEVICE_MODEL_DESCRIPTION;
  static const char* UPNP_FSMDA_CPM_DEVICE_MODEL_URL;
  static const char* UPNP_FSMDA_CPM_DEVICE_MODEL_NUMBER;
  static const char* UPNP_FSMDA_CPM_DEVICE_MODEL_NAME;
  static const char* UPNP_FSMDA_CPM_SERVICE_TYPE;
  static const char* UPNP_FSMDA_CPM_SERVICE_ID;
  static const char* UPNP_FSMDA_CPM_SERVICE_NAME;
  static const char* UPNP_FSMDA_CPM_SERVICE_SCPDXML;
  static const char* UPNP_FSMDA_MANUFACTURER;
  static const char* UPNP_FSMDA_MANUFACTURER_URL;

  // class methods
  static PLT_UPnP*
  requestUpnpReference();
  static void
  releaseUpnpReference();
  static const unsigned int
  get_references_count();
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
