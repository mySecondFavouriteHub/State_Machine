#include <iostream>
#include <string>
#include "GameEngine.h"
using namespace std;

const int state_count = 8; // total number of states
string state_names[state_count]= {"start", "map loaded", "map validated", "players added",
        "assign reinforcement", "issue orders", "execute orders", "win"}; // names of states
bool state_loops[state_count]= {0, 1, 0, 1, 0, 1, 1, 0}; // indicates if a state has a loop (1 = yes, 0 = no)
int state_resets[state_count]= {-1, -1, -1, -1, -1, -1, 4, 0}; // indicates the index of the state to reset to (-1 = no reset)
State states[state_count];// array of all states
State* current_state = nullptr; // pointer to current state

int load_next_state(){// return value; [0, 1] = [success, fail]
    if(current_state->next_state == nullptr){
        return 1;
    }
    current_state = current_state->next_state;
    return 0;
}
int init_state_graph(){
    for(int i=0; i<state_count; i++){ // this is the loop that defines the graph
        states[i].name=state_names[i];
        if(i>0){
            states[i-1].next_state=&states[i];// link previous state's next_state to current state
        }
        if(state_loops[i]){
            states[i].loop=&states[i];// link loop to itself
        }
        if(state_resets[i]>=0){
            states[i].reset=&states[state_resets[i]];// link reset to the specified state
        }
    }
    current_state=&states[0];// set initial state as start state
    states[state_count-1].next_state=nullptr;// last state's next_state is null
    return 0;
}
int state_machine(){      
    init_state_graph();
    while(true){ // main loop to run the state machine
        // at each iteration, display current state and prompt for command:
        // 'n' for next, 'l' for loop, 'r' for reset, 'q' for quit
        cout << "Current state: " << current_state->name << endl;
        cout << "Enter command (n: next, l: loop, r: reset, q: quit): ";
        char command;
        cin >> command;
        if(command == 'n'){
            if(load_next_state()){
                cout << "You have reached the end of the state graph. Goodbye!" << endl;
                break;
            }
        } else if(command == 'l'){
            if(current_state->loop){
                current_state = current_state->loop;
            } else {
                cout << "No loop state available. Staying in current state." << endl;
            }
        } else if(command == 'r'){
            if(current_state->reset){
                current_state = current_state->reset;
            } else {
                cout << "No reset state available. Staying in current state." << endl;
            }
        } else if(command == 'q'){
            break;
        } else {
            cout << "Invalid command. Please try again." << endl;
        }
    }
    return 0;
}
