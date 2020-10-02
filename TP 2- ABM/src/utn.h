/*
 * utn.h
 *
 *  Created on: Sep 8, 2020
 *      Author: Mauro
 */

#ifndef UTN_H_
#define UTN_H_

#define LIMITE_BUFFER_STRING 4096

int utn_getNumero(char* mensaje, char* mensajeError, int* pResultado,int reintentos,int maximo,int minimo);
int getInt (int* pResultado);
int esNumerica(char* cadena, int limite);
int myGets(char* cadena, int longitud);
int esUnNombreValido(char* cadena,int limite);
int utn_getNombre(char* mensaje, char* mensajeError, char* pResultado,int reintentos, int limite);
int utn_getNumeroFloat(float* pResultado,char* mensaje,char* mensajeError,float minimo,float maximo,int reintentos);
int utn_getNickName(char* mensaje, char* mensajeError, char* pResultado,int reintentos, int limite);
int utn_getNumeroFloat(float* pResultado,char* mensaje,char* mensajeError,float minimo,float maximo,int reintentos);
int getFloat(float* pFloat);
int esFlotante(char* array,int limite);

#endif /* UTN_H_ */
