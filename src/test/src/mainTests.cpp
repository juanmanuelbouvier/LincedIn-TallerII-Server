#include <stdio.h>

#include <gtest/gtest.h>

int main(int argc, char **argv) {
  printf("Running main() from %s\n", __FILE__);
  testing::InitGoogleTest(&argc, argv);
  system("mkdir -p \".temp-test\"");
  int code = RUN_ALL_TESTS();
  system("rm -rf \".temp-test/\" *.log");
  return code;
}
