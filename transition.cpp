#include "transition.h"

transition::transition(char state, char op, char input)
{
  next_state = state;
  stack_operator = op;
  stack_input = input;  
}

char transition::getNextState()
{
  return next_state;
}

char transition::getStackOperator()
{
  return stack_operator;
}

char transition::getStackInput()
{
  return stack_input;
}
