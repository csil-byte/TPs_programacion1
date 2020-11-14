/*
 * parser.h
 *
 *  Created on: 2 nov. 2020
 *      Author: user
 */

#ifndef PARSER_H_
#define PARSER_H_
#define LONG_TXT 128

int parser_EmployeeFromText(FILE* pFile , LinkedList* pArrayListEmployee);
int parser_EmployeeFromBinary(FILE* pFile , LinkedList* pArrayListEmployee);
int parser_EmployeeToText(FILE* pFile , LinkedList* pArrayListEmployee);



#endif /* PARSER_H_ */
