/*
 ============================================================================
 Name        : TP 1 - Armar una calculadora
 Author      : Cecilia Silva 1H, 95348591
 Version     : 10000.5
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "bibliotp1UTN.h"
#include "calculadora.h"

#define MAX INT_MAX
#define MIN INT_MIN


int main(void)
{
	setbuf (stdout, NULL);
	float numero1 ;
	float numero2 ;
	float r_Suma ;
	float r_Resta;
	float r_Multiplicacion;
	float r_Division;
	float r_Factor1;
	float r_Factor2;
	int menu;

	do{
		if (utn_getNumero("\nIngresar una opción\n1- Ingresar 1er operando (A=x)\n2- Ingresar 2do operando (B=y)\n3- Calcular todas las operaciones\n4- Informar resultados\n5- Salir\n", "Error. Ingresar un número válido\n ", &menu, 2, MAX, MIN) == 0)
		{
			switch (menu)
			{
			case 1:
				if (utn_getNumeroFloat( &numero1,"Ingresar un número:\n", "Error. Ingresar un número válido\n ", INT_MIN ,INT_MAX,  2) == 0)
				{
					printf("Valor de X es: %.2f\n", numero1);
				}
				break;
			case 2:
				if (utn_getNumeroFloat( &numero2,"Ingresar un número:\n", "Error. Ingresar un número válido\n ",INT_MIN ,INT_MAX,  2) == 0)
					{
						printf("Valor de Y es: %.2f\n", numero2);
					}
				break;
			case 3:
				if (!calcular_operaciones (&numero1, &numero2, &r_Suma, &r_Resta, &r_Multiplicacion, &r_Division, &r_Factor1, &r_Factor2))
				{
					printf("========Operaciones calculadas con éxito=============\n");
				}
				else
				{
					printf("========Hubo un error, favor volver a intentar=============\n");
				}
				break;
			case 4:
				if (!mostrar_resultados (&numero1, &numero2, &r_Suma, &r_Resta, &r_Multiplicacion, &r_Division, &r_Factor1, &r_Factor2))
				{
					printf("\n========Resultados devueltos con éxito=============\n");
				}
				else
				{
					printf("========Hubo un error, favor volver a intentar=============\n");
				}
				break;
			case 5:
				break;
			}
		}
	}while (menu != 5);

}

