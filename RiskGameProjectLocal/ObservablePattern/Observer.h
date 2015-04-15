/*
 * Observer.h
 *
 *  Created on: Mar 2, 2015
 *      Author: mateus
 */

#ifndef OBSERVER_H_
#define OBSERVER_H_

class Observer
{
	public:
		virtual ~Observer();
		virtual void update() = 0;

	protected:
		Observer();
};

#endif /* OBSERVER_H_ */
