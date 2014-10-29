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
  addClass (const string& applicationId, unsigned int classIndex)=0;

  virtual void
  removeClass (const string& applicationId, unsigned int classIndex)=0;

  virtual void
  addClassDescription (const string& applicationId, unsigned int classIndex,
		       const string& classType, unsigned int maxDevices,
		       unsigned int minDevices, const string& hardwareReq,
		       const string& softwareReq, const string& networkReq)=0;
};

class ClassHandlingHPEInterface
{
public:
  virtual
  ~ClassHandlingHPEInterface ()
  {
  }

  virtual void
  getClassVariableValue (const string& name, const string& value);

  virtual void
  setClassVariableValue (const string& name, const string& value);
};

#endif /* FSMDA_CLASS_HANDLING_H_ */
