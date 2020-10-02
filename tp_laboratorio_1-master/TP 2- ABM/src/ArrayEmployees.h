/*
 * Employee.h
 *
 *  Created on: 21 sep. 2020
 *      Author: user
 */

#ifndef ARRAYEMPLOYEES_H_
#define ARRAYEMPLOYEES_H_
#define SALARY_MAX 99999999.00
#define QTY_EMPLOYEES 1000
#define TRUE 1
#define FALSE 0
#define FIRST_NAME 51
#define LAST_NAME 51
struct {
	int id;
	char name[FIRST_NAME];
	char lastName[LAST_NAME];
	float salary;
	int sector;
	int isEmpty;
}typedef Employee;

int initEmployees(Employee* pList, int limit);
int addEmployee(Employee* pList, int len, int id, char name[],char lastName[],float salary,int sector);
int findEmployeeById(Employee* pList, int len, int id);
int removeEmployee(Employee* list, int len, int id);
int sortEmployees(Employee* pList, int len, int orden);
int printEmployees(Employee* pList, int len);

int employee_buscadorIndiceLibre (Employee* pList, int len);
int employee_printByIndex(Employee* pList, int limit, int index);
int employee_generarIdNuevo(void);
int getEmployeeInfo(Employee* pList, int lim);
int employee_modificar (Employee* pList, int lim);
int employee_buscarId(Employee* pList, int limite, int id);
int inactive_Employee (Employee* pList, int len);
int employee_salaryAverage(Employee *pList, int len);
int employee_validacionAlta (Employee* pList, int len);
int employee_inform (Employee* pList, int len);
int getMainMenu(int* menu);
#endif /* ARRAYEMPLOYEES_H_ */
