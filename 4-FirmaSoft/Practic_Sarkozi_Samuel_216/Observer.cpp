#include "Observer.h"

void Observable::addObserver(Observer* obs)
{
	participanti.push_back(obs);
}

void Observable::removeObserver(Observer* obs)
{
	participanti.erase(remove(participanti.begin(), participanti.end(), obs), participanti.end());
}

void Observable::notify()
{
	for (auto obs : participanti)
		obs->update();
}
