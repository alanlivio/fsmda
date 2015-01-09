#ifndef FSMDA_MODEL_PASSIVE_OBJECTS_API_H_
#define FSMDA_MODEL_PASSIVE_OBJECTS_API_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/
#include <string>

using std::string;

/*----------------------------------------------------------------------
 |   PassiveClassInterface abstract class
 +---------------------------------------------------------------------*/
class PassiveClassInterface {
 public:
  // public constructors & destructors
  virtual ~PassiveClassInterface() {}

  // public pure virtual methods
  virtual void Prepare(const string& position) = 0;
  virtual void SendContent(char* content) = 0;
};

/*----------------------------------------------------------------------
 |   PassiveClassListenerInterface abstract class
 +---------------------------------------------------------------------*/
class PassiveClassListenerInterface {
 public:
  // public constructors & destructors
  virtual ~PassiveClassListenerInterface() {}

  // public pure virtual methods
  virtual void NotifyError(const string& message, const string& object_id) = 0;
};

#endif  // FSMDA_MODEL_PASSIVE_OBJECTS_API_H_
