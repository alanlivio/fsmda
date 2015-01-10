############################## Headers ####################################
# Headers
nobase_pkginclude_HEADERS =\
  fsmda/model/ondemand_objects_api.h\
  fsmda/model/active_objects_api.h\
  fsmda/model/passive_objects_api.h\
  fsmda/model/mediacapture_objects_api.h\
  fsmda/model/class_handling_api.h\
  fsmda/model/device_pairing_api.h

############################## Libraries ####################################
# Libraries
lib_LTLIBRARIES = libfsmda.la

# Libraries sources
libfsmda_la_SOURCES = \
  fsmda//device_description.cc\
  fsmda//device_class_description.cc\
  fsmda/parent_class_handler.cc\
  fsmda/child_class_handler.cc\
  fsmda/upnp/upnp_ppm.cc\
  fsmda/upnp/upnp_cpm.cc\
  fsmda/upnp/upnp_passive_ccm.cc\
  fsmda/upnp/upnp_passive_pcm.cc\
  fsmda/upnp/upnp_active_ccm.cc\
  fsmda/upnp/upnp_active_pcm.cc\
  fsmda/upnp/upnp_mediacapture_pcm.cc\
  fsmda/upnp/upnp_mediacapture_ccm.cc\
  fsmda/upnp/upnp_ondemand_pcm.cc\
  fsmda/upnp/upnp_ondemand_ccm.cc\
  fsmda/upnp/upnp_fsmda_utils.cc
  
# Libraries compiler options
libfsmda_la_CPPFLAGS = -I./ $(PLATINUMKIT_CFLAGS) $(LIBXML2_CFLAGS)

# Libraries linker options
libfsmda_la_LDFLAGS =  $(PLATINUMKIT_LIBS) $(LIBXML2_LIBS)

############################## pkg-config ####################################
# Libraries pkg-config file
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libfsmda.pc
