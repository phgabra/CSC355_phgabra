/*
 * This program simulates DFA.
 *
 * Author: Philo Gabra
 */


#include <iostream>
#include <string>
#include <cassert>
using namespace std;

// DFA States
enum State {
    A,  // Start state
    B,  // State after 1 'a'
    C,  // State after 2 'a's
    D,  // State after 'ab'
    E,  // State after 'abb'
    ERROR  // Error state
};

/*  Checks if the current state is an acceptign state.
 *  
 *  @param current state
 *  @return true if the current state is an accepting state. false, otherwise.
 */
bool isAcceptingState(State currentState) {
    return currentState == B || currentState == C || currentState == E;
}

/*  Convert enum State type to string.
 *  
 *  @param current state
 *  @return state in string
 */
string toString(State currentState) {
    switch (currentState) {
        case A: return "A";
        case B: return "B";
        case C: return "C";
        case D: return "D";
        case E: return "E";
        case ERROR: return "ERROR";
        default: assert(false);
    }
}

/*  Simulates DFA state transition on the input symbol.
 *  
 *  @param current state
 *  @param input symbol
 *  @return transited state or error.
 */
State transition(State currentState, char symbol) {
    switch (currentState) {
        case A:
            if (symbol == 'a') return B;
            break;
        case B:
            if (symbol == 'a') return C;
            if (symbol == 'b') return D;
            break;
        case C:
            return ERROR;  // No valid transitions from C
        case D:
            if (symbol == 'b') return E;
            break;
        case E:
            return ERROR;  // No valid transitions from E
    }
    return ERROR;
}

int main() {
    string inputs[8] = {
        "a",        // accept.
        "aa",       // accept.
        "ab",       // accept.
        "aba",      // accept.
        "abb",      // accept.
        "b",        // reject.
        "abaa",     // reject.
        "abbb"      // reject.
    };

    for (int i = 0; i < sizeof(inputs)/sizeof(inputs[0]); i++) {

        State currentState = A; // Start at A

        string path = "A";
        char curSymbol;
        State prevState;

        string input = inputs[i];
        cout << "Input string: " << input << endl;
        // Process each symbol in the input string
        for (int j = 0; j < input.length(); j++) {
            char symbol = input[j];
            prevState = currentState;
            currentState = transition(currentState, symbol);

            string stateStr = toString(currentState);
            path = path + "->" + stateStr;
            
            // If we encounter an undefined transition (ERROR state)
            if (currentState == ERROR) {
                cout << "Error: Undefined transition for symbol '" << symbol << "' from state '";
                cout <<  toString(prevState) << "'. Thus, the input rejected." << endl;
                cout << "Path: " << path << endl;
                break; // Exit with an error
            }
        }
        
        if (currentState != ERROR) {
            if (isAcceptingState(currentState)) {
                cout << "Input accepted!" << endl;
            }
            else {
                cout << "Input rejected!" << endl;
            }
            cout << "Path: " << path << endl;
        }
    }
    
    return 0;
}
