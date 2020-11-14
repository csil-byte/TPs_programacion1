#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "../inc/LinkedList.h"
#include "Employee.h"
#include "utn.h"
#include "Controller.h"
#include "parser.h"

#define LONG_NOMBRE 127
static int findMaxId(LinkedList* pArrayListEmployee);
int controller_generarIdNuevo(LinkedList* pArrayListEmployee);

//////////////////////// //////       ID         ///////////////////////////////////////////////////////////

/** \brief Encuentra cual es el max id, según la longitud de la lista, la recorre con un for hasta
 * encontrar el valor maximo y lo devuelve por return.
 *
 * \param LinkedList* pArrayListEmployee
 * \return int  --------- devuelve -1 cuando hay error |  id > -1 cuando todo ok
 *
 */
static int findMaxId(LinkedList* pArrayListEmployee)
{
	Employee* pEmployee;
	int len;
	int max;
	int id = -1;

	if(pArrayListEmployee != NULL)
	{
		len = ll_len(pArrayListEmployee);
		for(int i =0;i<len;i++)
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
/** \brief Genera id nuevo llamando a findMaxId para tener en cuenta el maximo y usa una bandera para saber
 * cuando se cargan los datos por primera vez para leer el listado de ids.
 *
 * \param LinkedList* pArrayListEmployee
 * \return int  --------- devuelve -1 cuando hay error |  id > -1 cuando todo ok
 *
 */
int controller_generarIdNuevo(LinkedList* pArrayListEmployee)
	{
	static int id = -1;
    static int flag = 1;

	    if(pArrayListEmployee != NULL)
	    {
			if(flag == 1)
			{
				id = findMaxId(pArrayListEmployee);
				flag++;
			}
			id++;
	    }
	    return id;
	}

/////////////////////////////////       C  A  R  G  A      //////////////////////////////////////////////////////

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *	Después de las validaciones, abre el archivo en modo lectura y lo parsea.
 *
 * \param path char* |  \param pArrayListEmployee LinkedList*
 * \return int |   -1 si si los paramentros recibidos son NULL | -2 si no logra abrir el archivo | 0 todo ok (logró parsear)
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
				parser_EmployeeFromText(pFile, pArrayListEmployee);
				fclose(pFile);
				retorno = 0;
			}
			else {
				retorno = -2;
			}
		}
		return retorno;
}
/** \brief Carga los datos de los empleados desde el archivo data.bin (modo binario).
 *Después de las validaciones, abre el archivo en modo lectura y lo parsea.
 *
 * \param path char* |  \param pArrayListEmployee LinkedList*
 * \return int |   -1 si si los paramentros recibidos son NULL | -2 si no logra abrir el archivo | 0 todo ok (logró parsear)
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
			result = parser_EmployeeFromBinary(pFile, pArrayListEmployee);
			fclose(pFile);
		} else {
			result = -2;
		}
	}
	return result;
}

/////////////////////////////////       ALTA | MODIFICACIÓN | BAJA      //////////////////////////////////////////////////////

/** \brief Alta de empleados
 *	Usa ll_isEmpty como flag para verificar que primero se hayan cargado los datos desde archivo, se pide al usuario
 *	los datos que desea agregar, se genera un id, y se llama al newParametros para guardar en un buffer.
 * 	Con el ll_add se agregan los datos recibidos del buffer en pArrayListEmployee.
 *
 * \param path char*
 * \param  LinkedList*
 * \return int -1 si hubo error en la carga o no se cargó el archivo previamente.
 *
 */
int controller_addEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	char name[LONG_NOMBRE];
	char horasTrabajadas[LONG_NOMBRE];
	char sueldo[LONG_NOMBRE];
	char id[LONG_NOMBRE] ;
	Employee* bufferEmpleado;

	if (ll_isEmpty(pArrayListEmployee)==0)
	{
		if(     utn_getCadenaNumerica ("Ingresar horas trabajadas\n", "Error, ingresar un valor válido\n", horasTrabajadas,1, TEXTO_NUMERICO,2) ==0 &&
				utn_getCadenaNumerica ("Ingresar sueldo\n", "Error, ingresar un valor válido\n", sueldo,1, TEXTO_NUMERICO,2) ==0 &&
				utn_getNombre("Ingresar nombre\n", "Error, ingresar un nombre válido\n", name,2, LONG_NOMBRE) ==0
		   )
		{
			sprintf(id, "%d", controller_generarIdNuevo(pArrayListEmployee));
			bufferEmpleado = employee_newParametros(id, name, horasTrabajadas, sueldo);
			ll_add(pArrayListEmployee, bufferEmpleado);
			printf("Empleado agregado con éxito\n");
			retorno = 0;
		}
	}
	else
	{
		printf("Error, deberá cargar un archivo antes de agregar más empleados. Favor volver a intentar\n");
	}
	return retorno;
}
/** \brief Modificar datos de empleado
 *Usa ll_isEmpty como flag para verificar que primero se hayan cargado los datos desde archivo, se pide el ID a modificar.
 *Se verifica que sea válido y se imprime para luego pedir la confirmación del usuario.
 *En caso de confirmación, se modificaran todos los campos del empleado, se imprimirá el empleado modificado
 *	y luego se imprimiran todos los empleados para facilitar revisión.
 *
 * \param pArrayListEmployee LinkedList*
 * \return int -1 si hay error | 0 si todo ok
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

	if (ll_isEmpty(pArrayListEmployee)==0)
	{
		if 	(	pArrayListEmployee != NULL &&
				utn_getNumero("Ingrese el ID que desea modificar\n", "Error, ingrese una opción válida\n", &bufferId,2,999999,0) == 0
				&& findEmployeeById(pArrayListEmployee, bufferId) > -1  )
			{
				indiceAModificar = findEmployeeById(pArrayListEmployee, bufferId);
				printByIndex(pArrayListEmployee, indiceAModificar);
			if (utn_getNumero("\n¿Está seguro que desea modificar a este cliente?\n 0- Si \n 1- No\n", "Error, ingresar una opción válida\n", &confirmacion,2,1,0) == 0)
			{
				switch (confirmacion)
				{
				case (0):

				if (	(Employee*)ll_get(pArrayListEmployee, indiceAModificar) != NULL &&
						utn_getNumero("Ingrese horas trabajadas\n", "Error, ingrese un valor válido\n", &horasTrabajadas,2,999999,0) == 0 &&
						utn_getNumero("Ingrese el sueldo\n", "Error, ingrese un valor válido\n", &sueldo,2,999999,0) == 0 &&
						utn_getNombre("\n Nombre?","\nError",nombre,2,LONG_NOMBRE) == 0 )
				{
					bufferList = (Employee*)ll_get(pArrayListEmployee, indiceAModificar);

					employee_setHorasTrabajadas(bufferList, horasTrabajadas);
					employee_setSueldo(bufferList, sueldo);
					employee_setNombre(bufferList, nombre);

				printf("\n El empleado ha sido modificado. \n");
				printByIndex(pArrayListEmployee, indiceAModificar);
				controller_ListEmployee(pArrayListEmployee);
				retorno = 0;
				}
				break;
				case (1):
						printf("\n No se ha modificado al empleado. \n");
				retorno = 0;
				break;
				}
			}
		}
	}
	else
	{
		printf("Error, deberá cargar un archivo antes de agregar más empleados. Favor volver a intentar\n");
	}
	return retorno;
}
/** \brief Baja de empleado auxiliar - libera memoria
 *
 * \param pArrayListEmployee LinkedList*
 *
 */
void employee_delete(Employee* this)
{
	free(this);
}
/** \brief Baja de empleado
 *Usa ll_isEmpty como flag para verificar que primero se hayan cargado los datos desde archivo, se pide el ID a modificar.
 *Se verifica que sea válido y se imprime para luego pedir la confirmación del usuario.
 *En caso de confirmación, se eliminará al empleado usando ll_pop para no perder el acceso a la dirección del cliente en memoria.
 *
 * \param pArrayListEmployee LinkedList*
 * \return int -1 si no logró eliminarse | 0 si se eliminó empleado o si el usuario decidió no hacerlo
 *
 */
int controller_removeEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	int bufferId;
	int indiceAModificar;
	int confirmacion;
	Employee* bufferList;

	if (ll_isEmpty(pArrayListEmployee)==0)
	{
		if (  	pArrayListEmployee != NULL &&
				utn_getNumero("Ingrese el ID que desea eliminar\n", "Error, ingrese un número válido\n", &bufferId,2,INT_MAX,0) == 0 &&
				findEmployeeById(pArrayListEmployee, bufferId) > -1                  )
		{
			indiceAModificar = findEmployeeById(pArrayListEmployee, bufferId);
			printByIndex(pArrayListEmployee, indiceAModificar);
			if (utn_getNumero("\n¿Está seguro que desea eliminar a este empleado?\n 0- Si \n 1- No\n", "Error, ingresar una opción válida\n", &confirmacion,2,1,0) == 0)
			{
				switch(confirmacion)
				{
				case (0):
				bufferList = ll_pop(pArrayListEmployee,indiceAModificar);
				employee_delete(bufferList);
				printf("Empleado eliminado con éxito\n");
				retorno = 0;
				break;
				case (1):
				printf("El empleado no se ha eliminado\n");
				retorno = 0;
				break;
				}
			}
		}
		else if (findEmployeeById(pArrayListEmployee, bufferId) < 0 )
		{
			printf("Error, no existe ningún empleado bajo este ID. Favor volver a intentar\n");
		}
	}
	else
	{
		printf("Error, deberá cargar un archivo antes de agregar más empleados. Favor volver a intentar\n");
	}

	return retorno;
}

/////////////////////////////////////// INFORMES | LISTADOS | AUXILIARES  ///////////////////////////////////////

/** \brief Listar empleados
 *Usa ll_isEmpty como para verificar que primero se hayan cargado los datos desde algún archivo, hace las validaciones
 *	y guarda la longitud de la lista para luego iterar sobre ella e imprimir los datos. Se agregó el índice para
 *	asistir con la corrección.
 *
 * \param pArrayListEmployee LinkedList*
 * \return int -1 si hubo error | 0 si todo ok
 *
 */
int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	Employee* bufferEmployee;
	int len;

	if (ll_isEmpty(pArrayListEmployee)==0)
	{
		if (pArrayListEmployee != NULL && ll_len(pArrayListEmployee) > -1 &&(Employee*) ll_get(pArrayListEmployee,0) != NULL)
		{
			len = ll_len(pArrayListEmployee);
			for (int i = 0; i < len ; i++)
			{
				bufferEmployee = (Employee*)ll_get(pArrayListEmployee,i);
				printf("==============   Indice: %d |   ID: %d | Nombre: %s   | Horas trabajadas: %d  | Sueldo: %d    |         ==============  \n", i, bufferEmployee->id, bufferEmployee->nombre, bufferEmployee->horasTrabajadas, bufferEmployee->sueldo);
			}
			retorno = 0;
		}
	}
	else
	{
		printf("Error, deberá cargar un archivo antes de agregar más empleados. Favor volver a intentar\n");
	}
	return retorno;
}
/** \brief Listar empleado por indice
 *	Hace las validaciones y llama a ll_ger para obtener los datos del empleado en ese índice.
 *
 * \param pArrayListEmployee LinkedList*  | int index
 * \return int -1 si hubo error | 0 si todo ok
 *
 */
int printByIndex(LinkedList* pArrayListEmployee, int index)
{
	int retorno = -1;
	Employee* bufferEmployee;

	if (pArrayListEmployee != NULL && index > -1 && ll_len(pArrayListEmployee) > -1 && index <= ll_len(pArrayListEmployee) && (Employee*)ll_get(pArrayListEmployee,index) != NULL)
	{
		bufferEmployee = (Employee*)ll_get(pArrayListEmployee,index);
		printf("==============      Nombre: %s | Horas trabajadas: %d | Sueldo: %d |      ==============  \n:", bufferEmployee->nombre, bufferEmployee->horasTrabajadas, bufferEmployee->sueldo);
		retorno = 0;
	}
	return retorno;
}
/** \brief Ordenar empleados
 *	Usa ll_isEmpty como flag para verificar que se hayan cargado los datos de algún archivo. Luego utilizando el ll_sort,
 *		pasandole la función criterio auxiliar creada, se imprimen todos los empleados para facilitar
 *		revisión del ordenamiento.
 *
 * \param pArrayListEmployee LinkedList*
 * \return int -1 si hay errores | 0 si todo ok
 *
 */
int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	if (ll_isEmpty(pArrayListEmployee)==0)
	{
		if (ll_sort(pArrayListEmployee, employee_funcionCriterio, 0) != -1)
		{
			controller_ListEmployee(pArrayListEmployee);
			retorno = 0;
		}
	}
	else
	{
		printf("Error, deberá cargar un archivo antes de agregar más empleados. Favor volver a intentar\n");
	}
	return retorno;
}

/////////////////////////        G  U  A  R  D  A  R     ////////////////////////////////////////////////////

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *	Usa el ll_empty como bandera para asegurarse que hayan datos cargados para guardar, hace validaciones
 *	y abre el archivo en modo escritura, lo parsea y luego cierra el archivo.
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int -1 si parametros son NULL, - 2 si no puede abrir el archivo y 0 si todo ok
 *
 */
int controller_saveAsText(char* path , LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	FILE *pFile;

	if (ll_isEmpty(pArrayListEmployee)==0)
	{
		if (path != NULL && pArrayListEmployee != NULL)
		{
			pFile = fopen(path, "w");
			if (pFile != NULL)
			{
				parser_EmployeeToText(pFile, pArrayListEmployee);
				fclose(pFile);
				retorno = 0;
			} else
			{
				retorno = -2;
			}
		}
	}
	else
	{
		printf("Error, deberá cargar un archivo antes de agregar más empleados. Favor volver a intentar\n");
	}
	return retorno;
}
/** \brief Guarda los datos de los empleados en el archivo data.bin (modo binario).
 * Usa el ll_empty como bandera para asegurarse que hayan datos cargados para guardar, hace validaciones
 *	y abre el archivo en modo escritura, lo parsea y luego cierra el archivo.
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int -1 si hay errores | 0 si todo ok
 *
 */
int controller_saveAsBinary(char* path , LinkedList* pArrayListEmployee)
{
	FILE *pFile;
	int retorno = -1;
	int len = ll_len(pArrayListEmployee);
	Employee *pEmpleado;

	if (ll_isEmpty(pArrayListEmployee)==0)
	{
		if (path != NULL && pArrayListEmployee != NULL)
		{
			pFile = fopen (path, "wb");
			if (pFile != NULL)
			{
				for (int i = 0; i< len; i++)
				{
					pEmpleado = ll_get(pArrayListEmployee, i);
					fwrite (pEmpleado, sizeof(Employee),1, pFile);
				}
			}
		}
		retorno = 0;
		fclose (pFile);
	}
	else
	{
		printf("Error, deberá cargar un archivo antes de agregar más empleados. Favor volver a intentar\n");
	}
	return retorno;
}
/** \brief Listar empleado por id, devolviendo el indice
 *	Itera hasta encontrar el empleado solicitado por id, devolviendo el índice dentro de la LL
 *	en el que se encuentra
 *
 * \param pArrayListEmployee LinkedList*  |    int id
 * \return int -1 si hubo error | >-1 el indice
 *
 */
int findEmployeeById(LinkedList* pArrayListEmployee, int id)
{
	int retorno = -1;
	int len;
	Employee* bufferEmployee;
	if (pArrayListEmployee != NULL && id > -1 && ll_len(pArrayListEmployee) > -1)
	{
		len = ll_len(pArrayListEmployee);
		for (int i = 0; i < len; i++)
		{
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
/** \brief Hardcodeo - auxiliar interno para armado de programa
 *
 */
int controller_hardCode(LinkedList* pArrayListEmployee, char* name, char* horasTrabajadas, char* sueldo )
{
	int output = -1;
	char id[LONG_NOMBRE] ;
	Employee* bufferEmpleado;
	{
		sprintf(id, "%d", controller_generarIdNuevo(pArrayListEmployee));
		bufferEmpleado = employee_newParametros(id, name, horasTrabajadas, sueldo);
		ll_add(pArrayListEmployee, bufferEmpleado);
	}
    return output;
}
