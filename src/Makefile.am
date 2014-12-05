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
  fsmda/paring/device_description.cc\
  fsmda/paring/device_class_description.cc\
  fsmda/paring/parent_paring_manager.cc\
  fsmda/paring/child_paring_manager.cc\
  fsmda/paring/upnp_parent_paring.cc\
  fsmda/paring/upnp_child_paring.cc\
  fsmda/communication/upnp_active_ccm.cc\
  fsmda/communication/upnp_active_pcm.cc\
  fsmda/communication/upnp_passive_ccm.cc\
  fsmda/communication/upnp_passive_pcm.cc\
  fsmda/communication/upnp_mediacapture_pcm.cc\
  fsmda/communication/upnp_mediacapture_ccm.cc\
  fsmda/communication/upnp_ondemand_pcm.cc\
  fsmda/communication/upnp_ondemand_ccm.cc\
  fsmda/utils/upnp_fsmda_utils.cc
  
# Libraries compiler options
libfsmda_la_CPPFLAGS = -I./ $(PLATINUMKIT_CFLAGS) $(LIBXML2_CFLAGS)

# Libraries linker options
libfsmda_la_LDFLAGS =  $(PLATINUMKIT_LIBS) $(LIBXML2_LIBS)

############################## pkg-config ####################################
# Libraries pkg-config file
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libfsmda.pc
