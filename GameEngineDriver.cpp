#include <iostream>
#include "GameEngine.cpp"

// Free Function testGameStates()
void testGameStates() {

// Instantiates game engine
GameEngine* engine = new GameEngine();

    // while true, allows for breaking only when necessary
    while (true)
    {

        // Display relevant information on each new iteration
        std::cout << "\nCurrent State: " << engine->getCurrentState() << std::endl;
        std::cout << "Enter Command: ";
        
        // Takes command as input
        std::string x;
        std::cin >> x;

        // Checks if input exists for current state
        if (engine->validateTransition(x)) 
        {
            // Evaluates where to transition to
            engine->update(x);
        }
        
        // Input does not exist
        else
        {
            // Display error message for incorrect input
            std::cout << "Input is not recognized" << std::endl;
        }
    }

    // Frees up memory
    delete engine;
    engine = NULL;
}

// int main() {
//     testGameStates();

//     return 0;
// };
