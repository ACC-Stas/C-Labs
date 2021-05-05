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

tm getTime();
void taskMenu(Project& project, Task& task);
void projectMenu(Project& project);
void mainMenu(std::list<Project>& projects);

int main() {
	std::list<Project> projects;
	mainMenu(projects);
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
				std::vector<Task*> vec = (*projectIt).getTasks();
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
						std::cout << "Task " << it->name << "has ";
						time = (*projectIt).getFreeTaskTime(*it) / (60 * 60 * 24);
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
				std::cout << "Employees\n";
				for (auto it : (*projectIt).getEmployees()) {
					std::cout << it->name << '\n';
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
				"6 - copy data to some file\n" <<
				"7 - load data from file\n" <<
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
		case F1: {
			std::cout << "It is project menu\n" <<
				"1 - rename project\n" <<
				"2 - add task\n" <<
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

}

tm getTime() {
	tm time;
	bool incorrectInput;
	std::regex rx("(\\d{1,2})[\.:\\s](\\d{1,2})[\.:\\s](\\d{4})");
	std::cmatch res;
	std::string input;
	do {
		std::cout << "Enter date, for example: 14.04.2020: ";
		incorrectInput = false;
		getline(std::cin, input);
		if (input == "") {
			incorrectInput = true;
			continue;
		}
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
