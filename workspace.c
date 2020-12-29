//
// Created by Julie Chase on 12/21/20.
//
//this file contains my program without being separated into functions
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    //first argv i.e. [0] is the program name
    if (argc != 3) {
        printf("Wrong number of arguments were entered. Cannot complete Program, terminating.");
        exit(1);
    }
    FILE *f1;
    FILE *f2;
    // if we have correct number of command line args, open our FSM def and input files
    f1 = fopen(argv[1], "r");
    if (f1 == NULL) {
        printf("%s\n",argv[1]);
        printf("Could not open file. Terminating Program.");
        exit(1);
    }
    else{
        printf("processing FSM definition file %s\n", argv[1]);
        int count = 0;
        char line[10];
        //read through file, count number of lines (= # of transitions)
        while (!feof(f1)) { //read inputs file line by line
            if (fgets(line, 10, f1) != NULL) { //put line into input string
                count += 1;
            }
        }
        printf("FSM has %d transitions\n", count);
        // close and reopen to start reading again from beginning of file
        // may have to open in close in input while loop
        fclose(f1);
    }
    f2 = fopen(argv[2], "r");
    if (f2 == NULL) {
        printf("Could not open file. Terminating Program.");
        exit(1);
    }
    else{
        printf("processing FSM inputs file %s\n", argv[2]);
    }
    int currentState = 0; // initial state is always zero
    char state[5]; //to hold state as char
    int nextState = 0;
    char holder[10];// to hold FSM definition line info
    char input[3]; //to hold our input letter and \n and ending 0
    int step =-1; // we want first step to be 0 so start at -1
    //start at open inputs file
    while (!feof(f2)) { //reads inputs file line by line
        if (fgets(input, 10, f2) != NULL) { //put line into input string/array
            step+=1;
            if (step > 249){ // we say 249 instead of 250 bc we started at -1
                printf("Too many inputs in file. Maximum amount allowed is 250. Terminating Program.");
                exit(1);
            }
            //input = "a\n" - if doesnt look like this,
            if (!(input[0] >= 'a' && input[0]<='z' && strlen(input) == 2)){
                printf("incorrect input format. Terminating program");
                exit(1);
            }
            //got here means inputs file is in correct format
            //now we will try to find the line which tells us what the next state is in the FSM def file
            //make sure FSM definition file meets expected format and find next state
            //re-open FSM def file to start at the beginning each time
            f1 = fopen(argv[1], "r");
            //start all as false
            int matchFound = 0;
            int singNumState = 0;
            int dubNumState = 0;
            int lastTwoDub = 0;
            int lastTwoSing = 0;
            while (!feof(f1) && matchFound != 1) { //while not at end of file or until find match
                if (fgets(holder, 10, f1) != NULL) { //line by line put into holder array
                    //regRetFSM = regexec(&regex, holder, 0, NULL, 0); //check for match of state and input
                    //fgets includes newline so have to add one to length
                    //length of holder will be 8 if both states are double digits for starting double digit and 7 if second state isnt double digit
                    lastTwoDub = ((holder[5]>='0' && holder[5]<='9' && strlen(holder) == 7 )|| (holder[5]>='1' && holder[5]<='5' && holder[6]>='0' && holder[6]<='9' && strlen(holder) == 8));
                    //length of holder will be 6 if both states are single digits and 8 if second state is double digit
                    lastTwoSing = ((holder[4]>='0' && holder[4]<='9' && strlen(holder) == 6) || (holder[4]>='1' && holder[4]<='5' && holder[5]>='0' && holder[5]<='9' && strlen(holder) ==7));
                    sprintf(state, "%d", currentState); //puts current state into state array by converting currentState to a string
                    //for format of 00:a>00
                    //input[0] holds our input
                    dubNumState = holder[0]==state[0] && holder[1] == state[1] && holder[2]== ':' && holder[3]==input[0] && holder[4] == '>' && lastTwoDub;
                    //for format of 0:a>00
                    singNumState = holder[0]==state[0] && holder[1]== ':' && holder[2]==input[0] && holder[3] == '>' && lastTwoSing;
                    if (singNumState || dubNumState){
                        matchFound = 1;
                        //if (regRetFSM == 0) { //i.e. we found a match for the current state and input on that line
                        // make copy of string and find location of nextState
                        char stateN[10];
                        int i;
                        //holder format: state:input>nextState - we need to extract nextState
                        for(i=0;i<strlen(holder); i++){ //go through matched string in holder to get the nextState
                            if (holder[i] == '>'){ //once we hit the >, it means NextState is what is written next
                                i++; // add one to i to get to value of nextState
                                int k;
                                for (k=0;i<strlen(holder)-1; k++){ // loop through rest of holder but without counting the \n at the end
                                    //do a loop bc state cold be one or two numbers-- ex - could be 2 or could be 48
                                    stateN[k] = holder[i]; //copy next state into string
                                    i++;
                                }
                                stateN[k+1] = '\0';
                                break;
                            }
                        }
                        nextState = atoi(stateN);
                        //need to get rid of newlines in input - access 2nd space in array and change it to /0 -- first space is the letter
                        //input[2] = '\0';
                        printf("\t at step %d, input %c transitions FSM from state %d to state %d\n",
                               step, input[0], currentState, nextState);
                    }
                }
            }
            // check if had no match - could be file in wrong format or bad input
            //if (regRetFSM == REG_NOMATCH){
            if (!(singNumState || dubNumState)){
                //if state not there bc it is a dead end state also, then we give incorrect input
                printf("FSM definition file is in incorrect format or an incorrect input was entered for the current state. Terminating Program.");
                exit(1);
            }

        }
        currentState = nextState;
    }
    step+=1;
    printf("after %d steps, state machine finished successfully at state %d", step, currentState);
    fclose(f2);
    fclose(f1);
}