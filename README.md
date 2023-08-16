# Machine

The emulator is built using the 'make' command.
The format for the executable is './NPDA &ltinput file name&gt'.

The input file must consist of a relations table followed by test cases.
The beginning of the relations table must be specified by the token '%BT' and end with '%ET'.

Each transition of the table must occupy a single line by itself and use the following format:
(+)current_state | current_input | top_of_stack | next_state | stack_operator | stack_input

Each variable of the transition is signified by a character and separated by a space.
The current_state variable may be preceded by a '+' character to define it as an initial state.
The lambda operator is signified by the '#' character and also represents an empty stack.
The machine is non-deterministic thus a state may used multiple times to define multiple transitions.

Comments outside of the relations table are introduced by the '%T' token and occupy a single line.
Test cases must be a string of characters also occupying a single line.

Example:
%T This file tests the expression (a^Nb^N)*

%BT
+0 # # 1 s $
1 a $ 1 s a
1 a a 1 s a
1 b a 2 p a
2 b a 2 p a
2 # $ 3 p $
%ET

%T Testing a^nb^n
aaabbb
aaaaaaaaaabbbbbbbbbb
aaabbbaaabbb
aaaabbb
 
