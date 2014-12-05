#ifndef FSMDA_COMMUNICATION_MODEL_PASSIVE_OBJECT_INTERFACES_H_
#define FSMDA_COMMUNICATION_MODEL_PASSIVE_OBJECT_INTERFACES_H_

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
  virtual
  // public constructors & destructors
  ~PassiveCcmInterface() {
  }
  // public pure virtual methods
  virtual void
  prepare(const string& position)=0;
  virtual void
  sendContent(char* content)=0;
};

/*----------------------------------------------------------------------
 |   PassivePcmInterface abstract class
 +---------------------------------------------------------------------*/
class PassivePcmInterface {
 public:
  virtual
  // public constructors & destructors
  ~PassivePcmInterface() {
  }

  // public pure virtual methods
  virtual void
  notifyError(const string& message, const string& objectId)=0;
};

#endif  // FSMDA_COMMUNICATION_MODEL_PASSIVE_OBJECT_INTERFACES_H_
