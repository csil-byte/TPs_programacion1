#include "bibliotp1UTN.h"
#include <stdio.h>
#include <stdlib.h>

/*
 ============================================================================
 Name        : getInt

Pide un interger al usuario, valida que los argumentos no sean NULL y
que el usuario  haya pasado más de 0 reintentos, si es exitoso, la función
retorna 0, en caso contrario retornará -1.
 ============================================================================
*/
int getInt(char* mensaje, char* mensajeError, int* pResultado,int reintentos)
{
	int retorno = -1;
	int bufferInt;
	int resultadoScanf;
	if(mensaje != NULL && mensajeError != NULL && pResultado != NULL && reintentos >= 0)
	{
		do
		{
			printf("%s",mensaje);
			fflush(stdin);
			resultadoScanf = scanf("%d" , &bufferInt);
			if(resultadoScanf == 1)
			{
				retorno = 0;
				*pResultado = bufferInt;
				break;
			}
			else
			{
				printf("%s",mensajeError);
				reintentos--;
			}
		}while(reintentos >= 0);

		if (retorno == -1)
		{
			printf("Se quedó sin reintentos :( .\n");
		}
	}

return retorno;
}
/*
 ============================================================================
 Name        : getChar

Pide un caracter al usuario, valida que los argumentos no sean NULL y
que el usuario  haya pasado más de 0 reintentos, si es exitoso, la función
retorna 0, en caso contrario retornará -1.
 ============================================================================
*/
int getChar(char* mensaje, char* mensajeError, char* pResultado,int reintentos)

{
	int retorno = -1;
	char bufferChar;
	int resultadoScanf;
	if(		mensaje != NULL &&
			mensajeError != NULL &&
			pResultado != NULL &&
			reintentos >= 0)
	{
		do
		{
			printf("%s",mensaje);
			fflush(stdin);
			resultadoScanf = scanf(" %c" , &bufferChar);
			if(resultadoScanf == 1)
			{
				retorno = 0;
				*pResultado = bufferChar;
				break;
			}
			else
			{
				printf("%s",mensajeError);
				reintentos--;
			}
		}while(reintentos >= 0);
	}
	return retorno;
}
/*
 ============================================================================
 Name        : sumar

Valida que resultado no sea NULL, en ese caso procede a hacer la operación de 2 int,
la función retornará 0 & se guardará en *resultado la suma.
Caso contrario, retornará -1.
 ============================================================================
*/
int sumar (int* operador1, int* operador2, float* resultado)
{
	int resultadoSuma = -1;

	if (resultado != NULL)
	{
	(*resultado) = *operador1 + (float) *operador2;
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
int restar (int* operador1, int* operador2, float* resultado)
{
	int resultadoResta = -1;

	if (resultado != NULL)
	{
	(*resultado) = *operador1 - (float) *operador2;
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
int multiplicar (int* operador1, int* operador2, float* resultado)
{
	int errorMultiplicacion = -1;

	if (resultado != NULL)
	{
	(*resultado) = *operador1 * (float) *operador2;
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
int dividir (int* operador1, int* operador2, float* resultado )
{
	int errorDivision= -1;

	if (resultado != NULL)
	{
	if (*operador2 != 0) {
		(*resultado) = *operador1 / (float) *operador2;
		printf("El resultado de %d dividido por %d es:  %.2f \n",*operador1, *operador2, *resultado);
		errorDivision = 0;
	}
	else {
		printf("Error, no se puede dividir por 0\n");
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
int factorizar (int* operador1, float* resultado)
{
	int errorFactorizar = -1;
	*resultado = 1;

	if (resultado != NULL && *operador1 >= 0)
	{
	for (int i= 1; i <= *operador1; i++)
	{
		*resultado = *resultado * i;
	}
	errorFactorizar = 0;
	}
	else
	{
		printf("Error, no se puede calcular un número negativo\n");
	}

	return errorFactorizar;
}
/*
 ============================================================================
 Name        : menuCalculadora

Retorno está en -1 como default que se irá modificando de acuerdo si entra o no en los debidos casos.
Usamos una variable auxiliar para guardar los resultados de las cuentas en caso de elegir hacer operaciones.
Es un menú específico para calculadora, había hecho para el caso C que directamente recibiera a una función de cálculos que
incluyera el 2do switch en su propia función pero me pareció que hacía que el código y el pasaje de argumentos quedara muy
ilegible y me pareció mejor así.
 ============================================================================
*/
int menuCalculadora (int reintentos, char* menu, char* operador, int* numero1, int* numero2, float* resultadoCalculo)
{
	int retorno = -1;
	float resultadoCalculoFinal = *resultadoCalculo;

	while(reintentos >= 0)
	{
		if (getChar("\nIngresar una opción\n: \n A- Salir \n B - Realizar Operación", "Error, ingresar una opción válida\n", menu,2) == 0)
		{
		fflush(stdin);

		switch (*menu)
		{
		case 'A':
			printf("El programa ha finalizado");
			exit(0);
			retorno = 0;
			break;
		case 'B':
			getChar("Ingresar una opción: \n +: Suma \n - : Resta \n / : División \n * Multiplicación\n ! : Factorizar \n ", "Error, ingresar una opción válida\n", menu,2);
			switch(*menu)
			{
			case '+':
				sumar (numero1, numero2, &resultadoCalculoFinal);
				printf("La suma de %d más %d es:  %.2f\n", (int)*numero1, (int)*numero2, resultadoCalculoFinal);
				retorno = 0;
				break;
			case '/':
				if ((dividir (numero1, numero2, &resultadoCalculoFinal)) == 0)
				{
					retorno = 0;
				}
				else
				{
					retorno = -1;
				}

				break;
			case '*':
				multiplicar (numero1, numero2, &resultadoCalculoFinal);
				printf("La multiplicación de %d por %d es: %.2f\n", (int)*numero1, (int)*numero2, resultadoCalculoFinal);
				retorno = 0;
				break;
			case '-':
				restar (numero1, numero2, &resultadoCalculoFinal);
				printf("La resta de %d - %d es:  %.2f\n", (int)*numero1, (int)*numero2,  resultadoCalculoFinal);
				retorno = 0;
				break;
			case '!':
				if (factorizar (numero1, &resultadoCalculoFinal) == 0)
				{
				printf("El factorial de %d es %1.f\n", (int)*numero1, resultadoCalculoFinal);
				retorno = 0;
				}
				if (factorizar (numero2, &resultadoCalculoFinal) == 0)
				{
				printf("El factorial de %d es %1.f\n", (int)*numero2, resultadoCalculoFinal);
				retorno = 0;
				}
				break;
			}
			break;
		}

		if (retorno == 0)
		{
			break;
		}
		if (retorno != 0 && *menu != '/')
		{
			printf("Error, ingresar un número válido\n");
			reintentos--;
		}
		}

	if (retorno == -1 && *menu != '/')
	{
		printf("Se quedó sin intentos :( \n");
	}
	}

	return retorno;

}
