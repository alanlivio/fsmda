#ifndef ONDEMAND_OBJECT_INTERFACES_H_
#define ONDEMAND_OBJECT_INTERFACES_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include <string>

using namespace std;

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

#endif /* ONDEMAND_OBJECT_INTERFACES_H_ */
