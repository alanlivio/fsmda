#ifndef FSMDA_MODEL_PASSIVE_OBJECTS_API_H_
#define FSMDA_MODEL_PASSIVE_OBJECTS_API_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/
#include <string>

using std::string;

/*----------------------------------------------------------------------
 |   PassiveCcmInterface abstract class
 +---------------------------------------------------------------------*/
class PassiveCcmInterface {
 public:
  // public constructors & destructors
  virtual ~PassiveCcmInterface() {}

  // public pure virtual methods
  virtual void Prepare(const string& position) = 0;
  virtual void SendContent(char* content) = 0;
};

/*----------------------------------------------------------------------
 |   PassivePcmInterface abstract class
 +---------------------------------------------------------------------*/
class PassivePcmInterface {
 public:
  // public constructors & destructors
  virtual ~PassivePcmInterface() {}

  // public pure virtual methods
  virtual void NotifyError(const string& message, const string& object_id) = 0;
};

#endif  // FSMDA_MODEL_PASSIVE_OBJECTS_API_H_
