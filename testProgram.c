//
// Created by Julie Chase on 12/22/20.
//
#include <stdio.h>
#include "fileFunctions.h"
#include "transitionFunctions.h"

//testers for fileFunctions.h
void testArgumentsLess(char *fsm, char *infile);
void testArgumentsMore(char *fsm, char *infile);
void testInvalidFSMFile(char *fsm, char *infile);
void testInvalidInputFile(char *fsm, char *infile);
void testOutputWithValidFiles(char *fsm, char *infile);
void testFSMTooManyStates(char *fsm);
void testEmptyFSMFile(char *fsm);
void testTooLargeStateFSMFile(char *fsm);
void testNegStartStateFSMFile(char *fsm);
void testLineTooLongFSMFile(char *fsm);
void testWithValidFSMFile(char *fsm, char*fsm2);
void testTooManyInputs(char *input);
void testEmptyInputFile(char *input);
void testInvalidInputInFile(char *input, char *input2);
void testValidInputInFile(char *input, char *input2);
//testers for transitionFunctions.h
void testTooLargeNextState(char *input, char *fsm);
void testNegativeNextState(char *input, char *fsm);
void testInputHasNoMatch(char *input, char *fsm);

//I passed in two correct files into the program to test functions
int main(void){
    printf("Test 1: ");
    testArgumentsLess("./FSMdef.fsm", "./in.inputs");
    printf("\nTest 2: ");
    testArgumentsMore("./FSMdef.fsm", "./in.inputs");
    printf("\nTest 3: ");
    testInvalidFSMFile("./FSMNONE.txt", "./in.inputs");
    printf("\nTest 4: ");
    testInvalidInputFile("./FSMdef.fsm", "./inputsNONE.txt");
    printf("\nTest 5: ");
    testOutputWithValidFiles("./FSMdef.fsm", "./in.inputs");
    printf("\nTest 6: ");
    testFSMTooManyStates("./FSMtoomany.fsm");
    printf("\nTest 7: ");
    testEmptyFSMFile("./emptyFSM.fsm");
    printf("\nTest 8: ");
    testTooLargeStateFSMFile("./FSMinvalidState.fsm");
    printf("\nTest 9: ");
    testNegStartStateFSMFile("./FSMnegStart.fsm");
    printf("\nTest 10: ");
    testLineTooLongFSMFile("./FSMlineLong.fsm");
    printf("\nTest 11: ");
    testWithValidFSMFile("./FSMdef.fsm", "./FSM50states.fsm");
    printf("\nTest 12: ");
    testTooManyInputs("./inTooMany.inputs");
    printf("\nTest 13: ");
    testEmptyInputFile("./inEmpty.inputs");
    printf("\nTest 14: ");
    testInvalidInputInFile("./inInvalid1.inputs", "./inInvalid2.inputs");
    printf("\nTest 15: ");
    testValidInputInFile("./in.inputs", "./inWithCapitals.inputs");
    //we have now tested all functionality of the fileFunctions.h file
    //we will now test the transitionFunctions.h file
    //we dont need to test the function readInputs because all errors within the input file were caught in validInputLines -- checked syntax and num lines
    printf("\nTest 16: ");
    testTooLargeNextState("./in.inputs", "./FSMnextStateInvalid.fsm");
    printf("\nTest 17: ");
    testNegativeNextState("./in.inputs", "./FSMnegState.fsm");
    printf("\nTest 18: ");
    testInputHasNoMatch("./inWithCapitals.inputs", "./FSMdef.fsm");
    //we have now tested all functionality of the transitionFunctions.h file
}

//test functions for fileFunctions.h
void testArgumentsLess(char *fsm, char *infile){
    printf("Passing too little command line arguments to program.\n");
    printf("Expect Program to print out:\nWrong number of arguments were entered. "
           "Cannot complete Program, terminating.\n");
    printf("Program prints:\n");
    int n = readFiles(2, fsm, infile);
    if(n<0){
        printf("\nEnd of Program Print Message. Main program would then exit entire program.\n");
    }
}
void testArgumentsMore(char *fsm, char *infile){
    printf("Passing too many command line arguments to program.\n");
    printf("Expect Program to print out:\nWrong number of arguments were entered. "
           "Cannot complete Program, terminating.\n");
    printf("Program prints:\n");
    int n = readFiles(4, fsm, infile);
    if(n<0){
        printf("\nEnd of Program Print Message. Main program would then exit entire program.\n");
    }
}
void testInvalidFSMFile(char *fsm, char *infile){
    //give FSMDefFile that doesnt exist, see if it error appears like it should
    printf("Passing invalid FSM definition file to program.\n");
    printf("Expect Program to print out:\nCould not open FSM definition file. Terminating Program.\n");
    printf("Program prints:\n");
    int n = readFiles(3, fsm, infile);
    if(n<0){
        printf("\nEnd of Program Print Message. Main program would then exit entire program.\n");
    }
}
void testInvalidInputFile(char *fsm, char *infile){
    //give inputFile that doesnt exist, see if it error appears like it should
    printf("Passing invalid Inputs file to program.\n");
    printf("Expect Program to print out:\n"
           "processing FSM definition file %s\nand the number of transitions in the file\n"
           "Could not open inputs file. Terminating Program.\n", fsm);
    printf("Program prints:\n");
    int n = readFiles(3, fsm, infile);
    if(n<0){
        printf("\nEnd of Program Print Message. Main program would then exit entire program.\n");
    }
}
void testOutputWithValidFiles(char *fsm, char *infile){
    //give files that exists
    printf("Passing valid files to program.\n");
    printf("Expect Program to print out:\n"
           "processing FSM definition file %s\nand the number of transitions in the file\n"
           "processing FSM inputs file %s\n", fsm, infile);
    printf("Program prints:\n");
    int n = readFiles(3, fsm, infile);
    if(n<0){
        printf("\nEnd of Program Print Message. Main program would then exit entire program.\n");
    }
    else{
        printf("End of Program Print Message.\n");
    }
}
void testFSMTooManyStates(char *fsm){
    printf("Passing FSM file with too many states (51 to be exact).\n");
    printf("Expect Program to print out:\n"
           "Too many states in FSM definition file. FSM is limited to 50 states. Terminating Program.\n");
    printf("Program prints:\n");
    int n = validStartStates(fsm);
    if(n<0){
        printf("\nEnd of Program Print Message. Main program would then exit entire program.\n");
    }
}
void testEmptyFSMFile(char *fsm){
    printf("Passing FSM file with no states (i.e. empty).\n");
    printf("Expect Program to print out:\n"
           "FSM definition file was empty. Terminating Program.\n");
    printf("Program prints:\n");
    int n = validStartStates(fsm);
    if(n<0){
        printf("\nEnd of Program Print Message. Main program would then exit entire program.\n");
    }
}
void testTooLargeStateFSMFile(char *fsm){
    printf("Passing FSM file with invalid state (too large to be an int value).\n");
    printf("Expect Program to print out:\n"
           "Invalid start state value in FSM file. State value exceeded max integer value in C language. Terminating Program.\n");
    printf("Program prints:\n");
    int n = validStartStates(fsm);
    if(n<0){
        printf("\nEnd of Program Print Message. Main program would then exit entire program.\n");
    }
}
void testNegStartStateFSMFile(char *fsm){
    printf("Passing FSM file with negative start state.\n");
    printf("Expect Program to print out:\n"
           "Negative state numbers are not allowed in the FSM definition file. Terminating Program.\n");
    printf("Program prints:\n");
    int n = validStartStates(fsm);
    if(n<0){
        printf("\nEnd of Program Print Message. Main program would then exit entire program.\n");
    }
}
void testLineTooLongFSMFile(char *fsm){
    printf("Passing FSM file with line that exceeds valid capacity of 24 characters (line error in the file has 25 characters).\n");
    printf("Expect Program to print out:\n"
           "Line in FSM file exceeds length capacity. Incorrect format of file. Terminating Program.\n");
    printf("Program prints:\n");
    int n = validStartStates(fsm);
    if(n<0){
        printf("\nEnd of Program Print Message. Main program would then exit entire program.\n");
    }
}
void testWithValidFSMFile(char *fsm, char*fsm2){
    printf("Passing FSM files that should pass the validStartStates function with no errors. Second file has exactly 50 states.\n");
    printf("Expect Program to print out nothing.\n");
    printf("Program prints:\n");
    int v = validStartStates(fsm);
    int v2 = validStartStates(fsm2);
    int vAll = v==1&&v2==1? 1 : 0;
    if (vAll){ //if both are successful
        printf("Program printed nothing. FSM files pass this function.\n");
        printf("End of Program Print Message.\n");
    }
    else{
        printf("\nEnd of Program Print Message. Main program would then exit entire program.\n");
    }
}
void testTooManyInputs(char *input){
    printf("Passing input file with too many inputs (exceeds the max of 250 inputs).\n");
    printf("Expect Program to print out:\n"
           "Too many inputs in file. Maximum amount allowed is 250. Terminating Program.\n");
    printf("Program prints:\n");
    int n = validInputLines(input);
    if(n<0){
        printf("\nEnd of Program Print Message. Main program would then exit entire program.\n");
    }
}
void testEmptyInputFile(char *input){
    printf("Passing empty input file.\n");
    printf("Expect Program to print out:\n"
           "Inputs file was empty. Terminating Program.\n");
    printf("Program prints:\n");
    int n = validInputLines(input);
    if(n<0){
        printf("\nEnd of Program Print Message. Main program would then exit entire program.\n");
    }
}
void testInvalidInputInFile(char *input, char *input2){
    printf("Passing input files with invalid input. One file contains numbers and the other an input longer than one char.\n");
    printf("Expect Program to print out twice:\n"
           "Incorrect input format. Terminating program.\n");
    printf("Program prints:\n");
    int n = validInputLines(input);
    printf("\n");
    int n2 = validInputLines(input2);
    int nAll = n==-1&&n2==-1? 1 : 0;
    if(nAll){ //if both are unsuccessful
        printf("\nEnd of Program Print Message. Main program would then exit entire program.\n");
    }
}
void testValidInputInFile(char *input, char *input2){
    printf("Passing input files with valid input.\n"
           "Second file contains capital letters as well as lowercase. First file contains only lowercase.\n");
    printf("Expect Program to print out nothing.\n");
    printf("Program prints:\n");
    int v = validInputLines(input);
    int v2 = validInputLines(input2);
    int vAll = v==1&&v2==1? 1 : 0;
    if (vAll){ //if both are successful
        printf("Program printed nothing. Input files pass this function.\n");
        printf("End of Program Print Message.\n");
    }
    else{
        printf("\nEnd of Program Print Message. Main program would then exit entire program.\n");
    }
}
//end of test functions for fileFunctions.h
//we dont need to test the function readInputs because all errors with input file were caught in validInputLines -- checked syntax and num lines
//but we will call readInputs to test findNextState bc it calls this function
void testTooLargeNextState(char *input, char *fsm){
    printf("Passing valid input file and fsm def file with state that exceeds int_max to transition into.\n");
    printf("Expect Program to print out when it hits the invalid state transition:\n"
           "Incorrect state transition value in FSM file at state \"stateValue\" and input \"inputValue\"."
           "Next state value exceeded max integer value in C language. Terminating Program.\n");
    printf("Program prints:\n");
    int state;
    int step = -1;
    state = readInputs(input, fsm, &step);
    if (state==-1){
        printf("\nEnd of Program Print Message. Main program would then exit entire program.\n");
    }
}
void testNegativeNextState(char *input, char *fsm){
    printf("Passing valid input file and fsm def file with negative state to transition into.\n");
    printf("Expect Program to print out when it hits the invalid state transition:\n"
           "Negative state numbers are not allowed in the FSM definition file. Terminating Program.\n");
    printf("Program prints:\n");
    int state;
    int step = -1;
    state = readInputs(input, fsm, &step);
    if (state==-1){
        printf("\nEnd of Program Print Message. Main program would then exit entire program.\n");
    }
}
void testInputHasNoMatch(char *input, char *fsm){
    printf("Passing valid input file and fsm def file but some inputs are not in the fsm def file (i.e won't match any fsm def lines).\n");
    printf("Expect Program to print out when it hits the input line with no match:\n"
           "FSM definition file is in incorrect format or an incorrect input was entered for the current state. Terminating Program.\n");
    printf("Program prints:\n");
    int state;
    int step = -1;
    state = readInputs(input, fsm, &step);
    if (state==-1){
        printf("\nEnd of Program Print Message. Main program would then exit entire program.\n");
    }
}