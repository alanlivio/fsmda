# Tests options
TESTS = t0_test
AM_COLOR_TESTS = always

# Tests programs
check_PROGRAMS = t0_test

# Tests sources
t0_test_SOURCES = test0.cpp

# Tests compiler options
t0_test_CPPLAGS = $(PLATINUMKIT_CFLAGS)

# Tests linker options
t0_test_LDADD = $(top_srcdir)/src/libfsmda.la $(PLATINUMKIT_LIBS)

# Tests clean
CLEANFILES = *.log *.trs