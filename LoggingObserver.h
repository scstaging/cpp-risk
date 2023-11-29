#pragma once
#include <vector>
#include <iostream>
#include <list>
#include <string>
#include <fstream>

class IObserver {
    public:
        virtual void Update(const std::string &message_from_subject) = 0;
};

class ILoggable {

    public:
        virtual std::string stringToLog() = 0;

};

class Subject : public ILoggable {
  public:
    void Attach(IObserver *observer) {
       observers_.push_back(observer);
    }
    void Detach(IObserver *observer) {
       observers_.remove(observer);
    }
    void Notify() {
      for (auto observer : observers_) {
        (observer)->Update(this->stringToLog());
      }
    }
  private:
    std::list<IObserver*> observers_;
};

class LogObserver : public IObserver {
    public:
        LogObserver() : fileHandle("gamelog.txt") {}
        void Update(const std::string &message_from_subject) override {
            fileHandle << message_from_subject << "\n";
        }

    private:
        std::ofstream fileHandle;
};