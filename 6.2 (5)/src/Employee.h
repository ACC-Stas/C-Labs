#pragma once
#include <string>

struct Employee {
	std::string name, surName, patronymic;
	int Payment;
	Employee(std::string name, std::string surName, std::string patronymic, int Payment = 0) {
		this->name = name;
		this->surName = surName;
		this->patronymic = patronymic;
		this->Payment = Payment;
	}
	bool operator==(Employee& value);
};