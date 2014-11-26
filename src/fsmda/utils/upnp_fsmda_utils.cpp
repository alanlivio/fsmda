/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include "fsmda/utils/upnp_fsmda_utils.h"
#include "NptList.h"
#include "NptLogging.h"
#include "NptNetwork.h"
#include "NptTime.h"
#include "PltConstants.h"
#include "PltUPnP.h"
#include "PltUtilities.h"
#include <string>

/*----------------------------------------------------------------------
 |   class fields
 +---------------------------------------------------------------------*/
// singleton fields
PLT_UPnP* UpnpFsmdaUtils::upnp_singleton_ = NULL;
unsigned int UpnpFsmdaUtils::references_count_ = 0;
bool UpnpFsmdaUtils::upnp_running_ = false;

//PPM UPNP constant strings
const char* UpnpFsmdaUtils::UPNP_FSMDA_PPM_DEVICE_TYPE =
    "urn:schemas-upnp-org:device:fsmda-parent-paring-device:1";
const char* UpnpFsmdaUtils::UPNP_FSMDA_PPM_DEVICE_FRIENDLY_NAME =
    "fsmda parent paring device friendly name";
const char* UpnpFsmdaUtils::UPNP_FSMDA_PPM_DEVICE_MODEL_NAME =
    "fsmda-parent-paring-device model name";
const char* UpnpFsmdaUtils::UPNP_FSMDA_PPM_DEVICE_MODEL_DESCRIPTION =
    "fsmda parent paring model description";
const char* UpnpFsmdaUtils::UPNP_FSMDA_PPM_DEVICE_MODEL_URL =
    "http://www.ncl.org.br/fsmda/fsmda-parent-paring-device";
const char* UpnpFsmdaUtils::UPNP_FSMDA_PPM_DEVICE_MODEL_NUMBER = "1.0";
const char* UpnpFsmdaUtils::UPNP_FSMDA_PPM_SERVICE_TYPE =
    "urn:schemas-upnp-org:service:fsmda-parent-paring-service:1";
const char* UpnpFsmdaUtils::UPNP_FSMDA_PPM_SERVICE_ID =
    "urn:upnp-org:serviceId:parent-paring-service001";
const char* UpnpFsmdaUtils::UPNP_FSMDA_PPM_SERVICE_NAME =
    "urn:upnp-org:serviceId:parent-paring-service001-name";
const char* UpnpFsmdaUtils::UPNP_FSMDA_PPM_SERVICE_SCPDXML =
    "<?xml version=\"1.0\" ?>"
        "<scpd xmlns=\"urn:schemas-upnp-org:service-1-0\">"
        "   <specVersion>"
        "     <major>1</major>"
        "     <minor>0</minor>"
        "   </specVersion>"
        "   <actionList>"
        "     <action>"
        "       <name>addDeviceToClass</name>"
        "       <argumentList>"
        "         <argument>"
        "           <name>applicationId</name>"
        "           <direction>in</direction>"
        "           <relatedStateVariable>A_ARG_TYPE_applicationId</relatedStateVariable>"
        "         </argument>"
        "         <argument>"
        "           <name>deviceAddr</name>"
        "           <direction>in</direction>"
        "           <relatedStateVariable>A_ARG_TYPE_deviceAddr</relatedStateVariable>"
        "         </argument>"
        "         <argument>"
        "           <name>classIndex</name>"
        "           <direction>in</direction>"
        "           <relatedStateVariable>A_ARG_TYPE_classIndex</relatedStateVariable>"
        "         </argument>"
        "         <argument>"
        "           <name>deviceDesc</name>"
        "           <direction>in</direction>"
        "           <relatedStateVariable>A_ARG_TYPE_deviceDesc</relatedStateVariable>"
        "         </argument>"
        "       </argumentList>"
        "     </action>"
        "     <action>"
        "       <name>getChildIndex</name>"
        "       <argumentList>"
        "         <argument>"
        "           <name>applicationId</name>"
        "           <direction>in</direction>"
        "           <relatedStateVariable>A_ARG_TYPE_applicationId</relatedStateVariable>"
        "         </argument>"
        "         <argument>"
        "           <name>deviceAddr</name>"
        "           <direction>in</direction>"
        "           <relatedStateVariable>A_ARG_TYPE_deviceAddr</relatedStateVariable>"
        "         </argument>"
        "         <argument>"
        "           <name>classIndex</name>"
        "           <direction>in</direction>"
        "           <relatedStateVariable>A_ARG_TYPE_classIndex</relatedStateVariable>"
        "         </argument>"
        "         <argument>"
        "           <name>ret</name>"
        "           <retval />"
        "           <direction>out</direction>"
        "           <relatedStateVariable>A_ARG_TYPE_classIndex</relatedStateVariable>"
        "         </argument>"
        "       </argumentList>"
        "     </action>"
        "   </actionList>"
        "   <serviceStateTable>"
        "     <stateVariable sendEvents=\"no\">"
        "       <name>A_ARG_TYPE_applicationId</name>"
        "       <dataType>string</dataType>"
        "       <defaultValue></defaultValue>"
        "     </stateVariable>"
        "     <stateVariable sendEvents=\"no\">"
        "       <name>A_ARG_TYPE_deviceAddr</name>"
        "       <dataType>string</dataType>"
        "       <defaultValue></defaultValue>"
        "     </stateVariable>"
        "     <stateVariable sendEvents=\"no\">"
        "       <name>A_ARG_TYPE_classIndex</name>"
        "       <dataType>ui1</dataType>"
        "       <defaultValue>0</defaultValue>"
        "       <allowedValueRange>"
        "         <minimum>0</minimum>"
        "         <maximum>100</maximum>"
        "       </allowedValueRange>"
        "     </stateVariable>"
        "     <stateVariable sendEvents=\"no\">"
        "         <name>A_ARG_TYPE_deviceDesc</name>"
        "         <dataType>string</dataType>"
        "         <defaultValue></defaultValue>"
        "     </stateVariable>"
        "   </serviceStateTable>"
        "   <intel_nmpr:X_INTEL_NMPR xmlns:intel_nmpr=\"udn:schemas-intel-com:device-1-0\">2.1</intel_nmpr:X_INTEL_NMPR>"
        "   <dlna:X_DLNADOC xmlns:dlna=\"udn:schemas-dlna-org:device-1-0\">DMP 1.00</dlna:X_DLNADOC>"
        "  </scpd>";

//CPM UPNP constant strings
const char* UpnpFsmdaUtils::UPNP_FSMDA_CPM_DEVICE_TYPE =
    "urn:schemas-upnp-org:device:smda-child-paring-device:1";
const char* UpnpFsmdaUtils::UPNP_FSMDA_CPM_DEVICE_FRIENDLY_NAME =
    "fsmda child paring device  friendly name";
const char* UpnpFsmdaUtils::UPNP_FSMDA_CPM_DEVICE_MODEL_NAME =
    "fsmda-child-paring-device model name";
const char* UpnpFsmdaUtils::UPNP_FSMDA_CPM_DEVICE_MODEL_DESCRIPTION =
    "fsmda child paring model description";
const char* UpnpFsmdaUtils::UPNP_FSMDA_CPM_DEVICE_MODEL_URL =
    "http://www.ncl.org.br/fsmda/ondemand";
const char* UpnpFsmdaUtils::UPNP_FSMDA_CPM_DEVICE_MODEL_NUMBER = "1.0";
const char* UpnpFsmdaUtils::UPNP_FSMDA_CPM_SERVICE_TYPE =
    "urn:schemas-upnp-org:service:fsmda-child-paring-service:1";
const char* UpnpFsmdaUtils::UPNP_FSMDA_CPM_SERVICE_ID =
    "urn:upnp-org:serviceId:child-paring-service001";
const char* UpnpFsmdaUtils::UPNP_FSMDA_CPM_SERVICE_NAME =
    "urn:upnp-org:serviceId:child-paring-service001-name";
const char* UpnpFsmdaUtils::UPNP_FSMDA_CPM_SERVICE_SCPDXML =
    "<?xml version=\"1.0\" ?>"
        "<scpd xmlns=\"urn:schemas-upnp-org:service-1-0\">"
        "   <specVersion>"
        "     <major>1</major>"
        "     <minor>0</minor>"
        "   </specVersion>"
        "   <actionList>"
        "     <action>"
        "       <name>classAnnouncement</name>"
        "       <argumentList>"
        "         <argument>"
        "           <name>applicationId</name>"
        "           <direction>in</direction>"
        "           <relatedStateVariable>A_ARG_TYPE_applicationId</relatedStateVariable>"
        "         </argument>"
        "         <argument>"
        "           <name>classIndex</name>"
        "           <direction>in</direction>"
        "           <relatedStateVariable>A_ARG_TYPE_classIndex</relatedStateVariable>"
        "         </argument>"
        "         <argument>"
        "           <name>classDesc</name>"
        "           <direction>in</direction>"
        "           <relatedStateVariable>A_ARG_TYPE_classDesc</relatedStateVariable>"
        "         </argument>"
        "         <argument>"
        "           <name>classFunction</name>"
        "           <direction>in</direction>"
        "           <relatedStateVariable>A_ARG_TYPE_classFunction</relatedStateVariable>"
        "         </argument>"
        "       </argumentList>"
        "     </action>"
        "   </actionList>"
        "   <serviceStateTable>"
        "     <stateVariable sendEvents=\"no\">"
        "       <name>A_ARG_TYPE_applicationId</name>"
        "       <dataType>string</dataType>"
        "       <defaultValue></defaultValue>"
        "     </stateVariable>"
        "     <stateVariable sendEvents=\"no\">"
        "       <name>A_ARG_TYPE_classIndex</name>"
        "       <dataType>ui1</dataType>"
        "       <defaultValue>0</defaultValue>"
        "       <allowedValueRange>"
        "         <minimum>0</minimum>"
        "         <maximum>100</maximum>"
        "       </allowedValueRange>"
        "     </stateVariable>"
        "     <stateVariable sendEvents=\"no\">"
        "         <name>A_ARG_TYPE_classDesc</name>"
        "         <dataType>string</dataType>"
        "         <defaultValue></defaultValue>"
        "     </stateVariable>"
        "     <stateVariable sendEvents=\"no\">"
        "         <name>A_ARG_TYPE_classFunction</name>"
        "         <dataType>string</dataType>"
        "         <defaultValue></defaultValue>"
        "     </stateVariable>"
        "   </serviceStateTable>"
        "   <intel_nmpr:X_INTEL_NMPR xmlns:intel_nmpr=\"udn:schemas-intel-com:device-1-0\">2.1</intel_nmpr:X_INTEL_NMPR>"
        "   <dlna:X_DLNADOC xmlns:dlna=\"udn:schemas-dlna-org:device-1-0\">DMP 1.00</dlna:X_DLNADOC>"
        "  </scpd>";

//UPNP FSMDA Manufacturer constant strings
const char* UpnpFsmdaUtils::UPNP_FSMDA_MANUFACTURER = "FSMDA";
const char* UpnpFsmdaUtils::UPNP_FSMDA_MANUFACTURER_URL =
    "http://www.ncl.org.br/fsmda/ondemand";

/*----------------------------------------------------------------------
 |   UpnpUtils::requestUpnpReference
 +---------------------------------------------------------------------*/
PLT_UPnP*
UpnpFsmdaUtils::requestUpnpReference() {
  if (UpnpFsmdaUtils::upnp_singleton_ == NULL) {
    // setup Neptune logging
    NPT_LogManager::GetDefault().Configure(
        "plist:.level=FINE;.handlers=ConsoleHandler;.ConsoleHandler.colors=off;.ConsoleHandler.filter=42");

    // setup upnp service
    PLT_Constants::GetInstance().SetDefaultDeviceLease(NPT_TimeInterval(60.));
    NPT_List<NPT_IpAddress> list;
    PLT_UPnPMessageHelper::GetIPAddresses(list);
    UpnpFsmdaUtils::upnp_singleton_ = new PLT_UPnP();
    UpnpFsmdaUtils::upnp_singleton_->Start();
    UpnpFsmdaUtils::references_count_ = 0;
    UpnpFsmdaUtils::upnp_running_ = true;
  }
  UpnpFsmdaUtils::references_count_++;
  return UpnpFsmdaUtils::upnp_singleton_;
}

/*----------------------------------------------------------------------
 |   UpnpUtils::releaseUpnpReference
 +---------------------------------------------------------------------*/
void UpnpFsmdaUtils::releaseUpnpReference() {
  if (UpnpFsmdaUtils::references_count_ == 0)
    return;
  else if (UpnpFsmdaUtils::references_count_ == 1) {
    UpnpFsmdaUtils::upnp_singleton_->Stop();
    delete upnp_singleton_;
    UpnpFsmdaUtils::upnp_singleton_ = NULL;
    UpnpFsmdaUtils::references_count_ = 0;
    UpnpFsmdaUtils::upnp_running_ = false;
  } else
    UpnpFsmdaUtils::references_count_--;
}

/*----------------------------------------------------------------------
 |   UpnpUtils::references_count
 +---------------------------------------------------------------------*/
const unsigned int UpnpFsmdaUtils::get_references_count() {
  return UpnpFsmdaUtils::references_count_;
}

