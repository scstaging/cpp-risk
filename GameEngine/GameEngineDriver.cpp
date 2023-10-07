#include <iostream>
#include "GameEngine.cpp"

// Free Function testGameStates()
void testGameStates() {
GameEngine* engine = new GameEngine();

    while (true)
    {
        std::cout << "\nCurrent State: " << engine->getCurrentState() << std::endl;
        std::cout << "Enter Command: ";
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

    delete engine;
}

int main() {
    testGameStates();

    return 0;
}