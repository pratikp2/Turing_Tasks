#include <iostream>
using namespace std;

// Bitmasks for different states of a game character
const int STATE_ALIVE       = 0b00000001;
const int STATE_HEALTHY     = 0b00000010;
const int STATE_ATTACKING    = 0b00000100;
const int STATE_INJURED      = 0b00001000;
const int STATE_IN_COVER     = 0b00010000;

// Number of states we need to track
const int NUM_STATES = sizeof(int) * 8;
class Character {
    private:
        // Instead of multiple state variables, we use a single int to track states
        int states_;

    public:
        Character() : states_(0) {}

        // Using bitwise operations to set states
        void setState(int state) {
            states_ |= state; // Set the appropriate bit
        }
        void unsetState(int state) {
            states_ &= ~state; // Clear the appropriate bit
        }
        
        // Checking states using bitwise AND
        bool hasState(int state) const {
            return states_ & state;
        }
};
// Advanced memory management: managing an array of characters in memory efficiently.
void manageCharacters(int numCharacters) {
    Character* characters = new Character[numCharacters];
    for (int i = 0; i < numCharacters; ++i) {
	    // sample: 
		// character 1 : health injured but still fighting
		// character 2 : in normal - idle state
		// character 3 : seak cover due to unrtimately healt

		characters[i].setState(STATE_ALIVE); 
        if(i == 0) {
            characters[i].setState(STATE_ATTACKING | STATE_INJURED);		    
        }else if(i == 1) {
            characters[i].setState(STATE_HEALTHY);
        }else {
            characters[i].setState(STATE_IN_COVER | STATE_HEALTHY | STATE_ALIVE);
        }
    }

		//Simulating state updates
    for (int i = 0; i < numCharacters; ++i) {	
		int changes = 0;
        // Handling complex state interactions
        if (characters[i].hasState(STATE_ATTACKING) && characters[i].hasState(STATE_INJURED)) {
                characters[i].unsetState(STATE_HEALTHY);
                changes++;
        }
        cout << "Character[" << i << "]: ";
        if (characters[i].hasState(STATE_ALIVE))
                cout << "ALIVE ";
        if (characters[i].hasState(STATE_HEALTHY))
                cout << "HEALTHY ";		
		if (characters[i].hasState(STATE_ATTACKING))
                cout << "ATTACKING ";		
		if (characters[i].hasState(STATE_INJURED))
                cout << "INJURED ";	
		if (characters[i].hasState(STATE_IN_COVER))
                cout << "IN_COVER ";	
        cout << endl;
    }

    delete[] characters;
}

int main() {
	const int NUM_CHARACTERS = 5;
	manageCharacters(NUM_CHARACTERS);
	return 0;
}
