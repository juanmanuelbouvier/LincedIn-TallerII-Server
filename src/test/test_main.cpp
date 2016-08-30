#include <stdio.h>

#include "gtest/gtest.h"
#include "DummyTests.cpp"	// TODO: include .h, NEVER .cpp!

int main(int argc, char **argv) {
  printf("Running main() from test_main.cpp");
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
