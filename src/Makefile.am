############################## Headers ####################################
# Headers
nobase_pkginclude_HEADERS =\
  fsmda/model/ondemand_object_interfaces.h\
  fsmda/model/active_object_interfaces.h\
  fsmda/model/passive_object_interfaces.h\
  fsmda/model/mediacapture_object_interfaces.h\
  fsmda/model/class_handling_interfaces.h\
  fsmda/model/device_pairing_interfaces.h

############################## Libraries ####################################
# Libraries
lib_LTLIBRARIES = libfsmda.la

# Libraries sources
libfsmda_la_SOURCES = \
  fsmda/device_description.cc\
  fsmda/device_class_description.cc\
  fsmda/parent_pairing_manager.cc\
  fsmda/child_pairing_manager.cc\
  fsmda/pairing/upnp_parent_pairing.cc\
  fsmda/pairing/upnp_child_pairing.cc\
  fsmda/communication/upnp_passive_ccm.cc\
  fsmda/communication/upnp_passive_pcm.cc\
  fsmda/communication/upnp_active_ccm.cc\
  fsmda/communication/upnp_active_pcm.cc\
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
