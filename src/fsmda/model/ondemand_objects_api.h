#ifndef FSMDA_MODEL_ONDEMAND_OBJECTS_API_H_
#define FSMDA_MODEL_ONDEMAND_OBJECTS_API_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/
#include <string>

using std::string;

/*----------------------------------------------------------------------
 |   OnDemandPcmInterface abstract class
 +---------------------------------------------------------------------*/
class OnDemandPcmInterface {
 public:
  // public constructors & destructors
  virtual ~OnDemandPcmInterface() {}

  // public pure virtual methods
  virtual void NotifyOnDemandContent(const string& action,
                                     const string& location) = 0;
};

/*----------------------------------------------------------------------
 |   OnDemandCcmInterface abstract class
 +---------------------------------------------------------------------*/
class OnDemandCcmInterface {
 public:
  // public constructors & destructors
  virtual ~OnDemandCcmInterface() {}
};

#endif  // FSMDA_MODEL_ONDEMAND_OBJECTS_API_H_
