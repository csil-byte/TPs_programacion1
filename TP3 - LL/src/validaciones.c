/*
 * validaciones.c
 *
 *  Created on: 6 nov. 2020
 *      Author: user
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "validaciones.h"

#define TRUE 1
#define FALSE 0

/** \brief Permite validar si la cadena recibida es un nombre valido
 *
 * \param char* string | int len - longitud de la cadena
 * \return falso - 0 no es un número | 1 - es un núumero, verdadero | - 1 error
 *
 */
int isValidName(char* name, int len)
{
    int retorno = -1;
    if(name!= NULL)
    {
        retorno = TRUE;
        for(int i=0; name[i]!= '\0' && i < len; i++)
        {
            if((name[i] < 'a' || name [i] > 'z') && (name[i] < 'A' || name[i] > 'Z')
            	&& (name[i] != ' ') && (name[i] != '-' || name[0] == '-'))
            {
                retorno = FALSE;
                break;
            }
        }
    }
    return retorno;
}
/**
 * \brief Permite validar si la cadena númerica recibida es un número válido, permite números negativos y positivos
 * \param char *num, int len - longitud de la cadena
 * \return falso - 0 no es un número | 1 - es un núumero, verdadero | - 1 error
 */
int isValidNumber(char* numero, int len)
{
    int retorno = -1;
    int i = 0;

    if(numero!= NULL && len > 0)
    {
        retorno = TRUE;
        if(numero[0] == '-' || numero[0] == '+')
        {
            i = 1;
        }
        for( ; numero[i]!= '\0' && i < len; i++)
        {
            if(numero[i] < '0' || numero[i] > '9')
            {
                retorno = FALSE;
                break;
            }
        }
    }
    return retorno;
}
