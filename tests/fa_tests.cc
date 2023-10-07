#include <gtest/gtest.h>
#include "StateMachine/StateMachine.hpp"

#include "testFAs/end_with_zero_string_FA.hpp"
#include "testFAs/legal_number_FA.hpp"

using namespace lukaproject::StateMachineTest;
using namespace lukaproject;

class EndWithZeroFATest : public testing::TestWithParam<std::tuple<std::string, bool>>
{
};

INSTANTIATE_TEST_SUITE_P(
    EndWithZeroFATest_ParamOfTest_StateMachine_EndWithZeroStringFA,
    EndWithZeroFATest,
    testing::Values(
        std::make_tuple("000001010101010101011111010101000", true),
        std::make_tuple("111101010001011110011", false),
        std::make_tuple("1111111111111111111111111110111", false),
        std::make_tuple("11c1", false),
        std::make_tuple("00 01", false)));

TEST_P(EndWithZeroFATest, Test_StateMachine_EndWithZeroStringFA)
{
  auto parameter = GetParam();
  auto str = std::get<0>(parameter);
  auto is_accepted = std::get<1>(parameter);

  EndWithZeroStringFA fa;
  ASSERT_EQ(is_accepted, fa.Accepted(str));
}

class LegalNumberFATest : public testing::TestWithParam<std::tuple<std::string, bool>>
{
};

INSTANTIATE_TEST_SUITE_P(
    LegalNumberFATest_ParamOfTest_StateMachine_LegalNumberFA,
    LegalNumberFATest,
    testing::Values(
        std::make_tuple("12372498429330039900", true),
        std::make_tuple("-1", true),
        std::make_tuple("0", true),
        std::make_tuple("1", true),
        std::make_tuple("1213u89", false)));

TEST_P(LegalNumberFATest, Test_StateMachine_LegalNumberFA)
{
  auto parameter = GetParam();
  auto str = std::get<0>(parameter);
  auto is_accepted = std::get<1>(parameter);

  LegalNumberFA fa;
  ASSERT_EQ(is_accepted, fa.Accepted(str));
}