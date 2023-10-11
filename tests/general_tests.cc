#include <gtest/gtest.h>
#include <glog/logging.h>
#include "StateMachine/StateMachine.hpp"

#include "testFAs/end_with_zero_string_FA.hpp"

using namespace lukaproject::StateMachineTest;
using namespace lukaproject;

class EndWithZeroFAGeneralTest : public testing::Test
{
};

TEST_F(EndWithZeroFAGeneralTest, Test_ToString_FromString)
{
  EndWithZeroStringFA fa;
  LOG(INFO) << fa.ToString();

  lukaproject::StateMachine fsm;
  fsm.FromString(fa.ToString());

  LOG(INFO) << fsm.ToString();
}