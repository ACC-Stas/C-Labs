#include <cassert>
#include "Employee.h"
#include "Task.h"
#include "Project.h"

int main() {
	Employee employee1("Victor", "Vrot", "Reanaldovich", 15);
	Employee employee2("Victor", "Vrot", "Reanaldovich", 12);
	Employee employee3("Vaca", "Pupkin", "Reanaldovich", 114);
	
	assert((employee1 == employee2) == true);
	assert((employee1 == employee3) == false);
	employee1.name = "Vivaldy";

	Task task1("Name1", tm(), tm(), 15);
	Task task2("Name1", tm(), tm());
	Task task3("Name2", tm(), tm());

	assert((task1 == task2) == true);
	assert((task1 == task3) == false);

	task2.name = "Name2";
	task3.name = "Name3";
	task2.resources = 25;
	
	tm time = { 0,0,0,0,0,0 };
	time.tm_year = 170;
	task1.begining = time;
	time.tm_year = 180;
	task2.begining = time;
	time.tm_year = 190;
	task3.begining = time;
	task1.end = time;
	task2.end = time;
	task3.end = time;

	task1.addEmployee(employee1);
	task1.addEmployee(employee2);
	task1.addEmployee(employee3);
	bool throwException = false;
	try {
		task1.addEmployee(employee1);
	}
	catch (std::invalid_argument& ex) {
		throwException = true;
	}
	assert(throwException);

	task1.removeEmployee(employee1);
	task1.addEmployee(employee1);

	Project project1("Name1");
	Project project2("Name1");
	Project project3("Name3");

	assert((project1 == project2) == true);
	assert((project1 == project3) == false);
	project2.name = "Name2";

	project1.addTask(task1);
	project1.addTask(task2);
	project1.addTask(task3);
	throwException = false;
	try {
		project1.addTask(task1);
	}
	catch (std::invalid_argument& ex) {
		throwException = true;
	}
	assert(throwException);

	project1.removeTask(task1);
	project1.addTask(task1);

	assert(project1.getTask("Name1") == task1);
	throwException = false;
	try {
		project1.getTask("Name4");
	}
	catch (std::invalid_argument& ex) {
		throwException = true;
	}
	assert(throwException);

	project1.addEmployee(employee1);
	project1.addEmployee(employee2);
	project1.addEmployee(employee3);
	throwException = false;
	try {
		project1.addEmployee(employee1);
	}
	catch (std::invalid_argument& ex) {
		throwException = true;
	}
	assert(throwException);

	project1.removeEmployee(employee1);
	project1.addEmployee(employee1);

	std::vector<Task> tasks = project1.getTasks();
	assert(tasks[0] == task1 && tasks[1] == task2 && tasks[2] == task3);
	time.tm_year = 220;
	project1.getTask("Name1").begining = time;
	tasks = project1.getTasks();
	assert(tasks[0] == task2 && tasks[1] == task3 && tasks[2] == task1);

	std::vector<Employee> Employees = project1.getEmployees();
	assert(Employees[0] == employee2 && Employees[1] == employee3 && Employees[2] == employee1);

	std::vector<std::string> fullName;
	fullName.push_back(employee1.name);
	fullName.push_back(employee1.surName);
	fullName.push_back(employee1.patronymic);

	assert(project1.getEmployee(fullName) == employee1);
	fullName.pop_back();
	throwException = false;
	try {
		project1.getEmployee(fullName);
	}
	catch (std::invalid_argument& ex) {
		throwException = true;
	}
	assert(throwException);
	fullName.push_back("AMOGUS");
	throwException = false;
	try {
		project1.getEmployee(fullName);
	}
	catch (std::invalid_argument& ex) {
		throwException = true;
	}
	assert(throwException);

	tm date = project1.getBegining();
	assert(date.tm_mday == 31 && date.tm_mon == 11 && date.tm_year == 179);
	date = project1.getEnd();
	assert(date.tm_mday == 31 && date.tm_mon == 11 && date.tm_year == 189);

	assert(project1.getResources() == 181);
	
	assert(project1.getFreeTaskTime(task1) == 0);
	project1.removeTask(task1);
	throwException = false;
	try {
		project1.getFreeTaskTime(task1);
	}
	catch (std::invalid_argument& ex) {
		throwException = true;
	}
	assert(throwException);

	assert(project1.haveTaskName("Name2") == true);
	assert(project1.haveTaskName("Name4") == false);

	assert(project1.haveEmployee(employee1) == true);
	project1.removeEmployee(employee1);
	assert(project1.haveEmployee(employee1) == false);

	return 0;
}