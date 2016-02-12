#ifndef FSMDA_MODEL_PASSIVE_OBJECTS_API_H_
#define FSMDA_MODEL_PASSIVE_OBJECTS_API_H_

#include <string>

using std::string;

class PassiveClassInterface {
 public:
  // public constructors & destructors
  virtual ~PassiveClassInterface() {}

  // public pure virtual methods
  virtual void prepare(const string& position) = 0;
  virtual void send_content(char* content) = 0;
};

class PassiveClassListenerInterface {
 public:
  // public constructors & destructors
  virtual ~PassiveClassListenerInterface() {}

  // public pure virtual methods
  virtual void notify_error(const string& message, const string& object_id) = 0;
};

#endif  // FSMDA_MODEL_PASSIVE_OBJECTS_API_H_
