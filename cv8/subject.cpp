#include "subject.h"

void Subject::registerObserver(Observer* observer)
{
	observers.push_back(observer);
}

void Subject::removeObserver(Observer* observer)
{
	observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void Subject::notifyObservers()
{
	for (Observer* observer : observers) {
		observer->update();
	}
}