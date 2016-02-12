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

DeviceDescription::DeviceDescription()
    : doc_(NULL),
      rdf_content_(""),
      device_class_type_(DeviceClassDescription::kBaseDevice),
      initialized_(false) {}

DeviceDescription::~DeviceDescription() {}

int DeviceDescription::initialize_by_device_class(
    DeviceClassDescription::DeviceClassType type) {
  const char* rdf_content_aux =
      DeviceClassDescription::to_device_class_rdf_content(type);
  if (parse_xml_content(rdf_content_aux) == 0) {
    rdf_content_ = rdf_content_aux;
    initialized_ = true;
    return 0;
  } else {
    return -1;
  }
}

int DeviceDescription::initialize_by_rdf_content(const char* content) {
  // parse file
  if (parse_xml_content(content) == 0) {
    rdf_content_ = content;
    initialized_ = true;
    return 0;
  } else {
    return -1;
  }
}

int DeviceDescription::initialize_by_rdf_file(const string& rdf_file_path) {
  std::ifstream t;
  t.open(rdf_file_path.c_str());
  std::stringstream contents;
  contents << t.rdbuf();

  //  clog << " DeviceClassDescription::InitializeByRdfFile:: contents ="
  //       << contents.str().c_str() << endl;
  if (parse_xml_content(contents.str().c_str()) == 0) {
    initialized_ = true;
    rdf_content_ = contents.str().c_str();
    return 0;
  } else {
    return -1;
  }
}

int DeviceDescription::parse_xml_content(const char* rdf_content) {
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
  xml_doc          = xmlParseMemory(rdf_content, rdf_content_size);

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
  aux                = (const char*)nodes->nodeTab[0]->children->content;
  device_class_type_ = DeviceClassDescription::to_device_class_type(aux);
  clog << "DeviceDescription::ParseXmlContent::classType = " << aux << "(or "
       << device_class_type_ << ")" << endl;
  xmlXPathFreeObject(xpathObj);

  // capture pairingMethod
  xpathObj = xmlXPathEvalExpression(
      reinterpret_cast<const xmlChar*>("//fsmda:pairingMethod"), xpathCtx);
  assert(xpathObj != NULL);
  nodes = xpathObj->nodesetval;
  assert(nodes->nodeTab[0]);
  pairing_protocol_ = DeviceClassDescription::to_pairing_protocol(
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

DeviceClassDescription::DeviceClassType DeviceDescription::device_class_type() {
  return device_class_type_;
}

DeviceClassDescription::PairingProtocol DeviceDescription::pairing_method() {
  return pairing_protocol_;
}

const string DeviceDescription::rdf_content() { return rdf_content_; }

bool DeviceDescription::initialized() { return initialized_; }
