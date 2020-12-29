// Created by Julie Chase on 12/21/20.
#include <stdio.h>
#include "fileFunctions.h"
#include "transitionFunctions.h"

int main(int argc, char *argv[]) {
    int debug = 0;
    //argv[1] is fsm file
    //argv[2] is inputs file
    //check that files are able to be opened
    int fileInputs = readFiles(argc, argv[1], argv[2], &debug);
    //readFiles also checks that the FSM def file has at most 50 states and that all start states are valid
    //it also checks that all input lines are valid and that the number of lines in the inputs file does not exceed 250
    if (fileInputs < 0){ //if it is < 0, it means there was an issue opening one of the files or an issue processing one of he files
        exit(1);
    }
    int step =-1; // we want first step to be 0 so start step at -1
    int finalState; //this is where we save our final state to be printed out at the end
    //readInputs will loop through entire input file and print out state transitions as they happen
    //final return of readInputs is the state we are in when we get to the end of the inputs file
    finalState = readInputs(argv[2], argv[1], &step, &debug);
    if (finalState == -1){ //if it is < 0, it means there was some sort of error in readInputs bc all states need to be > 0
        exit(1);
    }
    //if we got here, it means our program ran successfully!
    step+=1;
    printf("after %d steps, state machine finished successfully at state %d\n", step, finalState);

}
