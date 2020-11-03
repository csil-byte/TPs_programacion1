#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Employee.h"

/****************************************************
    Menu:
     1. X Cargar los datos de los empleados desde el archivo data.csv (modo texto).
     2.   Cargar los datos de los empleados desde el archivo data.csv (modo binario).
     3. X Alta de empleado
     4. X Modificar datos de empleado
     5. X Baja de empleado
     6. X Listar empleados
     7. X Ordenar empleados -------- sueldo ascendente, si son =, id menor a mayor
     8.   Guardar los datos de los empleados en el archivo data.csv (modo texto).
     9.   Guardar los datos de los empleados en el archivo data.csv (modo binario).
    10.   Salir
*****************************************************/



int main()
{
	setbuf(stdout, NULL);
    int option = 0;

    LinkedList* listaEmpleados = ll_newLinkedList();

   //controller_addEmployee(listaEmpleados);

    /*


    printAllEmployees(listaEmpleados);
    controller_sort (listaEmpleados);
    //controller_addEmployee(listaEmpleados);
    //controller_addEmployee(listaEmpleados);
    //printByIndex(listaEmpleados, 0);
   // printByIndex(listaEmpleados, 1);
   // printByIndex(listaEmpleados, 2);
   // printByIndex(listaEmpleados, 3);
    controller_hardCode(listaEmpleados, "Laura", "5", "500" );
    	controller_hardCode(listaEmpleados, "Luciana", "3", "200" );
        controller_hardCode(listaEmpleados, "Marilu", "8", "1500" );
        controller_hardCode(listaEmpleados, "Martin", "4", "800" );
// printAllEmployees(listaEmpleados);
        printByIndex(listaEmpleados, 0);
        printByIndex(listaEmpleados, 1);
        printByIndex(listaEmpleados, 2);
        printByIndex(listaEmpleados, 3);
        //controller_sort (listaEmpleados);


*/

    	//controller_loadFromText("data.csv",listaEmpleados);
    	controller_loadFromBinary("data.csv",listaEmpleados);
    //	printAllEmployees(listaEmpleados);

    	controller_hardCode(listaEmpleados, "Luciana", "3", "200" );
    	printByIndex(listaEmpleados, 1);

    do{
        switch(option)
        {
            case 1:
                //controller_loadFromText("data.csv",listaEmpleados);
                //printAllEmployees(listaEmpleados);
                break;
        }
    }while(option != 10);
    return 0;
}

