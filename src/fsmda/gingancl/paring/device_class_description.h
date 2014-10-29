#ifndef FSMDA_GINGANCL_PARING_DEVICE_CLASS_DESCRIPTION_H_
#define FSMDA_GINGANCL_PARING_DEVICE_CLASS_DESCRIPTION_H_

#include <fsmda/gingancl/paring/device_description.h>
#include <string>
using namespace std;

class DeviceClassDescription
{
public:
  DeviceClassDescription (DeviceClassType deviceClassType);
  DeviceClassDescription (const string&  rdf_file);
  virtual
  ~DeviceClassDescription ();

  bool
  device_meets_requirements (DeviceDescription device_desc);
private:
  string
  execute_xpath_expression (const string&  xpathExpr);
};
#endif /* FSMDA_GINGANCL_PARING_DEVICE_CLASS_DESCRIPTION_H_ */
