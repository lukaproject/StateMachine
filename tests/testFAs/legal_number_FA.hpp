#ifndef LUKAPROJECT_STATE_MACHINE_TEST_FAS_LEGAL_NUMBER_FA_HPP_
#define LUKAPROJECT_STATE_MACHINE_TEST_FAS_LEGAL_NUMBER_FA_HPP_
#include "StateMachine/StateMachine.hpp"

#include <glog/logging.h>

namespace lukaproject::StateMachineTest
{

  class LegalNumberFA : public lukaproject::StateMachine
  {
  private:
    const StateType Begin = "Begin";
    const StateType Broken = "Broken";
    const StateType SignedHead = "SignedHead";
    const StateType NumberHead = "NumberHead";
    const StateType NumberNonHead = "NumberNonHead";
    const StateType ZeroHead = "ZeroHead";

    const EventType GetZero = "GetZero";
    const EventType GetMinusSign = "GetMinusSign";
    const EventType GetPlusSign = "GetPlusSign";
    const EventType GetNonZeroNumber = "GetNonZeroNumber";
    const EventType GetIllegalChar = "GetIllegalChar";

  public:
    LegalNumberFA()
    {
      std::vector<StateType> states{
          Begin,
          Broken,
          SignedHead,
          NumberHead,
          NumberNonHead,
          ZeroHead,
      };
      std::vector<Event> events{
          Event(
              GetMinusSign,
              {
                  {Begin, SignedHead},
                  {Broken, Broken},
                  {NumberHead, Broken},
                  {NumberNonHead, Broken},
                  {SignedHead, Broken},
                  {ZeroHead, Broken},
              }),
          Event(
              GetPlusSign,
              {
                  {Begin, SignedHead},
                  {Broken, Broken},
                  {NumberHead, Broken},
                  {NumberNonHead, Broken},
                  {SignedHead, Broken},
                  {ZeroHead, Broken},
              }),
          Event(
              GetZero,
              {
                  {Begin, ZeroHead},
                  {Broken, Broken},
                  {NumberHead, NumberNonHead},
                  {NumberNonHead, NumberNonHead},
                  {ZeroHead, Broken},
                  {SignedHead, ZeroHead},
              }),
          Event(
              GetNonZeroNumber,
              {
                  {Begin, NumberHead},
                  {Broken, Broken},
                  {NumberHead, NumberNonHead},
                  {NumberNonHead, NumberNonHead},
                  {ZeroHead, Broken},
                  {SignedHead, NumberHead},
              }),
          Event(
              GetIllegalChar,
              {
                  {Begin, Broken},
                  {Broken, Broken},
                  {NumberHead, Broken},
                  {NumberNonHead, Broken},
                  {ZeroHead, Broken},
                  {SignedHead, Broken},
              }),
      };

      std::string name("LegalNumber");
      StateType initial = Begin;
      std::unordered_set<StateType> final_states{
          ZeroHead,
          NumberHead,
          NumberNonHead,
      };

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
        if (c == '+')
        {
          ok = Go(GetPlusSign);
        }
        else if (c == '-')
        {
          ok = Go(GetMinusSign);
        }
        else if (c == '0')
        {
          ok = Go(GetZero);
        }
        else if ('0' < c && c <= '9')
        {
          ok = Go(GetNonZeroNumber);
        }
        else
        {
          ok = Go(GetIllegalChar);
        }

        if (!ok)
        {
          return false;
        }
      }
      LOG(INFO) << State();
      return IsFinal();
    }

    ~LegalNumberFA() = default;
  };

} // namespace lukaproject::StateMachineTest

#endif