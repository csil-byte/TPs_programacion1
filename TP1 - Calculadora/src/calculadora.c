/*
 * calculadora.c
 *
 *  Created on: 2 oct. 2020
 *      Author: user
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "calculadora.h"
#include "bibliotp1UTN.h"

#define MAX INT_MAX
#define MIN INT_MIN


/*
 ============================================================================
 Name        : sumar

Valida que resultado no sea NULL, en ese caso procede a hacer la operación de 2 int,
la función retornará 0 & se guardará en *resultado la suma.
Caso contrario, retornará -1.
 ============================================================================
*/
int sumar (float* operador1, float* operador2, float* resultado)
{
	int resultadoSuma = -1;

	if (resultado != NULL)
	{
	(*resultado) = *operador1 + ( *operador2);
	resultadoSuma = 0;
	}

	return resultadoSuma;
}
/*
 ============================================================================
 Name        : restar

Valida que resultado no sea NULL, en ese caso procede a hacer la operación de 2 int,
la función retornará 0 & se guardará en *resultado la resta.
Caso contrario, retornará -1.
 ============================================================================
*/
int restar (float* operador1, float* operador2, float* resultado)
{
	int resultadoResta = -1;

	if (resultado != NULL)
	{
	(*resultado) = *operador1 - ( *operador2);
	resultadoResta = 0;
	}

	return resultadoResta;
}
/*
 ============================================================================
 Name        : multiplicar

Valida que resultado no sea NULL, en ese caso procede a hacer la operación de 2 int,
la función retornará 0 & se guardará en *resultado la multiplicación.
Caso contrario, retornará -1.
 ============================================================================
*/
int multiplicar (float* operador1, float* operador2, float* resultado)
{
	int errorMultiplicacion = -1;

	if (resultado != NULL)
	{
	(*resultado) = *operador1 * (*operador2);
	errorMultiplicacion = 0;
	}

	return errorMultiplicacion;
}
/*
 ============================================================================
 Name        : dividir

Valida que resultado no sea NULL, en ese caso procede mediante un if a validar
que el 2do operador sea mayor a 0, sí lo es, hace la operación de 2 int,
la función retornará 0 & se guardará en *resultado la división.
Caso contrario, retornará -1 e imprimirá un mensaje de error al usuario.
 ============================================================================
*/
int dividir (float* operador1, float* operador2, float* resultado )
{
	int errorDivision= -1;

	if (resultado != NULL && operador1 != NULL && operador2 != NULL)
	{
		if (*operador2 != 0) {
			(*resultado) = *operador1 / *operador2;
			errorDivision = 0;
		}
		else {
			errorDivision = -1; }
	}

	return errorDivision;
}
/*
 ============================================================================
 Name        : factorizar

Valida que resultado no sea NULL, en ese caso procede a factorizar el número
brindado por el usuario, retorna 0 & se guarda en *resultado el valor correcto.
Caso contrario, retornará -1.
 ============================================================================
*/
int factorial (float* operador1, float* resultado)
{
	int errorFactorizar = -1;
	*resultado = 1;

	if (resultado != NULL && *operador1 >= 0)
	{
		for (int i= 1; i <= *operador1; i++)
		{
			*resultado = *resultado * i;
			errorFactorizar = 0;
		}
		if (*resultado > INT_MAX)
		{
			errorFactorizar = -2;
		}
	}
	else
	{
		errorFactorizar = -1;
	}
	return errorFactorizar;
}
int calcular_operaciones (float* numero1, float* numero2, float* r_Suma, float* r_Resta, float* r_Multiplicacion, float* r_Division, float* r_Factor1, float* r_Factor2)
{
	int retorno= 1;

	if (numero1 != NULL && numero2 != NULL)
	{
		sumar (numero1, numero2, r_Suma);
		multiplicar (numero1, numero2, r_Multiplicacion);
		restar (numero1, numero2, r_Resta);
		dividir (numero1, numero2, r_Division);
	    factorial (numero1, r_Factor1);
        factorial (numero2, r_Factor2);
        retorno = 0;
	}
	return retorno;
}
int mostrar_resultados (float* numero1, float* numero2, float* r_Suma, float* r_Resta, float* r_Multiplicacion, float* r_Division, float* r_Factor1, float* r_Factor2)
{
	int retorno = -1;
	if (numero1 != NULL && numero2 != NULL)
	{
		printf("[SUMA] %.2f+%.2f es: ---- %.2f \n", *numero1, *numero2, *r_Suma);
		printf("[MULTI] %.2f*%.2f es: ---- %.2f \n", *numero1, *numero2,*r_Multiplicacion);
		printf("[RESTA] %.2f-%.2f es: ---- %.2f \n", *numero1, *numero2,*r_Resta);

		if (*numero2 != 0)
		{
			printf("[DIVISION] %.2f/%.2f es: ---- %.2f \n", *numero1, *numero2,*r_Division);
		}
		else
		{
			printf("[DIVISION] No se puede dividir por 0.\n");
		}
		if(*numero1 > -1 && *r_Factor1 < INT_MAX  )
		{
			printf("[FACTOR X] %.2f! es: ---- %.2f \n", *numero1,*r_Factor1);
		}
		else if (*r_Factor1 > INT_MAX )
		{
			printf("[FACTORIAL X] No se pueden imprimir números tan grandes por limitaciones del sistema.\n");
		}
		else
		{
			printf("[FACTORIAL X] No se pueden factorizar números negativos.\n");
		}
		if(*numero2 > -1 && *r_Factor2 < INT_MAX  )
		{
			printf("[FACTORIAL Y] %.2f! es: ---- %.2f \n", *numero2,*r_Factor2);
		}
		else if (*r_Factor2 > INT_MAX )
		{
			printf("[FACTORIAL Y] No se pueden imprimir números tan grandes por limitaciones del sistema.\n");
		}
		else
		{
			printf("[FACTORIAL Y] No se pueden factorizar números negativos.\n");
		}
		retorno = 0;
	}

	return retorno;
}
