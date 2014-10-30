#ifndef FSMDA_GINGANCL_COMMUNICATION_ACTIVE_PCM_H_
#define FSMDA_GINGANCL_COMMUNICATION_ACTIVE_PCM_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include <fsmda/model/communication/active_object_control.h>
#include <string>

using namespace std;

/*----------------------------------------------------------------------
 |   ActivePCM class
 +---------------------------------------------------------------------*/
class ActivePCM : public ActivePCMInterface
{
public:
  // public constructors & destructors
  ActivePCM ();
  virtual
  ~ActivePCM ();

  // ActivePCMInterface overloaded methods
  virtual void
  requestPropertyValue (const string& objectID, const string& name);
  virtual void
  notifyEventTransition (const string& objectID, const string& eventID,
			 const string& transition);
  virtual void
  notifyError (const string& objectID, const string& message);
};

#endif /* FSMDA_GINGANCL_COMMUNICATION_ACTIVE_PCM_H_ */
