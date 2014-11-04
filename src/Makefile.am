############################## Headers ####################################
# Headers
nobase_pkginclude_HEADERS =\
  fsmda/communicationmanager/model/ondemand_object_control.h\
  fsmda/communicationmanager/model/active_object_control.h\
  fsmda/communicationmanager/model/passive_object_control.h\
  fsmda/communicationmanager/model/mediacapture_object_control.h\
  fsmda/paringmanager/model/class_handling.h\
  fsmda/paringmanager/model/device_paring.h

############################## Libraries ####################################
# Libraries
lib_LTLIBRARIES = libfsmda.la

# Libraries sources
libfsmda_la_SOURCES = \
  fsmda/paringmanager/device_description.cpp\
  fsmda/paringmanager/device_class_description.cpp\
  fsmda/paringmanager/parent_paring_manager.cpp\
  fsmda/paringmanager/child_paring_manager.cpp\
  fsmda/paringmanager/upnp/upnp_parent_paring.cpp\
  fsmda/paringmanager/upnp/upnp_child_paring.cpp\
  fsmda/communicationmanager/upnp/upnp_active_ccm.cpp\
  fsmda/communicationmanager/upnp/upnp_active_pcm.cpp\
  fsmda/communicationmanager/upnp/upnp_passive_ccm.cpp\
  fsmda/communicationmanager/upnp/upnp_passive_pcm.cpp\
  fsmda/communicationmanager/upnp/upnp_mediacapture_pcm.cpp\
  fsmda/communicationmanager/upnp/upnp_mediacapture_ccm.cpp\
  fsmda/communicationmanager/upnp/upnp_ondemand_pcm.cpp\
  fsmda/communicationmanager/upnp/upnp_ondemand_ccm.cpp\
  fsmda/utils/upnp_fsmda_utils.cpp
  
# Libraries compiler options
libfsmda_la_CPPFLAGS = -I./ $(PLATINUMKIT_CFLAGS) $(LIBXML2_CFLAGS)

# Libraries linker options
libfsmda_la_LDFLAGS =  $(PLATINUMKIT_LIBS) $(LIBXML2_LIBS)

############################## pkg-config ####################################
# Libraries pkg-config file
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libfsmda.pc
