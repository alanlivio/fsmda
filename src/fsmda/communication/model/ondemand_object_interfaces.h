#ifndef FSMDA_COMMUNICATION_MODEL_ONDEMAND_OBJECT_INTERFACES_H_
#define FSMDA_COMMUNICATION_MODEL_ONDEMAND_OBJECT_INTERFACES_H_

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
  virtual ~OnDemandPcmInterface() {
  }

  // public pure virtual methods
  virtual void
  notifyOnDemandContent(const string& action, const string&location)=0;
};

#endif  // FSMDA_COMMUNICATION_MODEL_ONDEMAND_OBJECT_INTERFACES_H_
