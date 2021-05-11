
#ifndef STATE_HPP
#define STATE_HPP

#include <string>
#include <iostream>

#include "state.hpp"

class Car;

// State base class
class State {
public:
  State() = default;
  ~State() = default;

  // Calls c->changeState(s)
  void changeState(Car *c, State *s);

  // Virtual state transition functions
  // + By default, nothing happens; Derived States can override if needed
  virtual void Start(Car *c) {}
  virtual void Stop(Car *c) {}
  virtual void Smash(Car *c) {}
  virtual std::string report() = 0;

private:
  State(const State &) = default;
  State &operator=(const State&) { return *this;}
};


/******************************************************************************/
// Derived State: Stopped
class Stopped : public State {
public:
  static State *instance()
  {
    // For all derived states, there only needs to be a single instance
    // + Use singleton pattern to prevent duplicate states
    // + A single instance of a state can be applied to N cars
    static State *oneInstance = new Stopped;
    return oneInstance;
  }

  // State transitions valid for this state
  void Start(Car *c) override;
  void Smash(Car *c) override;

  std::string report() override { return "Stopped";}

private:
  Stopped() = default;
  ~Stopped() = default;
  Stopped(const Stopped &) = default;
  Stopped &operator=(const Stopped &) { return *this;}
};


/******************************************************************************/
// Derived State: Running
class Running : public State {
public:
  static State *instance()
  {
    static State *oneInstance = new Running;
    return oneInstance;
  }

  // State transitions valid for this state
  void Stop(Car *c) override;
  void Smash(Car *c) override;

  std::string report() override { return "Running";}

private:
  Running() = default;
  ~Running() = default;
  Running(const Running &) = default;
  Running &operator=(const Running &) { return *this;}
};

/******************************************************************************/
// Derived State: Burning
class Burning : public State {
public:
  static State *instance()
  {
    static State *oneInstance = new Burning;
    return oneInstance;
  }

  // No state transitions possible; The car is burning.

  std::string report() override { return "Burning";}

private:
  Burning() = default;
  ~Burning() = default;
  Burning(const Burning &) = default;
  Burning &operator=(const Burning &) { return *this;}
};

/******************************************************************************/
// Derived State: Broken
class Broken : public State {
public:
  static State *instance()
  {
    static State *oneInstance = new Broken;
    return oneInstance;
  }

  // No state transitions possible; The car is broken.

  std::string report() override { return "Broken";}

private:
  Broken() = default;
  ~Broken() = default;
  Broken(const Broken &) = default;
  Broken &operator=(const Broken &) { return *this;}
};


/******************************************************************************/
// Car controlled by current State
class Car {
public:
  Car() {state = Stopped::instance();}
  ~Car() = default;

  void report() const { std::cout << "State: " << state->report() << std::endl;}

  // Delegate calls to state transitions relative to that current state
  virtual void Start() { state->Start(this);}
  virtual void Stop() { state->Stop(this);}
  virtual void Smash() { state->Smash(this);}

  void changeState(State *s) { state = s;}

private:
  State *state;
};

#endif // STATE_HPP
