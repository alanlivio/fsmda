############################## Headers ####################################
# Headers
nobase_pkginclude_HEADERS =\
  fsmda/communication/model/ondemand_object_interfaces.h\
  fsmda/communication/model/active_object_interfaces.h\
  fsmda/communication/model/passive_object_interfaces.h\
  fsmda/communication/model/mediacapture_object_interfaces.h\
  fsmda/paring/model/class_handling_interfaces.h\
  fsmda/paring/model/device_paring_interfaces.h

############################## Libraries ####################################
# Libraries
lib_LTLIBRARIES = libfsmda.la

# Libraries sources
libfsmda_la_SOURCES = \
  fsmda/paring/device_description.cpp\
  fsmda/paring/device_class_description.cpp\
  fsmda/paring/parent_paring_manager.cpp\
  fsmda/paring/child_paring_manager.cpp\
  fsmda/paring/upnp_parent_paring.cpp\
  fsmda/paring/upnp_child_paring.cpp\
  fsmda/communication/upnp_active_ccm.cpp\
  fsmda/communication/upnp_active_pcm.cpp\
  fsmda/communication/upnp_passive_ccm.cpp\
  fsmda/communication/upnp_passive_pcm.cpp\
  fsmda/communication/upnp_mediacapture_pcm.cpp\
  fsmda/communication/upnp_mediacapture_ccm.cpp\
  fsmda/communication/upnp_ondemand_pcm.cpp\
  fsmda/communication/upnp_ondemand_ccm.cpp\
  fsmda/utils/upnp_fsmda_utils.cpp
  
# Libraries compiler options
libfsmda_la_CPPFLAGS = -I./ $(PLATINUMKIT_CFLAGS) $(LIBXML2_CFLAGS)

# Libraries linker options
libfsmda_la_LDFLAGS =  $(PLATINUMKIT_LIBS) $(LIBXML2_LIBS)

############################## pkg-config ####################################
# Libraries pkg-config file
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libfsmda.pc
