// header file for GameEngine class
#include <string>
using namespace std;
struct State{ // state struct designed to act like a node in a graph                  
    string name;
    State* next_state; // at most three edges at x vertex: next_state, loop, reset
    State* loop;
    State* reset;
    State() : name("default state"), next_state(nullptr), loop(nullptr), reset(nullptr) {} // Default constructor
    State(string val) : name(val), next_state(nullptr),loop(nullptr), reset(nullptr) {}
};
typedef struct State State;

extern const int state_count; // total number of states
extern string state_names[];
extern bool state_loops[];
extern int state_resets[]; // specify the size, e.g., 10, or use 'state_count' if it's a constant
extern State* current_state; // pointer to current state
int load_next_state();// return value; [0, 1] = [success, fail]
int init_state_graph(); // initializes the state graph
int main(); // main function to run the state machine