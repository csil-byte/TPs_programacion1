#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"
#include "parser.h"
#include "Controller.h"



/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromText(FILE* pFile , LinkedList* pArrayListEmployee)
{

	int result = -1;
	Employee *pEmployee;
	char bufferHeader[500];
	char bufferId[500];
	char bufferName[500];
	char bufferWorkedHours[500];
	char bufferSalary[500];
	int scan;
	int flagId = 0;
	int maxId;

	if (pFile != NULL && pArrayListEmployee != NULL)
	{
		fscanf(pFile, "%[^\n]\n", bufferHeader);// SALTEA EL HEADER-
		do
		{
			scan = fscanf(pFile, "%[^,],%[^,],%[^,],%[^\n]\n", bufferId, bufferName, bufferWorkedHours, bufferSalary);
			if (scan == 4)
			{

				pEmployee = employee_newParametros(bufferId, bufferName, bufferWorkedHours, bufferSalary);
				if (pEmployee != NULL)
				{
					ll_add(pArrayListEmployee, pEmployee);//ll_add returns 0 if Ok
				}
				if (flagId == 0 || atoi(bufferId) > maxId)
				{
					flagId = 1;
					maxId = atoi(bufferId);
					result = maxId;
				}
			}
			else
			{
				break;
			}
		} while (!feof(pFile));
	}
	//printf("MAX ID - PARSER ------- %d\n", maxId);
	return result;
}

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromBinary(FILE* pFile , LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	Employee* pEmployee;

	if (pFile != NULL && pArrayListEmployee != NULL)
	{
		do
		{
			pEmployee = employee_new();
			if (pEmployee != NULL && fread(pEmployee,sizeof(Employee),1,pFile)==1)
			{

				retorno = ll_add(pArrayListEmployee, pEmployee);//returns 0
			} else {
				break;
			}
		} while (!feof(pFile));
	}
	return retorno;
}
