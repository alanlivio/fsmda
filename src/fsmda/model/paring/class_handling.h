#ifndef FSMDA_CLASS_HANDLING_H_
#define FSMDA_CLASS_HANDLING_H_

#include <string>
using namespace std;

class ClassHandlingPPMInterface
{
public:
  virtual
  ~ClassHandlingPPMInterface ()
  {
  }
  ;
  virtual void
  addClass (string applicationId, unsigned int classIndex)=0;

  virtual void
  removeClass (string applicationId, unsigned int classIndex)=0;

  virtual void
  addClassDescription (string applicationId, unsigned int classIndex,
		       string classType, unsigned int maxDevices,
		       unsigned int minDevices, string hardwareReq,
		       string softwareReq, string networkReq)=0;
};

class ClassHandlingHPEInterface
{
public:
  virtual
  ~ClassHandlingHPEInterface ()
  {
  }

  virtual void
  getClassVariableValue (string name, string value);

  virtual void
  setClassVariableValue (string name, string value);
};

#endif /* FSMDA_CLASS_HANDLING_H_ */
