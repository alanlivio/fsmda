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
ParentParingManager::addClass (string applicationId, unsigned int classIndex)
{
}
void
ParentParingManager::removeClass (string applicationId, unsigned int classIndex)
{
}
void
ParentParingManager::addClassDescription (string applicationId,
					  unsigned int classIndex,
					  string classType,
					  unsigned int maxDevices,
					  unsigned int minDevices,
					  string hardwareReq,
					  string softwareReq, string networkReq)
{
}

//////////////////// DeviceParingPPMInterface functions ////////////////////
void
ParentParingManager::addDeviceToClass (string applicationId, string deviceAddr,
				       unsigned int classIndex,
				       string deviceDesc)
{
}
void
ParentParingManager::getChildIndex (string applicationId, string deviceAddr,
				    unsigned int classIndex)
{
}
