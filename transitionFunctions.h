//
// Created by Julie Chase on 12/21/20.
//
#ifndef FINALPROJCOMPSYS_TRANSITIONFUNCTIONS_H
#define FINALPROJCOMPSYS_TRANSITIONFUNCTIONS_H
#include <string.h>
#include <stdio.h>
#include <limits.h>
#include <math.h>
#define inputLineGrab 5
#define stateLength 15
#define FSMLineHolder 30
#define maxFSMLineTake 26
#define maxFSMValidLine 24
#define maxIntLength 10
#define error (-1)

int readInputs(char *inputs, char *fsmFile, int *step, const int *debug);
int findNextState(char *fsmFile, const int *currentState, char *input, const int *currentStep, const int *debug);

//this function reads through the inputs file line by line and for each input line, calls findNextState
// which loops through the fsm file to find the transition for the current input and state
int readInputs(char *inputs, char *fsmFile, int *step, const int *debug) {
    int currentState = 0;
    int nextState = -1; // default to return to show error if error occurs because states must be >= 0
    char input[inputLineGrab] = ""; //to hold our input letter and \n
    //open inputs file
    FILE* inFile = fopen(inputs, "r");
    while (!feof(inFile)) { //reads inputs file line by line
        if (fgets(input, 4, inFile) != NULL) { //put line into input string/array
            *step = *step + 1; //increment step suing pointer and de-referencing
            //input = "a\n" or "A\n"- we checked this format in fileFunctions.h
            nextState = findNextState(fsmFile, &currentState, input, step, debug); //call findNextState to find transition
            if (nextState == -1){ //if nextState is -1, it means there was an error somewhere in findNextState --> exit function and go to main
                fclose(inFile);
                return nextState;
            }//if no error, just keep looping over inputs file to get to final state
        }
        currentState = nextState;//change current state to the state we transitioned into
    }
    return currentState; //return final state at the end
}
int findNextState(char *fsmFile, const int *currentState, char *input, const int *step, const int *debug){
    //format of file was already checked in processing.
    int nextState;
    char state[stateLength] = ""; //to hold state as char instead of int
    sprintf(state, "%d", *currentState); //puts current state into state array by converting currentState to a string
    char holder[FSMLineHolder] = "";// to hold FSM definition line info
    //now we will try to find the line in the FSM file which tells us what the next state is
    //make sure FSM definition file meets expected format and find next state -
    // we only made sure start state and line length was of correct format in fileFunctions.h validStates()
    //so now we need to check rest of line and next state's format
    //open FSM def file to start at the beginning each time
    FILE *fsm = fopen(fsmFile, "r");
    while (!feof(fsm)){ //while not at end of file or until find match (returns if we find match)
        if (fgets(holder, maxFSMLineTake, fsm) != NULL) { //line by line put into holder array
            //fgets includes newline so have to add one to length - last line may or may not have newline
            //int_max in c is 10 numbers long -- if had 2 int_max sized numbers + char + ":" + ">" = 23 + 1 for newline char if has newline
            if (strlen(holder)<=maxFSMValidLine) { //if greater than this, than the state values are too large to be valid
                int t;
                for (t=0; t <= strlen(state); t++) { //state doesnt have \n bc converted from int to string
                    //loop until not a match or got through length of string
                    if (state[t] != holder[t] || t == strlen(state)) { // break when hit end of State array or not a match
                        break;
                    }
                    //if state[t]=holder[t] (i.e. it matches), loop keeps going until hit strlen(state)
                }
                //once here, we broke the for loop
                //now figure out why
                //if strlen(state) = t,
                // means we got through the whole state and holder arrays with no issue - i.e. they matched
                //now we will check the rest of holder to see if it is a match
                // needs to be state:char>state
                if (t == strlen(state)) {//checks that we didnt break for loop bc there was a mismatch, rather that whole string matched
                    if (holder[t] == ':') { //next char is ':'
                        if (holder[t + 1] == input[0]) { //then next char is our input (input[1] = '\n' on most lines or '\0' if last line)
                            if (holder[t + 2] == '>') { //after input we want a '>'
                                if (holder[t + 3] >= '0' && holder[t+3]<='9') { // check that after '>', it is a number
                                    // this also makes sure nextState isn't negative
                                    //reach here we know that so far it is in correct format and we have found a match
                                    char stateN[stateLength];
                                    //holder format: state:input>nextState - we need to extract nextState
                                    int len;
                                    if (holder[strlen(holder)-1] == '\n'){ //check whether line has a newline after (last line might not)
                                        //we check this to know when to stop for the for loop below
                                        //ok to cast to int bc we only accept 26 chars at a time anyways so max length of holder will be 26
                                        len = (int)strlen(holder)-1;
                                    }
                                    else{
                                        len = (int)strlen(holder);
                                    }
                                    int i;
                                    for (i = 0; i < len; i++) { //go through matched string in holder to get the nextState
                                        if (holder[i] == '>') { //once we hit the >, it means NextState is what is written next
                                            i++; // add one to i to get to position of nextState
                                            int k;
                                            for (k = 0; i < len; k++) { // loop through rest of holder after '>'
                                                //do a loop bc state could be longer than one digit
                                                stateN[k] = holder[i]; //copy next state into stateN string/array
                                                i++;
                                            }
                                            //k becomes k++ after the loop - found in debugger
                                            stateN[k] = '\0'; //makes sure we know where state ends in stateN array
                                            break;
                                        }
                                    }
                                    char *ptr = "";
                                    //if nextState is a valid number, convert to int and return it after printf
                                    long int nS;
                                    nS = strtol(stateN, &ptr, 10);
                                    nextState = (int) nS;
                                    if (!*debug) {
                                        printf("\t at step %d, input %c transitions FSM from state %d to state %d\n",
                                               *step, input[0], *currentState, nextState);
                                    }
                                    fclose(fsm);
                                    return nextState;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    // if got here, means there was no match found - bad input for current state
    //if state not there bc it is a dead end state also, then we give error
    if (!*debug) {
        //FSM definition file is in incorrect format or
        printf("An incorrect input was entered for the current state. Terminating Program.");
    }
    fclose(fsm);
    return error;
}





#endif //FINALPROJCOMPSYS_TRANSITIONFUNCTIONS_H


