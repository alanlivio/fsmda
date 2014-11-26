#ifndef CLASS_HANDLING_INTERFACES_H_
#define CLASS_HANDLING_INTERFACES_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include <string>

using namespace std;

/*----------------------------------------------------------------------
 |   ClassHandlingPPMInterface abstract class
 +---------------------------------------------------------------------*/
class ClassHandlingPpmInterface {
 public:
  // public constructors & destructors
  virtual ~ClassHandlingPpmInterface() {
  }

  // public pure virtual methods
  virtual void
  addClass(const string& applicationId, unsigned int classIndex)=0;
  virtual void
  removeClass(const string& applicationId, unsigned int classIndex)=0;
  virtual void
  addClassDescription(const string& applicationId, unsigned int classIndex,
                      const string& classType, unsigned int maxDevices,
                      unsigned int minDevices, const string& hardwareReq,
                      const string& softwareReq, const string& networkReq)=0;
};

/*----------------------------------------------------------------------
 |   ClassHandlingHPEInterface abstract class
 +---------------------------------------------------------------------*/
class ClassHandlingHPEInterface {
 public:
  // public constructors & destructors
  virtual ~ClassHandlingHPEInterface() {
  }

  // public pure virtual methods
  virtual void
  getClassVariableValue(const string& name, const string& value);
  virtual void
  setClassVariableValue(const string& name, const string& value);
};

#endif /* CLASS_HANDLING_INTERFACES_H_ */
