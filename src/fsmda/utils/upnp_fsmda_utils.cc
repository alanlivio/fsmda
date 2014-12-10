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
unsigned int UpnpFsmdaUtils::upnp_references_count_ = 0;

// PPM UPNP constant strings
const char* UpnpFsmdaUtils::kPpmDeviceType =
    "urn:schemas-upnp-org:device:fsmda-parent-paring-device:1";
const char* UpnpFsmdaUtils::kPpmDeviceFriendlyName =
    "fsmda parent paring device friendly name";
const char* UpnpFsmdaUtils::kPpmDeviceModelName =
    "fsmda-parent-paring-device model name";
const char* UpnpFsmdaUtils::kPpmDeviceModelDescription =
    "fsmda parent paring model description";
const char* UpnpFsmdaUtils::kPpmDeviceModelUrl =
    "http://www.ncl.org.br/fsmda/fsmda-parent-paring-device";
const char* UpnpFsmdaUtils::kPpmDeviceNumber = "1.0";
const char* UpnpFsmdaUtils::kPpmServiceType =
    "urn:schemas-upnp-org:service:fsmda-parent-paring-service:1";
const char* UpnpFsmdaUtils::kPpmServiceId =
    "urn:upnp-org:serviceId:parent-paring-service001";
const char* UpnpFsmdaUtils::kPpmServiceName =
    "urn:upnp-org:serviceId:parent-paring-service001-name";
const char* UpnpFsmdaUtils::kPpmServiceScpdXml =
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
    "           "
    "<relatedStateVariable>A_ARG_TYPE_applicationId</relatedStateVariable>"
    "         </argument>"
    "         <argument>"
    "           <name>deviceAddr</name>"
    "           <direction>in</direction>"
    "           "
    "<relatedStateVariable>A_ARG_TYPE_deviceAddr</relatedStateVariable>"
    "         </argument>"
    "         <argument>"
    "           <name>classIndex</name>"
    "           <direction>in</direction>"
    "           "
    "<relatedStateVariable>A_ARG_TYPE_classIndex</relatedStateVariable>"
    "         </argument>"
    "         <argument>"
    "           <name>deviceDesc</name>"
    "           <direction>in</direction>"
    "           "
    "<relatedStateVariable>A_ARG_TYPE_deviceDesc</relatedStateVariable>"
    "         </argument>"
    "       </argumentList>"
    "     </action>"
    "     <action>"
    "       <name>getChildIndex</name>"
    "       <argumentList>"
    "         <argument>"
    "           <name>applicationId</name>"
    "           <direction>in</direction>"
    "           "
    "<relatedStateVariable>A_ARG_TYPE_applicationId</relatedStateVariable>"
    "         </argument>"
    "         <argument>"
    "           <name>deviceAddr</name>"
    "           <direction>in</direction>"
    "           "
    "<relatedStateVariable>A_ARG_TYPE_deviceAddr</relatedStateVariable>"
    "         </argument>"
    "         <argument>"
    "           <name>classIndex</name>"
    "           <direction>in</direction>"
    "           "
    "<relatedStateVariable>A_ARG_TYPE_classIndex</relatedStateVariable>"
    "         </argument>"
    "         <argument>"
    "           <name>ret</name>"
    "           <retval />"
    "           <direction>out</direction>"
    "           "
    "<relatedStateVariable>A_ARG_TYPE_classIndex</relatedStateVariable>"
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
    "   <intel_nmpr:X_INTEL_NMPR "
    "xmlns:intel_nmpr=\"udn:schemas-intel-com:device-1-0\">2.1</"
    "intel_nmpr:X_INTEL_NMPR>"
    "   <dlna:X_DLNADOC xmlns:dlna=\"udn:schemas-dlna-org:device-1-0\">DMP "
    "1.00</dlna:X_DLNADOC>"
    "  </scpd>";

// CPM UPNP constant strings
const char* UpnpFsmdaUtils::kCpmDeviceType =
    "urn:schemas-upnp-org:device:smda-child-paring-device:1";
const char* UpnpFsmdaUtils::kCpmDeviceFriendlyName =
    "fsmda child paring device friendly name";
const char* UpnpFsmdaUtils::kCpmDeviceModelName =
    "fsmda-child-paring-device model name";
const char* UpnpFsmdaUtils::kCpmDeviceModelDescription =
    "fsmda child paring model description";
const char* UpnpFsmdaUtils::kCpmDeviceModelUrl =
    "http://www.ncl.org.br/fsmda/ondemand";
const char* UpnpFsmdaUtils::kCpmDeviceModelNumber = "1.0";
const char* UpnpFsmdaUtils::kCpmServiceType =
    "urn:schemas-upnp-org:service:fsmda-child-paring-service:1";
const char* UpnpFsmdaUtils::kCpmServiceId =
    "urn:upnp-org:serviceId:child-paring-service001";
const char* UpnpFsmdaUtils::kCpmServiceName =
    "urn:upnp-org:serviceId:child-paring-service001-name";
const char* UpnpFsmdaUtils::kCpmServiceScpdXml =
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
    "           "
    "<relatedStateVariable>A_ARG_TYPE_applicationId</relatedStateVariable>"
    "         </argument>"
    "         <argument>"
    "           <name>classIndex</name>"
    "           <direction>in</direction>"
    "           "
    "<relatedStateVariable>A_ARG_TYPE_classIndex</relatedStateVariable>"
    "         </argument>"
    "         <argument>"
    "           <name>classDesc</name>"
    "           <direction>in</direction>"
    "           "
    "<relatedStateVariable>A_ARG_TYPE_classDesc</relatedStateVariable>"
    "         </argument>"
    "         <argument>"
    "           <name>classFunction</name>"
    "           <direction>in</direction>"
    "           "
    "<relatedStateVariable>A_ARG_TYPE_classFunction</relatedStateVariable>"
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
    "   <intel_nmpr:X_INTEL_NMPR "
    "xmlns:intel_nmpr=\"udn:schemas-intel-com:device-1-0\">2.1</"
    "intel_nmpr:X_INTEL_NMPR>"
    "   <dlna:X_DLNADOC xmlns:dlna=\"udn:schemas-dlna-org:device-1-0\">DMP "
    "1.00</dlna:X_DLNADOC>"
    "  </scpd>";

// UPNP UpnpOnDemandCcm constant strings
const char* UpnpFsmdaUtils::kOnDemandCcmDeviceModelName =
    "fsmda-ondemand-device";
const char* UpnpFsmdaUtils::kOnDemandCcmDeviceFriendlyName =
    "FSMDA OndDemand device";
const char* UpnpFsmdaUtils::kOnDemandCcmDeviceModelDescription =
    "FSMDA OndDemand device description";
const char* UpnpFsmdaUtils::kOnDemandCcmDeviceModelUrl =
    "http://www.ncl.org.br/fsmda/ondemand";
const char* UpnpFsmdaUtils::kOnDemandCcmDeviceModelNumber = "1.0";

// UPNP FSMDA Manufacturer constant strings
const char* UpnpFsmdaUtils::kFsmdaManufacturer = "FSMDA";
const char* UpnpFsmdaUtils::kFsmdaManufacturerUrl =
    "http://www.ncl.org.br/fsmda/ondemand";

/*----------------------------------------------------------------------
 |   UpnpUtils::GenerateGUID
 +---------------------------------------------------------------------*/
void UpnpFsmdaUtils::GenerateGUID(std::string& guid) {
  NPT_String guid_aux;
  PLT_UPnPMessageHelper::GenerateGUID(guid_aux);
  guid.assign(guid_aux.GetChars());
}

/*----------------------------------------------------------------------
 |   UpnpUtils::RequestUpnpReference
 +---------------------------------------------------------------------*/
PLT_UPnP* UpnpFsmdaUtils::GetRunningUpnpInstance() {
  if (UpnpFsmdaUtils::upnp_singleton_ == NULL) {
    // setup Neptune logging
    NPT_LogManager::GetDefault().Configure(
        "plist:.level=FINE;.handlers=ConsoleHandler;.ConsoleHandler.colors=off;"
        ".ConsoleHandler.filter=42");

    // setup upnp service
    PLT_Constants::GetInstance().SetDefaultDeviceLease(NPT_TimeInterval(60.));
    NPT_List<NPT_IpAddress> list;
    PLT_UPnPMessageHelper::GetIPAddresses(list);
    UpnpFsmdaUtils::upnp_singleton_ = new PLT_UPnP();
    UpnpFsmdaUtils::upnp_singleton_->SetIgnoreLocalUUIDs(false);
    UpnpFsmdaUtils::upnp_singleton_->Start();
    UpnpFsmdaUtils::upnp_references_count_ = 0;
  }
  UpnpFsmdaUtils::upnp_references_count_++;
  return UpnpFsmdaUtils::upnp_singleton_;
}

/*----------------------------------------------------------------------
 |   UpnpUtils::ReleaseUpnpReference
 +---------------------------------------------------------------------*/
void UpnpFsmdaUtils::ReleaseUpnpInstance() {
  if (UpnpFsmdaUtils::upnp_references_count_ == 0) {
    return;
  } else if (UpnpFsmdaUtils::upnp_references_count_ == 1) {
    UpnpFsmdaUtils::upnp_singleton_->Stop();
    delete upnp_singleton_;
    UpnpFsmdaUtils::upnp_singleton_ = NULL;
    UpnpFsmdaUtils::upnp_references_count_ = 0;
  } else {
    UpnpFsmdaUtils::upnp_references_count_--;
  }
}

/*----------------------------------------------------------------------
 |   UpnpUtils::IsUpnpRunning
 +---------------------------------------------------------------------*/
bool UpnpFsmdaUtils::IsUpnpRunning() {
  if (UpnpFsmdaUtils::upnp_singleton_ == NULL) {
    return false;
  } else {
    UpnpFsmdaUtils::upnp_singleton_->IsRunning();
  }
}
