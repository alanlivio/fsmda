#ifndef FSMDA_GINGANCL_CHILD_PARING_MANAGER_H_
#define FSMDA_GINGANCL_CHILD_PARING_MANAGER_H_

#include <fsmda/model/paring/device_paring.h>
#include <string>

class ChildParingManager : public DeviceParingPCMInterface
{
public:
  ChildParingManager ();

  virtual
  ~ChildParingManager ();

  //////////////////// DeviceParingPCMInterface functions ////////////////////
  virtual void
  classAnnouncement (string applicationID, unsigned int classIndex,
		     string classDesc, string classFunction);
};

#endif /* FSMDA_GINGANCL_CHILD_PARING_MANAGER_H_ */
