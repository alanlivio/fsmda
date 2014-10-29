# Tests options
TESTS = t0_test
AM_COLOR_TESTS = always

# Tests programs
check_PROGRAMS = t0_test

# t0_test
t0_test_SOURCES = test0.cpp
t0_test_CPPFLAGS = $(PLATINUMKIT_CFLAGS) $(LIBXML2_CFLAGS)
t0_test_LDADD = $(top_srcdir)/src/libfsmda.la $(PLATINUMKIT_LIBS)  $(LIBXML2_LIBS)

## t1_test
#t1_test_SOURCES = test1.cpp
#t1_test_CPPLAGS = $(PLATINUMKIT_CFLAGS)
#t1_test_LDADD = $(top_srcdir)/src/libfsmda.la $(PLATINUMKIT_LIBS)

# Tests clean
CLEANFILES = *.log *.trs