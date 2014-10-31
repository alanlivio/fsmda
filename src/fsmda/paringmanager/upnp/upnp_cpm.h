#ifndef FSMDA_GINGANCL_CHILD_PARING_MANAGER_H_
#define FSMDA_GINGANCL_CHILD_PARING_MANAGER_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include <fsmda/model/paring/device_paring.h>
#include <string>

/*----------------------------------------------------------------------
 |   ChildParingManager class
 +---------------------------------------------------------------------*/
class ChildParingManager : public DeviceParingPCMInterface
{
public:
  // public constructors & destructors
  ChildParingManager ();
  virtual
  ~ChildParingManager ();

  // DeviceParingPCMInterface overloaded methods
  virtual void
  classAnnouncement (const string& applicationID, unsigned int classIndex,
		     const string& classDesc, const string& classFunction);
};

#endif /* FSMDA_GINGANCL_CHILD_PARING_MANAGER_H_ */
