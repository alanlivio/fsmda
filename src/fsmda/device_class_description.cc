/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlmemory.h>
#include <libxml/xmlstring.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include "fsmda/device_class_description.h"
#include "fsmda/device_description.h"

using std::clog;
using std::endl;
using std::string;
using std::strlen;

/*----------------------------------------------------------------------
 |   class fields
 +---------------------------------------------------------------------*/

const char* DeviceClassDescription::kInvalidDeviceString = "invalid device";
const char* DeviceClassDescription::kBaseDeviceString = "base";
const char* DeviceClassDescription::kPassiveDeviceString = "passive";
const char* DeviceClassDescription::kActiveDeviceString = "active";
const char* DeviceClassDescription::kHtmlDeviceString = "html";
const char* DeviceClassDescription::kOnDemandDeviceString = "ondemand";
const char* DeviceClassDescription::kMediaCaptureDeviceString = "mediacapture";
const char* DeviceClassDescription::kInvalidPairingProtocolString =
    "invalid pairing protocol";
const char* DeviceClassDescription::kUpnpPairingProcotolString = "UPnP";
const char* DeviceClassDescription::kZeroconfPairingProtocolString = "Zeroconf";
const char* DeviceClassDescription::kInvalidCommunicationProtocolString =
    "invalid communication protocol";
const char* DeviceClassDescription::kUpnpCommunicationProcotolString = "UPnP";
const char* DeviceClassDescription::kHTTPCommunicationProtocolString = "HTTP";
const char* DeviceClassDescription::kAdHocSocketCommunicationProtocolString =
    "ad hoc socket";
const char* DeviceClassDescription::kPassiveDeviceDefaultRdfContent = "";
const char* DeviceClassDescription::kActiveDeviceDefaultRdfContent =
    "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
    "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\""
    "xmlns:prf=\"http://www.wapforum.org/profiles/UAPROF/ccppschema-20010430#\""
    "  xmlns:fsmda=\"http://www.ncl.org.br/fsmda\">"
    "  <fsmda:classType>active</fsmda:classType>"
    "  <fsmda:minDevices>1</fsmda:minDevices>"
    "  <fsmda:maxDevices>1</fsmda:maxDevices>"
    "  <fsmda:SoftwareRequirements>"
    "    <fsmda:softwareParams>"
    "    </fsmda:softwareParams>"
    "    <fsmda:supportedMessages>"
    "      <rdf:Bag>"
    "        <rdf:li>HTTP</rdf:li>"
    "      </rdf:Bag>"
    "    </fsmda:supportedMessages>"
    "  </fsmda:SoftwareRequirements>"
    "  <fsmda:NetworkRequirements>"
    "    <fsmda:pairingMethod>UPnP</fsmda:pairingMethod>"
    "  </fsmda:NetworkRequirements>"
    "  <fsmda:HardwareRequirements>"
    "  </fsmda:HardwareRequirements>"
    "</rdf:RDF>";

const char* DeviceClassDescription::kHtmlDeviceDefaultRdfContent =
    "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
    "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\""
    "xmlns:prf=\"http://www.wapforum.org/profiles/UAPROF/ccppschema-20010430#\""
    "  xmlns:fsmda=\"http://www.ncl.org.br/fsmda\">"
    "  <fsmda:classType>html</fsmda:classType>"
    "  <fsmda:minDevices>1</fsmda:minDevices>"
    "  <fsmda:maxDevices>1</fsmda:maxDevices>"
    "  <fsmda:SoftwareRequirements>"
    "    <fsmda:softwareParams>"
    "    </fsmda:softwareParams>"
    "    <fsmda:supportedMessages>"
    "      <rdf:Bag>"
    "        <rdf:li>HTTP</rdf:li>"
    "      </rdf:Bag>"
    "    </fsmda:supportedMessages>"
    "  </fsmda:SoftwareRequirements>"
    "  <fsmda:NetworkRequirements>"
    "    <fsmda:pairingMethod>UPnP</fsmda:pairingMethod>"
    "  </fsmda:NetworkRequirements>"
    "  <fsmda:HardwareRequirements>"
    "  </fsmda:HardwareRequirements>"
    "</rdf:RDF>";

const char* DeviceClassDescription::kOnDemandDeviceDefaultRdfContent =
    "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
    "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\""
    "xmlns:prf=\"http://www.wapforum.org/profiles/UAPROF/ccppschema-20010430#\""
    "  xmlns:fsmda=\"http://www.ncl.org.br/fsmda\">"
    "  <fsmda:classType>ondemand</fsmda:classType>"
    "  <fsmda:minDevices>1</fsmda:minDevices>"
    "  <fsmda:maxDevices>1</fsmda:maxDevices>"
    "  <fsmda:SoftwareRequirements>"
    "    <fsmda:softwareParams>"
    "    </fsmda:softwareParams>"
    "    <fsmda:supportedMessages>"
    "      <rdf:Bag>"
    "        <rdf:li>HTTP</rdf:li>"
    "      </rdf:Bag>"
    "    </fsmda:supportedMessages>"
    "  </fsmda:SoftwareRequirements>"
    "  <fsmda:NetworkRequirements>"
    "    <fsmda:pairingMethod>UPnP</fsmda:pairingMethod>"
    "  </fsmda:NetworkRequirements>"
    "  <fsmda:HardwareRequirements>"
    "  </fsmda:HardwareRequirements>"
    "</rdf:RDF>";

const char* DeviceClassDescription::kMediCaptureDeviceDefaultRdfContent =
    "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
    "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\""
    "xmlns:prf=\"http://www.wapforum.org/profiles/UAPROF/ccppschema-20010430#\""
    "  xmlns:fsmda=\"http://www.ncl.org.br/fsmda\">"
    "  <fsmda:classType>mediacapture</fsmda:classType>"
    "  <fsmda:minDevices>1</fsmda:minDevices>"
    "  <fsmda:maxDevices>1</fsmda:maxDevices>"
    "  <fsmda:SoftwareRequirements>"
    "    <fsmda:softwareParams>"
    "    </fsmda:softwareParams>"
    "    <fsmda:supportedMessages>"
    "      <rdf:Bag>"
    "        <rdf:li>HTTP</rdf:li>"
    "      </rdf:Bag>"
    "    </fsmda:supportedMessages>"
    "  </fsmda:SoftwareRequirements>"
    "  <fsmda:NetworkRequirements>"
    "    <fsmda:pairingMethod>UPnP</fsmda:pairingMethod>"
    "  </fsmda:NetworkRequirements>"
    "  <fsmda:HardwareRequirements>"
    "  </fsmda:HardwareRequirements>"
    "</rdf:RDF>";

/*----------------------------------------------------------------------
 |   DeviceClassDescription::DeviceClassDescription
 +---------------------------------------------------------------------*/
DeviceClassDescription::DeviceClassDescription()
    : device_class_type_(kBaseDevice),
      min_devices_(0),
      max_devices_(0),
      initialized_(false) {}

/*----------------------------------------------------------------------
 |   DeviceClassDescription::~DeviceClassDescription
 +---------------------------------------------------------------------*/
DeviceClassDescription::~DeviceClassDescription() {}

/*----------------------------------------------------------------------
 |   DeviceClassDescription::DeviceMeetRequirements
 +---------------------------------------------------------------------*/
bool DeviceClassDescription::DeviceMeetRequirements(
    DeviceDescription* device_desc) {
  if (!initialized_) {
    clog << "device_meets_requirements fail: not initialized_" << endl;
    return false;
  } else if (device_class_type_ != device_desc->device_class_type()) {
    clog << "device_meets_requirements fail: classType_" << endl;
    return false;
  } else if (pairing_protocol_ != device_desc->pairing_method()) {
    clog << "device_meets_requirements fail: pairingMethod_" << endl;
    return false;
  } else {
    return true;
  }
}

/*----------------------------------------------------------------------
 |   DeviceClassDescription::InitializeByDefaultDeviceClass
 +---------------------------------------------------------------------*/
int DeviceClassDescription::InitializeByDeviceClass(DeviceClassType type) {
  device_class_type_ = type;
  min_devices_ = 1;
  max_devices_ = UINT_MAX;
  pairing_protocol_ = DeviceClassDescription::kUpnpPairingProcotol;
  initialized_ = true;

  // initilize libxml
  xmlInitParser();

  // parse file
  const char* rdf_content = GetDeviceClassRdfDefaultContentByType(type);
  unsigned int rdf_content_size = strlen(rdf_content);
  xmlDocPtr xml_doc = xmlParseMemory(rdf_content, rdf_content_size);
  if (ParseAndReleaseXml(xml_doc) == 0) {
    initialized_ = true;
    return 0;
  } else
    return -1;
}

/*----------------------------------------------------------------------
 |   DeviceClassDescription::InitializeByRdfFile
 +---------------------------------------------------------------------*/
int DeviceClassDescription::InitializeByRdfFile(const string& rdf_file_path) {
  // initilize libxml
  xmlInitParser();

  // parse file
  xmlDocPtr xml_doc = xmlParseFile(rdf_file_path.c_str());
  if (ParseAndReleaseXml(xml_doc) == 0) {
    initialized_ = true;
    return 0;
  } else
    return -1;
}

int DeviceClassDescription::ParseAndReleaseXml(xmlDocPtr xml_doc) {
  int ret;
  xmlXPathContextPtr xpathCtx;
  xmlXPathObjectPtr xpathObj;
  xmlNodeSetPtr nodes;
  const char* aux;

  // initilize libxml
  xmlInitParser();

  // parse xml_doc
  assert(xml_doc != NULL);
  xpathCtx = xmlXPathNewContext(xml_doc);
  assert(xpathCtx != NULL);
  ret = xmlXPathRegisterNs(
      xpathCtx, reinterpret_cast<const xmlChar*>("fsmda"),
      reinterpret_cast<const xmlChar*>("http://www.ncl.org.br/fsmda"));
  assert(ret == 0);

  // capture classType
  xpathObj = xmlXPathEvalExpression(
      reinterpret_cast<const xmlChar*>("//fsmda:classType"), xpathCtx);
  assert(xpathObj != NULL);
  nodes = xpathObj->nodesetval;
  assert(nodes->nodeTab[0]);
  aux = (const char*)nodes->nodeTab[0]->children->content;
  device_class_type_ = DeviceClassDescription::GetDeviceClassTypeByString(aux);
  clog << "DeviceClassDescription::InitializeByParseRdfFile::classType = "
       << aux << "(or " << device_class_type_ << ")" << endl;
  xmlXPathFreeObject(xpathObj);

  // capture min_devices
  xpathObj = xmlXPathEvalExpression(
      reinterpret_cast<const xmlChar*>("//fsmda:minDevices"), xpathCtx);
  assert(xpathObj != NULL);
  nodes = xpathObj->nodesetval;
  assert(nodes->nodeTab[0]);
  aux = (const char*)nodes->nodeTab[0]->children->content;
  min_devices_ = atoi(aux);
  clog << "DeviceClassDescription::InitializeByParseRdfFile::minDevices = "
       << min_devices_ << endl;
  xmlXPathFreeObject(xpathObj);

  // capture max_devices
  xpathObj = xmlXPathEvalExpression(
      reinterpret_cast<const xmlChar*>("//fsmda:maxDevices"), xpathCtx);
  assert(xpathObj != NULL);
  nodes = xpathObj->nodesetval;
  assert(nodes->nodeTab[0]);
  aux = (const char*)nodes->nodeTab[0]->children->content;
  max_devices_ = atoi(aux);
  clog << "DeviceClassDescription::InitializeByParseRdfFile::maxDevices = "
       << max_devices_ << endl;
  xmlXPathFreeObject(xpathObj);

  // capture pairingMethod
  xpathObj = xmlXPathEvalExpression(
      reinterpret_cast<const xmlChar*>("//fsmda:pairingMethod"), xpathCtx);
  assert(xpathObj != NULL);
  nodes = xpathObj->nodesetval;
  assert(nodes->nodeTab[0]);
  pairing_protocol_ = DeviceClassDescription::GetPairingProtocolByString(
      (const char*)nodes->nodeTab[0]->children->content);
  clog << "DeviceClassDescription::InitializeByParseRdfFile::pairingMethod = "
       << pairing_protocol_ << endl;
  xmlXPathFreeObject(xpathObj);

  // release libxml
  xmlXPathFreeContext(xpathCtx);
  xmlFreeDoc(xml_doc);
  xmlCleanupParser();
  xmlMemoryDump();

  // TODO(alan@telemidia.puc-rio.br) return libxml errors
  return 0;
}

/*----------------------------------------------------------------------
 |   DeviceClassDescription::GetDeviceClassTypeByString
 +---------------------------------------------------------------------*/
DeviceClassDescription::DeviceClassType
DeviceClassDescription::GetDeviceClassTypeByString(const string& str) {
  if (!str.compare(kPassiveDeviceString))
    return kPassiveDevice;
  else if (!str.compare(kActiveDeviceString))
    return kActiveDevice;
  else if (!str.compare(kHtmlDeviceString))
    return kHtmlDevice;
  else if (!str.compare(kOnDemandDeviceString))
    return kOnDemandDevice;
  else if (!str.compare(kOnDemandDeviceString))
    return kMediaCaptureDevice;
  else if (!str.compare(kMediaCaptureDeviceString))
    return kMediaCaptureDevice;
  return kInvalidDevice;
}

/*----------------------------------------------------------------------
 |   DeviceClassDescription::GetPairingProtocolByString
 +---------------------------------------------------------------------*/
DeviceClassDescription::PairingProtocol
DeviceClassDescription::GetPairingProtocolByString(const std::string& str) {
  if (!str.compare(kUpnpPairingProcotolString))
    return kUpnpPairingProcotol;
  else if (!str.compare(kZeroconfPairingProtocolString))
    return kZeroconfPairingProtocol;
  else
    return kPairingProtocolInvalid;
}

/*----------------------------------------------------------------------
 |   DeviceClassDescription::GetCommunicationProtocoByString
 +---------------------------------------------------------------------*/
DeviceClassDescription::CommunicationProtocol
DeviceClassDescription::GetCommunicationProtocoByString(
    const std::string& str) {
  if (!str.compare(kUpnpCommunicationProcotolString))
    return kUpnpCommunicationProcotol;
  else if (!str.compare(kHTTPCommunicationProtocolString))
    return kHTTPCommunicationProtocol;
  else
    return kCommunicationProtocolInvalid;
}

const char* DeviceClassDescription::GetDeviceClassRdfDefaultContentByType(
    DeviceClassDescription::DeviceClassType type) {
  switch (type) {
    case kActiveDevice:
      return kActiveDeviceDefaultRdfContent;
      break;
    default:
      return "";
  }
}
/*----------------------------------------------------------------------
 |   DeviceClassDescription::GetDeviceClassTypeByString
 +---------------------------------------------------------------------*/
const char* DeviceClassDescription::GetPairingProtocolStringByEnum(
    DeviceClassDescription::PairingProtocol type) {
  switch (type) {
    case kUpnpPairingProcotol:
      return kUpnpPairingProcotolString;
      break;
    case kZeroconfPairingProtocol:
      return kZeroconfPairingProtocolString;
      break;
    default:
      return kInvalidCommunicationProtocolString;
  }
}

/*----------------------------------------------------------------------
 |   DeviceClassDescription::GetDeviceClassTypeByString
 +---------------------------------------------------------------------*/
const char* DeviceClassDescription::GetCommunicationProtocolStringByEnum(
    DeviceClassDescription::CommunicationProtocol type) {
  switch (type) {
    case kUpnpCommunicationProcotol:
      return kUpnpCommunicationProcotolString;
      break;
    case kHTTPCommunicationProtocol:
      return kHTTPCommunicationProtocolString;
      break;
    default:
      return kInvalidCommunicationProtocolString;
  }
}

/*----------------------------------------------------------------------
 |   DeviceClassDescription::GetDeviceClassTypeStringByEnum
 +---------------------------------------------------------------------*/
const char* DeviceClassDescription::GetDeviceClassTypeStringByEnum(
    DeviceClassDescription::DeviceClassType type) {
  switch (type) {
    case kBaseDevice:
      return kBaseDeviceString;
      break;
    case kPassiveDevice:
      return kPassiveDeviceString;
      break;
    case kActiveDevice:
      return kActiveDeviceString;
      break;
    case kHtmlDevice:
      return kHtmlDeviceString;
      break;
    case kOnDemandDevice:
      return kOnDemandDeviceString;
      break;
    case kMediaCaptureDevice:
      return kMediaCaptureDeviceString;
      break;
    default:
      return kInvalidDeviceString;
  }
}
