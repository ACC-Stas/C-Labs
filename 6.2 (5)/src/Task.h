#pragma once
#include "Employee.h"
#include <string>
#include <vector>

struct Task {
	std::vector<Employee*> workers;
	std::string name;
	tm begining, end;
	int resources;
	Task(std::string name, tm begining, tm end, int resources = 0) {
		this->name = name;
		this->begining = begining;
		this->end = end;
		this->resources = resources;
	}
	bool operator==(Task& value);
	void addEmployee(Employee& employee);
	void removeEmployee(Employee& employee);
};
