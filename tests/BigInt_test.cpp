#include "../BigInt.h"
#include <gtest/gtest.h>

class BigIntTest : public ::testing::Test {
protected:
    // settings for every test
    void SetUp() override {

    }

    // clear after every test
    void TearDown() override {

    }
};

//-----------------------------------------------------addition---------------------------------------------------------

// initialize child of class (child of "testing" from gtest)
class BigIntAdditionPositiveTest : public ::testing::TestWithParam<std::tuple<std::string, std::string, std::string>> {
};

TEST_P(BigIntAdditionPositiveTest,AdditionTest)
{
    auto params = GetParam();

    std::string num1_str = std::get<0>(params);
    std::string num2_str = std::get<1>(params);
    std::string expected = std::get<2>(params);

    BigInt num1(num1_str);
    BigInt num2(num2_str);
    BigInt result = num1 + num2;

    EXPECT_EQ(std::string(result.stringArray), expected);
}

INSTANTIATE_TEST_SUITE_P(
    AdditionCases,
    BigIntAdditionPositiveTest,
    ::testing::Values(
        std::make_tuple("100", "50", "150"),
        std::make_tuple("999", "0", "999"),
        std::make_tuple("999", "1", "1000"),
        std::make_tuple("999999999999999999999", "1", "1000000000000000000000"),
        std::make_tuple("999999999899999999999", "200000000000","1000000000099999999999")
    )
);

class BigIntAdditionNegativeTest : public ::testing::TestWithParam<std::tuple<std::string, std::string, std::string>> {
};

TEST_P(BigIntAdditionNegativeTest,NegativePlusNegative)
{
    auto params = GetParam();

    std::string num1_str = std::get<0>(params);
    std::string num2_str = std::get<1>(params);
    std::string expected = std::get<2>(params);

    BigInt num1(num1_str);
    BigInt num2(num2_str);
    BigInt result = num1 + num2;

    EXPECT_EQ(std::string(result.stringArray), expected);
}

INSTANTIATE_TEST_SUITE_P(
    NegativePlusNegative,
    BigIntAdditionNegativeTest,
    ::testing::Values(
        std::make_tuple("-100", "-1", "-101"),
        std::make_tuple("-999999999", "-1", "-1000000000"),
        std::make_tuple("-92", "-96", "-188"),
        std::make_tuple("-999", "-1", "-1000"),
        std::make_tuple("-89", "-57", "-146"),
        std::make_tuple("-89", "-57", "-146"),
        std::make_tuple( "-1234567890123456789","-1", "-1234567890123456790"),
        std::make_tuple("-5", "-3", "-8"),
        std::make_tuple("-10", "-20", "-30")
    )
);

TEST(BigIntAdditionNegativeTest, NegativePlusPositive1)
{
    BigInt num1("-100");
    BigInt num2("100");
    BigInt result = num1 + num2;

    EXPECT_EQ(std::string(result.stringArray), "0");
}

TEST(BigIntAdditionNegativeTest, NegativePlusPositive2)
{
    BigInt num1("-5");
    BigInt num2("3");
    BigInt result = num1 + num2;

    EXPECT_EQ(std::string(result.stringArray), "-2");
}

TEST(BigIntAdditionNegativeTest, NegativePlusPositive3)
{
    BigInt num1("-10");
    BigInt num2("15");
    BigInt result = num1 + num2;

    EXPECT_EQ(std::string(result.stringArray), "5");
}

TEST(BigIntAdditionNegativeTest, NegativePlusPositive4)
{
    BigInt num1("-1000000000");
    BigInt num2("1");
    BigInt result = num1 + num2;

    EXPECT_EQ(std::string(result.stringArray), "-999999999");
}



TEST(BigIntAdditionNegativeTest, PositivePlusNegative1)
{
    BigInt num1("5");
    BigInt num2("-3");
    BigInt result = num1 + num2;

    EXPECT_EQ(std::string(result.stringArray), "2");
}

TEST(BigIntAdditionNegativeTest, PositivePlusNegative2)
{
    BigInt num1("10");
    BigInt num2("-15");
    BigInt result = num1 + num2;

    EXPECT_EQ(std::string(result.stringArray), "-5");
}

TEST(BigIntAdditionNegativeTest, PositivePlusNegative3)
{
    BigInt num1("100");
    BigInt num2("-100");
    BigInt result = num1 + num2;

    EXPECT_EQ(std::string(result.stringArray), "0");
}


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


class BigIntSubstractionTest : public ::testing::TestWithParam<std::tuple<std::string, std::string, std::string>> {};

TEST_P(BigIntSubstractionTest,SubstractionTest)
{
    auto params = GetParam();

    std::string num1_str = std::get<0>(params);
    std::string num2_str = std::get<1>(params);
    std::string expected = std::get<2>(params);

    BigInt num1(num1_str);
    BigInt num2(num2_str);
    BigInt result = num1 - num2;

    EXPECT_EQ(std::string(result.stringArray), expected);
}

INSTANTIATE_TEST_SUITE_P(
    SubstractionCases,
    BigIntSubstractionTest,
    ::testing::Values(
        std::make_tuple("1000000000000000000000", "999999999999999999999", "1"),
        std::make_tuple("100","50","50"),

        //zero substracting
        std::make_tuple("100", "0", "100"),
        std::make_tuple("33", "0", "33")
    )
);

TEST(BigIntTest, SubstractionPositiveNumbers)
{
    BigInt num1("1000000000000000000000");
    BigInt num2("999999999999999999999");
    BigInt result = num1 - num2;

    EXPECT_EQ(std::string(result.stringArray), "1");
}

TEST(BigIntTest, SubstractionPositiveNumbers1)
{
    BigInt num1("1000000000000000000000");
    BigInt num2("999999999999999999999");
    BigInt result = num1 - num2;

    EXPECT_EQ(std::string(result.stringArray), "1");
}


int main(int argc, char * argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}