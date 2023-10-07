#ifndef LUKAPROJECT_STATE_MACHINE_TEST_FAS_END_WITH_ZERO_STRING_FA_HPP_
#define LUKAPROJECT_STATE_MACHINE_TEST_FAS_END_WITH_ZERO_STRING_FA_HPP_
#include "StateMachine/StateMachine.hpp"

#include <glog/logging.h>

namespace lukaproject::StateMachineTest
{

  class EndWithZeroStringFA : public lukaproject::StateMachine
  {

  private:
    const StateType EndWithZero = "EndWithZero";
    const StateType EndWithOne = "EndWithOne";
    const StateType Broken = "Broken";
    const StateType Begin = "Begin";

    const EventType GetOne = "GetOne";
    const EventType GetZero = "GetZero";
    const EventType GetOther = "GetOther";

  public:
    EndWithZeroStringFA()
    {
      std::vector<StateType> states{
          EndWithZero,
          EndWithOne,
          Broken,
          Begin,
      };
      std::vector<Event> events{
          Event(
              GetOne,
              {
                  {Begin, EndWithOne},
                  {EndWithOne, EndWithOne},
                  {EndWithZero, EndWithOne},
                  {Broken, Broken},
              }),
          Event(
              GetZero,
              {
                  {Begin, EndWithZero},
                  {EndWithZero, EndWithZero},
                  {EndWithOne, EndWithZero},
                  {Broken, Broken},
              }),

          Event(
              GetOther,
              {
                  {Begin, Broken},
                  {EndWithOne, Broken},
                  {EndWithZero, Broken},
                  {Broken, Broken},
              }),
      };
      std::string name("EndWithZeroString");
      StateType initial = Begin;
      std::unordered_set<StateType> final_states;

      Initial(
          states,
          events,
          name,
          initial,
          final_states);
    }

    bool Accepted(const std::string &str)
    {
      Reset();
      for (const auto &c : str)
      {
        bool ok = true;
        if (c == '0')
        {
          ok = Go(GetZero);
        }
        else if (c == '1')
        {
          ok = Go(GetOne);
        }
        else
        {
          ok = Go(GetOther);
        }
        if (!ok)
        {
          return false;
        }
      }
      LOG(INFO) << State();
      return State() == EndWithZero;
    }

    ~EndWithZeroStringFA() = default;
  };

} // namespace lukaproject::StateMachineTest

#endif