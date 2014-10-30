#ifndef FSMDA_GINGANCL_COMMUNICATION_SERVICE_CM_INTERFACE_H_
#define FSMDA_GINGANCL_COMMUNICATION_SERVICE_CM_INTERFACE_H_
/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

/*----------------------------------------------------------------------
 |   ServiceCMInterface class
 +---------------------------------------------------------------------*/
class ServiceCMInterface
{
public:
  // public constructors & destructors
  virtual
  ~ServiceCMInterface ()
  {
  }

  // public pure virtual methods
  virtual int
  start_communication_service ()=0;
  virtual int
  stop_communication_service ()=0;
};

#endif /* FSMDA_GINGANCL_COMMUNICATION_SERVICE_CM_INTERFACE_H_ */
