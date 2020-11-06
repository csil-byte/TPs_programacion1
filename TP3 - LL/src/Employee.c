
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "utn.h"
#include "validaciones.h"
#include "Employee.h"

/////////////////////////////////////        GETTERS & SETTERS                //////////////////////////////////////

/** \brief Permite asignar un valor validado al campo Id de la entidad.
 *
 * \param int id
 * \param Employee* this
 * \return int  --------- devuelve -1 cuando hay error |  0 cuando está todo ok
 *
 */
int employee_setId(Employee* this,int id)
{
int retorno = -1;
	if (this != NULL)
	{
		this->id = id;
		retorno = 0;
	}
	return retorno;
}
/** \brief Permite acceder a un campo de la entidad.
 * Hecho para recibir al ID como char, función auxiliar.
 *
 * \param char id
 * \param Employee* this
 * \return int  --------- devuelve -1 cuando hay error |  0 cuando está todo ok
 *
 */
int employee_getIdTxt (Employee* this, char* id)
{
	int retorno = -1;
	if (this != NULL  && id != NULL)
	{
		retorno = 0;
		sprintf(id, "%d", this->id);
	}
	return retorno;
}
/** \brief Permite acceder a un campo de la entidad.
 * Hecho para recibir al ID como char, función auxiliar.
 *
 * \param int id
 * \param Employee* this
 * \return int  --------- devuelve -1 cuando hay error |  0 cuando está todo ok
 *
 */
int employee_getId(Employee* this,int* id)
{
		int retorno = -1;
		if (this != NULL && id != NULL)
		{
			retorno = 0;
			*id = this->id;
		}
		return retorno;
}
/** \brief Permite asignar un valor validado al campo nombre de la entidad.
 *
 * \param int id
 * \param Employee* this
 * \return int  --------- devuelve -1 cuando hay error |  0 cuando está todo ok
 *
 */
int employee_setNombre(Employee* this,char* nombre)
{
	int retorno = -1;
	if (this != NULL && nombre != NULL && isValidName(nombre, LONG_NOMBRE))
		{
			retorno = 0;
			strcpy(this->nombre, nombre);
		}
		return retorno;
}
/** \brief Permite acceder a un campo de la entidad.
 *
 * \param char nombre
 * \param Employee* this
 * \return int  --------- devuelve -1 cuando hay error |  0 cuando está todo ok
 *
 */
int employee_getNombre(Employee* this,char* nombre)
{
	int retorno = -1;
		if (this != NULL && nombre != NULL)
		{
			retorno = 0;
			strcpy (nombre, this->nombre);
		}
		return retorno;
}
/** \brief Permite asignar un valor validado al campo horas trabajadas de la entidad.
 *
 * \param int horasTrabajadas
 * \param Employee* this
 * \return int  --------- devuelve -1 cuando hay error |  0 cuando está todo ok
 *
 */
int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas)
{
	int retorno = -1;
	if (this!= NULL && horasTrabajadas > -1 )
	{
		retorno = 0;
		this->horasTrabajadas = horasTrabajadas;
	}
	return retorno;
}
/** \brief Permite acceder a un campo de la entidad.
 *
 * \param int horasTrabajadas
 * \param Employee* this
 * \return int  --------- devuelve -1 cuando hay error |  0 cuando está todo ok
 *
 */
int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas)
{
	int retorno = -1;
	if (this != NULL && horasTrabajadas != NULL)
	{
		retorno = 0;
		*horasTrabajadas = this->horasTrabajadas;
	}
	return retorno;
}
/** \brief Permite asignar un valor validado al campo sueldo de la entidad.
 *
 * \param int sueldo
 * \param Employee* this
 * \return int  --------- devuelve -1 cuando hay error |  0 cuando está todo ok
 *
 */
int employee_setSueldo(Employee* this,int sueldo)
{
	int retorno = -1;
		if (this!= NULL && sueldo > -1 )
		{
			retorno = 0;
			this->sueldo = sueldo;
		}
		return retorno;
}
/** \brief Permite acceder a un campo de la entidad.
 *
 * \param int sueldo
 * \param Employee* this
 * \return int  --------- devuelve -1 cuando hay error |  0 cuando está todo ok
 *
 */
int employee_getSueldo(Employee* this,int* sueldo)
{
	int retorno = -1;
	if (this != NULL && sueldo != NULL)
	{
		retorno = 0;
		*sueldo = this->sueldo;
	}
	return retorno;
}

/////////////////////////////////////      AUXILIARES   CONSTRUCTORES     //////////////////////////////////////

/** \brief Permite reservar memoria dinámica para un elemento de la entidad
 *
 * \param  | no recibe |
 * \return puntero de la entidad construida -> Employee*
 *
 */
Employee* employee_new(void)
{
	return (Employee*) malloc (sizeof(Employee));
}
/** \brief Permite darle valores a los campos de la entidad utilizando los setters para acceder de forma segura
 *
 * \param recibe todos los campo de la entidad char | nombre, id, sueldo, horastrabajadas
 * \return int  --------- devuelve puntero a la entidad Employee |  NULL cuando hay error.
 *
 */
Employee* employee_newParametros(char* idStr,char* nombreStr,char* horasTrabajadasStr, char* sueldoStr)
{
	Employee* this = NULL;
	this = employee_new();

	if (this != NULL)
	{
		if (!employee_setId(this, atoi(idStr)) &&
			!employee_setNombre (this, nombreStr) &&
			!employee_setHorasTrabajadas (this, atoi(horasTrabajadasStr)) &&
			!employee_setSueldo (this, atoi(sueldoStr)))
		{
		return this;
		}
	}
	return NULL;
}

/////////////////////////////////////////   AUXILIARES      //////////////////////////////////////////////

/** \brief Genera opciones de menu y guarda la elegida en la variable pasada por referencia
 *
 * \param int* menu
 * \return int  --------- devuelve -1 cuando hay error |  0 cuando está todo ok
 *
 */
int getMenuCarga(int* menu)
{
	int retorno = -1;
	int bufferMenu;
	if (menu != NULL && utn_getNumero("\n1- Cargar datos -modo texto-\n2- Cargar datos -modo binario"
			"-\n3- Agregar un empleado\n4- Modificar un empleado\n5- Eliminar a un empleado"
			"\n6- Listar todos los empleados\n7- Ordenar empleados por sueldo\n8- Guardar los datos  -modo texto-\n9- Guardar los datos -modo binario-\n10- Salir\n", "\nError\n", &bufferMenu, 2, 10, 1) == 0)
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
/** \brief Función criterio auxialiar a LL_sort. En este caso ordena por sueldo ascendente y luego en caso de
 * haber sueldos de igual valor, ordena por id.
 *
 * \param void* item1 | item2  <- los elementos que se ordenaran
 * \return int  --------- devuelve -1 cuando hay error |  0 cuando está todo ok
 *
 */
int employee_funcionCriterio (void* item1, void* item2)
{
	int retorno = -1;
	Employee* e1;
	Employee* e2;
	int sueldo1;
	int sueldo2;
	int id1;
	int id2;

	e1 = (Employee*) item1;
	e2 = (Employee*) item2;

	if (employee_getSueldo(e1, &sueldo1) == 0 && employee_getSueldo (e2, &sueldo2) == 0 &&
		employee_getId (e1, &id1) == 0 && employee_getId (e2, &id2) == 0)
	{
		if (sueldo1 > sueldo2)
		{
			retorno = 0;
		}
		else if(sueldo1 == sueldo2)
		{
			if (id1 < id2)
			{
				retorno = 0;
			}
		}

	}
	return retorno;
}


