#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Employee.h"
#include "utn.h"
#include "Controller.h"
#include "parser.h"

#define LONG_NOMBRE 127
static int findMaxId(LinkedList* pArrayListEmployee);
int cliente_generarIdNuevo(LinkedList* pArrayListEmployee);

static int findMaxId(LinkedList* pArrayListEmployee)
{
	Employee* pEmployee;
	int len;
	int i;
	int max;
	int id = -1;

	if(pArrayListEmployee != NULL)
	{
		len = ll_len(pArrayListEmployee);
		for(i=0;i<len;i++)
		{
			pEmployee = (Employee*)ll_get(pArrayListEmployee,i);
			employee_getId(pEmployee,&id);
			if (i == 0 || id > max)
			{
				max = id;
			}
		}
		id = max;
	}
	return id;
}
int cliente_generarIdNuevo(LinkedList* pArrayListEmployee)
	{
	static int id = -1;
    static int flag = 1;

	    if(pArrayListEmployee != NULL)
	    {
			if(flag == 1)//only once, the first time after opening the file
			{
				id = findMaxId(pArrayListEmployee);
				flag++;
			}
			id++;
	    }
	    return id;
	}
/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromText(char* path , LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	FILE *pFile;

		if (path != NULL && pArrayListEmployee != NULL)
		{
			pFile = fopen(path, "r");
			if (pFile != NULL)
			{
				retorno = parser_EmployeeFromText(pFile, pArrayListEmployee); //parser_Employee returns 0 if Ok
				fclose(pFile);
			}
			else {
				retorno = -2; //couldn't open the file or the file doesn't exist
			}
		}
		return retorno;
}
/** \brief Carga los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee)
{
	int result = -1;
	FILE *pFile;

	if (path != NULL && pArrayListEmployee != NULL)
	{
		pFile = fopen(path, "rb");
		if (pFile != NULL)
		{
			result = parser_EmployeeFromBinary(pFile, pArrayListEmployee);//parser_Employee returns 0 if Ok
			fclose(pFile);
		} else {
			result = -2; //couldn't open the file
		}
	}
	return result;
}
/** \brief Alta de empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_addEmployee(LinkedList* pArrayListEmployee)
{
	int output = -1;
	char name[LONG_NOMBRE];
	char horasTrabajadas[LONG_NOMBRE];
	char sueldo[LONG_NOMBRE];
	char id[LONG_NOMBRE] ;
	Employee* bufferEmpleado;

	if(     utn_getCadenaNumerica ("Ingresar horas trabajadas\n", "Error, ingresar un valor válido\n", horasTrabajadas,1, TEXTO_NUMERICO,2) ==0 &&
			utn_getCadenaNumerica ("Ingresar sueldo\n", "Error, ingresar un valor válido\n", sueldo,1, TEXTO_NUMERICO,2) ==0 &&
			utn_getNombre("Ingresar nombre\n", "Error, ingresar un nombre válido\n", name,2, LONG_NOMBRE) ==0
	   )
	{
		sprintf(id, "%d", cliente_generarIdNuevo(pArrayListEmployee));
		//sprintf(bufferEmpleado->id, "%d", id); ///////////////////////////////////////////////// ID
		bufferEmpleado = employee_newParametros(id, name, horasTrabajadas, sueldo);
		//printf("CONTROLLER - ID-  %d\n", bufferEmpleado->id);
		//printf("CONTROLLER - SUELDO-  %d\n", bufferEmpleado->sueldo);
		ll_add(pArrayListEmployee, bufferEmpleado);
	}
    return output;
}

/** \brief Modificar datos de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_editEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	int bufferId;
	int indiceAModificar;
	int confirmacion;
	Employee* bufferList;
	int horasTrabajadas;
	int sueldo;
	char nombre[LONG_NOMBRE];

	if (
			//cliente_validacionAlta (pListClientes, QTY_CLIENTES) == 0 &&
			pArrayListEmployee != NULL &&
			//limite > 0 &&
			utn_getNumero("Ingrese el ID que desea modificar\n", "Error, ingrese una opción válida\n", &bufferId,2,999999,0) == 0
			&& findEmployeeById(pArrayListEmployee, bufferId) > -1
	)
	{
		indiceAModificar = findEmployeeById(pArrayListEmployee, bufferId);
		printByIndex(pArrayListEmployee, indiceAModificar);
		if (utn_getNumero("\n¿Está seguro que desea modificar a este cliente?\n 0- Si \n 1- No\n", "Error, ingresar una opción válida\n", &confirmacion,2,1,0) == 0)
		{
			if (
					(Employee*)ll_get(pArrayListEmployee, indiceAModificar) != NULL &&
					utn_getNumero("Ingrese horas trabajadas\n", "Error, ingrese un valor válido\n", &horasTrabajadas,2,999999,0) == 0 &&
					utn_getNumero("Ingrese el sueldo\n", "Error, ingrese un valor válido\n", &sueldo,2,999999,0) == 0 &&
					utn_getNombre("\n Nombre?","\nError",nombre,2,LONG_NOMBRE) == 0 )
			{
				bufferList = (Employee*)ll_get(pArrayListEmployee, indiceAModificar);
				employee_setHorasTrabajadas(bufferList, horasTrabajadas);
				employee_setSueldo(bufferList, sueldo);
				employee_setNombre(bufferList, nombre);
			}
		}
		printf("\n El cliente ha sido modificado. \n");
		printByIndex(pArrayListEmployee, indiceAModificar);
		retorno = 0;
	}
	return retorno;
}

/** \brief Baja de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_removeEmployee(LinkedList* pArrayListEmployee)
{
		int retorno = -1;
		int bufferId;
		int indiceAModificar;
		int confirmacion;
		Employee* bufferList;


		if (    //cliente_validacionAlta (pListClientes, QTY_CLIENTES) == 0 && limite > 0 &&
				pArrayListEmployee != NULL &&
				utn_getNumero("Ingrese el ID que desea eliminar\n", "Error, ingrese un número válido\n", &bufferId,2,999999,0) == 0 &&
				findEmployeeById(pArrayListEmployee, bufferId) > -1                  )
		{
			indiceAModificar = findEmployeeById(pArrayListEmployee, bufferId);
			printByIndex(pArrayListEmployee, indiceAModificar);
				if (utn_getNumero("\n¿Está seguro que desea eliminar a este empleado?\n 0- Si \n 1- No\n", "Error, ingresar una opción válida\n", &confirmacion,2,1,0) == 0)
				{
					bufferList = ll_pop(pArrayListEmployee,indiceAModificar);
					employee_delete(bufferList);
				}
		}
		return retorno;
}

/** \brief Listar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
    return 1;
}

/** \brief Ordenar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
    return 1;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char* path , LinkedList* pArrayListEmployee)
{
    return 1;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsBinary(char* path , LinkedList* pArrayListEmployee)
{
    return 1;
}
int findEmployeeById(LinkedList* pArrayListEmployee, int id)
{
	int retorno = -1;
	int len;
	//int bufferId;
	Employee* bufferEmployee;
	if (pArrayListEmployee != NULL && id > -1 && ll_len(pArrayListEmployee) > -1)
	{
		len = ll_len(pArrayListEmployee);
		for (int i = 0; i < len; i++)
		{
			//employee_getId(bufferEmployee, &bufferId);
			if (bufferEmployee != NULL && (Employee*)ll_get(pArrayListEmployee,i) != NULL )
			{
				bufferEmployee = (Employee*) ll_get(pArrayListEmployee,i);
				if( bufferEmployee->id == id )
				{
					retorno = i;
					break;
				}
			}
		}
	}
	return retorno;
}
int printByIndex(LinkedList* pArrayListEmployee, int index)
{
	int retorno = -1;
	Employee* bufferEmployee;

	if (pArrayListEmployee != NULL && index > -1 && ll_len(pArrayListEmployee) > -1 && (Employee*)ll_get(pArrayListEmployee,index) != NULL)
	{
		bufferEmployee = (Employee*)ll_get(pArrayListEmployee,index);
		printf("==============      Nombre: %s | Horas trabajadas: %d | Sueldo: %d |      ==============  \n:", bufferEmployee->nombre, bufferEmployee->horasTrabajadas, bufferEmployee->sueldo);
		retorno = 0;

	}
	return retorno;
}

void employee_delete(Employee* this)
{
	free(this);
}
int controller_hardCode(LinkedList* pArrayListEmployee, char* name, char* horasTrabajadas, char* sueldo )
{
	int output = -1;
	char id[LONG_NOMBRE] ;
	Employee* bufferEmpleado;
	{
		sprintf(id, "%d", cliente_generarIdNuevo(pArrayListEmployee));
		bufferEmpleado = employee_newParametros(id, name, horasTrabajadas, sueldo);
		//printf("HARCODE==== - ID-  %d\n", bufferEmpleado->id);
		//printf("HARCODE==== - SUELDO-  %d\n", bufferEmpleado->sueldo);
		ll_add(pArrayListEmployee, bufferEmpleado);
	}
    return output;
}
int printAllEmployees(LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	Employee* bufferEmployee;
	int len;

	if (pArrayListEmployee != NULL && ll_len(pArrayListEmployee) > -1 &&(Employee*) ll_get(pArrayListEmployee,0) != NULL)
	{
		len = ll_len(pArrayListEmployee);
		for (int i = 0; i < len ; i++)
		{
			bufferEmployee = (Employee*)ll_get(pArrayListEmployee,i);
printf("==============   Indice: %d |   ID: %d | Nombre: %s   | Horas trabajadas: %d  | Sueldo: %d    |         ==============  \n", i, bufferEmployee->id, bufferEmployee->nombre, bufferEmployee->horasTrabajadas, bufferEmployee->sueldo);
//printf("==============    ID: %d | Nombre: %s   | Horas trabajadas: %d  | Sueldo: %d    |         ==============  \n", bufferEmployee->id, bufferEmployee->nombre, bufferEmployee->horasTrabajadas, bufferEmployee->sueldo);

		}
		retorno = 0;
	}
	return retorno;
}
int controller_sort (LinkedList* pArrayListEmployee)
{
	int retorno = -1;

	if (ll_sort(pArrayListEmployee, employee_funcionCriterio, 0) != -1)
	{
		printAllEmployees(pArrayListEmployee);
	}
	return retorno;
}
