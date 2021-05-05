#pragma once
#include <string>

struct Employee {
	std::string name, surName, patronymic;
	int monthPayment;
	Employee(std::string name, std::string surName, std::string patronymic, int monthPayment = 0) {
		this->name = name;
		this->surName = surName;
		this->patronymic = patronymic;
		this->monthPayment = monthPayment;
	}
	bool operator==(Employee& value);
};