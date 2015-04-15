/*
 * Observable.cpp
 *
 *  Created on: Mar 2, 2015
 *      Author: mateus
 */

#include "Observable.h"
#include "Observer.h"
#include <iostream>

Observable::Observable() {};

Observable::~Observable() {};

void Observable::attach(Observer* anObserver)
{
	this->observers.push_back(anObserver);
}

void Observable::detach(Observer* anObserver)
{
	this->observers.remove(anObserver);
}

void Observable::notify()
{
	std::list<Observer*>::iterator i;

	if (this->observers.size() > 0)
	{
		for(std::list<Observer*>::iterator i = this->observers.begin(); i != this->observers.end(); ++i)
		{
			(*i)->update();
		}
	}
}
