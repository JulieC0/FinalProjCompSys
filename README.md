# FinalProjCompSys
This program will allow inputs to be a single lowercase or uppercase character. 
To run this program, please enter from the command line in the directory to which you dowload these files:

gcc -o main main.c

and then run the command ./main followed by an FSM definition file name and an inputs file name.
For example, to get the results: 

processing FSM definition file test1.fsm

FSM has 16 transitions

processing FSM inputs file test1.inputs

  at step 0, input a transitions FSM from state 0 to state 1
  
  at step 1, input a transitions FSM from state 1 to state 0
  
  at step 2, input a transitions FSM from state 0 to state 1
  
  at step 3, input a transitions FSM from state 1 to state 0
  
  at step 4, input b transitions FSM from state 0 to state 1
  
  at step 5, input c transitions FSM from state 1 to state 2
  
  at step 6, input b transitions FSM from state 2 to state 1
  
  at step 7, input c transitions FSM from state 1 to state 2
  
after 8 steps, state machine finished successfully at state 2,

You would need to run the program like this:
./main ./FSMdef.fsm ./in.inputs

To run the test file, enter in the command line in the same directory:

gcc -o testProgram testProgram.c

and then after running the gcc just type ./testProgram into the command line and it should give these results (though the PASSED lines are on newlines when running the program):

Test 1: Passing too little command line arguments to program.
PASSED: result=-1, expected=-1, actual=-1

Test 2: Passing too many command line arguments to program.
PASSED: result=-1, expected=-1, actual=-1

Test 3: Passing invalid FSM definition file to program.
PASSED: result=-1, expected=-1, actual=-1

Test 4: Passing invalid Inputs file to program.
PASSED: result=-1, expected=-1, actual=-1

Test 5: Passing valid files to program.
PASSED: result=1, expected=1, actual=1

Test 6: Passing FSM file with too many states (51 to be exact).
PASSED: result=-1, expected=-1, actual=-1

Test 7: Passing FSM file with no states (i.e. empty).
PASSED: result=-1, expected=-1, actual=-1

Test 8: Passing FSM file without a transition for state 0.
PASSED: result=-1, expected=-1, actual=-1

Test 9: Passing FSM file with invalid start state (too large to be an int value).
PASSED: result=-1, expected=-1, actual=-1

Test 10: Passing FSM file with negative start state.
PASSED: result=-1, expected=-1, actual=-1

Test 11: Passing FSM file with line that exceeds valid capacity of 24 characters (line error in the file has 25 characters).
PASSED: result=-1, expected=-1, actual=-1

Test 12: Passing FSM files that should pass the validStartStates function with no errors. Second file has exactly 50 states.
PASSED: result=1, expected=1, actual=1

Test 13: Passing input file with too many inputs (exceeds the max of 250 inputs).
PASSED: result=-1, expected=-1, actual=-1

Test 14: Passing empty input file.
PASSED: result=-1, expected=-1, actual=-1

Test 15: Passing input files with invalid input. One file contains numbers and the other an input longer than one char.
PASSED: result=-1, expected=-1, actual=-1

Test 16: Passing input files with valid input.
Second file contains capital letters as well as lowercase. First file contains only lowercase.
PASSED: result=1, expected=1, actual=1

Test 17: Passing valid input file and fsm def file with state that exceeds int_max to transition into.
PASSED: result=-1, expected=-1, actual=-1

Test 18: Passing valid input file and fsm def file with negative state to transition into.
PASSED: result=-1, expected=-1, actual=-1

Test 19: Passing valid input file and fsm def file with invalid next state to transition into (numbers and chars in state).
PASSED: result=-1, expected=-1, actual=-1

Test 20: Passing valid input file and fsm def file but some inputs are not in the fsm def file (i.e won't match any fsm def lines).
PASSED: result=-1, expected=-1, actual=-1

Test 21: Passing valid input file and fsm def file.
PASSED: result=3, expected=3, actual=3


