#include "LoggingObserver.h"
#include "GameEngine.h"
#include <iostream>

void testLoggingObserver()
{
    LogObserver logObserver;
    GameEngine* engine = new GameEngine();
    engine->Attach(&logObserver);
    engine->update("loadmap");
}

int main() {
    testLoggingObserver();
    
    return 0;
}