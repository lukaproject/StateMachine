#pragma once
#ifndef LUKAPROJECT_STATE_MACHINE_STATE_MACHINE_HPP_
#define LUKAPROJECT_STATE_MACHINE_STATE_MACHINE_HPP_

#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <vector>
#include <optional>

namespace lukaproject
{

  using StateType = std::string;
  using EventType = std::string;
  using EdgeType = std::tuple<StateType, StateType>;

  inline const StateType &From(const EdgeType &edge)
  {
    return std::get<0>(edge);
  }

  inline const StateType &Target(const EdgeType &edge)
  {
    return std::get<1>(edge);
  }

  class Event
  {
  public:
    Event(EventType event, std::set<EdgeType> edges = std::set<EdgeType>());
    StateType EventName() const;

    std::set<EdgeType>::const_iterator cbegin() const;
    std::set<EdgeType>::const_iterator cend() const;
    std::set<EdgeType>::iterator begin();
    std::set<EdgeType>::iterator end();

    bool Exist(StateType from, StateType target) const;
    std::optional<StateType> Then(StateType from) const;

    void AddEdge(StateType from, StateType target);
    void AddEdge(EdgeType edge);
    void RemoveEdge(EdgeType edge);

    ~Event() = default;

  private:
    EventType event_;
    std::set<EdgeType> edges_;
  };

  class StateMachine
  {
  public:
    StateMachine(
        std::vector<StateType> states,
        std::vector<Event> events,
        std::string name,
        StateType initial,
        std::unordered_set<StateType> final_states);

    bool Can(EventType event) const;

    StateType State() const;

    std::string MachineName() const;

    bool IsFinal() const;

    bool Go(EventType event);

    ~StateMachine() = default;

  private:
    std::unordered_map<StateType, std::unordered_set<EventType>> states_;
    std::unordered_map<EventType, Event> events_;

    std::string name_;
    StateType initial_;
    StateType now_;
    std::unordered_set<StateType> final_states_;

    std::optional<StateType> _CanGoNext(EventType event) const;
  };

} // namespace lukaproject

#endif