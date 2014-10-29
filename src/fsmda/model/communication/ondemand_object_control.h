#ifndef FSMDA_ONDEMAND_OBJECT_CONTROL_H_
#define FSMDA_ONDEMAND_OBJECT_CONTROL_H_

#include <string>
#include <vector>
using namespace std;

class OnDemandPCMInterface
{
public:
  virtual
  ~OnDemandPCMInterface ()
  {
  }

  virtual void
  notifyOnDemandContent (const string& action, const string&location)=0;
};

#endif /* FSMDA_ONDEMAND_OBJECT_CONTROL_H_ */
