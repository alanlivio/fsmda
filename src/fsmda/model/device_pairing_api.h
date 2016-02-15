#ifndef FSMDA_MODEL_DEVICE_PAIRING_API_H_
#define FSMDA_MODEL_DEVICE_PAIRING_API_H_

#include <string>

using std::string;

class ParentPairingInterface {
 public:
  // public constructors & destructors
  virtual ~ParentPairingInterface() {
  }

  // public pure virtual methods
  virtual void add_device_to_class(const string& application_id,
                                   const string& device_address,
                                   unsigned int class_index,
                                   const string& device_desc) = 0;
  virtual void get_child_index(const string& application_id,
                               const string& device_address,
                               unsigned int class_index) = 0;
};

class ChildPairingInterface {
 public:
  // public constructors & destructors
  virtual ~ChildPairingInterface() {
  }

  // public pure virtual methods
  virtual void class_announcement(const string& application_id,
                                  unsigned int class_index,
                                  const string& class_desc,
                                  const string& class_function) = 0;
};

#endif  // FSMDA_MODEL_DEVICE_PAIRING_API_H_
