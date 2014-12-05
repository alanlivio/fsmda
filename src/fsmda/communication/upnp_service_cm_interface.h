#ifndef FSMDA_COMMUNICATION_UPNP_SERVICE_CM_INTERFACE_H_
#define FSMDA_COMMUNICATION_UPNP_SERVICE_CM_INTERFACE_H_
/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

/*----------------------------------------------------------------------
 |   ServiceCmInterface class
 +---------------------------------------------------------------------*/
class ServiceCmInterface {
 public:
  // public constructors & destructors
  virtual ~ServiceCmInterface() {
  }

  // public pure virtual methods
  virtual int StartCommunicationService()=0;
  virtual int StopCommunicationService()=0;
  virtual bool IsServiceStartd()=0;
};

#endif  // FSMDA_COMMUNICATION_UPNP_SERVICE_CM_INTERFACE_H_
