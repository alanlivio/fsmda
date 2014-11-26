#include "fsmda/communicationmanager/model/passive_object_interfaces.h"
#include "fsmda/communicationmanager/upnp/upnp_active_pcm.h"
#include "fsmda/communicationmanager/upnp/upnp_mediacapture_pcm.h"
#include "fsmda/communicationmanager/upnp/upnp_ondemand_pcm.h"
#include "fsmda/communicationmanager/upnp/upnp_passive_pcm.h"
#include "fsmda/paringmanager/device_class_description.h"
#include "fsmda/paringmanager/parent_paring_manager.h"
#include <string>

ParentParingManager::ParentParingManager() {
}

ParentParingManager::~ParentParingManager() {
}

/*----------------------------------------------------------------------
 |   ParentParingManager::addClass
 +---------------------------------------------------------------------*/
void ParentParingManager::addClass(const string& applicationId,
                                   unsigned int classIndex) {
}
/*----------------------------------------------------------------------
 |   ParentParingManager::removeClass
 +---------------------------------------------------------------------*/
void ParentParingManager::removeClass(const string& applicationId,
                                      unsigned int classIndex) {
}
/*----------------------------------------------------------------------
 |   ParentParingManager::addClassDescription
 +---------------------------------------------------------------------*/
void ParentParingManager::addClassDescription(const string& applicationId,
                                              unsigned int classIndex,
                                              const string& classType,
                                              unsigned int maxDevices,
                                              unsigned int minDevices,
                                              const string& hardwareReq,
                                              const string& softwareReq,
                                              const string& networkReq) {
}

/*----------------------------------------------------------------------
 |   ParentParingManager::addDeviceToClass
 +---------------------------------------------------------------------*/
void ParentParingManager::addDeviceToClass(const string& applicationId,
                                           const string& deviceAddr,
                                           unsigned int classIndex,
                                           const string& deviceDesc) {
}
/*----------------------------------------------------------------------
 |   ParentParingManager::getChildIndex
 +---------------------------------------------------------------------*/
void ParentParingManager::getChildIndex(const string& applicationId,
                                        const string& deviceAddr,
                                        unsigned int classIndex) {
}

ActivePcmInterface*
ParentParingManager::createActivePcm(unsigned int classIndex) {
  if (map_classDescription_[classIndex]->classType_
      == DeviceClassDescription::kFsmdaActiveDevice)
    return new UpnpActivePcm();
  else
    return NULL;
}
MediaCapturePcmInterface*
ParentParingManager::createMediaCapturePcm(unsigned int classIndex) {
  if (map_classDescription_[classIndex]->classType_
      == DeviceClassDescription::kFsmdaMediaCaptureDevice)
    return new UpnpMediaCapturePcm();
  else
    return NULL;
}
OnDemandPcmInterface*
ParentParingManager::createOnDemandPcm(unsigned int classIndex) {
  if (map_classDescription_[classIndex]->classType_
      == DeviceClassDescription::kFsmdaOnDemandDevice)
    return new UpnpOnDemandPcm();
  else
    return NULL;
}
PassivePcmInterface*
ParentParingManager::createPassivePcm(unsigned int classIndex) {
  if (map_classDescription_[classIndex]->classType_
      == DeviceClassDescription::kFsmdaPassiveDevice)
    return new UpnpPassivePcm();
  else
    return NULL;
}

