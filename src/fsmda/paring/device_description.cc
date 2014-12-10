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
#include <iostream>
#include <string>

using std::clog;
using std::endl;

/*----------------------------------------------------------------------
 |   DeviceDescription::DeviceDescription
 +---------------------------------------------------------------------*/
DeviceDescription::DeviceDescription()
    : doc_(NULL),
      class_type_(DeviceClassDescription::kFsmdaBaseDevice),
      initialized_(false) {}

/*----------------------------------------------------------------------
 |   DeviceDescription::~DeviceDescription
 +---------------------------------------------------------------------*/
DeviceDescription::~DeviceDescription() {}

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
  clog << "--->fsmda:classType = " << aux << "(or " << this->class_type_ << ")"
       << endl;
  xmlXPathFreeObject(xpathObj);

  // capture paringMethod
  xpathObj = xmlXPathEvalExpression(
      reinterpret_cast<const xmlChar*>("//fsmda:pairingMethod"), xpathCtx);
  assert(xpathObj != NULL);
  nodes = xpathObj->nodesetval;
  assert(nodes->nodeTab[0]);
  this->paring_method_ = (const char*)nodes->nodeTab[0]->children->content;
  clog << "--->fsmda:pairingMethod = " << this->paring_method_ << endl;
  xmlXPathFreeObject(xpathObj);

  // release libxml
  xmlXPathFreeContext(xpathCtx);
  xmlFreeDoc(doc_);
  xmlCleanupParser();
  xmlMemoryDump();

  this->initialized_ = true;
  return 0;
}
