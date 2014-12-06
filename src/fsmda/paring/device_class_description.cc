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

/*----------------------------------------------------------------------
 |   class fields
 +---------------------------------------------------------------------*/
const char* DeviceClassDescription::deviceClassTypeMap_[] = { "base", "passive",
    "active", "html", "ondemand", "mediacapture" };

/*----------------------------------------------------------------------
 |   DeviceClassDescription::DeviceClassDescription
 +---------------------------------------------------------------------*/
DeviceClassDescription::DeviceClassDescription()
    : doc_(NULL),
      classType_(kFsmdaBaseDevice),
      min_devices_(0),
      max_devices_(0),
      initialized_(false) {
}

/*----------------------------------------------------------------------
 |   DeviceClassDescription::~DeviceClassDescription
 +---------------------------------------------------------------------*/
DeviceClassDescription::~DeviceClassDescription() {
}

/*----------------------------------------------------------------------
 |   DeviceClassDescription::DeviceMeetRequirements
 +---------------------------------------------------------------------*/
bool DeviceClassDescription::DeviceMeetRequirements(
    DeviceDescription* device_desc) {
  if (!initialized_) {
    clog << "device_meets_requirements fail: not initialized_" << endl;
    return false;
  } else if (this->classType_ != device_desc->classType_) {
    clog << "device_meets_requirements fail: classType_" << endl;
    return false;
  } else if (this->paringMethod_ != device_desc->paringMethod_) {
    clog << "device_meets_requirements fail: paringMethod_" << endl;
    return false;
  } else {
    return true;
  }
}

/*----------------------------------------------------------------------
 |   DeviceClassDescription::InitializeByDefaultDeviceClass
 +---------------------------------------------------------------------*/
int DeviceClassDescription::InitializeByDefaultDeviceClass(
    DeviceClassType type) {
  this->classType_ = type;
  this->min_devices_ = 1;
  this->max_devices_ = UINT_MAX;
  this->paringMethod_ = "UPnP";
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
  aux = (const char*) nodes->nodeTab[0]->children->content;
  this->classType_ = DeviceClassDescription::GetDeviceClassTypeByString(aux);
  clog << "--->fsmda:classType = " << aux << "(or " << this->classType_ << ")"
       << endl;
  xmlXPathFreeObject(xpathObj);

  // capture min_devices
  xpathObj = xmlXPathEvalExpression(
      reinterpret_cast<const xmlChar*>("//fsmda:minDevices"), xpathCtx);
  assert(xpathObj != NULL);
  nodes = xpathObj->nodesetval;
  assert(nodes->nodeTab[0]);
  aux = (const char*) nodes->nodeTab[0]->children->content;
  this->min_devices_ = atoi(aux);
  clog << "--->fsmda:minDevices = " << this->min_devices_ << endl;
  xmlXPathFreeObject(xpathObj);

  // capture max_devices
  xpathObj = xmlXPathEvalExpression(
      reinterpret_cast<const xmlChar*>("//fsmda:maxDevices"), xpathCtx);
  assert(xpathObj != NULL);
  nodes = xpathObj->nodesetval;
  assert(nodes->nodeTab[0]);
  aux = (const char*) nodes->nodeTab[0]->children->content;
  this->max_devices_ = atoi(aux);
  clog << "--->fsmda:maxDevices = " << this->max_devices_ << endl;
  xmlXPathFreeObject(xpathObj);

  // capture paringMethod
  xpathObj = xmlXPathEvalExpression(
      reinterpret_cast<const xmlChar*>("//fsmda:pairingMethod"), xpathCtx);
  assert(xpathObj != NULL);
  nodes = xpathObj->nodesetval;
  assert(nodes->nodeTab[0]);
  this->paringMethod_ = (const char*) nodes->nodeTab[0]->children->content;
  clog << "--->fsmda:pairingMethod = " << this->paringMethod_ << endl;
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
DeviceClassDescription::DeviceClassType DeviceClassDescription::GetDeviceClassTypeByString(
    const string& str) {
  if (!str.compare(deviceClassTypeMap_[kFsmdaPassiveDevice]))
    return kFsmdaPassiveDevice;
  else if (!str.compare(deviceClassTypeMap_[kFsmdaActiveDevice]))
    return kFsmdaActiveDevice;
  else if (!str.compare(deviceClassTypeMap_[kFsmdaHtmlDevice]))
    return kFsmdaHtmlDevice;
  else if (!str.compare(deviceClassTypeMap_[kFsmdaOnDemandDevice]))
    return kFsmdaOnDemandDevice;
  else if (!str.compare(deviceClassTypeMap_[kFsmdaMediaCaptureDevice]))
    return kFsmdaMediaCaptureDevice;
  else
    return kFsmdaBaseDevice;
}
