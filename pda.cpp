#include <stdlib.h>
#include <iostream>
#include <string.h>
#include "pda.h"

pushdown_automata::pushdown_automata(ifstream& infile) 
{
  char line[256], current_state, current_input, top_of_stack, next_state, stack_operator, stack_input = 0, temp;
  bool found_state = false, isInitial = false;

  do {
    // find beginning of user defined transition table
    if (infile.eof()) {
      cout << "Error: input file must contain \"%BT\" to signify the beginning of the table\n";
      exit(1); 
    }
    infile.getline(line, 256);
  } while(strcmp(line, "%BT"));

  cout << "Building non-deterministic pushdown automata...\n";
  while (true) {
    if ((current_state = infile.get()) == '+') {
      isInitial = true;
      current_state = infile.get();
    }
    temp = infile.get();
    current_input = infile.get();

    // test whether end of the transition table is reached
    if (current_state == '%' && temp == 'E' && current_input == 'T')
      break;

    infile.get();
    top_of_stack = infile.get();
    infile.get();
    next_state = infile.get();
    infile.get();
    stack_operator = infile.get();

    // stack operator must be valid
    if (stack_operator != 'p' && stack_operator != 's') {
      cout << "Error: stack operator must be either 's' (push) or 'p' (pop)\n";
      exit(1);
    }

    infile.get();
    stack_input = infile.get();

    if (infile.get() != '\n') {
      cout << "Error: line must be six characters separated by spaces\n";
      exit(1);
    }

    // insert transition into data structure
    for (int i = 0; i < relations.size(); ++i)
      if (relations[i].statecmp(current_state, current_input, top_of_stack)) {
        relations[i].addTransition(next_state, stack_operator, stack_input);
        found_state = true;
        break;
      }
    if (!found_state) {
      relations.push_back(state(current_state, current_input, top_of_stack, isInitial));
      relations.back().addTransition(next_state, stack_operator, stack_input);
    }

    stack_input = 0;
    found_state = false;
    isInitial = false;
  }

  infile.get();
  cout << "Machine read to accept input.\n\n";
}

bool pushdown_automata::test_string(char *s, int pos) 
{
  char prevState;

  if (pos < (int)strlen(s))
    if (pos == -1) {
      for (int i = 0; i < relations.size(); ++i)
        if (relations[i].isInitial()) {
          current_state = relations[i].getState();
          if (relations[i].statecmp(current_state, '#', '#'))                  // test lambda before first input
            for (int j = 0; j < relations[i].getTransitions().size(); ++j) {
              prevState = current_state;
              takeTransition(relations[i].getTransitions()[j]);
              if (test_string(s,pos+1))
                return true;
              reverseTransition(relations[i].getTransitions()[j], prevState);
            }
	  if (relations[i].statecmp(current_state, s[pos+1], '#'))             // test whether first input has initial state
            for (int j = 0; j < relations[i].getTransitions().size(); ++j) {
              prevState = current_state;
              takeTransition(relations[i].getTransitions()[j]);
              if (test_string(s,pos+2))
                return true;
              reverseTransition(relations[i].getTransitions()[j], prevState);
            }
        }
    }
    else
      // test each transition from the current state
      for (int i = 0; i < relations.size(); ++i) {
        if (relations[i].statecmp(current_state, '#', Stack.top()))            // test lambda transition
          for (int j = 0; j < relations[i].getTransitions().size(); ++j) {
            prevState = current_state;
            takeTransition(relations[i].getTransitions()[j]);
            if (test_string(s,pos))
              return true;
            reverseTransition(relations[i].getTransitions()[j], prevState);
          }
        if (relations[i].statecmp(current_state, s[pos], Stack.top()))        // test next input in string
          for (int j = 0; j < relations[i].getTransitions().size(); ++j) {
            prevState = current_state;
            takeTransition(relations[i].getTransitions()[j]);
            if (test_string(s,pos+1))
              return true;
            reverseTransition(relations[i].getTransitions()[j], prevState);
          }
      } 
  else
    for (int i = 0; i < relations.size(); ++i)
      if (relations[i].statecmp(current_state, '#', Stack.top()))
        return true;
      
  return false;
}

void pushdown_automata::takeTransition(transition t)
{
  current_state = t.getNextState();
  if (t.getStackOperator() == 's')
    Stack.push(t.getStackInput());
  else
    Stack.pop();
}

void pushdown_automata::reverseTransition(transition t, char prevState) 
{  
  current_state = prevState;
  if (t.getStackOperator() == 's')
    Stack.pop();
  else
    Stack.push(t.getStackInput());

  return;
}
