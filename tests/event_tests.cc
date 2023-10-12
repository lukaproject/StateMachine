#include <gtest/gtest.h>
#include "StateMachine/StateMachine.hpp"
using namespace lukaproject;

class EventTests : public testing::Test
{
};

TEST_F(EventTests, exist_test)
{
  Event e("panic");
  e.AddEdge("green", "red");
  e.AddEdge("yellow", "red");

  ASSERT_TRUE(e.Exist("yellow", "red"));
  ASSERT_FALSE(e.Exist("red", "green"));
}

TEST_F(EventTests, Then_test)
{
  Event e("panic");
  e.AddEdge("green", "red");
  e.AddEdge("yellow", "red");
  ASSERT_EQ(e.Then("yellow").value(), "red");
  ASSERT_EQ(e.Then("black"), std::nullopt);
}

TEST_F(EventTests, to_string)
{
  Event e("panic");
  e.AddEdge("green", "red");
  e.AddEdge("yellow", "red");

  ASSERT_EQ("panic:(green|red),(yellow|red),", e.ToString());
}