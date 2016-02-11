/* Copyright 2014 libtemplate team */

#include "gtest/gtest.h"
#include <iostream>
#include <signal.h>
#include <fstream>

using std::cout;
using std::clog;
using std::cerr;

void HandleInterrupt(int sig) {
    int ret = system("./release_fake_child_parent.sh > /dev/null");
}

int main(int argc, char **argv) {
  // redirect clog to /dev/null/
  static std::ofstream logOutput;
  logOutput.open("/dev/null");
  clog.rdbuf(logOutput.rdbuf());

  signal(SIGINT, HandleInterrupt);
  signal(SIGSTOP, HandleInterrupt);
  signal(SIGTERM, HandleInterrupt);
  signal(SIGTSTP, HandleInterrupt);

  // configure gtest
  //  ::testing::FLAGS_gtest_repeat = 2;
  //  ::testing::FLAGS_gtest_output = "/tmp/res.xml";
  ::testing::FLAGS_gtest_break_on_failure = true;
  ::testing::FLAGS_gtest_list_tests = false;
  ::testing::FLAGS_gtest_print_time = 0;
  ::testing::FLAGS_gtest_color = "yes";
  //    ::testing::FLAGS_gtest_filter = "PairingAsParent.*";
  ::testing::FLAGS_gtest_filter = "*.*InDifferentProcesses";
  //  ::testing::FLAGS_gtest_filter =
  //  "PairingAsParent.ActiveInDifferentProcesses";
  //  ::testing::FLAGS_gtest_filter = "-*.*InSameProcesses";
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
