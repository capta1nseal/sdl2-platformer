class Input
{
public:
    Input()
    {
        for (int i = 0; i < inputArraySize; i++)
            inputArray[i] = false;
    }

    void setKeyboardState(const Uint8 *newKeyboardState)
    {
        keyboardState = newKeyboardState;
    }

    void updateInputs()
    {
        for (int i = 0; i < inputArraySize; i++)
            inputArray[i] = 0;
        if (keyboardState[SDL_SCANCODE_UP])
            inputArray[0] = true;
        if (keyboardState[SDL_SCANCODE_RIGHT])
            inputArray[1] = true;
        if (keyboardState[SDL_SCANCODE_DOWN])
            inputArray[2] = true;
        if (keyboardState[SDL_SCANCODE_LEFT])
            inputArray[3] = true;
        if (keyboardState[SDL_SCANCODE_Z])
            inputArray[4] = true;
        if (keyboardState[SDL_SCANCODE_X])
            inputArray[5] = true;
        if (keyboardState[SDL_SCANCODE_C])
            inputArray[6] = true;
        if (keyboardState[45])
            inputArray[7] = true;
        if (keyboardState[56])
            inputArray[8] = true;
    }

    bool upPressed() { return inputArray[0]; }
    bool rightPressed() { return inputArray[1]; }
    bool downPressed() { return inputArray[2]; }
    bool leftPressed() { return inputArray[3]; }
    bool jumpPressed() { return inputArray[4]; }
    bool attackPressed() { return inputArray[5]; }
    bool dashPressed() { return inputArray[6]; }
    bool zoomInPressed() { return inputArray[7]; }
    bool zoomOutPressed() { return inputArray[8]; }

private:
    static const int inputArraySize = 9;
    std::array<bool, inputArraySize> inputArray;
    const Uint8 *keyboardState;
};

// below is a map of indeces in the input array to the keys they represent. this should be changed later to make controls rebindable
/*
0 - up arrow
1 - right arrow
2 - down arrow
3 - left arrow
4 - Z
5 - X
6 - C
7 - +
8 - -
*/