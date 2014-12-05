#ifndef FSMDA_PARING_MODEL_DEVICE_PARING_INTERFACES_H_
#define FSMDA_PARING_MODEL_DEVICE_PARING_INTERFACES_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include <string>

using std::string;

/*----------------------------------------------------------------------
 |   DeviceParingCpmInterface abstract class
 +---------------------------------------------------------------------*/
class DeviceParingPpmInterface {
 public:
  // public constructors & destructors
  virtual ~DeviceParingPpmInterface() {
  }

  // public pure virtual methods
  virtual void AddDeviceToClass(const string& application_id,
                                const string& device_address,
                                unsigned int class_index,
                                const string& device_desc)=0;
  virtual void GetChildIndex(const string& application_id,
                             const string& device_address,
                             unsigned int class_index)=0;
};

/*----------------------------------------------------------------------
 |   DeviceParingCpmInterface abstract class
 +---------------------------------------------------------------------*/
class DeviceParingCpmInterface {
 public:
  // public constructors & destructors
  virtual ~DeviceParingCpmInterface() {
  }

  // public pure virtual methods
  virtual void ClassAnnouncement(const string& application_id,
                                 unsigned int class_index,
                                 const string& class_desc,
                                 const string& class_function)=0;
};

#endif  // FSMDA_PARING_MODEL_DEVICE_PARING_INTERFACES_H_
