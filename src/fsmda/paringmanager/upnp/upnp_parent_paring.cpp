/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include "fsmda/paringmanager/upnp/upnp_ppm.h"
#include <string>

/*----------------------------------------------------------------------
 |   UpnpPpm::UpnpPpm
 +---------------------------------------------------------------------*/
UpnpPpm::UpnpPpm ()
{

}

/*----------------------------------------------------------------------
 |   UpnpPpm::~UpnpPpm
 +---------------------------------------------------------------------*/
UpnpPpm::~UpnpPpm ()
{

}

/*----------------------------------------------------------------------
 |   UpnpPpm::addClass
 +---------------------------------------------------------------------*/
void
UpnpPpm::addClass (const string& applicationId,
			       unsigned int classIndex)
{
}
/*----------------------------------------------------------------------
 |   UpnpPpm::removeClass
 +---------------------------------------------------------------------*/
void
UpnpPpm::removeClass (const string& applicationId,
				  unsigned int classIndex)
{
}
/*----------------------------------------------------------------------
 |   UpnpPpm::addClassDescription
 +---------------------------------------------------------------------*/
void
UpnpPpm::addClassDescription (const string& applicationId,
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
 |   UpnpPpm::addDeviceToClass
 +---------------------------------------------------------------------*/
void
UpnpPpm::addDeviceToClass (const string& applicationId,
				       const string& deviceAddr,
				       unsigned int classIndex,
				       const string& deviceDesc)
{
}
/*----------------------------------------------------------------------
 |   UpnpPpm::getChildIndex
 +---------------------------------------------------------------------*/
void
UpnpPpm::getChildIndex (const string& applicationId,
				    const string& deviceAddr,
				    unsigned int classIndex)
{
}
