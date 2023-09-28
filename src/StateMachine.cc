#include <cassert>

#include "StateMachine/StateMachine.hpp"

namespace lukaproject
{

  StateMachine::StateMachine(
      std::vector<StateType> states,
      std::vector<Event> events,
      std::string name,
      StateType initial,
      std::unordered_set<StateType> final_states)
  {
    name_ = name;
    initial_ = initial;
    final_states_ = final_states;

    for (const auto &state : states)
    {
      states_.insert({state, std::unordered_set<EventType>()});
    }

    for (auto &event : events)
    {
      for (const auto &edge : event)
      {
        auto iter = states_.find(From(edge));
        assert(iter != states_.end());
        iter->second.insert(event.EventName());
      }
    }
  }

  bool StateMachine::Can(EventType event) const
  {
    auto v = _CanGoNext(event);
    return v != std::nullopt;
  }

  StateType StateMachine::State() const
  {
    return now_;
  }

  std::string StateMachine::MachineName() const
  {
    return name_;
  }

  bool StateMachine::IsFinal() const
  {
    return final_states_.find(now_) != final_states_.end();
  }

  bool StateMachine::Go(EventType event)
  {
    auto v = _CanGoNext(event);
    if (v != std::nullopt)
    {
      return false;
    }
    now_ = v.value();
    return true;
  }

  std::optional<StateType> StateMachine::_CanGoNext(EventType eventName) const
  {
    const auto iter = events_.find(eventName);
    if (iter != events_.end())
    {
      return iter->second.Then(now_);
    }
    return std::nullopt;
  }

} // namespace lukaproject
