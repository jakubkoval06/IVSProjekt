//  ==============================
//  project:    IVS Calculator (Tests)
//  author:     xkadlep01 Patrik Kadlecek
//  date:       1.4.2006
//  ==============================

#include <gtest/gtest.h>
#include "math_lib.h"



//========== ADD TESTS ==========
TEST(Add, BasicCases) {
    EXPECT_DOUBLE_EQ(add(5,5),10);
    EXPECT_DOUBLE_EQ(add(-5,-5),-10);
    EXPECT_DOUBLE_EQ(add(5,-5),0);
    EXPECT_DOUBLE_EQ(add(5,0),5);
    EXPECT_DOUBLE_EQ(add(0,5),5);
    EXPECT_DOUBLE_EQ(add(0,0),0);
    EXPECT_DOUBLE_EQ(add(1.5,2.5),4.0);
    EXPECT_DOUBLE_EQ(add(-1.5,1.5),0.0);
}

//========== SUBTRACT TESTS ==========
TEST(Subtract, BasicCases) {
    EXPECT_DOUBLE_EQ(subtract(5,5),0);
    EXPECT_DOUBLE_EQ(subtract(-5,-5),0);
    EXPECT_DOUBLE_EQ(subtract(-5,5),-10);
    EXPECT_DOUBLE_EQ(subtract(5,-5),10);
    EXPECT_DOUBLE_EQ(subtract(5,0),5);
    EXPECT_DOUBLE_EQ(subtract(0,0),0);
    EXPECT_DOUBLE_EQ(subtract(5.5,2.5),3.0);
    EXPECT_DOUBLE_EQ(subtract(1.5,3.0),-1.5);
}

//========== MULTIPLY TESTS ==========
TEST(Multiply, BasicCases) {
    EXPECT_DOUBLE_EQ(multiply(5,5),25);
    EXPECT_DOUBLE_EQ(multiply(-5,-5),25);
    EXPECT_DOUBLE_EQ(multiply(5,-5),-25);
    EXPECT_DOUBLE_EQ(multiply(0,5),0);
    EXPECT_DOUBLE_EQ(multiply(5,0),0);
    EXPECT_DOUBLE_EQ(multiply(0,0),0);
    EXPECT_DOUBLE_EQ(multiply(2.5,4.0),10.0);
    EXPECT_DOUBLE_EQ(multiply(-1.5,2.0),-3.0);
}

//========== DIVISION TESTS ==========
TEST(Divide, BasicCases) {
    EXPECT_DOUBLE_EQ(divide(25,5),5);
    EXPECT_DOUBLE_EQ(divide(-25,-5),5);
    EXPECT_DOUBLE_EQ(divide(25,-5),-5);
    EXPECT_DOUBLE_EQ(divide(5,5),1);
    EXPECT_DOUBLE_EQ(divide(5,1),5);
    EXPECT_DOUBLE_EQ(divide(7.5,2.5),3.0);
    EXPECT_DOUBLE_EQ(divide(1.0,4.0),0.25);
}

TEST(Divide, DivisionByZero) {
    EXPECT_DOUBLE_EQ(divide(0,5),0);

    EXPECT_THROW(divide(5,0), std::invalid_argument);
    EXPECT_THROW(divide(0,0), std::invalid_argument);
}

//========== FACTORIAL TESTS ==========
TEST(Factorial,BasicCases) {
    EXPECT_EQ(factorial(5),120);
    EXPECT_EQ(factorial(4),24);
    EXPECT_EQ(factorial(10),3628800);
}

TEST(Factorial, EdgeCases) {
    EXPECT_EQ(factorial(0),1);
    EXPECT_EQ(factorial(1),1);

    EXPECT_THROW(factorial(-1), std::invalid_argument);
    EXPECT_THROW(factorial(-5), std::invalid_argument);
}

//========== POWER TESTS ==========
TEST(Power, BasicCases) {
    EXPECT_DOUBLE_EQ(power(2,2),4);
    EXPECT_DOUBLE_EQ(power(2,10),1024);
    EXPECT_DOUBLE_EQ(power(20,2),400);
    EXPECT_DOUBLE_EQ(power(1,2),1);
    EXPECT_DOUBLE_EQ(power(0,2),0);
}

TEST(Power, EdgeCases) {
    EXPECT_DOUBLE_EQ(power(5,1),5);
    EXPECT_DOUBLE_EQ(power(0,0),1);
    EXPECT_DOUBLE_EQ(power(2,0),1);

    EXPECT_DOUBLE_EQ(power(5,-2),0.04);
    EXPECT_DOUBLE_EQ(power(0.2,-1),5);
}

//========== ROOT TESTS ==========
TEST(Root, BasicCases) {
    EXPECT_NEAR(root(9,2),3,1e-9);
    EXPECT_NEAR(root(8,3),2,1e-9);
    EXPECT_NEAR(root(1,5),1,1e-9);
    EXPECT_NEAR(root(0,5),0,1e-9);
    EXPECT_NEAR(root(2,2),1.41421356237,1e-9);
    EXPECT_NEAR(root(2.25,2),1.5,1e-9);
}

TEST(Root, EdgeCases) {
    EXPECT_THROW(root(-4,2), std::invalid_argument);
    EXPECT_THROW(root(4,0), std::invalid_argument);
    EXPECT_THROW(root(4,-2), std::invalid_argument);

    EXPECT_NEAR(root(-8,3),-2, 1e-9);
}

//========== SUM TESTS ==========
class Sum : public ::testing::Test {
protected:
    double positives[5] = {1, 2, 3, 4, 5};
    double negatives[3] = {-1, -2, -3};
    double mixed[4]     = {-2, -1, 1, 2};
    double single[1]    = {42};
};

TEST_F(Sum, BasicCases) {
    EXPECT_DOUBLE_EQ(sum(positives, 5), 15);
    EXPECT_DOUBLE_EQ(sum(negatives, 3), -6);
    EXPECT_DOUBLE_EQ(sum(mixed, 4), 0);
}

TEST_F(Sum, EdgeCases) {
    EXPECT_DOUBLE_EQ(sum(single, 1), 42);
    EXPECT_DOUBLE_EQ(sum(positives, 0), 0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    }