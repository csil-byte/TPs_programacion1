/*
 ============================================================================
 Name        : TP 1 - Armar una calculadora
 Author      : Cecilia Silva 1H, 95348591
 Version     : 10000.5
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "bibliotp1UTN.h"


int main(void)
{
setbuf (stdout, NULL);

int numero1;
char operador;
int numero2;
char menu;
float resultadoCalculo;


if((getInt("Ingresar un n�mero: \n", "N�mero inv�lido \n ", &numero1, 2) == 0) && (getInt("Ingresar otro n�mero:\n ", "N�mero inv�lido. \n ", &numero2, 2)) == 0)
{
	menuCalculadora (2, &menu, &operador, &numero1, &numero2, &resultadoCalculo);
}
}



