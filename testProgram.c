//
// Created by Julie Chase on 12/22/20.
//
#include <stdio.h>
#include "fileFunctions.h"
#include "transitionFunctions.h"

//testers for fileFunctions.h
void testArgumentsLess(char *fsm, char *infile, int expect);
void testArgumentsMore(char *fsm, char *infile, int expect);
void testInvalidFSMFile(char *fsm, char *infile, int expect);
void testInvalidInputFile(char *fsm, char *infile, int expect);
void testOutputWithValidFiles(char *fsm, char *infile, int expect);
void testFSMTooManyStates(char *fsm, int expect);
void testEmptyFSMFile(char *fsm, int expect);
void testTooLargeStateFSMFile(char *fsm, int expect);
void testNegStartStateFSMFile(char *fsm, int expect);
void testLineTooLongFSMFile(char *fsm, int expect);
void testWithValidFSMFile(char *fsm, char*fsm2, int expect);
void testTooManyInputs(char *input, int expect);
void testEmptyInputFile(char *input, int expect);
void testInvalidInputInFile(char *input, char *input2, int expect);
void testValidInputInFile(char *input, char *input2, int expect);
//testers for transitionFunctions.h
void testTooLargeNextState(char *input, char *fsm, int expect);
void testNegativeNextState(char *input, char *fsm, int expect);
void testInputHasNoMatch(char *input, char *fsm, int expect);
void testInputandFSMValid(char *input, char *fsm, int expect);

int main(void){
    printf("Test 1: ");
    testArgumentsLess("./FSMdef.fsm", "./in.inputs", -1);
    printf("\nTest 2: ");
    testArgumentsMore("./FSMdef.fsm", "./in.inputs", -1);
    printf("\nTest 3: ");
    testInvalidFSMFile("./FSMNONE.txt", "./in.inputs", -1);
    printf("\nTest 4: ");
    testInvalidInputFile("./FSMdef.fsm", "./inputsNONE.txt", -1);
    printf("\nTest 5: ");
    testOutputWithValidFiles("./FSMdef.fsm", "./in.inputs", 1);
    printf("\nTest 6: ");
    testFSMTooManyStates("./FSMtoomany.fsm", -1);
    printf("\nTest 7: ");
    testEmptyFSMFile("./emptyFSM.fsm", -1);
    printf("\nTest 8: ");
    testTooLargeStateFSMFile("./FSMinvalidState.fsm", -1);
    printf("\nTest 9: ");
    testNegStartStateFSMFile("./FSMnegStart.fsm", -1);
    printf("\nTest 10: ");
    testLineTooLongFSMFile("./FSMlineLong.fsm", -1);
    printf("\nTest 11: ");
    testWithValidFSMFile("./FSMdef.fsm", "./FSM50states.fsm", 1);
    printf("\nTest 12: ");
    testTooManyInputs("./inTooMany.inputs", -1);
    printf("\nTest 13: ");
    testEmptyInputFile("./inEmpty.inputs", -1);
    printf("\nTest 14: ");
    testInvalidInputInFile("./inInvalid1.inputs", "./inInvalid2.inputs", -1);
    printf("\nTest 15: ");
    testValidInputInFile("./in.inputs", "./inWithCapitals.inputs",1);
    //we have now tested all functionality of the fileFunctions.h file
    //we will now test the transitionFunctions.h file
    //we dont need to test the function readInputs because all errors within the input file were caught in validInputLines -- checked syntax and num lines
    printf("\nTest 16: ");
    testTooLargeNextState("./in.inputs", "./FSMnextStateInvalid.fsm", -1);
    printf("\nTest 17: ");
    testNegativeNextState("./in.inputs", "./FSMnegState.fsm", -1);
    printf("\nTest 18: ");
    testInputHasNoMatch("./inWithCapitals.inputs", "./FSMdef.fsm", -1);
    printf("\nTest 19: ");
    testInputandFSMValid("./inWithCapitals.inputs", "./FSMcapitalValid.fsm", 3);
    //we have now tested all functionality of the transitionFunctions.h file
}

//test functions for fileFunctions.h
void testArgumentsLess(char *fsm, char *infile, int expect){
    printf("Passing too little command line arguments to program.\n");
    //program has embedded print messages that print on error.
    // so it will print these out before we have the test val
    // printf("Expect Program to print out:Wrong number of arguments were entered.
    // Cannot complete Program, terminating.";
    int result = readFiles(2, fsm, infile);
    printf("\n%s: result=%d, expected=%d, actual=%d\n",
           (expect == result ? "PASSED" : "FAILED"),
           result, expect, result);

}
void testArgumentsMore(char *fsm, char *infile, int expect){
    printf("Passing too many command line arguments to program.\n");
    //printf("Expect Program to print out:Wrong number of arguments were entered.
    // Cannot complete Program, terminating.");
    int result = readFiles(4, fsm, infile);
    printf("\n%s: result=%d, expected=%d, actual=%d\n",
           (expect == result ? "PASSED" : "FAILED"),
           result, expect, result);

}
void testInvalidFSMFile(char *fsm, char *infile, int expect){
    //give FSMDefFile that doesnt exist, see if it error appears like it should
    printf("Passing invalid FSM definition file to program.\n");
    //printf("Expect Program to print out:Could not open FSM definition file.
    // Terminating Program.");
    int result = readFiles(3, fsm, infile);
    printf("\n%s: result=%d, expected=%d, actual=%d\n",
           (expect == result ? "PASSED" : "FAILED"),
           result, expect, result);

}
void testInvalidInputFile(char *fsm, char *infile, int expect){
    //give inputFile that doesnt exist, see if it error appears like it should
    printf("Passing invalid Inputs file to program.\n");
    //printf("Expect Program to print out:processing FSM definition file %s
    // and the number of transitions in the file
    // Could not open inputs file. Terminating Program.\n", fsm);
    int result = readFiles(3, fsm, infile);
    printf("\n%s: result=%d, expected=%d, actual=%d\n",
           (expect == result ? "PASSED" : "FAILED"),
           result, expect, result);
}
void testOutputWithValidFiles(char *fsm, char *infile, int expect){
    //give files that exists
    printf("Passing valid files to program.\n");
    //printf("Expect Program to print out:processing FSM definition file %s
    // and the number of transitions in the file processing FSM inputs file %s", fsm, infile);
    int result = readFiles(3, fsm, infile);
    printf("%s: result=%d, expected=%d, actual=%d\n",
           (expect == result ? "PASSED" : "FAILED"),
           result, expect, result);
}
void testFSMTooManyStates(char *fsm, int expect){
    printf("Passing FSM file with too many states (51 to be exact).\n");
    //printf("Expect Program to print out: Too many states in FSM definition file.
    // FSM is limited to 50 states. Terminating Program.");
    int result = validStartStates(fsm);
    printf("\n%s: result=%d, expected=%d, actual=%d\n",
           (expect == result ? "PASSED" : "FAILED"),
           result, expect, result);
}
void testEmptyFSMFile(char *fsm, int expect){
    printf("Passing FSM file with no states (i.e. empty).\n");
    //printf("Expect Program to print out: FSM definition file was empty. Terminating Program.");
    int result = validStartStates(fsm);
    printf("\n%s: result=%d, expected=%d, actual=%d\n",
           (expect == result ? "PASSED" : "FAILED"),
           result, expect, result);
}
void testTooLargeStateFSMFile(char *fsm, int expect){
    printf("Passing FSM file with invalid state (too large to be an int value).\n");
    //printf("Expect Program to print out:Invalid start state value in FSM file.
    // State value exceeded max integer value in C language. Terminating Program.")
    int result = validStartStates(fsm);
    printf("\n%s: result=%d, expected=%d, actual=%d\n",
           (expect == result ? "PASSED" : "FAILED"),
           result, expect, result);
}
void testNegStartStateFSMFile(char *fsm, int expect){
    printf("Passing FSM file with negative start state.\n");
    //printf("Expect Program to print out:Negative state numbers are not allowed in the FSM definition file.
    // Terminating Program.");
    int result = validStartStates(fsm);
    printf("\n%s: result=%d, expected=%d, actual=%d\n",
           (expect == result ? "PASSED" : "FAILED"),
           result, expect, result);
}
void testLineTooLongFSMFile(char *fsm, int expect){
    printf("Passing FSM file with line that exceeds valid capacity of 24 characters (line error in the file has 25 characters).\n");
    //printf("Expect Program to print out:Line in FSM file exceeds length capacity.
    // Incorrect format of file. Terminating Program.");
    int result = validStartStates(fsm);
    printf("\n%s: result=%d, expected=%d, actual=%d\n",
           (expect == result ? "PASSED" : "FAILED"),
           result, expect, result);
}
void testWithValidFSMFile(char *fsm, char*fsm2, int expect){
    printf("Passing FSM files that should pass the validStartStates function with no errors. Second file has exactly 50 states.\n");
    //printf("Expect Program to print out nothing.\n");
    int v = validStartStates(fsm);
    int v2 = validStartStates(fsm2);
    int vAll = v==1&&v2==1? 1 : 0;
    //if (vAll){ //if both are successful
        //printf("Program printed nothing. FSM files pass this function.");
    printf("%s: result=%d, expected=%d, actual=%d\n",
           (expect == vAll ? "PASSED" : "FAILED"),
           vAll, expect, vAll);
}
void testTooManyInputs(char *input, int expect){
    printf("Passing input file with too many inputs (exceeds the max of 250 inputs).\n");
    //printf("Expect Program to print out:Too many inputs in file.
    // Maximum amount allowed is 250. Terminating Program.");
    int result = validInputLines(input);
    printf("\n%s: result=%d, expected=%d, actual=%d\n",
           (expect == result ? "PASSED" : "FAILED"),
           result, expect, result);
}
void testEmptyInputFile(char *input, int expect){
    printf("Passing empty input file.\n");
    //printf("Expect Program to print out:Inputs file was empty. Terminating Program.");
    int result = validInputLines(input);
    printf("\n%s: result=%d, expected=%d, actual=%d\n",
           (expect == result ? "PASSED" : "FAILED"),
           result, expect, result);
}
void testInvalidInputInFile(char *input, char *input2, int expect){
    printf("Passing input files with invalid input. One file contains numbers and the other an input longer than one char.\n");
    //printf("Expect Program to print out twice:Incorrect input format. Terminating program.");
    int n = validInputLines(input);
    int n2 = validInputLines(input2);
    int nAll = n==-1&&n2==-1? -1 : 0;
    printf("\n%s: result=%d, expected=%d, actual=%d\n",
           (expect == nAll ? "PASSED" : "FAILED"),
           nAll, expect, nAll);
}
void testValidInputInFile(char *input, char *input2, int expect){
    printf("Passing input files with valid input.\n"
           "Second file contains capital letters as well as lowercase. First file contains only lowercase.\n");
    //printf("Expect Program to print out nothing.");
    int v = validInputLines(input);
    int v2 = validInputLines(input2);
    int vAll = v==1&&v2==1? 1 : 0;
    //if (vAll){ //if both are successful
        //printf("Program printed nothing. Input files pass this function.");
    printf("%s: result=%d, expected=%d, actual=%d\n",
           (expect == vAll ? "PASSED" : "FAILED"),
           vAll, expect, vAll);
}
//end of test functions for fileFunctions.h
//we dont need to test the function readInputs because all errors with input file were caught in validInputLines -- checked syntax and num lines
//but we will call readInputs to test findNextState bc it calls this function
void testTooLargeNextState(char *input, char *fsm, int expect){
    printf("Passing valid input file and fsm def file with state that exceeds int_max to transition into.\n");
    //printf("Expect Program to print out when it hits the invalid state transition:
    // Incorrect state transition value in FSM file at state "stateValue" and input "inputValue"
    // Next state value exceeded max integer value in C language. Terminating Program.");
    int state;
    int step = -1;
    state = readInputs(input, fsm, &step);
    printf("\n%s: result=%d, expected=%d, actual=%d\n",
           (expect == state ? "PASSED" : "FAILED"),
           state, expect, state);
}
void testNegativeNextState(char *input, char *fsm, int expect){
    printf("Passing valid input file and fsm def file with negative state to transition into.\n");
    //printf("Expect Program to print out when it hits the invalid state transition:
    // Negative state numbers are not allowed in the FSM definition file. Terminating Program.");
    int state;
    int step = -1;
    state = readInputs(input, fsm, &step);
    printf("\n%s: result=%d, expected=%d, actual=%d\n",
           (expect == state ? "PASSED" : "FAILED"),
           state, expect, state);
}
void testInputHasNoMatch(char *input, char *fsm, int expect){
    printf("Passing valid input file and fsm def file but some inputs are not in the fsm def file (i.e won't match any fsm def lines).\n");
    //printf("Expect Program to print out when it hits the input line with no match:
    // FSM definition file is in incorrect format or an incorrect input was entered for
    // the current state. Terminating Program.");
    int state;
    int step = -1;
    state = readInputs(input, fsm, &step);
    printf("\n%s: result=%d, expected=%d, actual=%d\n",
           (expect == state ? "PASSED" : "FAILED"),
           state, expect, state);
}

void testInputandFSMValid(char *input, char *fsm, int expect){
    printf("Passing valid input file and fsm def file.\n");
    //printf("Expect Program to print out all state transitions until last state (which is 3).");
    int state;
    int step = -1;
    state = readInputs(input, fsm, &step);
    printf("\n%s: result=%d, expected=%d, actual=%d\n",
           (expect == state ? "PASSED" : "FAILED"),
           state, expect, state);
}

