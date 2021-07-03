#ifndef employee_H_INCLUDED
#define employee_H_INCLUDED
typedef struct
{
    int id;
    char nombre[128];
    int horasTrabajadas;
    int sueldo;
}Employee;

Employee* employee_new();
Employee* employee_newParametros(char* idStr,char* nombreStr,char* horasTrabajadasStr, char* sueldoStr);
void employee_delete();

int employee_setId(Employee* this,int id);
int employee_getId(Employee* this,int* id);

int employee_setNombre(Employee* this,char* nombre);
int employee_getNombre(Employee* this,char* nombre);

int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas);
int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas);

int employee_setSueldo(Employee* this,int sueldo);
int employee_getSueldo(Employee* this,int* sueldo);

int employee_buscarUltimoId(LinkedList* pArrayListEmployee,int* ultimoId);
int employee_buscarId(LinkedList* pArrayListEmployee,int idBuscado);
Employee* employee_buscarXid(LinkedList* pArrayListEmployee,int idBuscado,int* indiceParaMododificar);
Employee* employee_menuModificion(Employee* emp);
int employee_sortByName(void* a,void* b);
int employee_sortByHoras(void* a,void* b);
int employee_sortBySueldo(void* a,void* b);

#endif // employee_H_INCLUDED
