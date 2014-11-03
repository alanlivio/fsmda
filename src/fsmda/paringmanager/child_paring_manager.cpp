#include "fsmda/communicationmanager/model/passive_object_control.h"
#include "fsmda/communicationmanager/upnp/upnp_active_ccm.h"
#include "fsmda/communicationmanager/upnp/upnp_mediacapture_ccm.h"
#include "fsmda/communicationmanager/upnp/upnp_ondemand_ccm.h"
#include "fsmda/communicationmanager/upnp/upnp_passive_ccm.h"
#include "fsmda/paringmanager/child_paring_manager.h"
#include "fsmda/paringmanager/device_class_description.h"
#include <string>

ChildParingManager::ChildParingManager ()
{
}

ChildParingManager::~ChildParingManager ()
{
}

ActiveCcmInterface*
ChildParingManager::createActiveCcm (unsigned int classIndex)
{
  if (map_classDescription_[classIndex]->classType_
      == DeviceClassDescription::FSDMA_ACTIVE)
    return new UpnpActiveCcm ();
  else
    return NULL;
}
MediaCaptureCcmInterface*
ChildParingManager::createMediaCaptureCcm (unsigned int classIndex)
{
  if (map_classDescription_[classIndex]->classType_
      == DeviceClassDescription::FSDMA_MEDIACAPTURE)
    return new UpnpMediaCaptureCcm ();
  else
    return NULL;
}

PassiveCcmInterface*
ChildParingManager::createPassiveCcm (unsigned int classIndex)
{
  if (map_classDescription_[classIndex]->classType_
      == DeviceClassDescription::FSDMA_PASSIVE)
    return new UpnpPassiveCcm ();
  else
    return NULL;
}

void
ChildParingManager::classAnnouncement (const string& applicationID,
				       unsigned int classIndex,
				       const string& classDesc,
				       const string& classFunction)
{

}

