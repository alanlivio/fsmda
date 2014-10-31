/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include <fsmda/gingancl/paring/parent_paring_manager.h>

/*----------------------------------------------------------------------
 |   DeviceDescription::ParentParingManager
 +---------------------------------------------------------------------*/
ParentParingManager::ParentParingManager ()
{

}

/*----------------------------------------------------------------------
 |   DeviceDescription::~ParentParingManage
 +---------------------------------------------------------------------*/
ParentParingManager::~ParentParingManager ()
{

}

/*----------------------------------------------------------------------
 |   DeviceDescription::addClass
 +---------------------------------------------------------------------*/
void
ParentParingManager::addClass (const string& applicationId,
			       unsigned int classIndex)
{
}
/*----------------------------------------------------------------------
 |   DeviceDescription::removeClass
 +---------------------------------------------------------------------*/
void
ParentParingManager::removeClass (const string& applicationId,
				  unsigned int classIndex)
{
}
/*----------------------------------------------------------------------
 |   DeviceDescription::addClassDescription
 +---------------------------------------------------------------------*/
void
ParentParingManager::addClassDescription (const string& applicationId,
					  unsigned int classIndex,
					  const string& classType,
					  unsigned int maxDevices,
					  unsigned int minDevices,
					  const string& hardwareReq,
					  const string& softwareReq,
					  const string& networkReq)
{
}

/*----------------------------------------------------------------------
 |   DeviceDescription::addDeviceToClass
 +---------------------------------------------------------------------*/
void
ParentParingManager::addDeviceToClass (const string& applicationId,
				       const string& deviceAddr,
				       unsigned int classIndex,
				       const string& deviceDesc)
{
}
/*----------------------------------------------------------------------
 |   DeviceDescription::getChildIndex
 +---------------------------------------------------------------------*/
void
ParentParingManager::getChildIndex (const string& applicationId,
				    const string& deviceAddr,
				    unsigned int classIndex)
{
}
