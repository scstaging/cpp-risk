#pragma once
#include <vector>

class Subject {

    public:
        virtual void Attach(Observer* o) = 0;
        virtual void Detach(Observer* o) = 0;
        virtual void Notify() = 0;
        Subject();
        ~Subject();

    private:
        std::vector<Observer*> *_observers;

};

class Observer {

    public:
        ~Observer();
        virtual void Update() = 0;
    protected:
        Observer();

};

class LogObserver : public Observer {

    public:
        void Update();

};

class ILoggable {

    public:
        virtual void stringToLog();

};