#ifndef FSMDA_MODEL_ONDEMAND_OBJECTS_API_H_
#define FSMDA_MODEL_ONDEMAND_OBJECTS_API_H_

#include <string>

using std::string;

class OnDemandClassListenerInterface {
 public:
  // public constructors & destructors
  virtual ~OnDemandClassListenerInterface() {}

  // public pure virtual methods
  virtual void notify_ondemand_content(const string& action,
                                       const string& location) = 0;
};

class OnDemandClassInterface {
 public:
  // public constructors & destructors
  virtual ~OnDemandClassInterface() {}
  // public pure virtual methods
  virtual void notify_error(const string& message, const string& object_id) = 0;
};

#endif  // FSMDA_MODEL_ONDEMAND_OBJECTS_API_H_
