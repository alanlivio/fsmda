#include "device_class_description.h"

#include <libxml/tree.h>
#include <libxml/xmlmemory.h>
#include <libxml/xmlstring.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include <cassert>
#include <cstdlib>
#include <iostream>

using namespace std;

string DeviceClassDescription::deviceClassTypeMap[] =
  { "base", "passive", "active", "html", "ondemand", "mediacapture" };

DeviceClassDescription::DeviceClassDescription () :
    doc_ (NULL), classType_ (FSDMA_BASE)
{
}

DeviceClassDescription::~DeviceClassDescription ()
{
  // TODO Auto-generated destructor stub
}

int
DeviceClassDescription::parse_rdf_file (const string& rdf_file)
{
  int ret;
  xmlXPathContextPtr xpathCtx;
  xmlXPathObjectPtr xpathObj;
  xmlNodeSetPtr nodes;
  const char* aux;

  //initilize libxml
  xmlInitParser ();
  doc_ = xmlParseFile (rdf_file.c_str ());
  assert(doc_ != NULL);
  xpathCtx = xmlXPathNewContext (this->doc_);
  assert(xpathCtx != NULL);
  ret = xmlXPathRegisterNs (xpathCtx, (xmlChar*) "fsmda",
			    (xmlChar*) "http://www.ncl.org.br/fsmda");
  assert(ret == 0);

  //capture classType
  xpathObj = xmlXPathEvalExpression ((xmlChar*) "//fsmda:classType", xpathCtx);
  assert(xpathObj != NULL);
  nodes = xpathObj->nodesetval;
  assert(nodes->nodeTab[0]);
  aux = (const char*) nodes->nodeTab[0]->children->content;
  this->classType_ = this->get_device_class_type_by_string (aux);
  clog << "--->fsmda:classType = " << aux << "(or " << this->classType_ << ")"
      << endl;
  xmlXPathFreeObject (xpathObj);

  //capture min_devices
  xpathObj = xmlXPathEvalExpression ((xmlChar*) "//fsmda:minDevices", xpathCtx);
  assert(xpathObj != NULL);
  nodes = xpathObj->nodesetval;
  assert(nodes->nodeTab[0]);
  aux = (const char*) nodes->nodeTab[0]->children->content;
  this->min_devices_ = atoi (aux);
  clog << "--->fsmda:minDevices = " << this->min_devices_ << endl;
  xmlXPathFreeObject (xpathObj);

  //capture max_devices
  xpathObj = xmlXPathEvalExpression ((xmlChar*) "//fsmda:maxDevices", xpathCtx);
  assert(xpathObj != NULL);
  nodes = xpathObj->nodesetval;
  assert(nodes->nodeTab[0]);
  aux = (const char*) nodes->nodeTab[0]->children->content;
  this->max_devices_ = atoi (aux);
  clog << "--->fsmda:maxDevices = " << this->max_devices_ << endl;
  xmlXPathFreeObject (xpathObj);

  //capture paringMethod
  xpathObj = xmlXPathEvalExpression ((xmlChar*) "//fsmda:pairingMethod",
				     xpathCtx);
  assert(xpathObj != NULL);
  nodes = xpathObj->nodesetval;
  assert(nodes->nodeTab[0]);
  aux = (const char*) nodes->nodeTab[0]->children->content;
  this->paringMethod_ = this->get_device_class_type_by_string (aux);
  clog << "--->fsmda:pairingMethod = " << aux << endl;
  xmlXPathFreeObject (xpathObj);

  //release libxml
  xmlXPathFreeContext (xpathCtx);
  xmlFreeDoc (doc_);
  xmlCleanupParser ();
  xmlMemoryDump ();

  return 0;
}

DeviceClassDescription::DeviceClassType
DeviceClassDescription::get_device_class_type_by_string (const string& str)

{
  if (!str.compare (
      DeviceClassDescription::deviceClassTypeMap[DeviceClassDescription::FSDMA_PASSIVE]))
    return DeviceClassDescription::FSDMA_PASSIVE;
  else if (!str.compare (
      DeviceClassDescription::deviceClassTypeMap[DeviceClassDescription::FSDMA_ACTIVE]))
    return DeviceClassDescription::FSDMA_ACTIVE;
  else if (!str.compare (
      DeviceClassDescription::deviceClassTypeMap[DeviceClassDescription::FSDMA_HTML]))
    return DeviceClassDescription::FSDMA_HTML;
  else if (!str.compare (
      DeviceClassDescription::deviceClassTypeMap[DeviceClassDescription::FSDMA_ONDEMAND]))
    return DeviceClassDescription::FSDMA_ONDEMAND;
  else if (!str.compare (
      DeviceClassDescription::deviceClassTypeMap[DeviceClassDescription::FSDMA_MEDIACAPTURE]))
    return DeviceClassDescription::FSDMA_MEDIACAPTURE;
  else
    return DeviceClassDescription::FSDMA_BASE;
}
