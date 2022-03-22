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
	void addObserver(Observer* obs);
	void removeObserver(Observer* obs);
protected:
	void notify();
};

