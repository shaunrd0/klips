
#include "state.hpp"

// Delegate calls from State->changeState to Car->changeState
void State::changeState(Car *c, State *s) { c->changeState(s);}

// Stopped state transitions
void Stopped::Start(Car *c) { changeState(c, Running::instance());}
void Stopped::Smash(Car *c) { changeState(c, Broken::instance());}

// Running state transitions
void Running::Stop(Car *c) { changeState(c, Stopped::instance());}
void Running::Smash(Car *c) { changeState(c, Burning::instance());}
