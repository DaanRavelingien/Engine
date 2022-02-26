#pragma once
#include "document.h"

class Component;

template<class T>
class CompConstructor
{
public:
	T* ConstructComp(const rapidJson::Value& args) = 0;
};
