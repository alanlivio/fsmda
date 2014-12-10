/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include "fsmda/paring/device_class_description.h"
#include "fsmda/paring/device_description.h"
#include "libxml/parser.h"
#include "libxml/tree.h"
#include "libxml/xmlmemory.h"
#include "libxml/xmlstring.h"
#include "libxml/xpath.h"
#include "libxml/xpathInternals.h"
#include <cassert>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <string>

using std::clog;
using std::endl;
using std::string;

/*----------------------------------------------------------------------
 |   class fields
 +---------------------------------------------------------------------*/
const char* DeviceClassDescription::device_class_type_strings_[] = {
    "base", "passive", "active", "html", "ondemand", "mediacapture"};

const char* DeviceClassDescription::paring_protocol_strings_[] = {"Upnp",
                                                                  "Zeroconf"};
const char* DeviceClassDescription::communication_protocol_strings_[] = {
    "Upnp", "HTTP"};

/*----------------------------------------------------------------------
 |   DeviceClassDescription::DeviceClassDescription
 +---------------------------------------------------------------------*/
DeviceClassDescription::DeviceClassDescription()
    : doc_(NULL),
      device_class_type_(kFsmdaBaseDevice),
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
  } else if (this->device_class_type_ != device_desc->device_class_type()) {
    clog << "device_meets_requirements fail: classType_" << endl;
    return false;
  } else if (this->paring_protocol_ != device_desc->paring_method()) {
    clog << "device_meets_requirements fail: paringMethod_" << endl;
    return false;
  } else {
    return true;
  }
}

/*----------------------------------------------------------------------
 |   DeviceClassDescription::InitializeByDefaultDeviceClass
 +---------------------------------------------------------------------*/
int DeviceClassDescription::InitializeByDeviceClass(DeviceClassType type) {
  this->device_class_type_ = type;
  this->min_devices_ = 1;
  this->max_devices_ = UINT_MAX;
  this->paring_protocol_ = DeviceClassDescription::kUpnpParingProcotol;
  this->initialized_ = true;
  return 0;
}

/*----------------------------------------------------------------------
 |   DeviceClassDescription::InitializeByParseRdfFile
 +---------------------------------------------------------------------*/
int DeviceClassDescription::InitializeByParseRdfFile(const string& rdf_file) {
  int ret;
  xmlXPathContextPtr xpathCtx;
  xmlXPathObjectPtr xpathObj;
  xmlNodeSetPtr nodes;
  const char* aux;

  // initilize libxml
  xmlInitParser();
  doc_ = xmlParseFile(rdf_file.c_str());
  assert(doc_ != NULL);
  xpathCtx = xmlXPathNewContext(this->doc_);
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
  this->device_class_type_ =
      DeviceClassDescription::GetDeviceClassTypeByString(aux);
  clog << "DeviceClassDescription::InitializeByParseRdfFile::classType = "
       << aux << "(or " << this->device_class_type_ << ")" << endl;
  xmlXPathFreeObject(xpathObj);

  // capture min_devices
  xpathObj = xmlXPathEvalExpression(
      reinterpret_cast<const xmlChar*>("//fsmda:minDevices"), xpathCtx);
  assert(xpathObj != NULL);
  nodes = xpathObj->nodesetval;
  assert(nodes->nodeTab[0]);
  aux = (const char*)nodes->nodeTab[0]->children->content;
  this->min_devices_ = atoi(aux);
  clog << "DeviceClassDescription::InitializeByParseRdfFile::minDevices = "
       << this->min_devices_ << endl;
  xmlXPathFreeObject(xpathObj);

  // capture max_devices
  xpathObj = xmlXPathEvalExpression(
      reinterpret_cast<const xmlChar*>("//fsmda:maxDevices"), xpathCtx);
  assert(xpathObj != NULL);
  nodes = xpathObj->nodesetval;
  assert(nodes->nodeTab[0]);
  aux = (const char*)nodes->nodeTab[0]->children->content;
  this->max_devices_ = atoi(aux);
  clog << "DeviceClassDescription::InitializeByParseRdfFile::maxDevices = "
       << this->max_devices_ << endl;
  xmlXPathFreeObject(xpathObj);

  // capture paringMethod
  xpathObj = xmlXPathEvalExpression(
      reinterpret_cast<const xmlChar*>("//fsmda:pairingMethod"), xpathCtx);
  assert(xpathObj != NULL);
  nodes = xpathObj->nodesetval;
  assert(nodes->nodeTab[0]);
  this->paring_protocol_ = DeviceClassDescription::GetParingProtocolByString(
      (const char*)nodes->nodeTab[0]->children->content);
  clog << "DeviceClassDescription::InitializeByParseRdfFile::pairingMethod = "
       << this->paring_protocol_ << endl;
  xmlXPathFreeObject(xpathObj);

  // release libxml
  xmlXPathFreeContext(xpathCtx);
  xmlFreeDoc(doc_);
  xmlCleanupParser();
  xmlMemoryDump();

  this->initialized_ = true;
  return 0;
}

/*----------------------------------------------------------------------
 |   DeviceClassDescription::GetDeviceClassTypeByString
 +---------------------------------------------------------------------*/
DeviceClassDescription::DeviceClassType
DeviceClassDescription::GetDeviceClassTypeByString(const string& str) {
  if (!str.compare(device_class_type_strings_[kFsmdaPassiveDevice]))
    return kFsmdaPassiveDevice;
  else if (!str.compare(device_class_type_strings_[kFsmdaActiveDevice]))
    return kFsmdaActiveDevice;
  else if (!str.compare(device_class_type_strings_[kFsmdaHtmlDevice]))
    return kFsmdaHtmlDevice;
  else if (!str.compare(device_class_type_strings_[kFsmdaOnDemandDevice]))
    return kFsmdaOnDemandDevice;
  else if (!str.compare(device_class_type_strings_[kFsmdaMediaCaptureDevice]))
    return kFsmdaMediaCaptureDevice;
  else
    return kFsmdaBaseDevice;
}

/*----------------------------------------------------------------------
 |   DeviceClassDescription::GetParingProtocolByString
 +---------------------------------------------------------------------*/
DeviceClassDescription::ParingProtocol
DeviceClassDescription::GetParingProtocolByString(const std::string& str) {
  if (!str.compare(paring_protocol_strings_[kUpnpParingProcotol]))
    return kUpnpParingProcotol;
  else if (!str.compare(paring_protocol_strings_[kZeroconfParingProtocol]))
    return kZeroconfParingProtocol;
  else
    return kParingProtocolInvalid;
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
const char* DeviceClassDescription::GetParingProtocolStringByEnum(
    DeviceClassDescription::ParingProtocol type) {
  switch (type) {
    case kUpnpParingProcotol:
      return paring_protocol_strings_[kUpnpParingProcotol];
      break;
    case kZeroconfParingProtocol:
      return paring_protocol_strings_[kZeroconfParingProtocol];
      break;
    default:
      return paring_protocol_strings_[kUpnpParingProcotol];
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
    case kFsmdaBaseDevice:
      return device_class_type_strings_[kFsmdaBaseDevice];
      break;
    case kFsmdaPassiveDevice:
      return device_class_type_strings_[kFsmdaPassiveDevice];
      break;
    case kFsmdaActiveDevice:
      return device_class_type_strings_[kFsmdaActiveDevice];
      break;
    case kFsmdaHtmlDevice:
      return device_class_type_strings_[kFsmdaHtmlDevice];
      break;
    case kFsmdaOnDemandDevice:
      return device_class_type_strings_[kFsmdaOnDemandDevice];
      break;
    case kFsmdaMediaCaptureDevice:
      return device_class_type_strings_[kFsmdaMediaCaptureDevice];
      break;
    default:
      return device_class_type_strings_[kFsmdaBaseDevice];
  }
}
