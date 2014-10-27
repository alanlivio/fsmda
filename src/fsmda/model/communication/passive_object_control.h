#ifndef FSMDA_PASSIVE_OBJECT_CONTROL_H_
#define FSMDA_PASSIVE_OBJECT_CONTROL_H_

#include <string>
#include <vector>
using namespace std;

class PassiveCCMInterface {
 public:
  virtual ~PassiveCCMInterface()=0;
  virtual void prepare(string position)=0;
  virtual void sendContent(char* content)=0;
};

class PassivePCMInterface {
 public:
  virtual ~PassivePCMInterface()=0;
  virtual void notifyError(string message, string objectId)=0;
};

#endif /* FSMDA_PASSIVE_OBJECT_CONTROL_H_ */
