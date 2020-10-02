/*
 ============================================================================
 Name        : TP2
 Author      : Cecilia Silva
 Version     : v1.5000
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "utn.h"
#include "ArrayEmployees.h"
#define QTY_EMPLOYEES 1000

int main(void) {
	setbuf(stdout, NULL);
	Employee pList[QTY_EMPLOYEES];
	int menu;
	initEmployees(pList, QTY_EMPLOYEES);


	do {
		getMainMenu(&menu);
		switch (menu) {
		case 1:
			getEmployeeInfo(pList, QTY_EMPLOYEES);
			break;
		case 2:
			employee_modificar(pList, QTY_EMPLOYEES);
			break;
		case 3:
			inactive_Employee (pList, QTY_EMPLOYEES);
			break;
		case 4:
			employee_inform (pList, QTY_EMPLOYEES);
			break;
		case 5:
			printf("Programa finalizado");
			exit(0);
			break;
		}

	} while (menu != 6);

}
