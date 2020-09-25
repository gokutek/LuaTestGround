#pragma once

#include <string>

class Animal
{
public:
	Animal();
	~Animal();

	void Eat(const std::string& what);
	void Sleep(int tm);
	int GetAge() const;
	void SetAge(int age);

private:
	int age_;
};
