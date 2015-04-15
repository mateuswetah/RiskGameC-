/*
 * Observable.h
 *
 *  Created on: Mar 2, 2015
 *      Author: mateus
 */

#ifndef OBSERVABLE_H_
#define OBSERVABLE_H_

#include <list>

class Observer;

class Observable
{
	public:
		virtual ~Observable();

		virtual void attach(Observer* anObserver);
		virtual void detach(Observer* anObserver);
		void notify();

	protected:
		Observable();

	private:
		std::list<Observer*> observers;

};

#endif /* OBSERVABLE_H_ */
