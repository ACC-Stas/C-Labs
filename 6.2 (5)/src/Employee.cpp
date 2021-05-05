#include "Employee.h"

bool Employee::operator==(Employee& value) {
	if (value.name == name && value.surName == surName && value.patronymic == patronymic) {
		return true;
	}
	else {
		return false;
	}
}