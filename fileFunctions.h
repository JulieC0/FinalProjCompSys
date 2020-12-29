//
// Created by Julie Chase on 12/21/20.
//
#ifndef FINALPROJCOMPSYS_FILEFUNCTIONS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define lineMaxFSM 30
#define stateMax 15
#define fiftyStatesMax 600
#define maxFSMValidLine 24
#define intakeMax 26
#define maxIntLength 10
#define maxNumStates 50
#define inputMax 5
#define maxInputLines 250
#define error (-1)
#define success 1
#define stateLength 15

int readFiles(int argc, char *arg1, char *arg2, const int *debug);
int validStartStates(char *fsmFile, const int *debug);
int validInputLines(char* input, const int *debug);

//this function will make sure that both the input and fsm def files can be read. if not, returns error message
int readFiles(int argc, char *arg1, char *arg2, const int *debug){
    FILE *f1;
    FILE *f2;
    //first argv i.e. [0] is the program name, argv[1] is fsm file, arg[2] is input file
    //the return value of the program will tell us if it is successful or not in main
    if (argc != 3) {
        if (!*debug) {
            printf("Wrong number of arguments were entered. Cannot complete Program, terminating.");
        }
        return error;
    }
    // if we have the correct number of command line args, open our FSM def and input files
    //open fsm file first
    f1 = fopen(arg1, "r");
    if (f1 == NULL) { //if there was an error reading the fsm def file
        if (!*debug) {
            printf("Could not open FSM definition file. Terminating Program.");
        }
        return error;
    }
    else{ //if we are able to read the fsm def file
        if (!*debug) {
            printf("processing FSM definition file %s\n", arg1);
        }
        fclose(f1);
        int n = validStartStates(arg1, debug);
        if (n<0){ //if there was an issue validating the fsm file, error will be printed within validStates()
            return error; //return -1 to reflect that there was an error
        }
        if (!*debug) {
            //printf("FSM has %d transitions\n", count);
            printf("FSM has %d transitions\n", n);
        }
    }
    //now try to open inputs file
    f2 = fopen(arg2, "r");
    if (f2 == NULL) {
        if (!*debug) {
            printf("Could not open inputs file. Terminating Program.");
        }
        return error;
    }
    else{
        if (!*debug){
            printf("processing FSM inputs file %s\n", arg2);
        }
        int v = validInputLines(arg2, debug);
        if (v<0){ //if there was an issue validating the input file, error will be printed within validInputLines()
            return error; //return -1 to reflect that there was an error
        }
        //if inputs file has no errors, close file and return 1 to show success
        fclose(f2);
    }
    return success;
}

//this function will check that the FSM def file has at most 50 states and that all lines contain valid information
int validStartStates(char *fsmFile, const int *debug) {
    char holder[lineMaxFSM] = ""; //to hold each line from fsmFile
    char number[stateMax] = ""; //to hold our start state
    char states[fiftyStatesMax] = ""; //to hold list of all states - enough room for 50 separators and 50 ints of size 10
    int position = 0; //hold position in states we are at when we add a new state
    int count = 0; //to count number of unique states
    int lines = 0; //to count number of transition lines
    char *ptr = "";
    int k;
    int zero = 0;
    //open fsm file
    FILE *fsm = fopen(fsmFile, "r");
    while (!feof(fsm)) { //while not at end of file
        //grabbing 26 but only really grabs 25
        if (fgets(holder, intakeMax, fsm) != NULL) { //max for int is 10 digits + 10 digits + ':' +'>' + letter + '\n' = max length of line is 24
            //so if the fsm def line is longer than 25 characters, then the string length we grab will equal 25
            //i.e. if the line was longer than 25 characters, then strlen(holder) will be the max we grab which is 25
            //we can only validly take 24 characters at a time - so we expect strlen(holder)<=24 if valid
            if (strlen(holder) > maxFSMValidLine) {
                if (!*debug) {
                    printf("Line in FSM file exceeds length capacity. Incorrect format of file. Terminating Program.");
                }
                fclose(fsm);
                return error; //failure signal
            }
            int i = 0;
            while (holder[i] != ':') { //for each digit in the start state
                if (!(holder[i] >= '0' && holder[i] <= '9')) { //if it is not a number
                    if (!*debug) {
                        printf("Incorrect format for FSM start state.\n"
                               "States must contain only numbers and no special characters (including a minus sign). Terminating Program.");
                    }
                    fclose(fsm);
                    return error;
                }
                number[i] = holder[i]; //copy over the start state into number array if it is valid
                i++;
            }
            i++;
            int j = i;
            //check that the rest of the line is valid
            //next should be a single char and >
            if (!(((holder[j] >= 'a' && holder[j] <= 'z') || (holder[j] >= 'A' && holder[j] <= 'Z')) &&
                  holder[j + 1] == '>')) {
                if (!*debug) {
                    printf("FSM definition file is in incorrect format. Terminating Program.");
                }
                fclose(fsm);
                return error;
            }
            j += 2;
            char stateN[stateLength]="";
            //holder format: state:input>nextState - we need to extract nextState
            int len;
            if (holder[strlen(holder) - 1] == '\n') { //check whether line has a newline after (last line might not)
                //we check this to know when to stop for the for loop below
                //ok to cast to int bc we only accept 26 chars at a time anyways so max length of holder will be 26
                len = (int) strlen(holder) - 1;
            }
            else {
                len = (int) strlen(holder);
            }
            int a;
            //check the rest of the line after '>' is valid
            for (a = 0; j < len; a++) {
                if (!(holder[j] >= '0' && holder[j] <= '9')) { //if there is an incorrect value as next state
                    if (!*debug) {
                        printf("Incorrect format for FSM transition state.\n"
                                   "States must contain only numbers and no special characters (including a minus sign). Terminating Program.");
                    }
                    fclose(fsm);
                    return error;
                }
                else {
                    stateN[a] = holder[j]; //copy next state into stateN string/array
                    j++;
                }
            }
            //k becomes a++ after the loop - found in debugger
            stateN[a] = '\0'; //makes sure we know where state ends in stateN array
            //get here we have transition state
            char *p = "";
            //convert our state to a long long to check whether it is larger than an int can hold
            // we are only allowed to use valid integers for states
            long long value = strtol(stateN, &p, 10);
            //check if nextState is a valid int
            if (strlen(stateN) > maxIntLength || value > INT_MAX) {
                if (!*debug) {
                    printf("Incorrect state transition value in FSM file.\n"
                           "Next state value on one of the lines exceeded max integer value in C language. Terminating Program.");
                }
                fclose(fsm);
                return error;
            }
            //if no problems with line in fsm def file, i.e. in correct format
            //i holds the value after the last digit in the start state
            number[i-1] = '\0'; //terminate the start state number array with a null so we know where state ends in array
            long long val = strtoll(number, &ptr, 10); //get the numeric value of the start state
            //then check that the numeric value of the start state is valid
            //by checking length and value,
            // we make sure each start state (and eventually all the states we transition to) are valid
            if (strlen(number) > maxIntLength || val > INT_MAX) { //if the state's numeric value is invalid
                if (!*debug) {
                    printf("Invalid start state value in FSM file. State value exceeded max integer value in C language. Terminating Program.");
                }
                fclose(fsm);
                return error; //failure signal
            }
            if (val == 0){ //check to make sure there is a transition for 0
                zero=1;
            }
            // if line is valid, check if start state is in the states array. if not, add it to the states array
            int in = 0; //this will let us know whether or not the start state is already in the states array
            char statesCopy[fiftyStatesMax] = ""; //holds copy so strtok doesn't change original states array -
            // enough room for 50 separators and 50 ints of size 10
            const char* separator = "|"; //this is how our states are separated
            strcpy(statesCopy, states); // copy states
            //below code using strtok and while loop idea was taken from
            //https://www.tutorialspoint.com/c_standard_library/c_function_strtok.htm
            char *eachState = strtok(statesCopy, separator); //eachState will no refer to each state in our states array
            int compare;
            while (eachState!= NULL){
                compare = strcmp(eachState, number); //compare the current start state with each value in the states array
                if (compare == 0){ // if the state is already in states array, reflect this with the in variable and exit the while loop
                    in=1;
                    break;
                }
                else{
                    eachState = strtok(NULL, separator); //go to next value in states array
                }
            }
            if (in==0){//if we exit the while loop and in=0, it means the state is not already in the states array
                //add current start state to the states array
                i=0;
                //we set k=position so that we start at the next available spot in the states array
                for (k=position; k<position+strlen(number); k++){
                    states[k] = number[i];
                    i++;
                }
                //k gets incremented to k++ after loop
                position = k; //reset to position to k (the incremented position)
                states[position] = '|'; //add delimiter after
                position+=1; //increment position by 1
                count+=1; //increment count of states
                if (count>maxNumStates){ //we can only have a max of 50 different states in our file
                    if (!*debug) {
                        printf("Too many states in FSM definition file. FSM is limited to 50 states. Terminating Program.");
                    }
                    fclose(fsm);
                    return error;
                }
            }
            lines+=1;
        }
    }
    if (!zero){ //will see if there is no transition for zero - this also happens ot catch empty files
        if (!*debug) {
            printf("FSM definition file did not contain a state transition for the initial start state at 0.\n"
                   "0 must have at least one state transition. Terminating Program.");
        }
        fclose(fsm);
        return error;
    }
    fclose(fsm);
    return lines; //on success
}
//this function checks that all input lines are valid and that the number of lines in the inputs file does not exceed 250
int validInputLines(char* input, const int *debug){
    int count = 0; //count for number of inputs
    char data[inputMax] = ""; //input line only needs space for one char + newline but giving it extra space
    FILE *inFile = fopen(input, "r");
    while (!feof(inFile)) { //reads inputs file line by line
        if (fgets(data, inputMax, inFile) != NULL){
            //check that input is a letter followed by either a newline or a null terminator (if last line in file may not have \n)
            if (!(((data[0] >= 'a' && data[0] <= 'z')||(data[0] >= 'A' && data[0] <= 'Z')) && (data[1]=='\n'||data[1]=='\0'))) {
                if (!*debug) {
                    printf("Incorrect input format. Terminating program.");
                }
                fclose(inFile);
                return error;
            }
            //if it does match the correct format, increment count of lines in file
            count++;
            if (count>maxInputLines){ //if we exceed 250 lines, which is the max we will allow, it is an error
                if (!*debug) {
                    printf("Too many inputs in file. Maximum amount allowed is 250. Terminating Program.");
                }
                fclose(inFile);
                return error;
            }
        }
    }
    if (count == 0){ //if FSM file was empty
        if (!*debug) {
            printf("Inputs file was empty. Terminating Program.");
        }
        fclose(inFile);
        return error;
    }
    //if encountered no errors thus far, input file seems to be in correct format
    fclose(inFile);
    return success; //on success
}

#endif //FINALPROJCOMPSYS_FILEFUNCTIONS_H
