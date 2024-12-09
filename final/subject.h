/**
 *
 * @file subject.h
 * @brief Manages a list of observers and notifies them of changes.
 *
 * @author Kseniia Blokhina
 * @login BLO0021
 *
 */
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