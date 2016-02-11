

#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlmemory.h>
#include <libxml/xmlstring.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "fsmda/device_class_description.h"
#include "fsmda/device_description.h"

using std::clog;
using std::endl;
using std::string;
using std::ifstream;
using std::strlen;



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
const char* DeviceClassDescription::kInvalidDeviceDefaultRdfContent =
    "invalid rdf";
const char* DeviceClassDescription::kPassiveDeviceDefaultRdfContent =
    "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
    "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns\" xmlns:prf=\"http://www.wapforum.org/profiles/UAPROF/ccppschema-20010430\" xmlns:fsmda=\"http://www.ncl.org.br/fsmda\">"
    "  <fsmda:classType>passive</fsmda:classType>"
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

const char* DeviceClassDescription::kActiveDeviceDefaultRdfContent =
    "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
    "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns\" xmlns:prf=\"http://www.wapforum.org/profiles/UAPROF/ccppschema-20010430\" xmlns:fsmda=\"http://www.ncl.org.br/fsmda\">"
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
    "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns\" xmlns:prf=\"http://www.wapforum.org/profiles/UAPROF/ccppschema-20010430\" xmlns:fsmda=\"http://www.ncl.org.br/fsmda\">"
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
    "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns\" xmlns:prf=\"http://www.wapforum.org/profiles/UAPROF/ccppschema-20010430\" xmlns:fsmda=\"http://www.ncl.org.br/fsmda\">"
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
    "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns\" xmlns:prf=\"http://www.wapforum.org/profiles/UAPROF/ccppschema-20010430\" xmlns:fsmda=\"http://www.ncl.org.br/fsmda\">"
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


DeviceClassDescription::DeviceClassDescription()
    : device_class_type_(kBaseDevice),
      rdf_content_(""),
      min_devices_(0),
      max_devices_(0),
      initialized_(false) {}


DeviceClassDescription::~DeviceClassDescription() {}


DeviceClassDescription::DeviceClassType
DeviceClassDescription::device_class_type() {
  return device_class_type_;
}


DeviceClassDescription::PairingProtocol
DeviceClassDescription::pairing_protocol() {
  return pairing_protocol_;
}


DeviceClassDescription::CommunicationProtocol
DeviceClassDescription::communication_protocol() {
  return communication_protocol_;
}


const string& DeviceClassDescription::rdf_content() {
  return rdf_content_;
}


unsigned int DeviceClassDescription::min_devices() { return min_devices_; }


unsigned int DeviceClassDescription::max_devices() { return max_devices_; }


bool DeviceClassDescription::IsDeviceCompatible(
    DeviceDescription* device_desc) {
  if (!initialized_) {
    clog
        << "DeviceClassDescription::IsDeviceCompatible:: fail: not initialized_"
        << endl;
    return false;
  } else if (device_class_type_ != device_desc->device_class_type()) {
    clog << "DeviceClassDescription::IsDeviceCompatible:: fail: classType_"
         << endl;
    return false;
  } else if (pairing_protocol_ != device_desc->pairing_method()) {
    clog << "DeviceClassDescription::IsDeviceCompatible:: pairingMethod_"
         << endl;
    return false;
  } else {
    return true;
  }
}


int DeviceClassDescription::InitializeByDeviceClass(DeviceClassType type) {
  const char* rdf_content_aux = GetDeviceClassRdfDefaultContentByType(type);
  if (ParseXmlContent(rdf_content_aux) == 0) {
    rdf_content_ = rdf_content_aux;
    initialized_ = true;
    return 0;
  } else {
    return -1;
  }
}


int DeviceClassDescription::InitializeByRdfContent(const char* content) {
  // parse file
  if (ParseXmlContent(content) == 0) {
    rdf_content_ = content;
    initialized_ = true;
    return 0;
  } else {
    return -1;
  }
}


int DeviceClassDescription::InitializeByRdfFile(const string& rdf_file_path) {
  std::ifstream t;
  t.open(rdf_file_path.c_str());
  std::stringstream contents;
  contents << t.rdbuf();

  //  clog << " DeviceClassDescription::InitializeByRdfFile:: contents ="
  //       << contents.str().c_str() << endl;
  if (ParseXmlContent(contents.str().c_str()) == 0) {
    initialized_ = true;
    rdf_content_ = contents.str().c_str();
    return 0;
  } else {
    return -1;
  }
}


int DeviceClassDescription::ParseXmlContent(const char* rdf_content) {
  int ret;
  unsigned int rdf_content_size;
  const char* aux;
  xmlXPathContextPtr xpathCtx;
  xmlXPathObjectPtr xpathObj;
  xmlNodeSetPtr nodes;
  xmlDocPtr xml_doc;

  //  clog << " DeviceClassDescription::ParseXmlContent:: rdf_content ="
  //       << rdf_content << endl;
  // initilize libxml
  xmlInitParser();
  rdf_content_size = strlen(rdf_content);
  xml_doc = xmlParseMemory(rdf_content, rdf_content_size);

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
  clog << "DeviceClassDescription::ParseXmlContent::classType = " << aux
       << "(or " << device_class_type_ << ")" << endl;
  xmlXPathFreeObject(xpathObj);

  // capture min_devices
  xpathObj = xmlXPathEvalExpression(
      reinterpret_cast<const xmlChar*>("//fsmda:minDevices"), xpathCtx);
  assert(xpathObj != NULL);
  nodes = xpathObj->nodesetval;
  assert(nodes->nodeTab[0]);
  aux = (const char*)nodes->nodeTab[0]->children->content;
  min_devices_ = atoi(aux);
  clog << "DeviceClassDescription::ParseXmlContent::minDevices = "
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
  clog << "DeviceClassDescription::ParseXmlContent::maxDevices = "
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
  clog << "DeviceClassDescription::ParseXmlContent::pairingMethod = "
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


DeviceClassDescription::DeviceClassType
DeviceClassDescription::GetDeviceClassTypeByString(const string& str) {
  if (!str.compare(kBaseDeviceString))
    return kBaseDevice;
  else if (!str.compare(kPassiveDeviceString))
    return kPassiveDevice;
  else if (!str.compare(kActiveDeviceString))
    return kActiveDevice;
  else if (!str.compare(kHtmlDeviceString))
    return kHtmlDevice;
  else if (!str.compare(kOnDemandDeviceString))
    return kOnDemandDevice;
  else if (!str.compare(kMediaCaptureDeviceString))
    return kMediaCaptureDevice;
  return kInvalidDevice;
}


DeviceClassDescription::PairingProtocol
DeviceClassDescription::GetPairingProtocolByString(const string& str) {
  if (!str.compare(kUpnpPairingProcotolString))
    return kUpnpPairingProcotol;
  else if (!str.compare(kZeroconfPairingProtocolString))
    return kZeroconfPairingProtocol;
  else
    return kPairingProtocolInvalid;
}


DeviceClassDescription::CommunicationProtocol
DeviceClassDescription::GetCommunicationProtocoByString(
    const string& str) {
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
    case kPassiveDevice:
      return kPassiveDeviceDefaultRdfContent;
      break;
    case kHtmlDevice:
      return kHtmlDeviceDefaultRdfContent;
      break;
    case kOnDemandDevice:
      return kOnDemandDeviceDefaultRdfContent;
      break;
    case kMediaCaptureDevice:
      return kMediCaptureDeviceDefaultRdfContent;
      break;
    default:
      return kInvalidDeviceDefaultRdfContent;
  }
}

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
