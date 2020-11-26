/*
 * calculadora.h
 *
 *  Created on: 2 oct. 2020
 *      Author: user
 */

#ifndef CALCULADORA_H_
#define CALCULADORA_H_

#include <stdio.h>
#include <stdlib.h>


int sumar (float* operador1, float* operador2, float* resultado);
int restar (float* operador1, float* operador2, float* resultado);
int multiplicar (float* operador1, float* operador2, float* resultado);
int dividir (float* operador1, float* operador2, float* resultado );
int factorial (float* operador1, float* resultado1);
int calcular_operaciones (float* numero1, float* numero2, float* r_Suma, float* r_Resta, float* r_Multiplicacion, float* r_Division, float* r_Factor1, float* r_Factor2);
int mostrar_resultados (float* numero1, float* numero2, float* r_Suma, float* r_Resta, float* r_Multiplicacion, float* r_Division, float* r_Factor1, float* r_Factor2);


#endif /* CALCULADORA_H_ */
