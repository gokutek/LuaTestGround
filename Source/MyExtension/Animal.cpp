#include <iostream>
#include "Animal.h"

Animal::Animal()
	: age_(0)
{
}

Animal::~Animal()
{
}

void Animal::Eat(const std::string& what)
{
	std::cout << "Eat:" << what << std::endl;
}

void Animal::Sleep(int tm)
{
	std::cout << "Sleep:" << tm << std::endl;
}

int Animal::GetAge() const
{
	return age_;
}

void Animal::SetAge(int age)
{
	age_ = age;
}
