#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"
#include "parser.h"
#include "Controller.h"



/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo texto).
 *			analizará la cadena y continuará leyendo mientras se cumpla la regla que se le pasó
 * \param path char* |   \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromText(FILE* pFile , LinkedList* pArrayListEmployee)
{

	int result = -1;
	Employee *pEmployee;
	char header[LONG_TXT];
	char bufferHoras[LONG_TXT];
	char bufferId[LONG_TXT];
	char bufferSueldo[LONG_TXT];
	char bufferNombre[LONG_TXT];
	int scan;

	if (pFile != NULL && pArrayListEmployee != NULL)
	{
		fscanf(pFile, "%[^\n]\n", header);
		do
		{
			scan = fscanf(pFile, "%[^,],%[^,],%[^,],%[^\n]\n", bufferId, bufferNombre, bufferHoras, bufferSueldo);
			if (scan == 4)
			{
				pEmployee = employee_newParametros(bufferId, bufferNombre, bufferHoras, bufferSueldo);
				if (pEmployee != NULL)
				{
					ll_add(pArrayListEmployee, pEmployee);
					result = 0;
				}
			}
			else
			{
				break;
			}
		} while (!feof(pFile));
	}
	return result;
}
/** \brief Parsea los datos los datos de los empleados desde el archivo data.bin(modo binario).
 *
 * \param path char* | \param pArrayListEmployee LinkedList*
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

				retorno = ll_add(pArrayListEmployee, pEmployee);
			}
			else
			{
				employee_delete(pEmployee);
				break;
			}
		} while (!feof(pFile));
	}
	return retorno;
}
/** \brief Parsea los datos los datos de los empleados al  archivo data.csv(modo texto).
 *
 * \param path char* | \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeToText(FILE* pFile , LinkedList* pArrayListEmployee)
{
	int result = -1;
	Employee *pEmployee;
	int len;
	int bufferId;
	char bufferNombre[LONG_NOMBRE];
	int bufferSueldo;
	int bufferHoras;

	if (pFile != NULL && pArrayListEmployee != NULL)
	{
		len = ll_len(pArrayListEmployee);
		fprintf(pFile, "ID, NOMBRE, HORAS TRABAJADAS, SUELDO\n");
		for (int i = 0; i < len; i++)
		{
			pEmployee = (Employee*)ll_get(pArrayListEmployee, i);
			if (pEmployee != NULL
					&& employee_getId(pEmployee, &bufferId) == 0
					&& employee_getNombre(pEmployee, bufferNombre) == 0
					&& employee_getSueldo(pEmployee, &bufferSueldo) == 0
					&& employee_getHorasTrabajadas(pEmployee, &bufferHoras) == 0)
			{
				fprintf(pFile, "%d,%s,%d,%d\n", bufferId, bufferNombre, bufferHoras, bufferSueldo);
				result = 0;
			}
		}
	}
	return result;
}
