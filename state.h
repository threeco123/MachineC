#include <vector>
#include "transition.h"

using namespace std;

class state 
{
  private:
    char internal_state, current_input, top_of_stack;
    bool initial_state;
    vector<transition> state_transitions;
  public:
    state(char state, char input, char stack, bool isInitial);
    bool statecmp(char internal_state, char current_input, char top_of_stack);
    vector<transition> getTransitions();
    void addTransition(char next_state, char stack_operator, char stack_input);
    char getState();
    bool isInitial();
};
