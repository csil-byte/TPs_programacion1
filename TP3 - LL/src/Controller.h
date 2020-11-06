#include "Employee.h"

int controller_loadFromText(char* path , LinkedList* pArrayListEmployee);
int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee);
int controller_addEmployee(LinkedList* pArrayListEmployee);
int controller_editEmployee(LinkedList* pArrayListEmployee);
int controller_removeEmployee(LinkedList* pArrayListEmployee);
int controller_ListEmployee(LinkedList* pArrayListEmployee);
int controller_sortEmployee(LinkedList* pArrayListEmployee);
int controller_saveAsText(char* path , LinkedList* pArrayListEmployee);
int controller_saveAsBinary(char* path , LinkedList* pArrayListEmployee);

int findEmployeeById(LinkedList* pArrayListEmployee, int id);
int printByIndex(LinkedList* pArrayListEmployee, int index);
void employee_delete(Employee* this);
int controller_hardCode(LinkedList* pArrayListEmployee, char* name, char* horasTrabajadas, char* sueldo );



int controller_generarIdNuevo(LinkedList* pArrayListEmployee);

