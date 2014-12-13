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
#include <iostream>
#include <string>
#include "fsmda/device_class_description.h"
#include "fsmda/device_description.h"

using std::clog;
using std::endl;
using std::string;

/*----------------------------------------------------------------------
 |   class fields
 +---------------------------------------------------------------------*/
// TODO(alan@telemidia.puc-rio.br): convert to map
const char* DeviceClassDescription::device_class_type_strings_[] = {
    "base", "passive", "active", "html", "ondemand", "mediacapture"};

const char* DeviceClassDescription::pairing_protocol_strings_[] = {"UPnP",
                                                                  "Zeroconf"};
const char* DeviceClassDescription::communication_protocol_strings_[] = {
    "UPnP", "HTTP"};

/*----------------------------------------------------------------------
 |   DeviceClassDescription::DeviceClassDescription
 +---------------------------------------------------------------------*/
DeviceClassDescription::DeviceClassDescription()
    : doc_(NULL),
      device_class_type_(kBaseDevice),
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
  return 0;
}

/*----------------------------------------------------------------------
 |   DeviceClassDescription::InitializeByParseRdfFile
 +---------------------------------------------------------------------*/
int DeviceClassDescription::InitializeByRdfFile(const string& rdf_file) {
  int ret;
  xmlXPathContextPtr xpathCtx;
  xmlXPathObjectPtr xpathObj;
  xmlNodeSetPtr nodes;
  const char* aux;

  // initilize libxml
  xmlInitParser();
  doc_ = xmlParseFile(rdf_file.c_str());
  assert(doc_ != NULL);
  xpathCtx = xmlXPathNewContext(doc_);
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
  device_class_type_ =
      DeviceClassDescription::GetDeviceClassTypeByString(aux);
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
  xmlFreeDoc(doc_);
  xmlCleanupParser();
  xmlMemoryDump();

  initialized_ = true;
  return 0;
}

/*----------------------------------------------------------------------
 |   DeviceClassDescription::GetDeviceClassTypeByString
 +---------------------------------------------------------------------*/
DeviceClassDescription::DeviceClassType
DeviceClassDescription::GetDeviceClassTypeByString(const string& str) {
  if (!str.compare(device_class_type_strings_[kPassiveDevice]))
    return kPassiveDevice;
  else if (!str.compare(device_class_type_strings_[kActiveDevice]))
    return kActiveDevice;
  else if (!str.compare(device_class_type_strings_[kHtmlDevice]))
    return kHtmlDevice;
  else if (!str.compare(device_class_type_strings_[kOnDemandDevice]))
    return kOnDemandDevice;
  else if (!str.compare(device_class_type_strings_[kMediaCaptureDevice]))
    return kMediaCaptureDevice;
  else
    return kBaseDevice;
}

/*----------------------------------------------------------------------
 |   DeviceClassDescription::GetPairingProtocolByString
 +---------------------------------------------------------------------*/
DeviceClassDescription::PairingProtocol
DeviceClassDescription::GetPairingProtocolByString(const std::string& str) {
  if (!str.compare(pairing_protocol_strings_[kUpnpPairingProcotol]))
    return kUpnpPairingProcotol;
  else if (!str.compare(pairing_protocol_strings_[kZeroconfPairingProtocol]))
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
  if (!str.compare(communication_protocol_strings_[kUpnpCommunicationProcotol]))
    return kUpnpCommunicationProcotol;
  else if (!str.compare(
               communication_protocol_strings_[kHTTPCommunicationProtocol]))
    return kHTTPCommunicationProtocol;
  else
    return kCommunicationProtocolInvalid;
}
/*----------------------------------------------------------------------
 |   DeviceClassDescription::GetDeviceClassTypeByString
 +---------------------------------------------------------------------*/
const char* DeviceClassDescription::GetPairingProtocolStringByEnum(
    DeviceClassDescription::PairingProtocol type) {
  switch (type) {
    case kUpnpPairingProcotol:
      return pairing_protocol_strings_[kUpnpPairingProcotol];
      break;
    case kZeroconfPairingProtocol:
      return pairing_protocol_strings_[kZeroconfPairingProtocol];
      break;
    default:
      return pairing_protocol_strings_[kUpnpPairingProcotol];
  }
}

/*----------------------------------------------------------------------
 |   DeviceClassDescription::GetDeviceClassTypeByString
 +---------------------------------------------------------------------*/
const char* DeviceClassDescription::GetCommunicationProtocolStringByEnum(
    DeviceClassDescription::CommunicationProtocol type) {
  switch (type) {
    case kUpnpCommunicationProcotol:
      return communication_protocol_strings_[kUpnpCommunicationProcotol];
      break;
    case kHTTPCommunicationProtocol:
      return communication_protocol_strings_[kHTTPCommunicationProtocol];
      break;
    default:
      return communication_protocol_strings_[kUpnpCommunicationProcotol];
  }
}

/*----------------------------------------------------------------------
 |   DeviceClassDescription::GetDeviceClassTypeStringByEnum
 +---------------------------------------------------------------------*/
const char* DeviceClassDescription::GetDeviceClassTypeStringByEnum(
    DeviceClassDescription::DeviceClassType type) {
  switch (type) {
    case kBaseDevice:
      return device_class_type_strings_[kBaseDevice];
      break;
    case kPassiveDevice:
      return device_class_type_strings_[kPassiveDevice];
      break;
    case kActiveDevice:
      return device_class_type_strings_[kActiveDevice];
      break;
    case kHtmlDevice:
      return device_class_type_strings_[kHtmlDevice];
      break;
    case kOnDemandDevice:
      return device_class_type_strings_[kOnDemandDevice];
      break;
    case kMediaCaptureDevice:
      return device_class_type_strings_[kMediaCaptureDevice];
      break;
    default:
      return device_class_type_strings_[kBaseDevice];
  }
}
