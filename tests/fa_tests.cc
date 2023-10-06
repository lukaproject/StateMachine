#include <gtest/gtest.h>
#include "StateMachine/StateMachine.hpp"

#include "testFAs/end_with_zero_string_FA.hpp"

using namespace lukaproject::StateMachineTest;
using namespace lukaproject;

class EndWithZeroFATest : public testing::TestWithParam<std::tuple<std::string, bool>>
{
};

INSTANTIATE_TEST_SUITE_P(
    ParamOfTest_StateMachine_EndWithZeroStringFA,
    EndWithZeroFATest,
    testing::Values(
        std::make_tuple("000001010101010101011111010101000", true),
        std::make_tuple("111101010001011110011", false),
        std::make_tuple("1111111111111111111111111110111", false)));

TEST_P(EndWithZeroFATest, Test_StateMachine_EndWithZeroStringFA)
{
  auto parameter = GetParam();
  auto str = std::get<0>(parameter);
  auto is_accepted = std::get<1>(parameter);

  EndWithZeroStringFA fa;
  ASSERT_EQ(is_accepted, fa.Accepted(str));
}
