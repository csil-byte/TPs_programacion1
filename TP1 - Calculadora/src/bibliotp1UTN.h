/*
 * bibliotp1.UTN
 *
 *  Created on: Sep 8, 2020
 *      Author: Mauro
 */

#ifndef UTN_H_
#define UTN_H_

int utn_getNumero(char* mensaje, char* mensajeError, int* pResultado,int reintentos,int maximo,int minimo);
int getInt (int* pResultado);
int esNumerica(char* cadena, int limite);
int myGets(char* cadena, int longitud);

int getChar(char* mensaje, char* mensajeError, char* pResultado,int reintentos);
int utn_getNumeroFloat(float* pResultado,char* mensaje,char* mensajeError,float minimo,float maximo,int reintentos);
int getFloat(float* pFloat);
int esFlotante(char* array,int limite);


#endif /* UTN_H_ */
