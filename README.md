# FinalProjCompSys
This program will allow inputs to be a single lowercase or uppercase character. 
To run this program, please enter from the command line in the directory to which you dowload these files ./main followed by an FSM definition file name and an inputs file name.
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
