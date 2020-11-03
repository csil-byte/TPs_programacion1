
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "utn.h"
#include "Employee.h"


/////////////////////////////////////        GETTERS & SETTERS                //////////////////////////////////////


int employee_setId(Employee* this,int id)
{
int retorno = -1;
//static int maximoId = -1;

	if (this != NULL)
	{
		//id= cliente_generarIdNuevo();
		//printf("ID - employee setId: %d \n", id);
		this->id = id;
		//printf("ID - employee setId: %d \n", this->id);
		retorno = 0;
	}
	return retorno;
}
int cliente_getIdTxt (Employee* this, char* id)
{
	int retorno = -1;
	if (this != NULL  && id != NULL)
	{
		retorno = 0;
		sprintf(id, "%d", this->id);
	}
	return retorno;
}
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

int employee_setNombre(Employee* this,char* nombre)
{
	int retorno = -1;
	if (this != NULL && nombre != NULL && esUnNombreValido(nombre, LONG_NOMBRE))
		{
			retorno = 0;
			strcpy(this->nombre, nombre);
		}
		return retorno;
}
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

int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas)
{
	int retorno = -1;
	if (this!= NULL && horasTrabajadas > -1 )
			//&& esNumerica(horasTrabajadas, 1000))
	{
		retorno = 0;
		this->horasTrabajadas = horasTrabajadas;
	}
	return retorno;
}
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

int employee_setSueldo(Employee* this,int sueldo)
{
	int retorno = -1;
		if (this!= NULL && sueldo > -1 )
				//&& esNumerica(*sueldo, 1000))
		{
			retorno = 0;
			this->sueldo = sueldo;
		}
		return retorno;
}
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

int esNombreValido(char* cadena,int limite)
{
	int respuesta = 1; // TODO OK

	for(int i=0; i<=limite && cadena[i] != '\0';i++)
	{
		if(	(cadena[i] < 'A' || cadena[i] > 'Z') &&
			(cadena[i] < 'a' || cadena[i] > 'z') &&
			cadena[i] != '.')
		{
			respuesta = 0;
			break;
		}
	}
	return respuesta;
}
int esNumero(int* pResultado, int limite)
{
	int retorno= -1;
		char buffer[50];
		if(pResultado != NULL &&
				myGets(buffer, sizeof(buffer))==0 &&
				esNumerica(buffer, sizeof(buffer))==1)
		{
			retorno=0;
			*pResultado=atoi(buffer);
		}
		return retorno;
}
/////////////////////////////////////        C O N S T R U C T O R E S                //////////////////////////////////////
Employee* employee_new(void)
{
	return (Employee*) malloc (sizeof(Employee));
}
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
			//printf("idStr: %s \n, ",idStr); empty
			//printf("idStr: %s \n, ",this->id); NULL
			//printf("idStr: %d,\n", (int)idStr); direccion memoria
			//printf("NewPARAMENTROS: - idStr: %d \n, ",this->id);          WORKS
			//printf("NewPARAMENTROS: - Sueldo: %d \n, ",this->sueldo);     WORKS
			//printf("%s, ", nombreStr);
			//printf("%s ", horasTrabajadasStr);
			//printf("%s ", sueldoStr);
		return this;
		}
	}
	return NULL;
}
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

	if (employee_getSueldo(e1, &sueldo1) == 0 &&
		employee_getSueldo (e2, &sueldo2) == 0 &&
		employee_getId (e1, &id1) == 0 &&
		employee_getId (e2, &id2) == 0)
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


/////////////////////////////////////       FINDERS               //////////////////////////////////////

