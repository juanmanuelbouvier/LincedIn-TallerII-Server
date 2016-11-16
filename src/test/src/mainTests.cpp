#include <stdio.h>

#include <gtest/gtest.h>

int main(int argc, char **argv) {
  printf("Running main() from %s\n", __FILE__);
  testing::InitGoogleTest(&argc, argv);
  //If exist, remove old test garbage
  system("rm -rf \".temp-test/\" *.log");

  //Create enviroment temp for thest.
  system("mkdir -p \".temp-test\"");

  int code = RUN_ALL_TESTS();

  //Remove enviroment
  system("rm -rf \".temp-test/\" *.log");

  return code;
}
