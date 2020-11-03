#ifndef employee_H_INCLUDED
#define employee_H_INCLUDED

#define LONG_NOMBRE 127
#define TEXTO_NUMERICO 999999

typedef struct
{
    int id;
    char nombre[LONG_NOMBRE];
    int horasTrabajadas;
    int sueldo;
}Employee;


int esNombreValido(char* cadena,int limite);
int esNumero(int* pResultado, int limite);

/////////////////////////////////////        C O N S T R U C T O R E S                //////////////////////////////////////
//int cliente_generarIdNuevo(void);
Employee* employee_new(void);
Employee* employee_newParametros(char* idStr,char* nombreStr,char* horasTrabajadasStr, char* sueldoStr);
void employee_delete();

/////////////////////////////////////        GETTERS   &&  SETTERS                     //////////////////////////////////////
int employee_setId(Employee* this,int id);
int employee_getId(Employee* this,int* id);
int cliente_getIdTxt (Employee* this, char* id);

int employee_setNombre(Employee* this,char* nombre);
int employee_getNombre(Employee* this,char* nombre);

int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas);
int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas);

int employee_setSueldo(Employee* this,int sueldo);
int employee_getSueldo(Employee* this,int* sueldo);

int employee_funcionCriterio (void* item1, void* item2);



#endif // employee_H_INCLUDED
