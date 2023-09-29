#include <gtest/gtest.h>
#include "StateMachine/StateMachine.hpp"

#include "testFAs/end_with_zero_string_FA.hpp"

using namespace lukaproject::StateMachineTest;
using namespace lukaproject;

class GeneralTest : public testing::Test
{
};

TEST_F(GeneralTest, Test_StateMachine_EndWithZeroStringFA)
{
  EndWithZeroStringFA fa;
  ASSERT_TRUE(fa.Accepted("00000101010101010101000"));
}
