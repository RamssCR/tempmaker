#include <gtest/gtest.h>

TEST(Samples, AddsTwoNumbers) {
    EXPECT_EQ(10, 5 + 5);
}

TEST(Samples, ComparesTwoString) {
    EXPECT_NE("Santa", "Claus");
}