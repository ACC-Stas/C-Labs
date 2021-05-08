#include "Project.h"
#include <algorithm>
#include <iostream>

bool Project::operator==(Project& value) {
	if (value.name == name) {
		return true;
	}
	else {
		return false;
	}
}

void Project::addTask(Task& task) {
	for (auto it : tasks) {
		if (it == task) {
			throw std::invalid_argument("There is already task with such name");
		}
	}
	tasks.push_back(task);
}

void Project::removeTask(Task& task) {
	for (auto it = tasks.begin(); it != tasks.end(); it++) {
		if ((*it) == task) {
			tasks.erase(it);
			break;
		}
	}
}

Task& Project::getTask(std::string name) {
	for (auto it = tasks.begin(); it != tasks.end(); it++) {
		if ((*it).name == name) {
			return *it;
		}
	}
	throw std::invalid_argument("There is no task with such name");
}

void Project::addEmployee(Employee& employee) {
	bool isNew = true;
	for (auto it : workers) {
		if (it == employee) {
			isNew = false;
		}
	}
	if (isNew) {
		workers.push_back(employee);
	}
	else {
		throw std::invalid_argument("this worker is already here");
	}
}

Employee& Project::getEmployee(std::vector<std::string> fullName) {
	if (fullName.size() < 3) {
		throw std::invalid_argument("It can't be fullName: 3 strings are required");
	}
	Employee temp(fullName[0], fullName[1], fullName[2]);
	for (auto it = workers.begin(); it != workers.end(); it++) {
		if ((*it) == temp) {
			return *it;
		}
	}
	throw std::invalid_argument("There is no workers with such name");
}

void Project::removeEmployee(Employee& employee) {
	for (auto it = workers.begin(); it != workers.end(); it++) {
		if ((*it) == employee) {
			workers.erase(it);
			break;
		}
	}
}

std::vector<Task>& Project::getTasks() {
	std::sort(tasks.begin(), tasks.end(), [](Task left, Task right) -> bool { //the earlier starts, the "smaller" it is
		if (difftime(mktime(&right.begining), mktime(&left.begining)) > 0) {
			return true;
		}
		else {
			return false;
		}
		});
	return tasks;
}

std::vector<Employee>& Project::getEmployees() {
	return workers;
}

tm Project::getBegining() {
	tm begining = { 0,0,0,0,0,0 };
	auto first = tasks.begin();
	if (first != tasks.end()) {
		begining = (*first).begining;
	}
	for (auto it : tasks) {
		if (difftime(mktime(&begining), mktime(&it.begining)) > 0) {
			begining = it.begining;
		}
	}
	return begining;
}

tm Project::getEnd() {
	tm  end = { 0,0,0,0,0,0 };
	auto first = tasks.begin();
	if (first != tasks.end()) {
		end = (*first).end;
	}
	for (auto it : tasks) {
		if (difftime(mktime(&end), mktime(&it.end)) < 0) {
			end = it.end;
		}
	}
	return end;
}

int Project::getResources() {
	int resources = 0;
	for (auto it : tasks) {
		resources += it.resources;
	}
	for (auto it : workers) {
		resources += it.Payment;
	}
	return resources;
}

time_t Project::getFreeTaskTime(Task task) {
	bool found = false;
	for (auto it : tasks) {
		if (it == task) {
			found = true;
		}
	}
	if (!found) {
		throw std::invalid_argument("There is no task with such name");
	}
	tm beging = getBegining();
	tm end = getEnd();
	time_t freeTime = difftime(mktime(&end), mktime(&task.end)), time;
	bool meetWorker;
	for (auto it : tasks) {
		for (auto worker : it.workers) {
			meetWorker = false;
			for (auto taskWorker : task.workers) {
				if (worker == taskWorker) {
					meetWorker = true;
				}
			}
			if (meetWorker) {
				time = difftime(mktime(&task.end), mktime(&it.begining));
				if (time >= 0 && freeTime > time) {
					freeTime = time;
				}
			}
		}
	}
	return freeTime;
}

bool Project::haveTaskName(std::string name) {
	bool haveTaskName = false;
	for (auto it : tasks) {
		if (it.name == name) {
			haveTaskName = true;
			break;
		}
	}
	return haveTaskName;
}

bool Project::haveEmployee(Employee& employee) {
	for (auto it : workers) {
		if (it == employee) {
			return true;
		}
	}
	return false;
}