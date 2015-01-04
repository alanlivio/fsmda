#ifndef FSMDA_MODEL_DEVICE_PAIRING_API_H_
#define FSMDA_MODEL_DEVICE_PAIRING_API_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include <string>

using std::string;

/*----------------------------------------------------------------------
 |   DevicePairingCpmInterface abstract class
 +---------------------------------------------------------------------*/
class DevicePairingPpmInterface {
 public:
  // public constructors & destructors
  virtual ~DevicePairingPpmInterface() {}

  // public pure virtual methods
  virtual void AddDeviceToClass(const string& application_id,
                                const string& device_address,
                                unsigned int class_index,
                                const string& device_desc) = 0;
  virtual void GetChildIndex(const string& application_id,
                             const string& device_address,
                             unsigned int class_index) = 0;
};

/*----------------------------------------------------------------------
 |   DevicePairingCpmInterface abstract class
 +---------------------------------------------------------------------*/
class DevicePairingCpmInterface {
 public:
  // public constructors & destructors
  virtual ~DevicePairingCpmInterface() {}

  // public pure virtual methods
  virtual void ClassAnnouncement(const string& application_id,
                                 unsigned int class_index,
                                 const string& class_desc,
                                 const string& class_function) = 0;
};

#endif  // FSMDA_MODEL_DEVICE_PAIRING_API_H_
