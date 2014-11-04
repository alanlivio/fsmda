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
class UpnpFsmdaUtils
{
public:
  // class fields and methods
  static const char* UPNP_FSMDA_PPM_DEVICE_TYPE;
  static const char* UPNP_FSMDA_PPM_MODEL_DESCRIPTION;
  static const char* UPNP_FSMDA_PPM_MODEL_URL;
  static const char* UPNP_FSMDA_PPM_MODEL_NUMBER;
  static const char* UPNP_FSMDA_PPM_MODEL_NAME;
  static const char* UPNP_FSMDA_CPM_DEVICE_TYPE;
  static const char* UPNP_FSMDA_CPM_FRIENDLY_NAME;
  static const char* UPNP_FSMDA_CPM_MODEL_DESCRIPTION;
  static const char* UPNP_FSMDA_CPM_MODEL_URL;
  static const char* UPNP_FSMDA_CPM_MODEL_NUMBER;
  static const char* UPNP_FSMDA_CPM_MODEL_NAME;
  static const char* UPNP_FSMDA_PPM_FRIENDLY_NAME;
  static const char* UPNP_FSMDA_MANUFACTURER;
  static const char* UPNP_FSMDA_MANUFACTURER_URL;
  static const char* PARENT_PARING_MANAGER_SCPDXML;
  static const char* CHILD_PARING_MANAGER_SCPDXML;
  static PLT_UPnP*
  requestUpnpReference ();
  static void
  releaseUpnpReference ();

private:
  // private constructors & destructors
  UpnpFsmdaUtils (){}
  ~UpnpFsmdaUtils (){}

  // private fields
  static PLT_UPnP * upnp_singleton_;
  static bool upnp_running_;
  static unsigned int references_count_;
};

#endif /* UPNP_FSMDA_UTILS_H */
