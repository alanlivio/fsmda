#ifndef FSMDA_GINGANCL_PARING_DEVICE_DESCRIPTION_H_
#define FSMDA_GINGANCL_PARING_DEVICE_DESCRIPTION_H_

#include <string>
using namespace std;

enum DeviceClassType
{
  PASSIVE, ACTIVE, HTML, ONDEMAND, MEDIACAPTURE
};

class DeviceDescription
{
public:
  DeviceDescription (string rdf_file);
  virtual
  ~DeviceDescription ();

};

#endif /* FSMDA_GINGANCL_PARING_DEVICE_DESCRIPTION_H_ */
