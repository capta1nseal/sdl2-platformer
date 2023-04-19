#include <iostream> // debugging

#include <array> // for holding the bolean array of inputs

using namespace std;

class InputData
{
public:
    array<bool, 7> inputArray; // each bool in the array holds the state of a particular key, documented in constructor
    
    InputData()
    {
        inputArray = {
            false, // up arrow
            false, // right arrow
            false, // down arrow
            false, // left arrow
            false, // Z
            false, // X
            false  // C
        };
    }
private:
    
};
