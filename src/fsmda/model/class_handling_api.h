#ifndef FSMDA_MODEL_CLASS_HANDLING_API_H_
#define FSMDA_MODEL_CLASS_HANDLING_API_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include <string>

using std::string;

/*----------------------------------------------------------------------
 |   ClassHandlingPPMInterface abstract class
 +---------------------------------------------------------------------*/
class ParentClassHandlingInterface {
 public:
  // public constructors & destructors
  virtual ~ParentClassHandlingInterface() {}

  // public pure virtual methods
  virtual void AddClass(const string& application_id,
                        unsigned int class_index) = 0;
  virtual void RemoveClass(const string& applicationId,
                           unsigned int classIndex) = 0;
  virtual void AddClassDescription(const string& application_id,
                                   unsigned int class_index,
                                   const string& class_type,
                                   unsigned int max_devices,
                                   unsigned int min_devices,
                                   const string& hardware_requirements,
                                   const string& software_requirements,
                                   const string& network_requirements) = 0;
};

/*----------------------------------------------------------------------
 |   ClassHandlingHPEInterface abstract class
 +---------------------------------------------------------------------*/
class HpeClassHandlingInterface {
 public:
  // public constructors & destructors
  virtual ~HpeClassHandlingInterface() {}

  // public pure virtual methods
  virtual void getClassVariableValue(const string& name,
                                     const string& value) = 0;
  virtual void setClassVariableValue(const string& name,
                                     const string& value) = 0;
};

#endif  // FSMDA_MODEL_CLASS_HANDLING_API_H_
