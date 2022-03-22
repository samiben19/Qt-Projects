#pragma once
#include <vector>

using std::vector;
using std::remove;

class Observer
{
public:
	virtual void update() = 0;
};

class Observable
{
private:
	vector<Observer*> participanti;
public:
	void addObserver(Observer* obs) {
		participanti.push_back(obs);
	}
	void removeObserver(Observer* obs) {
		participanti.erase(remove(participanti.begin(), participanti.end(), obs), participanti.end());
	}
protected:
	void notify() {
		for (auto obs : participanti)
			obs->update();
	}
};