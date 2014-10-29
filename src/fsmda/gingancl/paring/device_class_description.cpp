#include "device_class_description.h"

#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlmemory.h>
#include <libxml/xpath.h>
#include <cassert>

DeviceClassDescription::DeviceClassDescription (DeviceClassType deviceClassType)
{
}

DeviceClassDescription::DeviceClassDescription (const string& rdf_file)
{
  xmlInitParser ();
  xmlDocPtr doc;
  xmlXPathContextPtr xpathCtx;
  xmlXPathObjectPtr xpathObj;
  doc = xmlParseFile (rdf_file.c_str());
  assert (doc != NULL);

  xmlCleanupParser ();

  xmlMemoryDump ();
}

DeviceClassDescription::~DeviceClassDescription ()
{
  // TODO Auto-generated destructor stub
}

string
DeviceClassDescription::execute_xpath_expression (const string& xpathExpr)
{

  return string("path");
}
