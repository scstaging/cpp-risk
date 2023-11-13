#include "LoggingObserver.h"

Subject::Subject()
{
    _observers = new std::vector<Observer*>;
}
Subject::~Subject()
{
    delete _observers;
}
void Subject::Attach(Observer* o) 
{
    _observers->push_back(o);
};
void Subject::Detach(Observer* o) 
{
    // Detach
};
void Subject::Notify() 
{
    std::vector<Observer *>::iterator i = _observers->begin();
    for (; i != _observers->end(); i++)
        (*i)->Update();
};


Observer::Observer(){};
Observer::~Observer(){};