using namespace std;

class transition 
{
  private:
    char next_state, stack_operator, stack_input;
  public:
    transition(char state, char op, char input);
    char getNextState();
    char getStackOperator();
    char getStackInput();
};
