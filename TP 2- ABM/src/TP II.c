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

	/*employee_hardCode(pList, QTY_EMPLOYEES, "Alicia","Sanchez",50.00,2);
	employee_hardCode(pList, QTY_EMPLOYEES, "Tamara","Aaaaa",20.000,5);
	employee_hardCode(pList, QTY_EMPLOYEES, "Zandra","Fernandez",1000.00,1);
	employee_hardCode(pList, QTY_EMPLOYEES, "Daniela","Cruz",32.00,3);
	employee_hardCode(pList, QTY_EMPLOYEES, "Marcos","Cruz",32.00,5);
	*/

	do {
		getMainMenu(&menu);
		switch (menu) {
		case 1:
			getEmployeeInfo(pList, QTY_EMPLOYEES);
			printEmployees(pList, QTY_EMPLOYEES);
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
			printf("======Programa finalizado=========\n");
			exit(0);
			break;
		}

	} while (menu != 5);

}
