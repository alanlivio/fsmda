############################## build aux rules  ###############################
autogen-configure:
	@./autogen.sh
	./configure

############################## code quality rules  ############################
cpplint:
	@find src/ -name "*.cc"  -o -name "*.h" | grep -v config.h|  xargs -r python ./build-aux/cpplint.py  --root=src --filter=-readability/streams,-build/include_order,-legal/copyright ;\
	find tests/ -name "*.cc"  -o -name "*.h" | grep -v gtest| grep -v gmock| xargs -r python ./build-aux/cpplint.py  --root=tests --filter=-readability/streams,-build/include_order,-legal/copyright;\
	find programs/ -name "*.cc"  -o -name "*.h" | xargs -r python ./build-aux/cpplint.py  --root=programs --filter=-readability/streams,-build/include_order,-legal/copyright;

clang-format:
	@find src/ -name "*.cc"  -o -name "*.h" | grep -v config.h|   xargs clang-format-3.5 -i -style=google ;\
	find tests/ -name "*.cc"  -o -name "*.h" | grep -v gtest| grep -v gmock| xargs clang-format-3.5 -i -style=google ;\
	find programs/ -name "*.cc"  -o -name "*.h" | xargs clang-format-3.5 -i -style=google;

############################## fech rules  ####################################

libtemplate_remote  = https://github.com/alanlivio/libtemplate-autotools-cpp/raw/master/
google_style_remote = http://google-styleguide.googlecode.com/svn/trunk
google_test_remote  = http://googletest.googlecode.com/svn/trunk
google_mock_remote  = http://googlemock.googlecode.com/svn/trunk
protbuf_remote      = https://protobuf.googlecode.com/svn/trunk/
gnulib_remote       = http://git.savannah.gnu.org/cgit/gnulib.git/plain

fetch-build-aux:
	@fetch () { wget -O "$$2/`basename $$1`" "$$1"; };\
	fetch $(google_style_remote)/cpplint/cpplint.py ./build-aux/;\
	chmod +x ./build-aux/cpplint.py;\
	fetch $(protbuf_remote)/m4/acx_pthread.m4 ./build-aux/;

fetch-libtemplate-aux-in-template-instance:
	@fetch () { wget -O "$$2/`basename $$1`" "$$1"; };\
	fetch $(libtemplate_remote)/maint.mk .;\
	fetch $(libtemplate_remote)/.gitignore .;\
	fetch $(libtemplate_remote)/configure.ac .;\
	fetch $(libtemplate_remote)/Makefile.am .;\
	fetch $(libtemplate_remote)/src/Makefile.am ./src;\
	fetch $(libtemplate_remote)/programs/Makefile.am ./programs;\
	fetch $(libtemplate_remote)/tests/Makefile.am ./tests/;

fetch-gtest-gmock:
	@fetch () { wget -O "$$2/`basename $$1`" "$$1"; };\
	mkdir -p ./tests/gtest/src;\
	mkdir -p ./tests/gtest/include/gtest/internal;\
	mkdir -p ./tests/gmock/src/;\
	mkdir -p ./tests/gmock/include/gmock/internal;\
	fetch $(google_test_remote)/src/gtest-all.cc ./tests/gtest/src/;\
	fetch $(google_test_remote)/src/gtest_main.cc ./tests/gtest/src/;\
	fetch $(google_test_remote)/src/gtest.cc ./tests/gtest/src/;\
	fetch $(google_test_remote)/src/gtest-port.cc ./tests/gtest/src/;\
	fetch $(google_test_remote)/src/gtest-death-test.cc ./tests/gtest/src/;\
	fetch $(google_test_remote)/src/gtest-printers.cc ./tests/gtest/src/;\
	fetch $(google_test_remote)/src/gtest-filepath.cc  ./tests/gtest/src/;\
	fetch $(google_test_remote)/src/gtest-test-part.cc ./tests/gtest/src/;\
	fetch $(google_test_remote)/src/gtest-internal-inl.h ./tests/gtest/src/;\
	fetch $(google_test_remote)/src/gtest-typed-test.cc ./tests/gtest/src/;\
	fetch $(google_test_remote)/include/gtest/gtest_pred_impl.h ./tests/gtest/include/gtest/;\
	fetch $(google_test_remote)/include/gtest/gtest.h ./tests/gtest/include/gtest/;\
	fetch $(google_test_remote)/include/gtest/gtest-message.h ./tests/gtest/include/gtest/;\
	fetch $(google_test_remote)/include/gtest/gtest-test-part.h ./tests/gtest/include/gtest/;\
	fetch $(google_test_remote)/include/gtest/gtest-spi.h ./tests/gtest/include/gtest//;\
	fetch $(google_test_remote)/include/gtest/gtest-printers.h ./tests/gtest/include/gtest/;\
	fetch $(google_test_remote)/include/gtest/gtest-param-test.h ./tests/gtest/include/gtest/;\
	fetch $(google_test_remote)/include/gtest/gtest_prod.h ./tests/gtest/include/gtest//;\
	fetch $(google_test_remote)/include/gtest/gtest-typed-test.h ./tests/gtest/include/gtest/;\
	fetch $(google_test_remote)/include/gtest/gtest-death-test.h ./tests/gtest/include/gtest/;\
	fetch $(google_test_remote)/include/gtest/gtest-param-test.h.pump ./tests/gtest/include/gtest/;\
	fetch $(google_test_remote)/include/gtest/internal ./tests/gtest/include/gtest/internal/;\
	fetch $(google_test_remote)/include/gtest/internal/gtest-type-util.h.pump ./tests/gtest/include/gtest/internal/;\
	fetch $(google_test_remote)/include/gtest/internal/gtest-linked_ptr.h ./tests/gtest/include/gtest/internal/;\
	fetch $(google_test_remote)/include/gtest/internal/gtest-filepath.h ./tests/gtest/include/gtest/internal/;\
	fetch $(google_test_remote)/include/gtest/internal/gtest-tuple.h.pump ./tests/gtest/include/gtest/internal/;\
	fetch $(google_test_remote)/include/gtest/internal/gtest-param-util-generated.h ./tests/gtest/include/gtest/internal/;\
	fetch $(google_test_remote)/include/gtest/internal/gtest-type-util.h ./tests/gtest/include/gtest/internal/;\
	fetch $(google_test_remote)/include/gtest/internal/gtest-port.h ./tests/gtest/include/gtest/internal/;\
	fetch $(google_test_remote)/include/gtest/internal/gtest-param-util-generated.h.pump ./tests/gtest/include/gtest/internal/;\
	fetch $(google_test_remote)/include/gtest/internal/gtest-param-util.h ./tests/gtest/include/gtest/internal/;\
	fetch $(google_test_remote)/include/gtest/internal/gtest-internal.h ./tests/gtest/include/gtest/internal/;\
	fetch $(google_test_remote)/include/gtest/internal/gtest-death-test-internal.h ./tests/gtest/include/gtest/internal/;\
	fetch $(google_test_remote)/include/gtest/internal/gtest-tuple.h ./tests/gtest/include/gtest/internal/;\
	fetch $(google_test_remote)/include/gtest/internal/gtest-string.h ./tests/gtest/include/gtest/internal/;\
	fetch $(google_mock_remote)/src/gmock-all.cc ./tests/gmock/src/;\
	fetch $(google_mock_remote)/src/gmock_main.cc ./tests/gmock/src/;\
	fetch $(google_mock_remote)/src/gmock-cardinalities.cc ./tests/gmock/src/;\
	fetch $(google_mock_remote)/src/gmock-matchers.cc ./tests/gmock/src/;\
	fetch $(google_mock_remote)/src/gmock.cc ./tests/gmock/src/;\
	fetch $(google_mock_remote)/src/gmock-spec-builders.cc ./tests/gmock/src/;\
	fetch $(google_mock_remote)/src/gmock-internal-utils.cc ./tests/gmock/src/;\
	fetch $(google_mock_remote)/include/gmock/gmock-actions.h ./tests/gmock/include/gmock/;\
	fetch $(google_mock_remote)/include/gmock/gmock-cardinalities.h ./tests/gmock/include/gmock/;\
	fetch $(google_mock_remote)/include/gmock/gmock-generated-actions.h ./tests/gmock/include/gmock/;\
	fetch $(google_mock_remote)/include/gmock/gmock-generated-actions.h.pump ./tests/gmock/include/gmock/;\
	fetch $(google_mock_remote)/include/gmock/gmock-generated-function-mockers.h ./tests/gmock/include/gmock/;\
	fetch $(google_mock_remote)/include/gmock/gmock-generated-function-mockers.h.pump ./tests/gmock/include/gmock/;\
	fetch $(google_mock_remote)/include/gmock/gmock-generated-matchers.h ./tests/gmock/include/gmock/;\
	fetch $(google_mock_remote)/include/gmock/gmock-generated-matchers.h.pump ./tests/gmock/include/gmock/;\
	fetch $(google_mock_remote)/include/gmock/gmock-generated-nice-strict.h ./tests/gmock/include/gmock/;\
	fetch $(google_mock_remote)/include/gmock/gmock-generated-nice-strict.h.pump ./tests/gmock/include/gmock/;\
	fetch $(google_mock_remote)/include/gmock/gmock.h ./tests/gmock/include/gmock/;\
	fetch $(google_mock_remote)/include/gmock/gmock-matchers.h ./tests/gmock/include/gmock/;\
	fetch $(google_mock_remote)/include/gmock/gmock-more-actions.h ./tests/gmock/include/gmock/;\
	fetch $(google_mock_remote)/include/gmock/gmock-more-matchers.h ./tests/gmock/include/gmock/;\
	fetch $(google_mock_remote)/include/gmock/gmock-spec-builders.h ./tests/gmock/include/gmock/;\
	fetch $(google_mock_remote)/include/gmock/internal/gmock-internal-utils.h ./tests/gmock/include/gmock/internal/;\
	fetch $(google_mock_remote)/include/gmock/internal/gmock-generated-internal-utils.h ./tests/gmock/include/gmock/internal/;\
	fetch $(google_mock_remote)/include/gmock/internal/gmock-generated-internal-utils.h.pump ./tests/gmock/include/gmock/internal/;\
	fetch $(google_mock_remote)/include/gmock/internal/gmock-port.h  ./tests/gmock/include/gmock/internal/;\
	true
