#ifndef FSMDA_ONDEMAND_OBJECT_CONTROL_H_
#define FSMDA_ONDEMAND_OBJECT_CONTROL_H_

#include <string>
#include <vector>
using namespace std;

class OnDemandCCMInterface {
 public:
  virtual ~OnDemandCCMInterface()=0;
  virtual void notifyOnDemandContent(string action, string location);
};

#endif /* FSMDA_ONDEMAND_OBJECT_CONTROL_H_ */
