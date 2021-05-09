#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <fstream>
#include <list>
#include <conio.h>
#include "Employee.h"
#include "Task.h"
#include "Project.h"

#define ZERO_BUTTON 48
#define ONE_BUTTON 49
#define TWO_BUTTON 50
#define THREE_BUTTON 51
#define FOUR_BUTTON 52
#define FIVE_BUTTON 53
#define SIX_BUTTON 54
#define SEVEN_BUTTON 55
#define EIGHT_BUTTON 56
#define NINE_BUTTON 57
#define ESC 27
#define F1 94

int getResources();
std::vector<std::string> getFullName();
tm getTime();
void taskMenu(Project& project, Task& task);
void projectMenu(Project& project);
void mainMenu(std::list<Project>& projects);
void loadData(std::list<Project>& projects, std::string nameOfFile);
void saveData(std::list<Project>& projects, std::string nameOfFile);

int main() {
	std::list<Project> projects;
	loadData(projects, "data.txt");

	mainMenu(projects);

	saveData(projects, "data.txt");
	return 0;
}

void mainMenu(std::list<Project>& projects) {
	char input;
	do {
		std::cout << "Your command?";
		input = _getch();
		if (input == 0 || input == -32) {
			input = _getch();
		}
		std::cout << '\n';
		switch (input) {
		case ONE_BUTTON: {
			bool isNew;
			Project project("");
			do {
				std::cout << "Enter project name: ";
				isNew = true;
				std::string name;
				std::cin >> name;
				project.name = name;
				for (auto it : projects) {
					if (it == project) {
						isNew = false;
						std::cout << "This name is already used. Enter another one: ";
					}
				}
			} while (!isNew);
			projects.push_back(project);
			break;
		}
		case TWO_BUTTON: {
			std::cout << "Enter name of project, that need to be deleted: ";
			std::string name;
			std::cin >> name;
			Project project(name);
			bool deleted = false;
			for (auto it = projects.begin(); it != projects.end(); it++) {
				if ((*it) == project) {
					deleted = true;
					projects.erase(it);
					std::cout << "Project is deleted";
					break;
				}
			}
			if (!deleted) {
				std::cout << "There is no such project";
			}
			break;
		}
		case THREE_BUTTON: {
			std::cout << "Enter the name of the project about which you want to see information: ";
			std::string name;
			std::cin >> name;
			bool found = false;
			auto projectIt = projects.begin();
			for (; projectIt != projects.end(); projectIt++) {
				if ((*projectIt).name == name) {
					found = true;
					break;
				}
			}
			if (found) {
				std::cout << "Project name: " + name << '\n';
				std::vector<Task> vec = (*projectIt).getTasks();
				if (vec.size() < 1) {
					std::cout << "There is no tasks\n";
				}
				else {
					tm begining = (*projectIt).getBegining();
					tm end = (*projectIt).getEnd();
					std::cout << "Projects starts at: " << begining.tm_mday << '.' << begining.tm_mon << '.' << begining.tm_year + 1900 << '\n';
					std::cout << "Projects ends at: " << end.tm_mday << '.' << end.tm_mon << '.' << end.tm_year + 1900 << '\n';
					std::cout << "Estimated cost of project is: " << (*projectIt).getResources() << '\n';
					int time;
					for (auto it : vec) {
						std::cout << "Task " << it.name << " has ";
						time = (*projectIt).getFreeTaskTime(it) / (60 * 60 * 24);
						if (time == 0) {
							std::cout << "no free time\n";
							std::cout << "Critical task\n";
						}
						else {
							std::cout << time << " days of free time\n";
							std::cout << "Isn't critical\n";
						}
					}
				}
				std::cout << "Employees:\n";
				for (auto it : (*projectIt).getEmployees()) {
					std::cout << it.name << " " << it.surName << " " << it.patronymic << '\n';
				}
			}
			else {
				std::cout << "There is no such project";
			}
			break;
		}
		case FOUR_BUTTON: {
			std::cout << "List of projets\n";
			for (auto it : projects) {
				std::cout << it.name << '\n';
			}
			break;
		}
		case FIVE_BUTTON: {
			std::cout << "Enter, what project you would like to change: ";
			std::string name;
			std::cin >> name;
			Project project(name);
			bool found = false;
			for (auto it = projects.begin(); it != projects.end(); it++) {
				if (*it == project) {
					projectMenu(*it);
					found = true;
					break;
				}
			}
			if (!found) {
				std::cout << "There is no such project";
			}
			break;
		}
		case F1: {
			std::cout << "It is main menu\n" <<
				"1 - add project\n" <<
				"2 - delete project\n" <<
				"3 - show information about project\n" <<
				"4 - show list of projects\n" <<
				"5 - change project\n" <<
				"F1 - help\n" <<
				"ESC - close program\n";
			break;
		}
		case ESC: {
			std::cout << "Press escape one more time: ";
			if (_getch() == ESC) {
				return;
			}
			else {
				std::cout << '\n';
			}
			break;
		}
		default: {
			break;
		}
		}
		std::cout << '\n';
	} while (true);
}

void projectMenu(Project& project) {
	char input;
	do {
		std::cout << "Your command?";
		input = _getch();
		if (input == 0 || input == -32) {
			input = _getch();
		}
		std::cout << '\n';
		switch (input) {
		case ONE_BUTTON: {
			std::cout << "Enter new name: ";
			std::string name;
			std::cin >> name;
			project.name = name;
			break;
		}
		case TWO_BUTTON: {
			std::string name;
			tm beginging;
			tm end;
			std::cout << "Enter name of task: ";
			std::cin >> name;
			std::cout << "Enter begining date\n";
			beginging = getTime();
			std::cout << "Enter end date\n";
			end = getTime();
			if (difftime(mktime(&end), mktime(&beginging)) <= 0) {
				std::cout << "End date is earlier than begining date\n";
				break;
			}
			Task task(name, beginging, end);
			try {
				project.addTask(task);
			}
			catch (std::invalid_argument& ex) {
				std::cout << "Task with such name is already exist\n";
				break;
			}
			break;
		}
		case THREE_BUTTON: {
			std::cout << "Enter name of task you want to alter: ";
			std::string name;
			std::cin >> name;
			if (!project.haveTaskName(name)) {
				std::cout << "There is no task with such name";
				break;
			}
			taskMenu(project, project.getTask(name));
			break;
		}
		case FOUR_BUTTON: {
			std::cout << "Adding employee\n";
			std::vector<std::string> fullName(getFullName());
			Employee employee(fullName[0], fullName[1], fullName[2]);
			if (project.haveEmployee(employee)) {
				std::cout << "Employee with such full name is already in the project";
				break;
			}
			project.addEmployee(employee);
			break;
		}
		case FIVE_BUTTON: {
			std::cout << "Removing employee\n";
			std::vector<std::string> fullName(getFullName());
			Employee employee(fullName[0], fullName[1], fullName[2]);
			if (!project.haveEmployee(employee)) {
				std::cout << "There is no employee with such full name";
				break;
			}
			project.removeEmployee(employee);
			break;
		}
		case SIX_BUTTON: {
			std::cout << "Changing price for employee\n";
			std::vector<std::string> fullName(getFullName());
			Employee employee(fullName[0], fullName[1], fullName[2]);
			if (!project.haveEmployee(employee)) {
				std::cout << "There is no employee with such full name";
				break;
			}
			int resoureces = getResources();
			project.getEmployee(fullName).Payment = resoureces;
			break;
		}
		case SEVEN_BUTTON: {
			std::cout << "Enter name of task, that need to be removed: ";
			std::string name;
			std::cin >> name;
			if (!project.haveTaskName(name)) {
				std::cout << "There is no task with such name";
				break;
			}
			Task task(name, tm(), tm());
			project.removeTask(task);
			break;
		}
		case F1: {
			std::cout << "It is project menu\n" <<
				"1 - rename project\n" <<
				"2 - add task\n" <<
				"3 - change task\n" <<
				"4 - add employee\n" <<
				"5 - remove employee\n" <<
				"6 - change payment for employee\n" <<
				"7 - remove task\n" << 
				"F1 - help\n" <<
				"ESC - return to main menu\n";
			break;
		}
		case ESC: {
			std::cout << "Press escape one more time: ";
			if (_getch() == ESC) {
				return;
			}
			else {
				std::cout << '\n';
			}
			break;
		}
		default: {
			break;
		}
		}
		std::cout << '\n';
	} while (true);
}

void taskMenu(Project& project, Task& task) {
	char input;
	do {
		std::cout << "Your command?";
		input = _getch();
		if (input == 0 || input == -32) {
			input = _getch();
		}
		std::cout << '\n';
		switch (input) {
		case ONE_BUTTON: {
			std::cout << "Enter new name of task: ";
			std::string name;
			std::cin >> name;
			if (project.haveTaskName(name)) {
				std::cout << "This name is already used by another task";
				break;
			}
			task.name = name;
			break;
		}
		case TWO_BUTTON: {
			std::cout << "Changing resources\n";
			int resources = getResources();
			task.resources = resources;
			break;
		}
		case THREE_BUTTON: {
			std::cout << "Adding employee to task. Employee shoud already be part of the project\n";
			std::vector<std::string> fullName(getFullName());
			Employee employee(fullName[0], fullName[1], fullName[2]);
			if (!project.haveEmployee(employee)) {
				std::cout << "There is no employee at project with such full name";
				break;
			}
			try {
				task.addEmployee(employee);
			}
			catch (std::invalid_argument& ex) {
				std::cout << "This employee is already part of the task";
			}
			break;
		}
		case FOUR_BUTTON: {
			std::cout << "This task use " << task.resources << " of resources";
			break;
		}
		case F1: {
			std::cout << "It is task menu\n" <<
				"1 - change name\n" << 
				"2 - change resources\n" <<
				"3 - add employee to task\n" <<
				"4 - show resources\n" << 
				"F1 - help\n" <<
				"ESC - return to main menu\n";
			break;
		}
		case ESC: {
			std::cout << "Press escape one more time: ";
			if (_getch() == ESC) {
				return;
			}
			else {
				std::cout << '\n';
			}
			break;
		}
		default: {
			break;
		}
		}
		std::cout << '\n';
	} while (true);
}

tm getTime() {
	tm time;
	bool incorrectInput;
	std::regex rx("(\\d{1,2})[.:\\s](\\d{1,2})[.:\\s](\\d{4})");
	std::cmatch res;
	std::string input;
	do {
		std::cout << "Enter date, for example: 14.04.2020: ";
		incorrectInput = false;
		getline(std::cin, input);
		if (std::regex_search(input.c_str(), res, rx)) {
			int day = std::stoi(res[1]);
			int month = std::stoi(res[2]);
			int year = std::stoi(res[3]);
			if (day < 0 || day > 31) {
				std::cout << "Incorrect day\n";
				incorrectInput = true;
				continue;
			}
			if (month < 0 || month > 12) {
				std::cout << "Incorrect month\n";
				incorrectInput = true;
				continue;
			}
			if (year < 1971 || year > 2150) {
				incorrectInput = true;
				std::cout << "Incorrect year: only 1971 to 2150 are supported\n";
				continue;
			}
			time = { 0,0,0,day,month,year - 1900};
			if (mktime(&time) == -1) {
				incorrectInput = true;
				std::cout << "Sorry, but we can't use such date, try another one\n";
				continue;
			}
		}
		else {
			incorrectInput = true;
			std::cout << "It is not a date";
		}
		std::cout << '\n';
	} while (incorrectInput);
	return time;
}

std::vector<std::string> getFullName() {
	bool incorrectInput;
	std::regex rx("(\\w+)[\\s+](\\w+)[\\s+](\\w+)");
	std::cmatch res;
	std::string input;
	std::vector<std::string> fullName;
	do {
		std::cout << "Enter full name, for example: Victor Victorovich Victorious: ";
		incorrectInput = false;
		getline(std::cin, input);
		if (input == "") {
			incorrectInput = true;
			continue;
		}
		if (std::regex_search(input.c_str(), res, rx)) {
			fullName.push_back(res[1]);
			fullName.push_back(res[2]);
			fullName.push_back(res[3]);
		}
		else {
			incorrectInput = true;
			std::cout << "It is not a full name";
		}
		std::cout << '\n';
	} while (incorrectInput);
	return fullName;
}

int getResources() {
	bool incorrectInput;
	std::regex rx("^(-?[0-9]+)");
	std::cmatch res;
	std::string input;
	int resources;
	do {
		std::cout << "Enter positive number, that represents resources: ";
		incorrectInput = false;
		getline(std::cin, input);
		if (input == "") {
			incorrectInput = true;
			continue;
		}
		if (std::regex_search(input.c_str(), res, rx)) {
			resources = std::stoi(res[1]);
			if (resources < 0) {
				incorrectInput = true;
				std::cout << "Number needs to be positive";
			}
		}
		else {
			incorrectInput = true;
			std::cout << "It is not a number";
		}
		std::cout << '\n';
	} while (incorrectInput);
	return resources;
}

void loadData(std::list<Project>& projects, std::string nameOfFile) {
	std::ifstream fin(nameOfFile);
	std::string line;
	std::cmatch res;
	std::regex rxName("^#Name\\s+([\\d\\w]+)");
	std::regex rxFullName("^#FullName\\s+([\\d\\w]+)\\s+([\\d\\w]+)\\s+([\\d\\w]+)");
	std::regex rxBegining("^#Begining\\s+(\\d{1,2})[.:\\s](\\d{1,2})[.:\\s](\\d{3,4})");
	std::regex rxEnd("^#End\\s+(\\d{1,2})[.:\\s](\\d{1,2})[.:\\s](\\d{3,4})");
	std::regex rxResources("^#Resources\\s+(\\d+)");
	do {
		std::getline(fin, line);
		if (line == "#Project") {
			Project project("Name");
			do {
				std::getline(fin, line);
				if (std::regex_search(line.c_str(), res, rxName)) {
					project.name = res[1];
				}

				if (line == "#Task") {
					Task task("Name", tm(), tm());
					do {
						std::getline(fin, line);
						if (std::regex_search(line.c_str(), res, rxName)) {
							task.name = res[1];
						}
						if (std::regex_search(line.c_str(), res, rxBegining)) {
							tm beginging = { 0,0,0,0,0,0 };
							tm end = { 0,0,0,0,0,0 };
							beginging.tm_mday = std::stoi(res[1]);
							beginging.tm_mon = std::stoi(res[2]);
							beginging.tm_year = std::stoi(res[3]);
							std::getline(fin, line);  //next line must be with end date
							std::regex_search(line.c_str(), res, rxEnd);
							end.tm_mday = std::stoi(res[1]);
							end.tm_mon = std::stoi(res[2]);
							end.tm_year = std::stoi(res[3]);
							task.begining = beginging;
							task.end = end;
						}
						if (std::regex_search(line.c_str(), res, rxResources)) {
							task.resources = std::stoi(res[1]);
						}
						if (line == "#Employee") {
							Employee employee("Name", "SurName", "patronimic");
							do {
								std::getline(fin, line);
								if (std::regex_search(line.c_str(), res, rxFullName)) {
									employee.name = res[1];
									employee.surName = res[2];
									employee.patronymic = res[3];
								}
								if (std::regex_search(line.c_str(), res, rxResources)) {
									employee.Payment = std::stoi(res[1]);
								}
							} while (line != "Employee#");
							task.addEmployee(employee);
						}
					} while (line != "Task#");
					project.addTask(task);
				}

				if (line == "#Employee") {
					Employee employee("Name", "SurName", "patronimic");
					do {
						std::getline(fin, line);
						if (std::regex_search(line.c_str(), res, rxFullName)) {
							employee.name = res[1];
							employee.surName = res[2];
							employee.patronymic = res[3];
						}
						if (std::regex_search(line.c_str(), res, rxResources)) {
							employee.Payment = std::stoi(res[1]);
						}
					} while (line != "Employee#");
					project.addEmployee(employee);
				}

			} while (line != "Project#");
			projects.push_back(project);
		}
	} while (line != "#ENDOFLIST#");
	fin.close();
}

void saveData(std::list<Project>& projects, std::string nameOfFile) {
	std::ofstream fout(nameOfFile);
	for (auto project : projects) {
		fout << "#Project\n";
		fout << "#Name " << project.name << '\n';
		for (auto task : project.getTasks()) {
			fout << "#Task\n";
			fout << "#Name " << task.name << '\n';
			fout << "#Begining " << task.begining.tm_mday << '.' << task.begining.tm_mon << '.' << task.begining.tm_year << '\n';
			fout << "#End " << task.end.tm_mday << '.' << task.end.tm_mon << '.' << task.end.tm_year << '\n';
			fout << "#Resources " << task.resources << '\n';
			for (auto employee : task.workers) {
				fout << "#Employee\n";
				fout << "#FullName " << employee.name << " " << employee.surName << " " << employee.patronymic << '\n';
				fout << "#Resources " << employee.Payment << '\n';
				fout << "Employee#\n";
			}
			fout << "Task#\n";
		}
		for (auto employee : project.getEmployees()) {
			fout << "#Employee\n";
			fout << "#FullName " << employee.name << " " << employee.surName << " " << employee.patronymic << '\n';
			fout << "#Resources " << employee.Payment << '\n';
			fout << "Employee#\n";
		}
		fout << "Project#\n";
	}
	fout << "#ENDOFLIST#\n";
	fout.close();
}

