#include <gtest/gtest.h>
#include "math_lib.h"

TEST(Add, BasicCases) {
    EXPECT_DOUBLE_EQ(add(5,5),10);
    EXPECT_DOUBLE_EQ(add(-5,-5),-10);
    EXPECT_DOUBLE_EQ(add(5,-5),0);
    EXPECT_DOUBLE_EQ(add(5,0),5);
    EXPECT_DOUBLE_EQ(add(0,5),5);
    EXPECT_DOUBLE_EQ(add(0,0),0);
}

TEST(Subtract, BasicCases) {
    EXPECT_DOUBLE_EQ(subtract(5,5),0);
    EXPECT_DOUBLE_EQ(subtract(-5,-5),0);
    EXPECT_DOUBLE_EQ(subtract(-5,5),-10);
    EXPECT_DOUBLE_EQ(subtract(5,-5),10);
    EXPECT_DOUBLE_EQ(subtract(5,0),5);
    EXPECT_DOUBLE_EQ(subtract(0,0),0);
}

TEST(Multiply, BasicCases) {
    EXPECT_DOUBLE_EQ(multiply(5,5),25); 
    EXPECT_DOUBLE_EQ(multiply(-5,-5),25);
    EXPECT_DOUBLE_EQ(multiply(5,-5),-25);
    EXPECT_DOUBLE_EQ(multiply(0,5),0);
    EXPECT_DOUBLE_EQ(multiply(0,0),0);
}

TEST(Divide, BasicCases) {
    EXPECT_DOUBLE_EQ(divide(25,5), 5);
    EXPECT_DOUBLE_EQ(divide(-25,-5), 5);
    EXPECT_DOUBLE_EQ(divide(25,-5), -5);
    EXPECT_DOUBLE_EQ(divide(5,5), 1);
    EXPECT_DOUBLE_EQ(divide(5,1), 5);

}

TEST(Divide, DivisionByZero) {
    EXPECT_DOUBLE_EQ(divide(0,5),0);

    EXPECT_THROW(divide(5,0), std::invalid_argument);
    EXPECT_THROW(divide(0,0), std::invalid_argument);

}

/*
TODO
TEST(Factorial,) {

}


TEST(Sum,) {

}


TEST(Power) {

}


TEST(Root) {

}

*/

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}