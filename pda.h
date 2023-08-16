#include <map>
#include <vector>
#include <stack>
#include <fstream>
#include "state.h"

using namespace std;

class pushdown_automata 
{
  private:
    vector<state> relations;    // transition table
    char current_state;
    stack<char> Stack;  
  public:
    pushdown_automata(ifstream& infile);    
    bool test_string(char *s, int pos);
    void takeTransition(transition t);
    void reverseTransition(transition t, char prevState);
};
