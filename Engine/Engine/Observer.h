#pragma once
#include "Events.h"

template<typename T>
class Observer
{
public:
	virtual ~Observer() = default;
	virtual void Notify(T* payload, Event event) = 0;
};

