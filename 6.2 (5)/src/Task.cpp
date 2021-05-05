#include "Task.h"
#include <iostream>

bool Task::operator==(Task& value) {
	if (value.name == name) {
		return true;
	}
	else {
		return false;
	}
}
void Task::addEmployee(Employee& employee) {
	bool isNew = true;
	for (auto it : workers) {
		if (*it == employee) {
			isNew = false;
		}
	}
	if (isNew) {
		workers.push_back(&employee);
	}
	else {
		throw std::invalid_argument("this worker is already here");
	}
}
void Task::removeEmployee(Employee& employee) {
	for (auto it = workers.begin(); it != workers.end(); it++) {
		if ((**it) == employee) {
			workers.erase(it);
		}
	}
}
