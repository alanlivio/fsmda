/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include "fsmda/utils/upnp_fsmda_utils.h"
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

// UPNP FSMDA Manufacturer constant strings
const char* UpnpFsmdaUtils::kFsmdaManufacturer = "FSMDA";
const char* UpnpFsmdaUtils::kFsmdaManufacturerUrl =
    "http://www.ncl.org.br/fsmda/ondemand";

// PPM UPNP constant strings
const char* UpnpFsmdaUtils::kPpmDeviceType =
    "urn:schemas-upnp-org:device:fsmda-parent-pairing-device:1";
const char* UpnpFsmdaUtils::kPpmDeviceFriendlyName =
    "fsmda parent pairing device friendly name";
const char* UpnpFsmdaUtils::kPpmDeviceModelName =
    "fsmda-parent-pairing-device model name";
const char* UpnpFsmdaUtils::kPpmDeviceModelDescription =
    "fsmda parent pairing model description";
const char* UpnpFsmdaUtils::kPpmDeviceModelUrl =
    "http://www.ncl.org.br/fsmda/fsmda-parent-pairing-device";
const char* UpnpFsmdaUtils::kPpmDeviceNumber = "1.0";
const char* UpnpFsmdaUtils::kPpmServiceType =
    "urn:schemas-upnp-org:service:fsmda-parent-pairing-service:1";
const char* UpnpFsmdaUtils::kPpmServiceId =
    "urn:upnp-org:serviceId:parent-pairing-service001";
const char* UpnpFsmdaUtils::kPpmServiceName =
    "urn:upnp-org:serviceId:parent-pairing-service001-name";
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
    "<relatedStateVariable>A_ARG_TYPE_applicationId</relatedStateVariable>"
    "         </argument>"
    "         <argument>"
    "           <name>deviceAddr</name>"
    "           <direction>in</direction>"
    "<relatedStateVariable>A_ARG_TYPE_deviceAddr</relatedStateVariable>"
    "         </argument>"
    "         <argument>"
    "           <name>classIndex</name>"
    "           <direction>in</direction>"
    "<relatedStateVariable>A_ARG_TYPE_classIndex</relatedStateVariable>"
    "         </argument>"
    "         <argument>"
    "           <name>deviceDesc</name>"
    "           <direction>in</direction>"
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
    "<relatedStateVariable>A_ARG_TYPE_applicationId</relatedStateVariable>"
    "         </argument>"
    "         <argument>"
    "           <name>deviceAddr</name>"
    "           <direction>in</direction>"
    "<relatedStateVariable>A_ARG_TYPE_deviceAddr</relatedStateVariable>"
    "         </argument>"
    "         <argument>"
    "           <name>classIndex</name>"
    "           <direction>in</direction>"
    "<relatedStateVariable>A_ARG_TYPE_classIndex</relatedStateVariable>"
    "         </argument>"
    "         <argument>"
    "           <name>ret</name>"
    "           <retval />"
    "           <direction>out</direction>"
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
    "urn:schemas-upnp-org:device:fsmda-child-pairing-device:1";
const char* UpnpFsmdaUtils::kCpmDeviceFriendlyName =
    "fsmda child pairing device friendly name";
const char* UpnpFsmdaUtils::kCpmDeviceModelName =
    "fsmda-child-pairing-device model name";
const char* UpnpFsmdaUtils::kCpmDeviceModelDescription =
    "fsmda child pairing model description";
const char* UpnpFsmdaUtils::kCpmDeviceModelUrl =
    "http://www.ncl.org.br/fsmda/ondemand";
const char* UpnpFsmdaUtils::kCpmDeviceModelNumber = "1.0";
const char* UpnpFsmdaUtils::kCpmServiceType =
    "urn:schemas-upnp-org:service:fsmda-child-pairing-service:1";
const char* UpnpFsmdaUtils::kCpmServiceId =
    "urn:upnp-org:serviceId:child-pairing-service001";
const char* UpnpFsmdaUtils::kCpmServiceName =
    "urn:upnp-org:serviceId:child-pairing-service001-name";
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
    "<relatedStateVariable>A_ARG_TYPE_applicationId</relatedStateVariable>"
    "         </argument>"
    "         <argument>"
    "           <name>classIndex</name>"
    "           <direction>in</direction>"
    "<relatedStateVariable>A_ARG_TYPE_classIndex</relatedStateVariable>"
    "         </argument>"
    "         <argument>"
    "           <name>classDesc</name>"
    "           <direction>in</direction>"
    "<relatedStateVariable>A_ARG_TYPE_classDesc</relatedStateVariable>"
    "         </argument>"
    "         <argument>"
    "           <name>classFunction</name>"
    "           <direction>in</direction>"
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

// active PCM UPNP constant strings
const char* UpnpFsmdaUtils::kActivePcmDeviceType =
    "urn:schemas-upnp-org:device:fsmda-active-parent-communication-device:1";
const char* UpnpFsmdaUtils::kActivePcmDeviceFriendlyName =
    "fsmda active parent communication device friendly name";
const char* UpnpFsmdaUtils::kActivePcmDeviceModelName =
    "fsmda-active-parent-communication-device model name";
const char* UpnpFsmdaUtils::kActivePcmDeviceModelDescription =
    "fsmda active parent communication model description";
const char* UpnpFsmdaUtils::kActivePcmDeviceModelUrl =
    "http://www.ncl.org.br/fsmda/active";
const char* UpnpFsmdaUtils::kActivePcmDeviceModelNumber = "1.0";
const char* UpnpFsmdaUtils::kActivePcmServiceType =
    "urn:schemas-upnp-org:service:fsmda-active-parent-communication-service:1";
const char* UpnpFsmdaUtils::kActivePcmServiceId =
    "urn:upnp-org:serviceId:child-pairing-service001";
const char* UpnpFsmdaUtils::kActivePcmServiceName =
    "urn:upnp-org:serviceId:child-pairing-service001-name";
const char* UpnpFsmdaUtils::kActivePcmServiceScpdXml =
    "<?xml version=\"1.0\" ?>"
    "<scpd xmlns=\"urn:schemas-upnp-org:service-1-0\">"
    "   <specVersion>"
    "     <major>1</major>"
    "     <minor>0</minor>"
    "   </specVersion>"
    "   <actionList>"
    "     <action>"
    "       <name>RequestPropertyValue</name>"
    "       <argumentList>"
    "         <argument>"
    "           <name>object_id</name>"
    "           <direction>in</direction>"
    "<relatedStateVariable>A_ARG_TYPE_object_id</relatedStateVariable>"
    "         </argument>"
    "         <argument>"
    "           <name>name</name>"
    "           <direction>in</direction>"
    "<relatedStateVariable>A_ARG_TYPE_property_name</relatedStateVariable>"
    "         </argument>"
    "       </argumentList>"
    "     </action>"
    "     <action>"
    "       <name>NotifyEventTransition</name>"
    "       <argumentList>"
    "         <argument>"
    "           <name>object_id</name>"
    "           <direction>in</direction>"
    "<relatedStateVariable>A_ARG_TYPE_object_id</relatedStateVariable>"
    "         </argument>"
    "         <argument>"
    "           <name>event_id</name>"
    "           <direction>in</direction>"
    "<relatedStateVariable>A_ARG_TYPE_event_id</relatedStateVariable>"
    "         </argument>"
    "           <name>transition</name>"
    "           <direction>in</direction>"
    "<relatedStateVariable>A_ARG_TYPE_transition</relatedStateVariable>"
    "         </argument>"
    "       </argumentList>"
    "     </action>"
    "     <action>"
    "       <name>NotifyError</name>"
    "       <argumentList>"
    "         <argument>"
    "           <name>object_id</name>"
    "           <direction>in</direction>"
    "<relatedStateVariable>A_ARG_TYPE_object_id</relatedStateVariable>"
    "         </argument>"
    "         <argument>"
    "           <name>message</name>"
    "           <direction>in</direction>"
    "<relatedStateVariable>A_ARG_TYPE_message</relatedStateVariable>"
    "         </argument>"
    "       </argumentList>"
    "     </action>"
    "   </actionList>"
    "   <serviceStateTable>"
    "     <stateVariable sendEvents=\"no\">"
    "       <name>A_ARG_TYPE_object_id</name>"
    "       <dataType>string</dataType>"
    "       <defaultValue></defaultValue>"
    "     </stateVariable>"
    "     <stateVariable sendEvents=\"no\">"
    "         <name>A_ARG_TYPE_property_name</name>"
    "         <dataType>string</dataType>"
    "         <defaultValue></defaultValue>"
    "     </stateVariable>"
    "     <stateVariable sendEvents=\"no\">"
    "         <name>A_ARG_TYPE_event_id</name>"
    "         <dataType>string</dataType>"
    "         <defaultValue></defaultValue>"
    "     </stateVariable>"
    "     <stateVariable sendEvents=\"no\">"
    "         <name>A_ARG_TYPE_transition</name>"
    "         <dataType>string</dataType>"
    "         <defaultValue></defaultValue>"
    "     </stateVariable>"
    "     <stateVariable sendEvents=\"no\">"
    "         <name>A_ARG_TYPE_message</name>"
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

// active Ccm Upnp constant strings
const char* UpnpFsmdaUtils::kActiveCcmDeviceType =
    "urn:schemas-upnp-org:device:fsmda-active-child-communication-device:1";
const char* UpnpFsmdaUtils::kActiveCcmDeviceFriendlyName =
    "fsmda active child communication device friendly name";
const char* UpnpFsmdaUtils::kActiveCcmDeviceModelName =
    "fsmda-active-child-communication-device model name";
const char* UpnpFsmdaUtils::kActiveCcmDeviceModelDescription =
    "fsmda active child communication model description";
const char* UpnpFsmdaUtils::kActiveCcmDeviceModelUrl =
    "http://www.ncl.org.br/fsmda/ondemand";
const char* UpnpFsmdaUtils::kActiveCcmDeviceModelNumber = "1.0";
const char* UpnpFsmdaUtils::kActiveCcmServiceType =
    "urn:schemas-upnp-org:service:fsmda-active-child-communication-service:1";
const char* UpnpFsmdaUtils::kActiveCcmServiceId =
    "urn:upnp-org:serviceId:fsmda-active-child-communication-service001";
const char* UpnpFsmdaUtils::kActiveCcmServiceName =
    "urn:upnp-org:serviceId:fsmda-active-child-communication-service001-name";
const char* UpnpFsmdaUtils::kActiveCcmServiceScpdXml =
    "<?xml version=\"1.0\" ?>"
    "<scpd xmlns=\"urn:schemas-upnp-org:service-1-0\">"
    "   <specVersion>"
    "     <major>1</major>"
    "     <minor>0</minor>"
    "   </specVersion>"
    "   <actionList>"
    "     <action>"
    "       <name>Prepare</name>"
    "       <argumentList>"
    "         <argument>"
    "           <name>object_id</name>"
    "           <direction>in</direction>"
    "<relatedStateVariable>A_ARG_TYPE_object_id</relatedStateVariable>"
    "         </argument>"
    "         <argument>"
    "           <name>object_src</name>"
    "           <direction>in</direction>"
    "<relatedStateVariable>A_ARG_TYPE_object_src</relatedStateVariable>"
    "         </argument>"
    "       </argumentList>"
    "         <argument>"
    "           <name>properties</name>"
    "           <direction>in</direction>"
    "<relatedStateVariable>A_ARG_TYPE_properties</relatedStateVariable>"
    "         </argument>"
    "         <argument>"
    "           <name>events</name>"
    "           <direction>in</direction>"
    "<relatedStateVariable>A_ARG_TYPE_events</relatedStateVariable>"
    "         </argument>"
    "       </argumentList>"
    "     </action>"
    "     <action>"
    "       <name>AddEvent</name>"
    "       <argumentList>"
    "         <argument>"
    "           <name>object_id</name>"
    "           <direction>in</direction>"
    "<relatedStateVariable>A_ARG_TYPE_object_id</relatedStateVariable>"
    "         </argument>"
    "         <argument>"
    "           <name>evt</name>"
    "           <direction>in</direction>"
    "<relatedStateVariable>A_ARG_TYPE_evt</relatedStateVariable>"
    "         </argument>"
    "       </argumentList>"
    "     </action>"
    "   </actionList>"
    "   <serviceStateTable>"
    "     <stateVariable sendEvents=\"no\">"
    "       <name>A_ARG_TYPE_object_id</name>"
    "       <dataType>string</dataType>"
    "       <defaultValue></defaultValue>"
    "     </stateVariable>"
    "     <stateVariable sendEvents=\"no\">"
    "         <name>A_ARG_TYPE_object_src</name>"
    "         <dataType>string</dataType>"
    "         <defaultValue></defaultValue>"
    "     </stateVariable>"
    "     <stateVariable sendEvents=\"no\">"
    "         <name>A_ARG_TYPE_properties</name>"
    "         <dataType>string</dataType>"
    "         <defaultValue></defaultValue>"
    "     </stateVariable>"
    "     <stateVariable sendEvents=\"no\">"
    "         <name>A_ARG_TYPE_evt</name>"
    "         <dataType>string</dataType>"
    "         <defaultValue></defaultValue>"
    "     </stateVariable>"
    "     <stateVariable sendEvents=\"no\">"
    "         <name>A_ARG_TYPE_events</name>"
    "         <dataType>string</dataType>"
    "         <defaultValue></defaultValue>"
    "     </stateVariable>"
    "     <stateVariable sendEvents=\"no\">"
    "         <name>A_ARG_TYPE_event_id</name>"
    "         <dataType>string</dataType>"
    "         <defaultValue></defaultValue>"
    "     </stateVariable>"
    "     <stateVariable sendEvents=\"no\">"
    "         <name>A_ARG_TYPE_action</name>"
    "         <dataType>string</dataType>"
    "         <defaultValue></defaultValue>"
    "     </stateVariable>"
    "     <stateVariable sendEvents=\"no\">"
    "         <name>A_ARG_TYPE_property_value</name>"
    "         <dataType>string</dataType>"
    "         <defaultValue></defaultValue>"
    "     </stateVariable>"
    "     <stateVariable sendEvents=\"no\">"
    "         <name>A_ARG_TYPE_property_duration</name>"
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

// Passive Pcm Upnp constant strings
const char* UpnpFsmdaUtils::kPassivePcmDeviceType =
    "urn:schemas-upnp-org:device:fsmda-passive-parent-communication-device:1";
const char* UpnpFsmdaUtils::kPassivePcmDeviceFriendlyName =
    "fsmda passive parent communication device friendly name";
const char* UpnpFsmdaUtils::kPassivePcmDeviceModelName =
    "fsmda-passive-parent-communication-device model name";
const char* UpnpFsmdaUtils::kPassivePcmDeviceModelDescription =
    "fsmda passive parent communication model description";
const char* UpnpFsmdaUtils::kPassivePcmDeviceModelUrl =
    "http://www.ncl.org.br/fsmda/ondemand";
const char* UpnpFsmdaUtils::kPassivePcmDeviceModelNumber = "1.0";
const char* UpnpFsmdaUtils::kPassivePcmServiceType =
    "urn:schemas-upnp-org:service:fsmda-passive-parent-communication-service:1";
const char* UpnpFsmdaUtils::kPassivePcmServiceId =
    "urn:upnp-org:serviceId:fsmda-passive-parent-communication-service001";
const char* UpnpFsmdaUtils::kPassivePcmServiceName =
    "urn:upnp-org:serviceId:fsmda-passive-parent-communication-service001-name";
const char* UpnpFsmdaUtils::kPassivePcmServiceScpdXml =
    "<?xml version=\"1.0\" ?>"
    "<scpd xmlns=\"urn:schemas-upnp-org:service-1-0\">"
    "   <specVersion>"
    "     <major>1</major>"
    "     <minor>0</minor>"
    "   </specVersion>"
    "   <actionList>"
    "     <action>"
    "       <name>NotifyError</name>"
    "       <argumentList>"
    "         <argument>"
    "           <name>object_id</name>"
    "           <direction>in</direction>"
    "<relatedStateVariable>A_ARG_TYPE_object_id</relatedStateVariable>"
    "         </argument>"
    "         <argument>"
    "           <name>message</name>"
    "           <direction>in</direction>"
    "<relatedStateVariable>A_ARG_TYPE_message</relatedStateVariable>"
    "         </argument>"
    "       </argumentList>"
    "     </action>"
    "   </actionList>"
    "   <serviceStateTable>"
    "     <stateVariable sendEvents=\"no\">"
    "       <name>A_ARG_TYPE_object_id</name>"
    "       <dataType>string</dataType>"
    "       <defaultValue></defaultValue>"
    "     </stateVariable>"
    "     <stateVariable sendEvents=\"no\">"
    "         <name>A_ARG_TYPE_message</name>"
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

// Passive Ccm Upnp constant strings
const char* UpnpFsmdaUtils::kPassiveCcmDeviceType =
    "urn:schemas-upnp-org:device:fsmda-passive-child-communication-device:1";
const char* UpnpFsmdaUtils::kPassiveCcmDeviceFriendlyName =
    "fsmda passive child communication device friendly name";
const char* UpnpFsmdaUtils::kPassiveCcmDeviceModelName =
    "fsmda-passive-child-communication-device model name";
const char* UpnpFsmdaUtils::kPassiveCcmDeviceModelDescription =
    "fsmda passive child communication model description";
const char* UpnpFsmdaUtils::kPassiveCcmDeviceModelUrl =
    "http://www.ncl.org.br/fsmda/ondemand";
const char* UpnpFsmdaUtils::kPassiveCcmDeviceModelNumber = "1.0";
const char* UpnpFsmdaUtils::kPassiveCcmServiceType =
    "urn:schemas-upnp-org:service:fsmda-passive-child-communication-service:1";
const char* UpnpFsmdaUtils::kPassiveCcmServiceId =
    "urn:upnp-org:serviceId:fsmda-passive-child-communication-service001";
const char* UpnpFsmdaUtils::kPassiveCcmServiceName =
    "urn:upnp-org:serviceId:fsmda-passive-child-communication-service001-name";
const char* UpnpFsmdaUtils::kPassiveCcmServiceScpdXml =
    "<?xml version=\"1.0\" ?>"
    "<scpd xmlns=\"urn:schemas-upnp-org:service-1-0\">"
    "   <specVersion>"
    "     <major>1</major>"
    "     <minor>0</minor>"
    "   </specVersion>"
    "   <actionList>"
    "     <action>"
    "       <name>Prepare</name>"
    "       <argumentList>"
    "         <argument>"
    "           <name>position</name>"
    "           <direction>in</direction>"
    "<relatedStateVariable>A_ARG_TYPE_object_id</relatedStateVariable>"
    "         </argument>"
    "       </argumentList>"
    "     </action>"
    "     <action>"
    "       <name>SendContent</name>"
    "       <argumentList>"
    "         <argument>"
    "           <name>content</name>"
    "           <direction>in</direction>"
    "<relatedStateVariable>A_ARG_TYPE_content</relatedStateVariable>"
    "         </argument>"
    "       </argumentList>"
    "     </action>"
    "   </actionList>"
    "   <serviceStateTable>"
    "     <stateVariable sendEvents=\"no\">"
    "       <name>A_ARG_TYPE_position</name>"
    "       <dataType>string</dataType>"
    "       <defaultValue></defaultValue>"
    "     </stateVariable>"
    "     <stateVariable sendEvents=\"no\">"
    "         <name>A_ARG_TYPE_content</name>"
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

// MediaCapture Pcm Upnp constant strings
const char* UpnpFsmdaUtils::kMediaCapturePcmDeviceType =
    "urn:schemas-upnp-org:device:fsmda-mediacapture-parent-communication-"
    "device:1";
const char* UpnpFsmdaUtils::kMediaCapturePcmDeviceFriendlyName =
    "fsmda mediacapture parent communication device friendly name";
const char* UpnpFsmdaUtils::kMediaCapturePcmDeviceModelName =
    "fsmda-mediacapture-parent-communication-device model name";
const char* UpnpFsmdaUtils::kMediaCapturePcmDeviceModelDescription =
    "fsmda mediacapture parent communication model description";
const char* UpnpFsmdaUtils::kMediaCapturePcmDeviceModelUrl =
    "http://www.ncl.org.br/fsmda/ondemand";
const char* UpnpFsmdaUtils::kMediaCapturePcmDeviceModelNumber = "1.0";
const char* UpnpFsmdaUtils::kMediaCapturePcmServiceType =
    "urn:schemas-upnp-org:service:fsmda-mediacapture-parent-communication-"
    "service:1";
const char* UpnpFsmdaUtils::kMediaCapturePcmServiceId =
    "urn:upnp-org:serviceId:fsmda-mediacapture-parent-communication-service001";
const char* UpnpFsmdaUtils::kMediaCapturePcmServiceName =
    "urn:upnp-org:serviceId:fsmda-mediacapture-parent-communication-service001-"
    "name";
const char* UpnpFsmdaUtils::kMediaCapturePcmServiceScpdXml =
    "<?xml version=\"1.0\" ?>"
    "<scpd xmlns=\"urn:schemas-upnp-org:service-1-0\">"
    "   <specVersion>"
    "     <major>1</major>"
    "     <minor>0</minor>"
    "   </specVersion>"
    "   <actionList>"
    "     <action>"
    "       <name>SendContent</name>"
    "       <argumentList>"
    "         <argument>"
    "           <name>content</name>"
    "           <direction>in</direction>"
    "<relatedStateVariable>A_ARG_TYPE_content</relatedStateVariable>"
    "         </argument>"
    "         <argument>"
    "           <name>resource_id</name>"
    "           <direction>in</direction>"
    "<relatedStateVariable>A_ARG_TYPE_resource_id</relatedStateVariable>"
    "         </argument>"
    "         <argument>"
    "           <name>child_index</name>"
    "           <direction>in</direction>"
    "<relatedStateVariable>A_ARG_TYPE_child_index</relatedStateVariable>"
    "         </argument>"
    "       </argumentList>"
    "     </action>"
    "   </actionList>"
    "   <serviceStateTable>"
    "     <stateVariable sendEvents=\"no\">"
    "       <name>A_ARG_TYPE_content</name>"
    "       <dataType>string</dataType>"
    "       <defaultValue></defaultValue>"
    "     </stateVariable>"
    "     <stateVariable sendEvents=\"no\">"
    "         <name>A_ARG_TYPE_resource_id</name>"
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

// MediaCapture Ccm Upnp constant strings
const char* UpnpFsmdaUtils::kMediaCaptureCcmDeviceType =
    "urn:schemas-upnp-org:device:fsmda-mediacapture-child-communication-device:"
    "1";
const char* UpnpFsmdaUtils::kMediaCaptureCcmDeviceFriendlyName =
    "fsmda mediacapture child communication device friendly name";
const char* UpnpFsmdaUtils::kMediaCaptureCcmDeviceModelName =
    "fsmda-mediacapture-child-communication-device model name";
const char* UpnpFsmdaUtils::kMediaCaptureCcmDeviceModelDescription =
    "fsmda mediacapture child communication model description";
const char* UpnpFsmdaUtils::kMediaCaptureCcmDeviceModelUrl =
    "http://www.ncl.org.br/fsmda/ondemand";
const char* UpnpFsmdaUtils::kMediaCaptureCcmDeviceModelNumber = "1.0";
const char* UpnpFsmdaUtils::kMediaCaptureCcmServiceType =
    "urn:schemas-upnp-org:service:fsmda-mediacapture-child-communication-"
    "service:1";
const char* UpnpFsmdaUtils::kMediaCaptureCcmServiceId =
    "urn:upnp-org:serviceId:fsmda-mediacapture-child-communication-service001";
const char* UpnpFsmdaUtils::kMediaCaptureCcmServiceName =
    "urn:upnp-org:serviceId:fsmda-mediacapture-child-communication-service001-"
    "name";
const char* UpnpFsmdaUtils::kMediaCaptureCcmServiceScpdXml =
    "<?xml version=\"1.0\" ?>"
    "<scpd xmlns=\"urn:schemas-upnp-org:service-1-0\">"
    "   <specVersion>"
    "     <major>1</major>"
    "     <minor>0</minor>"
    "   </specVersion>"
    "   <actionList>"
    "     <action>"
    "       <name>RequestContent</name>"
    "       <argumentList>"
    "         <argument>"
    "           <name>resource_id</name>"
    "           <direction>in</direction>"
    "<relatedStateVariable>A_ARG_TYPE_resource_id</relatedStateVariable>"
    "         </argument>"
    "         <argument>"
    "           <name>child_index</name>"
    "           <direction>in</direction>"
    "<relatedStateVariable>A_ARG_TYPE_child_index</relatedStateVariable>"
    "         </argument>"
    "       </argumentList>"
    "     </action>"
    "   </actionList>"
    "   <serviceStateTable>"
    "     <stateVariable sendEvents=\"no\">"
    "       <name>A_ARG_TYPE_resource_id</name>"
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
    "   </serviceStateTable>"
    "   <intel_nmpr:X_INTEL_NMPR "
    "xmlns:intel_nmpr=\"udn:schemas-intel-com:device-1-0\">2.1</"
    "intel_nmpr:X_INTEL_NMPR>"
    "   <dlna:X_DLNADOC xmlns:dlna=\"udn:schemas-dlna-org:device-1-0\">DMP "
    "1.00</dlna:X_DLNADOC>"
    "  </scpd>";

// OnDemand Pcm Upnp constant strings
const char* UpnpFsmdaUtils::kOnDemandPcmDeviceType =
    "urn:schemas-upnp-org:device:fsmda-ondemand-parent-communication-device:1";
const char* UpnpFsmdaUtils::kOnDemandPcmDeviceFriendlyName =
    "fsmda ondemand parent communication device friendly name";
const char* UpnpFsmdaUtils::kOnDemandPcmDeviceModelName =
    "fsmda-ondemand-parent-communication-device model name";
const char* UpnpFsmdaUtils::kOnDemandPcmDeviceModelDescription =
    "fsmda ondemand parent communication model description";
const char* UpnpFsmdaUtils::kOnDemandPcmDeviceModelUrl =
    "http://www.ncl.org.br/fsmda/ondemand";
const char* UpnpFsmdaUtils::kOnDemandPcmDeviceModelNumber = "1.0";
const char* UpnpFsmdaUtils::kOnDemandPcmServiceType =
    "urn:schemas-upnp-org:service:fsmda-ondemand-parent-communication-service:"
    "1";
const char* UpnpFsmdaUtils::kOnDemandPcmServiceId =
    "urn:upnp-org:serviceId:fsmda-ondemand-parent-communication-service001";
const char* UpnpFsmdaUtils::kOnDemandPcmServiceName =
    "urn:upnp-org:serviceId:fsmda-ondemand-parent-communication-service001-"
    "name";
const char* UpnpFsmdaUtils::kOnDemandPcmServiceScpdXml =
    "<?xml version=\"1.0\" ?>"
    "<scpd xmlns=\"urn:schemas-upnp-org:service-1-0\">"
    "   <specVersion>"
    "     <major>1</major>"
    "     <minor>0</minor>"
    "   </specVersion>"
    "   <actionList>"
    "     <action>"
    "       <name>NotifyOnDemandContent</name>"
    "       <argumentList>"
    "         <argument>"
    "           <name>action</name>"
    "           <direction>in</direction>"
    "<relatedStateVariable>A_ARG_TYPE_content</relatedStateVariable>"
    "         </argument>"
    "         <argument>"
    "           <name>location</name>"
    "           <direction>in</direction>"
    "<relatedStateVariable>A_ARG_TYPE_resource_id</relatedStateVariable>"
    "         </argument>"
    "       </argumentList>"
    "     </action>"
    "   </actionList>"
    "   <serviceStateTable>"
    "     <stateVariable sendEvents=\"no\">"
    "       <name>A_ARG_TYPE_action</name>"
    "       <dataType>string</dataType>"
    "       <defaultValue></defaultValue>"
    "     </stateVariable>"
    "     <stateVariable sendEvents=\"no\">"
    "         <name>A_ARG_TYPE_location</name>"
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

// OnDemand Ccm Upnp constant strings
const char* UpnpFsmdaUtils::kOnDemandCcmDeviceType =
    "urn:schemas-upnp-org:device:fsmda-ondemand-child-communication-device:1";
const char* UpnpFsmdaUtils::kOnDemandCcmDeviceFriendlyName =
    "fsmda ondemand child communication device friendly name";
const char* UpnpFsmdaUtils::kOnDemandCcmDeviceModelName =
    "fsmda-ondemand-child-communication-device model name";
const char* UpnpFsmdaUtils::kOnDemandCcmDeviceModelDescription =
    "fsmda ondemand child communication model description";
const char* UpnpFsmdaUtils::kOnDemandCcmDeviceModelUrl =
    "http://www.ncl.org.br/fsmda/ondemand";
const char* UpnpFsmdaUtils::kOnDemandCcmDeviceModelNumber = "1.0";
const char* UpnpFsmdaUtils::kOnDemandCcmServiceType =
    "urn:schemas-upnp-org:service:fsmda-ondemand-child-communication-service:1";
const char* UpnpFsmdaUtils::kOnDemandCcmServiceId =
    "urn:upnp-org:serviceId:fsmda-ondemand-child-communication-service001";
const char* UpnpFsmdaUtils::kOnDemandCcmServiceName =
    "urn:upnp-org:serviceId:fsmda-ondemand-child-communication-service001-name";
const char* UpnpFsmdaUtils::kOnDemandCcmServiceScpdXml =
    "<?xml version=\"1.0\" ?>"
    "<scpd xmlns=\"urn:schemas-upnp-org:service-1-0\">"
    "   <specVersion>"
    "     <major>1</major>"
    "     <minor>0</minor>"
    "   </specVersion>"
    "   <actionList>"
    "     <action>"
    "       <name>NotifyError</name>"
    "       <argumentList>"
    "         <argument>"
    "           <name>object_id</name>"
    "           <direction>in</direction>"
    "<relatedStateVariable>A_ARG_TYPE_object_id</relatedStateVariable>"
    "         </argument>"
    "         <argument>"
    "           <name>message</name>"
    "           <direction>in</direction>"
    "<relatedStateVariable>A_ARG_TYPE_message</relatedStateVariable>"
    "         </argument>"
    "       </argumentList>"
    "     </action>"
    "   </actionList>"
    "   <serviceStateTable>"
    "     <stateVariable sendEvents=\"no\">"
    "       <name>A_ARG_TYPE_message</name>"
    "       <dataType>string</dataType>"
    "       <defaultValue></defaultValue>"
    "     </stateVariable>"
    "     <stateVariable sendEvents=\"no\">"
    "         <name>A_ARG_TYPE_object_id</name>"
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

/*----------------------------------------------------------------------
 |   UpnpUtils::GenerateGUID
 +---------------------------------------------------------------------*/
void UpnpFsmdaUtils::GenerateGUID(std::string* guid) {
  NPT_String guid_aux;
  PLT_UPnPMessageHelper::GenerateGUID(guid_aux);
  guid->assign(guid_aux.GetChars());
}

/*----------------------------------------------------------------------
 |   UpnpUtils::RequestUpnpReference
 +---------------------------------------------------------------------*/
PLT_UPnP* UpnpFsmdaUtils::GetRunningInstance() {
  if (UpnpFsmdaUtils::upnp_singleton_ == NULL) {
    // setup Neptune logging
    NPT_LogManager::GetDefault().Configure(
        "plist:.level=;.handlers=ConsoleHandler;"
        ".ConsoleHandler.colors=off;"
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
void UpnpFsmdaUtils::ReleaseInstance() {
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
bool UpnpFsmdaUtils::IsUpnpStarted() {
  if (UpnpFsmdaUtils::upnp_singleton_ == NULL) {
    return false;
  } else {
    UpnpFsmdaUtils::upnp_singleton_->IsRunning();
  }
}
