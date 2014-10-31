/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include "fsmda/paringmanager/device_class_description.h"
#include "fsmda/paringmanager/device_description.h"
#include "libxml/parser.h"
#include "libxml/tree.h"
#include "libxml/xmlmemory.h"
#include "libxml/xmlstring.h"
#include "libxml/xpath.h"
#include "libxml/xpathInternals.h"
#include <cassert>
#include <string>
#include <iostream>

/*----------------------------------------------------------------------
 |   DeviceDescription::DeviceDescription
 +---------------------------------------------------------------------*/
DeviceDescription::DeviceDescription () :
    doc_ (NULL), classType_ (DeviceClassDescription::FSDMA_BASE), initialized_ (
	false)
{
}

/*----------------------------------------------------------------------
 |   DeviceDescription::~DeviceDescription
 +---------------------------------------------------------------------*/
DeviceDescription::~DeviceDescription ()
{
}

/*----------------------------------------------------------------------
 |   DeviceDescription::get_device_class_type_by_string
 +---------------------------------------------------------------------*/
int
DeviceDescription::initialize_by_rdf_file (const string& rdf_file)
{
  int ret;
  xmlXPathContextPtr xpathCtx;
  xmlXPathObjectPtr xpathObj;
  xmlNodeSetPtr nodes;
  const char* aux;

  // initilize libxml
  xmlInitParser ();
  doc_ = xmlParseFile (rdf_file.c_str ());
  assert(doc_ != NULL);
  xpathCtx = xmlXPathNewContext (this->doc_);
  assert(xpathCtx != NULL);
  ret = xmlXPathRegisterNs (xpathCtx, (xmlChar*) "fsmda",
			    (xmlChar*) "http://www.ncl.org.br/fsmda");
  assert(ret == 0);

  // capture classType
  xpathObj = xmlXPathEvalExpression ((xmlChar*) "//fsmda:classType", xpathCtx);
  assert(xpathObj != NULL);
  nodes = xpathObj->nodesetval;
  assert(nodes->nodeTab[0]);
  aux = (const char*) nodes->nodeTab[0]->children->content;
  this->classType_ = DeviceClassDescription::get_device_class_type_by_string (
      aux);
  clog << "--->fsmda:classType = " << aux << "(or " << this->classType_ << ")"
      << endl;
  xmlXPathFreeObject (xpathObj);

  // capture paringMethod
  xpathObj = xmlXPathEvalExpression ((xmlChar*) "//fsmda:pairingMethod",
				     xpathCtx);
  assert(xpathObj != NULL);
  nodes = xpathObj->nodesetval;
  assert(nodes->nodeTab[0]);
  this->paringMethod_ = (const char*) nodes->nodeTab[0]->children->content;
  clog << "--->fsmda:pairingMethod = " << this->paringMethod_ << endl;
  xmlXPathFreeObject (xpathObj);

  // release libxml
  xmlXPathFreeContext (xpathCtx);
  xmlFreeDoc (doc_);
  xmlCleanupParser ();
  xmlMemoryDump ();

  this->initialized_ = true;
  return 0;
}

