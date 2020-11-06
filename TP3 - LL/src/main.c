#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Employee.h"

/****************************************************
    Menu:
     1. X Cargar los datos de los empleados desde el archivo data.csv (modo texto).
     2. X Cargar los datos de los empleados desde el archivo data.csv (modo binario).
     3. X Alta de empleado
     4. X Modificar datos de empleado
     5. X Baja de empleado
     6. X Listar empleados
     7. X Ordenar empleados -------- sueldo ascendente, si son =, id menor a mayor
     8. X Guardar los datos de los empleados en el archivo data.csv (modo texto).
     9. X Guardar los datos de los empleados en el archivo data.csv (modo binario).
    10. X Salir
*****************************************************/

int main()
{
	setbuf(stdout, NULL);
    int option;
    int flagCarga = 0;

    LinkedList* listaEmpleados = ll_newLinkedList();

    printf("==================================Bienvenido===============================\n "
    	   "=====================Favor cargar los datos para comenzar==================\n");
    do{
    	getMenuCarga(&option);
        switch(option)
        {
            case 1:
                if (controller_loadFromText("data.csv",listaEmpleados) == 0 && flagCarga == 0)
                {
                	printf("Datos cargados con éxito\n");
                	controller_ListEmployee(listaEmpleados);
                	flagCarga = 1;
                }
                break;
            case 2:
            	if (controller_loadFromBinary("data.bin" , listaEmpleados) == 0 && flagCarga == 0)
            	{
            		printf("Datos cargados con éxito\n");
            		controller_ListEmployee(listaEmpleados);
            		flagCarga = 1;
            	}
            	break;
            case 3:
            	controller_addEmployee(listaEmpleados);
            	break;
            case 4:
            	controller_editEmployee(listaEmpleados);
            	break;
            case 5:
            	controller_removeEmployee(listaEmpleados);
            	break;
            case 6:
            	controller_ListEmployee(listaEmpleados);
            	break;
            case 7:
            	controller_sortEmployee(listaEmpleados);
            	break;
            case 8:
            	controller_saveAsText("data.csv",listaEmpleados);
            	break;
            case 9:
            	controller_saveAsBinary("data.bin" , listaEmpleados);
            	break;
            case 10:
            	printf("==================================Programa finalizado===============================\n ");
            	break;
        }
    }while(option != 10);

    ll_deleteLinkedList(listaEmpleados);

    return 0;
}

