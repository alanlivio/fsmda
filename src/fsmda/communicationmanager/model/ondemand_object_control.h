#ifndef FSMDA_ONDEMAND_OBJECT_CONTROL_H_
#define FSMDA_ONDEMAND_OBJECT_CONTROL_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include <string>

using namespace std;

/*----------------------------------------------------------------------
 |   MediaCapturePCMInterface abstract class
 +---------------------------------------------------------------------*/
class OnDemandPCMInterface
{
public:
  // public constructors & destructors
  virtual
  ~OnDemandPCMInterface ()
  {
  }

  // public pure virtual methods
  virtual void
  notifyOnDemandContent (const string& action, const string&location)=0;
};

#endif /* FSMDA_ONDEMAND_OBJECT_CONTROL_H_ */
