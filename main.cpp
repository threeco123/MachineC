// current state, current input, top of stack, next state, stack operator, stack input

#include <iostream>
#include <fstream>
#include <string.h>
#include "pda.h"

using namespace std;

int main (int argc, char *argv[]) 
{
  ifstream infile;
  infile.open(argv[1]);
  char line[256];

  // initialize emulator
  pushdown_automata machine(infile);

  // if line is not a comment, run through emulator
  infile.getline(line, 256);
  while (!infile.eof()) {
    if (line[0] == '%' && line[1] == 'T') {
      for (int i = 2; i < strlen(line); ++i)
        cout << line[i];
      cout << "...\n";
    }
    else if (strlen(line) == 0)
      ;
    else
      if (machine.test_string(line,-1))
        cout << "Success: " << line << " was accepted!\n\n";
      else
        cout << "Failure: " << line << " was not accepted.\n\n";
    infile.getline(line, 256);
  }

  return 0;
}

