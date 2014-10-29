#include "parent_paring_manager.h"

ParentParingManager::ParentParingManager ()
{
  // TODO Auto-generated constructor stub

}

ParentParingManager::~ParentParingManager ()
{
  // TODO Auto-generated destructor stub
}

//////////////////// ClassHandlingPPMInterface functions ////////////////////
void
ParentParingManager::addClass (const string& applicationId, unsigned int classIndex)
{
}
void
ParentParingManager::removeClass (const string& applicationId, unsigned int classIndex)
{
}
void
ParentParingManager::addClassDescription (const string& applicationId,
					  unsigned int classIndex,
					  const string& classType,
					  unsigned int maxDevices,
					  unsigned int minDevices,
					  const string& hardwareReq,
					  const string& softwareReq, const string& networkReq)
{
}

//////////////////// DeviceParingPPMInterface functions ////////////////////
void
ParentParingManager::addDeviceToClass (const string& applicationId, const string& deviceAddr,
				       unsigned int classIndex,
				       const string& deviceDesc)
{
}
void
ParentParingManager::getChildIndex (const string& applicationId, const string& deviceAddr,
				    unsigned int classIndex)
{
}
