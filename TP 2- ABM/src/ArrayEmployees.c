/*
 * Employee.c
 *
 *  Created on: 21 sep. 2020
 *      Author: user
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "ArrayEmployees.h"
#include "utn.h"
#define SALARY_MAX 99999999.00

//FUNCIONES REQUERIDAS POR TP

/*initEmployees
* \brief To indicate that all position in the array are empty, this function put the flag (isEmpty) in TRUE in all
* position of the array
* \param list Employee* Pointer to array of employees
* \param len int Array length
* \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
*
*/
int initEmployees(Employee* pList, int len) {
int retorno = -1;
	if (pList != NULL && len > 0) {
		for (int i = 0; i < len; i++)
		{
			pList[i].isEmpty = TRUE;
		}
		retorno = 0;
	}
return retorno;
}
/* AddEmployees
*brief add in a existing list of employees the values received as parameters in the first empty position
* \param list employee*
* \param len int
* \param id int
* \param name[] char
* \param lastName[] char
* \param salary float
* \param sector int
* \return int Return (-1) if Error [Invalid length or NULL pointer or without free space *** also validates that index is greater than -1***]  - (0) if Ok
*/
int addEmployee(Employee* pList, int len, int id, char name[],char lastName[],float salary,int sector)
{
	int retorno = -1;
	int indice;

	if ( pList != NULL && len > 0  && (employee_buscadorIndiceLibre (pList, QTY_EMPLOYEES)  > -1))
	{
		indice = employee_buscadorIndiceLibre (pList, QTY_EMPLOYEES);
		strncpy(pList[indice].name, name, FIRST_NAME);
		strncpy(pList[indice].lastName, lastName, LAST_NAME);
		pList[indice].id = id;
		pList[indice].sector = sector;
		pList[indice].salary = salary;
		pList[indice].isEmpty = FALSE;
		printf("\n=========== Empleado agregado correctamente ==============\n\n");
		retorno = 0;
	}
	return retorno;
}
/* findEmployeeById
* \brief find an Employee by Id and returns the index position in array.
* \param list Employee*
* \param len int
* \param id int
* \return Return employee index position or (-1) if [Invalid length or NULL pointer received or employee not found]
*/
int findEmployeeById(Employee* pList, int len, int id)
{
    int retorno = -1;
    if (pList != NULL && len > 0)
    {
        for (int i = 0; i < len; i++)
        {
            if(pList[i].isEmpty == FALSE )
            {
                if(pList[i].id == id)
                {
                   retorno = i;
                    break;
                }
            }
        }
    }
    return retorno;
}
/* removeEmployee
* \brief Remove a Employee by Id (put isEmpty Flag in 1)
* \param list Employee*
* \param len int
* \param id int
* \return int Return (-1) if Error [Invalid length or NULL pointer or if can't
find a employee] - (0) if Ok
*/
int removeEmployee(Employee* pList, int len, int id)
{
	int retorno = -1;
	int bufferIndex;
	int confirmacion;

	if(pList != NULL && len > 0 && id > -1 )
	{
		if (findEmployeeById(pList, QTY_EMPLOYEES, id) > -1)
		{
			bufferIndex = findEmployeeById(pList, QTY_EMPLOYEES, id);
			printf ("Este ID corresponde al siguiente empleado: \n");
			employee_printByIndex(pList, QTY_EMPLOYEES, bufferIndex);

			if ( !utn_getNumero("\n¿Está seguro de querer eliminar este empleado?\n 0 - Si\n 1 - No\n", "Error. Ingresar una opción válida\n", &confirmacion,2,1,0) &&
					confirmacion == 0)
			{
				pList[bufferIndex].isEmpty = TRUE;
				printf ("\n=======Empleado eliminado correctamente:========== \n");
				retorno = 0;
			}
			else
			{
				retorno = 0;
			}

		}

		else
		{
			printf ("Error, no se encuentra cargado ningún empleado con este ID. \nFavor volver a intentar\n");
		}
	}
	return retorno;
}
/*sortEmployees
* \brief Sort the elements in the array of employees, the argument order indicate UP or DOWN order
* \param list Employee*
* \param len int
* \param order int [1] indicate UP ASCENDANT  - [0] indicate DOWN DESCENDANT
* \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
*/
int sortEmployees(Employee* pList, int len, int orden)
{
	int retorno = -1;
	int flagSwap;
	Employee bufferEmployee;
	int newLen;

	if (employee_validacionAlta (pList, QTY_EMPLOYEES) == 0 && pList != NULL && len  > 0 && (orden == 0 || orden == 1) )
	{
		newLen = len-1;
		do
		{   flagSwap = 0;
				for (int i = 0; i < newLen; i++)
				{
					if (pList[i].isEmpty == FALSE && pList[i+1].isEmpty == FALSE)
					{
						if ((strcmp(pList[i].lastName, pList[i+1].lastName) < 0 && orden == 1) ||
							((strcmp(pList[i].lastName, pList[i+1].lastName) > 0) && orden == 0)
														||
										((strcmp(pList[i].lastName, pList[i+1].lastName) == 0 && pList[i].sector < pList[i+1].sector) && orden == 1) ||
										((strcmp(pList[i].lastName, pList[i+1].lastName) == 0 && pList[i].sector > pList[i+1].sector) && orden == 0))
						{
							flagSwap = 1;
							bufferEmployee = pList[i];
							pList[i] = pList[i+1];
							pList[i+1] = bufferEmployee;
						}
					}
				}
				newLen--;
		} while (flagSwap);
	}
	if (flagSwap == 0)
	{
		//printEmployees(pList, QTY_EMPLOYEES);
		retorno = 0;
	}
	return retorno;
}
/*printEmployees
* \brief prints the content of employees array
* \param list Employee*
* \param length int
* \returns [-1] if no employees have been added and [0] if at least one employee was added.
*/
int printEmployees(Employee* pList, int len)
{
int retorno = -1;

if (pList != NULL &&  len > 0)
{
	for (int i = 0; i < len; i++)
	{
		if (pList[i].isEmpty == FALSE)
		{
			printf ("INDICE: %d - ID: %d - Nombre: %s - Apellido: %s -  Sector %d - Salary %.2f  \n", i, pList[i].id, pList[i].name,pList[i].lastName, pList[i].sector, pList[i].salary );
			retorno = 0;
		}
	}
}
return retorno;
}

//FUNCIONES AUXILIARES PARA EMPLOYEE

/*employee_salaryAverage
* \brief function prints total salary of all employees and those whose salary is above average.
* \param list Employee* Pointer to array of employees
* \param len int Array length
* \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
*/
int employee_salaryAverage(Employee *pList, int len)
{
	int retorno = -1;
	int totalSalary= 0;
	float averageSalary;
	int aboveAverageSalary = 0;
	int totalEmployees = 0;

	if(employee_validacionAlta (pList, QTY_EMPLOYEES) == 0 && pList != NULL && len > 0 )
	{
		for (int i = 0; i < len; i++)
		{
			if(pList[i].isEmpty == FALSE)
			{
				totalSalary = totalSalary + pList[i].salary;
				totalEmployees++;
			}
		}
		printf("El salario total entre todos los empleados es: %d\n", totalSalary);
		averageSalary = totalSalary / (float)totalEmployees;
		printf("El promedio total entre los salarios de todos los empleados es: %.2f\n", averageSalary);

		for (int i = 0; i < len; i++)
		{
			if(pList[i].isEmpty == FALSE && pList[i].salary > averageSalary)
			{
				aboveAverageSalary++;
			}
		}
		printf("La cantidad de empleados que superan el sueldo promedio son: %d\n", aboveAverageSalary);
		retorno = 0;
	}
	return retorno;
}
/*inactive_Employee
* \brief function asks user for ID and validates that at least 1 employee has been added. if it's valid, it calls for removeEmployee.
* \param list Employee* Pointer to array of employees
* \param len int Array length
* \return int Return (-1) if Error [Invalid length,NULL pointer, invalid id or no employees have been added] - (0) if Ok
*
*/
int inactive_Employee (Employee* pList, int len)
{
	int retorno = -1;
	int bufferId;

	if ( employee_validacionAlta (pList, QTY_EMPLOYEES) == 0 && pList != NULL && len > -1)
	{
		printEmployees(pList, QTY_EMPLOYEES);
		if (utn_getNumero("\nIngrese el ID del empleado al que desea dar de baja\n", "Error, ingrese un ID válido\n", &bufferId,2,1000000000,1) == 0)
		{
			removeEmployee(pList, QTY_EMPLOYEES, bufferId);
			retorno = 0;
		}
	}

	return retorno;
}
/*employee_modificar
* \brief function validates at least one employee has been added, asks for valid id and gives the user the choice to modify different categories for employees.
* \param list Employee* Pointer to array of employees
* \param len int Array length
* \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
*/
int employee_modificar (Employee* pList, int lim)
{
	int retorno=  -1;
	Employee bufferList;
	int menuModificacion;
	int id;
	int indice;


	if (employee_validacionAlta (pList, QTY_EMPLOYEES) == 0 )
	{
		if ( pList != NULL && lim > 0 &&
				utn_getNumero("Ingrese el ID que desea modificar\n", "Error, ingrese una opción válida\n", &id,2,INT_MAX,1) == 0 &&
				findEmployeeById (pList, QTY_EMPLOYEES, id) > -1 )
		{
			indice = findEmployeeById (pList, QTY_EMPLOYEES, id);
			printf("El ID corresponde al empleado: ");
			employee_printByIndex(pList, QTY_EMPLOYEES, indice);
			do{
				if (utn_getNumero("\nIngrese un campo a modificar:\n Opcion: 1- Nombre \n Opcion: 2- Apellido \n Opcion: 3- Salario \n Opcion: 4- Sector \n Opcion: 5- Salir \n","Error, ingrese una opción válida\n",  &menuModificacion,2,5,1) == 0 )
				{

					switch (menuModificacion)
					{
					case 1:
						if (  utn_getNombre("Nombre?\n","\nError",bufferList.name,2,FIRST_NAME) == 0   )
						{
							strncpy(pList[indice].name, bufferList.name, FIRST_NAME);
							printf("Modificado correctamente\n");
							employee_printByIndex(pList, QTY_EMPLOYEES, indice);
							retorno = 0;
						}
						break;
					case 2:
						if (  utn_getNombre("Apellido?\n","\nError",bufferList.lastName,2,LAST_NAME) == 0   )
						{
							strncpy(pList[indice].lastName, bufferList.lastName, LAST_NAME);
							printf("Modificado correctamente\n");
							employee_printByIndex(pList, QTY_EMPLOYEES, indice);
							retorno = 0;
						}
						break;
					case 3:
						if  (  utn_getNumeroFloat(&bufferList.salary,"Salario?\n","\nError",1,SALARY_MAX,2) == 0 )
						{
							pList[indice].salary = bufferList.salary;
							printf("Modificado correctamente\n");
							employee_printByIndex(pList, QTY_EMPLOYEES, indice);
							retorno = 0;
						}
						break;
					case 4:
						if ( utn_getNumero("Ingrese un sector:\n 1 - Administración \n 2 - Logística & Operaciones \n 3 - Dirección \n 4 - Financiero \n 5 - RRHH \n 6 - Comercial \n 7 - Compras ","\nError", &bufferList.sector,2,7,1) == 0  )
						{
							pList[indice].sector = bufferList.sector;
							printf("Modificado correctamente\n");
							employee_printByIndex(pList, QTY_EMPLOYEES, indice);
							retorno = 0;
						}
						break;
					case 5:
						break;
					}
				}
			}while (menuModificacion != 5);
		}
		if (findEmployeeById (pList, QTY_EMPLOYEES, id) == -1)
		{
			printf("Este empleado no se encuentra registrado en el sistema. Favor volver a intentar\n");
		}
	}
		return retorno;
	}
/*getEmployeeInfo
* \brief function is in charge of asking users input in order to later call addEmployee to add employee to array. For sector, fictional names have been added for the sake of easier input but can be easily removed.
* \param list Employee* Pointer to array of employees
* \param lim int Array length
* \return int Return (-1) if Error [Invalid length or NULL pointer or if different user's input are invalid] - (0) if Ok
*/
int getEmployeeInfo(Employee* pList, int lim)
{
	int retorno = -1;
	int id;
	char name[FIRST_NAME];
	char lastName[LAST_NAME];
	float salary;
	int sector;
	int indice;

	if (employee_buscadorIndiceLibre (pList, QTY_EMPLOYEES) > -1)
	{
		indice = employee_buscadorIndiceLibre (pList, QTY_EMPLOYEES);
		if(	    ( utn_getNombre("Nombre?\n","\nError, favor ingresar un nombre válido\n",name,2,FIRST_NAME) == 0   ) &&
				( utn_getNombre("Apellido?\n","\nError, favor ingresar un apellido válido\n",lastName,2,LAST_NAME) == 0 ) &&
				( utn_getNumeroFloat(&salary,"Salario?\n","\nError\n",1,SALARY_MAX,2) == 0 ) &&
				( utn_getNumero("Ingrese un sector:\n 1 - Administración \n 2 - Logística & Operaciones \n 3 - Dirección \n 4 - Financiero \n 5 - RRHH \n 6 - Comercial \n 7 - Compras ","\nError\n", &sector,2,7,1) == 0  ))
		{
			id = employee_generarIdNuevo();
			pList[indice].id = id;
			addEmployee(pList, QTY_EMPLOYEES, id, name,lastName,salary,sector);
			retorno = 0;
		}
	}

	return retorno;
}
/*employee_generarIdNuevo
* \brief function is in charge of generating an unique id for each employee added.
* \return int Return id
*/
int employee_generarIdNuevo(void)
	{
	    static int id= 0;
	    id = id+1;
	    return id;
	}
/*employee_buscadorIndiceLibre
* \brief goes through array and finds first index position that is free and returns it
* \param list Employee*
* \param len int
* \return [-1] if there are no free spaces or >-1 to indicate index of free space
*/
int employee_buscadorIndiceLibre (Employee* pList, int len)
{
	int retorno = -1;
	if(pList != NULL && len > 0)
	{
		for(int i=0;i<len;i++)
		{
			if (pList[i].isEmpty == TRUE)
			{
				retorno = i;
				break;
			}
		}
	}
	return retorno;
}
/*employee_printByIndex
* \brief given an index, prints out information regarding employee in said index
* \param list Employee*
* \param length int
* \param index int
* \return [-1] if no employees have been added in said index [0] if there is one.
*/
int employee_printByIndex(Employee* pList, int limit, int index)
{
		int retorno = -1;
		if(pList != NULL && limit > 0 && index < limit)
		{
			if(pList[index].isEmpty == FALSE)
			{
				printf("INDICE: %d - ID: %d - Nombre: %s - Apellido: %s - Sector: %d - Salary: %.2f  \n",index, pList[index].id, pList[index].name, pList[index].lastName, pList[index].sector, pList[index].salary );
				retorno = 0;
			}
		}
		return retorno;
}
/*employee_validacionAlta
* \brief validate if there is at least one employee that has been added
* \param list Employee*
* \param length int
* \return [-1] if no employees have been added and [0] if there is at least one.
*/
int employee_validacionAlta (Employee* pList, int len)
{
int retorno = -1;
    if (pList != NULL && len > 0)
    {
        for (int i = 0; i < len; i++)
        {
            if(pList[i].isEmpty == FALSE )
            {
                retorno = 0;
                break;
            }
            else
            {
            	printf ("Error, deberá ingresar al menos un empleado para acceder a este sector. \n");
            	break;
            }
        }
    }
    return retorno;
}
/*employee_inform
* \brief validate if there is at least one employee that has been added, parameters received and asks for user what kind of data it wants to see
* \param list Employee*
* \param len int
* \return [-1] if no employees have been added, NULL pointer, array smaller than 1 and if invalid number for case and [0] if everything validated ok .
*/
int employee_inform (Employee* pList, int len)
{
	int retorno = -1;
	int menu;

	if (employee_validacionAlta (pList, QTY_EMPLOYEES) == 0 && pList != NULL && len > 0 )
	{
		do
		{
			if (utn_getNumero("\nElegir:\n 1- Listado de los empleados ordenados alfabéticamente por Apellido y Sector.\n 2- Total y promedio de los salarios, y cuántos empleados superan el salario promedio. \n 3- Salir\n","Error, ingrese una opción válida\n", &menu,2,3,1) == 0)
			{
				switch (menu)
				{
				case 1:
					if (sortEmployees(pList, QTY_EMPLOYEES, 0) == 0)
					{
						printEmployees(pList, QTY_EMPLOYEES);
						retorno = 0;
					}
					break;
				case 2:
					if (employee_salaryAverage(pList, QTY_EMPLOYEES) == 0)
					{
						retorno = 0;
					}
					break;
				case 3:
					printf("Programa finalizado\n");
					break;
				}
			}
		} while (menu != 3);
	}
	return retorno;
}
/*getMainMenu
* \brief gets int for main menu and validates option is valid.
* \param menu*
* \return [-1] if option is invalid and [0] if everything's ok.
*/
int getMainMenu(int* menu)
{
	int retorno = -1;
	int bufferMenu;

	if (menu != NULL && utn_getNumero("\n1-Alta\n2-Modificar\n3-Eliminar Empleado\n4-Informe\n5-Salir \n", "\nError\n", &bufferMenu, 2, 5, 1) == 0)
	{
		*menu = bufferMenu;
		retorno = 0;
	}
	else
	{
		exit(-1);
	}

	return retorno;

}

int employee_hardCode (Employee* pList, int len, char name[],char lastName[],float salary,int sector)
{
	int retorno = -1;
	int indice;
	int id;

	if ( pList != NULL && len > 0  && (employee_buscadorIndiceLibre (pList, QTY_EMPLOYEES)  > -1))
	{
		indice = employee_buscadorIndiceLibre (pList, QTY_EMPLOYEES);
		strncpy(pList[indice].name, name, FIRST_NAME);
		strncpy(pList[indice].lastName, lastName, LAST_NAME);
		id = employee_generarIdNuevo();
		pList[indice].id = id;
		pList[indice].sector = sector;
		pList[indice].salary = salary;
		pList[indice].isEmpty = FALSE;
		employee_printByIndex(pList, QTY_EMPLOYEES, indice);
		retorno = 0;
	}
	return retorno;
}
