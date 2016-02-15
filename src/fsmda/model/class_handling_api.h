#ifndef FSMDA_MODEL_CLASS_HANDLING_API_H_
#define FSMDA_MODEL_CLASS_HANDLING_API_H_

#include <string>

using std::string;

class HpeClassHandlingInterface {
 public:
  // public constructors & destructors
  virtual ~HpeClassHandlingInterface() {
  }

  // public pure virtual methods
  virtual void get_class_variable_value(const string& name,
                                        const string& value) = 0;
  virtual void set_class_variable_value(const string& name,
                                        const string& value) = 0;
};

class ParentClassHandlingInterface {
 public:
  // public constructors & destructors
  virtual ~ParentClassHandlingInterface() {
  }

  // public pure virtual methods
  virtual void add_class(const string& application_id,
                         unsigned int class_index) = 0;
  virtual void remove_class(const string& application_id,
                            unsigned int class_index) = 0;
  virtual void add_class_description(const string& application_id,
                                     unsigned int class_index,
                                     const string& class_type,
                                     unsigned int max_devices,
                                     unsigned int min_devices,
                                     const string& hardware_requirements,
                                     const string& software_requirements,
                                     const string& network_requirements) = 0;
  virtual void set_class_handling_hpe(const string& application_id,
                                      HpeClassHandlingInterface* hpe) = 0;
};

#endif  // FSMDA_MODEL_CLASS_HANDLING_API_H_
