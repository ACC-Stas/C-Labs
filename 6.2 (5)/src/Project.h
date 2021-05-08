#pragma once
#include "Employee.h"
#include "Task.h"

class Project {
private:
	std::vector<Task> tasks;
	std::vector <Employee> workers;
public:
	std::string name;
	Project(std::string name) {
		this->name = name;
	}
	bool operator==(Project& value);
	void addTask(Task& task);
	void removeTask(Task& task);
	Task& getTask(std::string name);
	void addEmployee(Employee& employee);
	void removeEmployee(Employee& employee);
	std::vector<Task>& getTasks();
	std::vector<Employee>& getEmployees();
	Employee& getEmployee(std::vector<std::string> fullName);
	tm getBegining();
	tm getEnd();
	int getResources();
	time_t getFreeTaskTime(Task task);
	bool haveTaskName(std::string name);
	bool haveEmployee(Employee& employee);
};

