#include "state.h"

state::state(char state, char input, char stack, bool isInitial) 
{
  internal_state = state;
  current_input = input;
  top_of_stack = stack;
  initial_state = isInitial;
}

// compare two states for equality
bool state::statecmp(char state, char input, char stack) 
{
  if (internal_state == state && current_input == input && top_of_stack == stack)
    return true;
  else
    return false;
}

vector<transition> state::getTransitions()
{
  return state_transitions;
}

void state::addTransition(char next_state, char stack_operator, char stack_input) 
{
  state_transitions.push_back(transition(next_state, stack_operator, stack_input));
}

char state::getState()
{
  return internal_state;
} 

bool state::isInitial()
{
  if (initial_state)
    return true;
  else
    return false;
}
