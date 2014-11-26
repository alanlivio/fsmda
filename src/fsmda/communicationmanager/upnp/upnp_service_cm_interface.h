#ifndef UPNP_SERVICE_CM_INTERFACE_H_
#define UPNP_SERVICE_CM_INTERFACE_H_
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
  virtual int
  start_communication_service()=0;
  virtual int
  stop_communication_service()=0;
  virtual bool
  is_service_started()=0;

};

#endif /* UPNP_SERVICE_CM_INTERFACE_H_ */
