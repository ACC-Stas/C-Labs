#include <stdio.h>
#include "src.h"

struct data {
	int beginDay, endDay, beginMonth, endMonth, beginYear, endYear;
	int employeesNumber;
	int rate; /*need to pay employ for hour of work*/
	int budget; /*sum, that company posses + will earn*/
	long long allCost;
	long long programmersCost;
	long long profit;
	int length;
	int workLength; /*approximate number of worknig day*/

}company;

int main() {
	printf("Enter 1 to set budget\n");
	printf("Enter 2 to set rate\n");
	printf("Enter 3 to set begin date\n");
	printf("Enter 4 to set end date\n");
	printf("Enter 5 to set employees number\n");
	printf("Enter 6 to show given data\n");
	printf("Enter 7 to show length of projetc\n");
	printf("Enter 8 to show analysed data\n");
	printf("Enter 9 to show version and developer of this programm\n");
	printf("Enter 10 to exit\n");
	int command;
	do {
		printf("Your command: ");
		command = getIntCommand(1, 10);
		switch (command) {
		case 1: {
			printf("Setting budget: ");
			company.budget = getIntCommand(1, 2000000000);
			printf("\n");
			break;
		}
		case 2: {
			printf("Setting rate: ");
			company.rate = getIntCommand(1, 100);
			printf("\n");
			break;
		}
		case 3: {
			printf("Setting begin date: ");
			setDate(&company.beginDay, &company.beginMonth, &company.beginYear);
			printf("\n%d.%d.%d - begin date\n", company.beginDay, company.beginMonth, company.beginYear);
			break;
		}
		case 4: {
			printf("Setting end date: ");
			setDate(&company.endDay, &company.endMonth, &company.endYear);
			printf("\n%d.%d.%d - end date\n", company.endDay, company.endMonth, company.endYear);
			break;
		}
		case 5: {
			printf("Setting employees number: ");
			company.employeesNumber = getIntCommand(1, 1000);
			printf("\n");
			break;
		}
		case 6: {
			printf("begin date - %d.%d.%d\n", company.beginDay, company.beginMonth, company.beginYear);
			printf("end date - %d.%d.%d\n", company.endDay, company.endMonth, company.endYear);
			printf("number of employees - %d\n", company.employeesNumber);
			printf("rate - %d\n", company.rate);
			printf("budget - %d\n", company.budget);
			break;
		}
		case 7: {
			company.length = calculateLength(company.beginDay, company.beginMonth, company.beginYear, company.endDay,
				company.endMonth, company.endYear);
			if (company.length <= 0) {
				printf("End data is earlier than begin. Choose another dates\n");
			}
			else {
				company.workLength = (company.length / 7) * 5 + company.length % 7;
				printf("Length - %d, workingh days - %d\n", company.length, company.workLength);
			}
			break;
		}
		case 8: {
			company.programmersCost = getProgrammersCost(company.workLength, company.rate, company.employeesNumber);
			if (company.programmersCost <= 0) {
				printf("Not enogh date. Work length, rate, number of employess are required. Press 6 to see, what you have entered\n");
			}
			else {
				company.allCost = 2.5 * company.programmersCost;
				company.profit = company.budget - company.allCost;
				printf("programmers cost - %lld, all cost - %lld, profit - %lld\n", company.programmersCost, company.allCost, company.profit);
				if (company.profit >= 1000) {
					printf("Analysis advise: start project\n");
				}
				else {
					printf("Analysis advise: cancel project\n");
				}
			}
			break;
		}
		case 9: {
			printf("Version of programm - 42\n");
			printf("Developer - Kononovich Stanislav\n");
			break;
		}
		default: {
			break;
		}
		}
	} while (command != 10);
	return 0;
}
