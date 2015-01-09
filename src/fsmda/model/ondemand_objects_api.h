#ifndef FSMDA_MODEL_ONDEMAND_OBJECTS_API_H_
#define FSMDA_MODEL_ONDEMAND_OBJECTS_API_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/
#include <string>

using std::string;

/*----------------------------------------------------------------------
 |   OnDemandClassListenerInterface abstract class
 +---------------------------------------------------------------------*/
class OnDemandClassListenerInterface {
 public:
  // public constructors & destructors
  virtual ~OnDemandClassListenerInterface() {}

  // public pure virtual methods
  virtual void NotifyOnDemandContent(const string& action,
                                     const string& location) = 0;
};

/*----------------------------------------------------------------------
 |   OnDemandClassInterface abstract class
 +---------------------------------------------------------------------*/
class OnDemandClassInterface {
 public:
  // public constructors & destructors
  virtual ~OnDemandClassInterface() {}
  // public pure virtual methods
  virtual void NotifyError(const string& message, const string& object_id) = 0;
};

#endif  // FSMDA_MODEL_ONDEMAND_OBJECTS_API_H_
