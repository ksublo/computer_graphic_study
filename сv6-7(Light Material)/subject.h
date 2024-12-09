#pragma once
#include "observer.h"
#include <vector>

using namespace std;

class Subject {
public:
    void registerObserver(Observer* observer);
    void removeObserver(Observer* observer);
    void notifyObservers();

private: 
    vector<Observer*> observers;
};