#include "gtest/gtest.h"
#include <iostream>
#include <signal.h>
#include <fstream>

using std::cout;
using std::clog;
using std::cerr;

void handle_interrupt(int sig) {
  int ret = system("./release_fake_child_parent.sh > /dev/null");
}

int main(int argc, char **argv) {
  // redirect clog to /dev/null/
  static std::ofstream logOutput;
  logOutput.open("/dev/null");
  clog.rdbuf(logOutput.rdbuf());

  signal(SIGINT, handle_interrupt);
  signal(SIGSTOP, handle_interrupt);
  signal(SIGTERM, handle_interrupt);
  signal(SIGTSTP, handle_interrupt);

  // configure gtest
  //  ::testing::FLAGS_gtest_repeat = 2;
  //  ::testing::FLAGS_gtest_output = "/tmp/res.xml";
  ::testing::FLAGS_gtest_break_on_failure = true;
  ::testing::FLAGS_gtest_list_tests       = false;
  ::testing::FLAGS_gtest_print_time       = 0;
  ::testing::FLAGS_gtest_color            = "yes";
  //    ::testing::FLAGS_gtest_filter = "PairingAsParent.*";
  ::testing::FLAGS_gtest_filter = "ClassHandling.*:*.*InDifferentProcesses";
  //  ::testing::FLAGS_gtest_filter =
  //  "PairingAsParent.ActiveInDifferentProcesses";
  //  ::testing::FLAGS_gtest_filter = "-*.*InSameProcesses";
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
