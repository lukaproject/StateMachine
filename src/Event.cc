#include <cassert>

#include "StateMachine/StateMachine.hpp"

namespace lukaproject
{
  Event::Event(
      EventType event,
      std::set<EdgeType> edges)
      : event_(event), edges_(edges) {}

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
      return Target(*it);
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

  void Event::RemoveEdge(EdgeType edge)
  {
    edges_.erase(edge);
  }
} // namespace lukaproject
