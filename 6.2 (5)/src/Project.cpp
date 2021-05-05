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
		if (*it == task) {
			throw std::invalid_argument("There is already task with such name");
		}
	}
	tasks.push_back(&task);
}

void Project::removeTask(Task& task) {
	for (auto it = tasks.begin(); it != tasks.end(); it++) {
		if ((**it) == task) {
			tasks.erase(it);
		}
	}
}

void Project::addEmployee(Employee& employee) {
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

void Project::removeEmployee(Employee& employee) {
	for (auto it = workers.begin(); it != workers.end(); it++) {
		if ((**it) == employee) {
			workers.erase(it);
		}
	}
}

std::vector<Task*> Project::getTasks() {
	std::sort(tasks.begin(), tasks.end(), [](Task* left, Task* right) -> bool { //the earlier starts, the "smaller" it is
		if (difftime(mktime(&right->begining), mktime(&left->begining)) > 0) {
			return true;
		}
		else {
			return false;
		}
		});
	return tasks;
}

std::vector<Employee*> Project::getEmployees() {
	return workers;
}

tm Project::getBegining() {
	tm begining = { 0,0,0,0,0,0 };
	for (auto it : tasks) {
		if (difftime(mktime(&begining), mktime(&it->begining)) > 0) {
			begining = it->begining;
		}
	}
	return begining;
}

tm Project::getEnd() {
	tm  end = { 0,0,0,0,0,0 };
	for (auto it : tasks) {
		if (difftime(mktime(&end), mktime(&it->end)) < 0) {
			end = it->end;
		}
	}
	return end;
}

int Project::getResources() {
	int resources = 0;
	for (auto it : tasks) {
		resources += it->resources;
	}
	return resources;
}

time_t Project::getFreeTaskTime(Task task) {
	bool found = false;
	for (auto it : tasks) {
		if (*it == task) {
			found = true;
		}
	}
	if (!found) {
		throw std::invalid_argument("There is no task with such name");
	}
	tm beging = getBegining();
	tm end = getEnd();
	time_t freeTime = difftime(mktime(&end), mktime(&beging)), time;
	bool meetWorker;
	for (auto it : tasks) {
		for (auto worker : it->workers) {
			meetWorker = false;
			for (auto taskWorker : task.workers) {
				if (worker == taskWorker) {
					meetWorker = true;
				}
			}
			if (meetWorker) {
				time = difftime(mktime(&task.end), mktime(&it->begining));
				if (time >= 0 && freeTime > time) {
					freeTime = time;
				}
			}
		}
	}
	return freeTime;
}