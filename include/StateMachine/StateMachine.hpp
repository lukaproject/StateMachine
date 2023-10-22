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
    //
    // event : event name
    // edges : event edges
    // sameTargetEdges: some states will route to the same target in
    //                  this event. like (s1->s5, s2->s5, s3->s5, s4->s5, s5->s5) can be
    //                  summarized to (s1, s2, s3, s4, s5) -> s5
    //
    Event(
        EventType event,
        std::set<EdgeType> edges = {},
        std::vector<std::tuple<std::set<StateType>, StateType>> sameTargetEdges = {});
    StateType EventName() const;

    // --
    // in order to use foreach to got all the edges
    // from this event.
    std::set<EdgeType>::const_iterator cbegin() const;
    std::set<EdgeType>::const_iterator cend() const;
    std::set<EdgeType>::iterator begin();
    std::set<EdgeType>::iterator end();
    // --

    // Check if this edge is existed in this event.
    bool Exist(StateType from, StateType target) const;

    // Get this event's next state from state `from`,
    // otherwise nullopt.
    std::optional<StateType> Then(StateType from) const;

    void AddEdge(StateType from, StateType target);
    void AddEdge(EdgeType edge);
    void AddEdges(std::set<StateType> froms, StateType target);
    void RemoveEdge(EdgeType edge);

    std::string ToString() const;
    static Event FromString(const std::string &str);

    ~Event() = default;

  private:
    EventType event_;
    std::set<EdgeType> edges_;
  };

  class StateMachine
  {
  public:
    StateMachine() = default;

    StateMachine(
        std::vector<StateType> states,
        std::vector<Event> events,
        std::string name,
        StateType initial,
        std::unordered_set<StateType> final_states);

    // Check if now can do this event. if it can do,
    // return true, otherwise return false.
    bool Can(EventType event) const;

    // current state.
    StateType State() const;

    std::string MachineName() const;

    // Check if it is final state.
    bool IsFinal() const;

    // Execute this event to this machine, if there
    // is an event from now state to next state, return
    // true and fallthrough to the next state, otherwise
    // return false and do nothing.
    bool Go(EventType event);

    // Reset the current state to initial state.
    void Reset();

    void Initial(
        std::vector<StateType> states,
        std::vector<Event> events,
        std::string name,
        StateType initial,
        std::unordered_set<StateType> final_states);

    // Unserialize string to state machine.
    void FromString(const std::string &str);

    // Serialize state machine to string.
    std::string ToString();

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