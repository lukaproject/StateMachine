#include <cassert>

#include "StateMachine/StateMachine.hpp"

#include <glog/logging.h>

namespace lukaproject
{

  StateMachine::StateMachine(
      std::vector<StateType> states,
      std::vector<Event> events,
      std::string name,
      StateType initial,
      std::unordered_set<StateType> final_states)
  {
    Initial(states, events, name, initial, final_states);
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
    if (v == std::nullopt)
    {
      return false;
    }
    now_ = v.value();
    return true;
  }

  void StateMachine::Initial(
      std::vector<StateType> states,
      std::vector<Event> events,
      std::string name,
      StateType initial,
      std::unordered_set<StateType> final_states)
  {
    name_ = name;
    now_ = initial;
    initial_ = initial;
    final_states_ = final_states;

    for (const auto &state : states)
    {
      states_.insert({state, std::unordered_set<EventType>()});
    }

    for (auto &event : events)
    {
      events_.insert({event.EventName(), event});
      for (const auto &edge : event)
      {
        auto iter = states_.find(From(edge));
        assert(iter != states_.end());
        iter->second.insert(event.EventName());
      }
    }
  }

  void StateMachine::Reset()
  {
    now_ = initial_;
  }

  void StateMachine::DebugPrintEvents()
  {
    LOG(INFO) << "Debug print events";
    for (auto &e : events_)
    {
      LOG(INFO) << e.first;
      for (const auto &edge : e.second)
      {
        LOG(INFO) << From(edge) << "," << Target(edge);
      }
    }
  }

  void StateMachine::DebugPrintStates()
  {
    LOG(INFO) << "Debug print states";
    for (auto &s : states_)
    {
      LOG(INFO) << "states:" << s.first;
      for (const auto &event : s.second)
      {
        LOG(INFO) << event;
      }
    }
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

  void StateMachine::FromString(const std::string &str)
  {
    int idx = 0, n = str.size();
    name_ = "";
    initial_ = "";
    now_ = "";
    auto f = [](int &i, const int &n, const std::string &s, std::string &res)
    {
      for (; i < n; i++)
      {
        if (s[i] != '\n')
        {
          res.push_back(s[i]);
        }
        else
        {
          i++;
          return;
        }
      }
    };

    f(idx, n, str, name_);
    f(idx, n, str, initial_);
    f(idx, n, str, now_);

    states_.clear();
    events_.clear();
    std::vector<std::string> rest;
    std::string s;
    for (; idx < n; idx++)
    {
      if (str[idx] != '\n')
      {
        s.push_back(str[idx]);
      }
      else
      {
        rest.push_back(s);
        s = "";
      }
    }

    for (int i = 0; i < ((int)rest.size()) - 1; i++)
    {
      auto e = Event::FromString(rest[i]);
      events_.insert({e.EventName(), e});
      for (const auto &edge : e)
      {
        auto g = [](std::unordered_map<lukaproject::StateType, std::unordered_set<lukaproject::StateType>> &states,
                    const StateType &state,
                    const EventType &eventName)
        {
          if (states.find(state) == states.end())
          {
            states.insert({state, std::unordered_set<EventType>()});
          }
          states[state].insert(eventName);
        };

        g(states_, From(edge), e.EventName());
        g(states_, Target(edge), e.EventName());
      }
    }

    final_states_.clear();
    auto final_states_str = rest.back();
    s = "";
    for (auto c : final_states_str)
    {
      if (c != ',')
      {
        s.push_back(c);
      }
      else
      {
        final_states_.insert(s);
        s = "";
      }
    }
  }

  std::string StateMachine::ToString()
  {
    std::stringstream res;

    res << name_ << "\n"
        << initial_ << "\n"
        << now_ << "\n";

    for (auto &p : events_)
    {
      res << p.second.ToString() << "\n";
    }
    for (auto &state : final_states_)
    {
      res << state << ",";
    }
    res << "\n";

    return res.str();
  }

} // namespace lukaproject
