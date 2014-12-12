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
#include <iostream>
#include <string>
#include "fsmda/device_class_description.h"
#include "fsmda/device_description.h"

using std::clog;
using std::endl;

/*----------------------------------------------------------------------
 |   DeviceDescription::DeviceDescription
 +---------------------------------------------------------------------*/
DeviceDescription::DeviceDescription()
    : doc_(NULL),
      class_type_(DeviceClassDescription::kBaseDevice),
      initialized_(false) {}

/*----------------------------------------------------------------------
 |   DeviceDescription::~DeviceDescription
 +---------------------------------------------------------------------*/
DeviceDescription::~DeviceDescription() {}

/*----------------------------------------------------------------------
 |   DeviceDescription::InitializeByDeviceClass
 +---------------------------------------------------------------------*/
int DeviceDescription::InitializeByDeviceClass(
    DeviceClassDescription::DeviceClassType device_class_type) {
  class_type_ = device_class_type;
  pairing_method_ = DeviceClassDescription::kUpnpPairingProcotol;
  initialized_ = true;
}

/*----------------------------------------------------------------------
 |   DeviceDescription::InitializeByRdfFile
 +---------------------------------------------------------------------*/
int DeviceDescription::InitializeByRdfFile(const string& rdf_file) {
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
  this->class_type_ = DeviceClassDescription::GetDeviceClassTypeByString(aux);
  clog << "DeviceDescription::InitializeByRdfFile::classType = " << aux
       << "(or " << this->class_type_ << ")" << endl;
  xmlXPathFreeObject(xpathObj);

  // capture pairingMethod
  xpathObj = xmlXPathEvalExpression(
      reinterpret_cast<const xmlChar*>("//fsmda:pairingMethod"), xpathCtx);
  assert(xpathObj != NULL);
  nodes = xpathObj->nodesetval;
  assert(nodes->nodeTab[0]);
  this->pairing_method_ = DeviceClassDescription::GetPairingProtocolByString(
      (const char*)nodes->nodeTab[0]->children->content);
  clog << "DeviceDescription::InitializeByRdfFile::pairingMethod = "
       << this->pairing_method_ << endl;
  xmlXPathFreeObject(xpathObj);

  // release libxml
  xmlXPathFreeContext(xpathCtx);
  xmlFreeDoc(doc_);
  xmlCleanupParser();
  xmlMemoryDump();

  this->initialized_ = true;
  return 0;
}
