#include <fsmda/gingancl/paring/device_class_description.h>
#include <fsmda/gingancl/paring/device_description.h>
#include <libxml/parser.h>
#include <libxml/xmlmemory.h>
#include <libxml/xmlstring.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <iostream>

using namespace std;

string DeviceClassDescription::deviceClassTypeMap[] =
  { "base", "passive", "active", "html", "ondemand", "mediacapture" };

/*----------------------------------------------------------------------
 |   DeviceClassDescription::DeviceClassDescription
 +---------------------------------------------------------------------*/
DeviceClassDescription::DeviceClassDescription () :
    doc_ (NULL), classType_ (FSDMA_BASE), min_devices_ (0), max_devices_ (0), initialized_ (
	false)
{
}

/*----------------------------------------------------------------------
 |   DeviceClassDescription::~DeviceClassDescription
 +---------------------------------------------------------------------*/
DeviceClassDescription::~DeviceClassDescription ()
{
}

/*----------------------------------------------------------------------
 |   DeviceClassDescription::device_meets_requirements
 +---------------------------------------------------------------------*/
bool
DeviceClassDescription::device_meets_requirements (
    DeviceDescription *device_desc)
{
  if (!initialized_)
    {
      clog << "device_meets_requirements fail: not initialized_" << endl;
      return false;
    }
  else if (this->classType_ != device_desc->classType_)
    {
      clog << "device_meets_requirements fail: classType_" << endl;
      return false;
    }
  else if (this->paringMethod_ != device_desc->paringMethod_)
    {
      clog << "device_meets_requirements fail: paringMethod_" << endl;
      return false;
    }
  else
    return true;
}

/*----------------------------------------------------------------------
 |   DeviceClassDescription::initialize_by_default_device_class
 +---------------------------------------------------------------------*/
int
DeviceClassDescription::initialize_by_default_device_class (
    DeviceClassType classType)
{
  this->classType_ = classType;
  this->min_devices_ = 1;
  this->max_devices_ = UINT_MAX;
  this->paringMethod_ = "UPnP";
  this->initialized_ = true;
  return 0;
}

/*----------------------------------------------------------------------
 |   DeviceClassDescription::initialize_by_parse_rdf_file
 +---------------------------------------------------------------------*/
int
DeviceClassDescription::initialize_by_parse_rdf_file (const string& rdf_file)
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
			    (xmlChar*) "http:// www.ncl.org.br/fsmda");
  assert(ret == 0);

  // capture classType
  xpathObj = xmlXPathEvalExpression ((xmlChar*) "// fsmda:classType", xpathCtx);
  assert(xpathObj != NULL);
  nodes = xpathObj->nodesetval;
  assert(nodes->nodeTab[0]);
  aux = (const char*) nodes->nodeTab[0]->children->content;
  this->classType_ = DeviceClassDescription::get_device_class_type_by_string (
      aux);
  clog << "--->fsmda:classType = " << aux << "(or " << this->classType_ << ")"
      << endl;
  xmlXPathFreeObject (xpathObj);

  // capture min_devices
  xpathObj = xmlXPathEvalExpression ((xmlChar*) "// fsmda:minDevices",
				     xpathCtx);
  assert(xpathObj != NULL);
  nodes = xpathObj->nodesetval;
  assert(nodes->nodeTab[0]);
  aux = (const char*) nodes->nodeTab[0]->children->content;
  this->min_devices_ = atoi (aux);
  clog << "--->fsmda:minDevices = " << this->min_devices_ << endl;
  xmlXPathFreeObject (xpathObj);

  // capture max_devices
  xpathObj = xmlXPathEvalExpression ((xmlChar*) "// fsmda:maxDevices",
				     xpathCtx);
  assert(xpathObj != NULL);
  nodes = xpathObj->nodesetval;
  assert(nodes->nodeTab[0]);
  aux = (const char*) nodes->nodeTab[0]->children->content;
  this->max_devices_ = atoi (aux);
  clog << "--->fsmda:maxDevices = " << this->max_devices_ << endl;
  xmlXPathFreeObject (xpathObj);

  // capture paringMethod
  xpathObj = xmlXPathEvalExpression ((xmlChar*) "// fsmda:pairingMethod",
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

/*----------------------------------------------------------------------
 |   DeviceClassDescription::get_device_class_type_by_string
 +---------------------------------------------------------------------*/
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
