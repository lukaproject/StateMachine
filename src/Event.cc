#include <cassert>
#include <sstream>
#include <glog/logging.h>

#include "StateMachine/StateMachine.hpp"

namespace lukaproject
{
  Event::Event(
      EventType event,
      std::set<EdgeType> edges,
      std::vector<std::tuple<std::set<StateType>, StateType>> sameTargetEdges)
      : event_(event), edges_(edges)
  {
    for (const auto &sameTargetEdge : sameTargetEdges)
    {
      AddEdges(std::get<0>(sameTargetEdge), std::get<1>(sameTargetEdge));
    }
  }

  EventType Event::EventName() const
  {
    return event_;
  }

  std::set<EdgeType>::const_iterator Event::cbegin() const
  {
    return edges_.cbegin();
  }
  std::set<EdgeType>::const_iterator Event::cend() const

  {
    return edges_.cend();
  }

  std::set<EdgeType>::iterator Event::begin()
  {
    return edges_.begin();
  }

  std::set<EdgeType>::iterator Event::end()
  {
    return edges_.end();
  }

  bool Event::Exist(StateType from, StateType target) const
  {
    auto it = edges_.find({from, target});
    return it != edges_.end();
  }

  std::optional<StateType> Event::Then(StateType from) const
  {
    auto it = edges_.lower_bound({from, ""});
    if (it != edges_.end() && From(*it) == from)
    {
      return Target(*it);
    }
    return std::nullopt;
  }

  void Event::AddEdge(StateType from, StateType target)
  {
    AddEdge({from, target});
  }

  void Event::AddEdge(EdgeType edge)
  {
    auto it = edges_.lower_bound({From(edge), ""});
    if (it != edges_.end() && From(*it) == From(edge))
    {
      assert(Target(*it) == Target(edge));
      return;
    }
    edges_.insert(edge);
  }

  void Event::AddEdges(std::set<StateType> froms, StateType target)
  {
    for (const auto &from : froms)
    {
      AddEdge(from, target);
    }
  }

  void Event::RemoveEdge(EdgeType edge)
  {
    edges_.erase(edge);
  }

  std::string Event::ToString() const
  {
    std::stringstream res;
    res << event_ << ":";
    for (const auto &edge : edges_)
    {
      res << "(" << From(edge) << "|" << Target(edge) << "),";
    }
    return res.str();
  }

  Event Event::FromString(const std::string &str)
  {
    int idx = 0, n = str.size();
    std::string event;
    for (; idx < n; idx++)
    {
      if (str[idx] != ':')
      {
        event.push_back(str[idx]);
      }
      else
      {
        idx++;
        break;
      }
    }

    Event e(event);
    std::string s;
    for (; idx < n; idx++)
    {
      if (str[idx] != ',')
      {
        s.push_back(str[idx]);
      }
      else
      {
        int j = 0, l = s.size();
        for (; j < l && s[j] != '|'; j++)
          ;

        e.AddEdge(s.substr(1, j - 1), s.substr(j + 1, l - j - 2));
        s = "";
      }
    }

    return e;
  }

} // namespace lukaproject
