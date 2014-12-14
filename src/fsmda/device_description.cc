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

/*----------------------------------------------------------------------
 |   DeviceDescription::DeviceDescription
 +---------------------------------------------------------------------*/
DeviceDescription::DeviceDescription()
    : doc_(NULL),
      rdf_content_(""),
      device_class_type_(DeviceClassDescription::kBaseDevice),
      initialized_(false) {}

/*----------------------------------------------------------------------
 |   DeviceDescription::~DeviceDescription
 +---------------------------------------------------------------------*/
DeviceDescription::~DeviceDescription() {}

/*----------------------------------------------------------------------
 |   DeviceDescription::InitializeByDeviceClass
 +---------------------------------------------------------------------*/
int DeviceDescription::InitializeByDeviceClass(DeviceClassDescription::DeviceClassType type) {

  const char* rdf_content_aux = DeviceClassDescription::GetDeviceClassRdfDefaultContentByType(type);
  if (ParseXmlContent(rdf_content_aux) == 0) {
    rdf_content_ = rdf_content_aux;
    initialized_ = true;
    return 0;
  } else
    return -1;
}

/*----------------------------------------------------------------------
 |   DeviceDescription::InitializeByRdfContent
 +---------------------------------------------------------------------*/
int DeviceDescription::InitializeByRdfContent(const char* content) {
  // parse file
  if (ParseXmlContent(content) == 0) {
    rdf_content_ = content;
    initialized_ = true;
    return 0;
  } else
    return -1;
}

/*----------------------------------------------------------------------
 |   DeviceDescription::InitializeByRdfFile
 +---------------------------------------------------------------------*/
int DeviceDescription::InitializeByRdfFile(const string& rdf_file_path) {

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
  } else
    return -1;
}

/*----------------------------------------------------------------------
 |   DeviceDescription::ParseXmlContent
 +---------------------------------------------------------------------*/
int DeviceDescription::ParseXmlContent(const char* rdf_content) {
  int ret;
  unsigned int rdf_content_size;
  const char* aux;
  xmlXPathContextPtr xpathCtx;
  xmlXPathObjectPtr xpathObj;
  xmlNodeSetPtr nodes;
  xmlDocPtr xml_doc;

  //  clog << " DeviceDescription::ParseXmlContent:: rdf_content ="
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
  clog << "DeviceDescription::ParseXmlContent::classType = " << aux << "(or "
       << device_class_type_ << ")" << endl;
  xmlXPathFreeObject(xpathObj);

  // capture pairingMethod
  xpathObj = xmlXPathEvalExpression(
      reinterpret_cast<const xmlChar*>("//fsmda:pairingMethod"), xpathCtx);
  assert(xpathObj != NULL);
  nodes = xpathObj->nodesetval;
  assert(nodes->nodeTab[0]);
  pairing_protocol_ = DeviceClassDescription::GetPairingProtocolByString(
      (const char*)nodes->nodeTab[0]->children->content);
  clog << "DeviceDescription::ParseXmlContent::pairingMethod = "
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

///*----------------------------------------------------------------------
// |   DeviceDescription::InitializeByDeviceClass
// +---------------------------------------------------------------------*/
// int DeviceDescription::InitializeByDeviceClass(
//    DeviceClassDescription::DeviceClassType device_class_type) {
//  class_type_ = device_class_type;
//  pairing_method_ = DeviceClassDescription::kUpnpPairingProcotol;
//  initialized_ = true;
//}

///*----------------------------------------------------------------------
// |   DeviceDescription::InitializeByRdfFile
// +---------------------------------------------------------------------*/
// int DeviceDescription::InitializeByRdfFile(const string& rdf_file) {
//  int ret;
//  xmlXPathContextPtr xpathCtx;
//  xmlXPathObjectPtr xpathObj;
//  xmlNodeSetPtr nodes;
//  const char* aux;

//  // initilize libxml
//  xmlInitParser();
//  doc_ = xmlParseFile(rdf_file.c_str());
//  assert(doc_ != NULL);
//  xpathCtx = xmlXPathNewContext(doc_);
//  assert(xpathCtx != NULL);
//  ret = xmlXPathRegisterNs(
//      xpathCtx, reinterpret_cast<const xmlChar*>("fsmda"),
//      reinterpret_cast<const xmlChar*>("http://www.ncl.org.br/fsmda"));
//  assert(ret == 0);

//  // capture classType
//  xpathObj = xmlXPathEvalExpression(
//      reinterpret_cast<const xmlChar*>("//fsmda:classType"), xpathCtx);
//  assert(xpathObj != NULL);
//  nodes = xpathObj->nodesetval;
//  assert(nodes->nodeTab[0]);
//  aux = (const char*)nodes->nodeTab[0]->children->content;
//  class_type_ = DeviceClassDescription::GetDeviceClassTypeByString(aux);
//  clog << "DeviceDescription::InitializeByRdfFile::classType = " << aux
//       << "(or " << class_type_ << ")" << endl;
//  xmlXPathFreeObject(xpathObj);

//  // capture pairingMethod
//  xpathObj = xmlXPathEvalExpression(
//      reinterpret_cast<const xmlChar*>("//fsmda:pairingMethod"), xpathCtx);
//  assert(xpathObj != NULL);
//  nodes = xpathObj->nodesetval;
//  assert(nodes->nodeTab[0]);
//  pairing_method_ = DeviceClassDescription::GetPairingProtocolByString(
//      (const char*)nodes->nodeTab[0]->children->content);
//  clog << "DeviceDescription::InitializeByRdfFile::pairingMethod = "
//       << pairing_method_ << endl;
//  xmlXPathFreeObject(xpathObj);

//  // release libxml
//  xmlXPathFreeContext(xpathCtx);
//  xmlFreeDoc(doc_);
//  xmlCleanupParser();
//  xmlMemoryDump();

//  initialized_ = true;
//  return 0;
//}
