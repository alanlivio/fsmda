#ifndef FSMDA_GINGANCL_PARING_DEVICE_DESCRIPTION_H_
#define FSMDA_GINGANCL_PARING_DEVICE_DESCRIPTION_H_

#include <string>

using namespace std;

class DeviceDescription
{
public:
  DeviceDescription ();
  virtual
  ~DeviceDescription ();
  int
  parse_rdf_file (const string& rdf_file);
};

#endif /* FSMDA_GINGANCL_PARING_DEVICE_DESCRIPTION_H_ */
