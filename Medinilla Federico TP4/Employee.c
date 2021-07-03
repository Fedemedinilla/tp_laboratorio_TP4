#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "misFuncionesGet.h"
#include "LinkedList.h"
#include "employee.h"
#include "Controller.h"

Employee* employee_new()
{
	Employee* auxEmpleado;

	auxEmpleado= (Employee*) malloc (sizeof(Employee));
	if(auxEmpleado!=NULL)
	{
		auxEmpleado->id=0;
		strcpy(auxEmpleado->nombre, " ");
		auxEmpleado->horasTrabajadas=0;
		auxEmpleado->sueldo=0;
	}

	return auxEmpleado;
}
Employee* employee_newParametros(char* idStr,char* nombreStr,char* horasTrabajadasStr, char* sueldoStr)
{
	Employee* auxEmpleado;
	auxEmpleado=employee_new();

	if(auxEmpleado!=NULL && idStr!=NULL && nombreStr!=NULL && horasTrabajadasStr!=NULL && sueldoStr!=NULL)
	{
		if(!(employee_setId(auxEmpleado,atoi(idStr))==0
            &&employee_setNombre(auxEmpleado,nombreStr)==0
            &&employee_setHorasTrabajadas(auxEmpleado,atoi(horasTrabajadasStr))==0
            &&employee_setSueldo(auxEmpleado,atoi(sueldoStr))==0))
		{
			free(auxEmpleado);
			auxEmpleado=NULL;
		}
	}

	return auxEmpleado;
}
///SETTERS
int employee_setId(Employee* this,int id)
{
    int error=1;

    if(this!=NULL && id>0)
    {
        this->id=id;
        error=0;
    }

    return error;
}
int employee_setNombre(Employee* this,char* nombre)
{
	int error=1;

	if(this!=NULL && strlen(nombre)<100 && strlen(nombre)>1 )
	{
		strcpy(this->nombre,nombre);
		error=0;
	}

	return error;
}

int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas)
{
	int error=1;

	if(this!=NULL && horasTrabajadas>50 && horasTrabajadas<500)
	{
		this->horasTrabajadas=horasTrabajadas;
		error=0;
	}

	return error;
}

int employee_setSueldo(Employee* this,int sueldo)
{
	int error=1;

	if(this!=NULL && sueldo>1000 && sueldo<1000000)
	{
		this->sueldo=sueldo;
		error=0;
	}

	return error;
}
///
///GETTERS
int employee_getId(Employee* this,int* id)
{
	int error=1;

	if(this!=NULL && id!=NULL)
	{
		*id=this->id;
		error=0;
	}

	return error;
}

int employee_getNombre(Employee* this,char* nombre)
{
	int error=1;

	if(this!=NULL && nombre!=NULL)
	{
		strcpy(nombre,this->nombre);
		error=0;
	}

	return error;
}

int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas)
{
	int error=1;

	if(this!=NULL && horasTrabajadas!=NULL)
	{
		*horasTrabajadas=this->horasTrabajadas;
		error=0;
	}

	return error;
}

int employee_getSueldo(Employee* this,int* sueldo)
{
	int error=1;

	if(this!=NULL && sueldo!=NULL)
	{
		*sueldo=this->sueldo;
		error=0;
	}

	return error;
}
///
int employee_buscarUltimoId(LinkedList* pArrayListEmployee,int* ultimoId)
{
    int error=1;
    Employee* auxEmpleado=NULL;
    int busquedaResultado=0;

    if(pArrayListEmployee!=NULL && ultimoId!=NULL)
    {
        for(int i=0;i<ll_len(pArrayListEmployee);i++)
        {
            auxEmpleado=(Employee*)ll_get(pArrayListEmployee,i);
            if(auxEmpleado->id>busquedaResultado || i==0)
            {
                busquedaResultado=auxEmpleado->id;
            }
        }
        *ultimoId=busquedaResultado+1;
        error=0;
    }

    return error;
}
int employee_buscarId(LinkedList* pArrayListEmployee,int idBuscado)
{
    int indiceBuscado;
    Employee* auxEmpleado;

    if(pArrayListEmployee!=NULL && idBuscado>0)
    {
        for(int i=0;i<ll_len(pArrayListEmployee);i++)
        {
            auxEmpleado=(Employee*)ll_get(pArrayListEmployee,i);
            if(auxEmpleado->id==idBuscado)
            {
                indiceBuscado=i;
                break;
            }
        }
    }

    return indiceBuscado;
}
Employee* employee_buscarXid(LinkedList* pArrayListEmployee,int idBuscado,int* indiceParaModificar)
{
    Employee* auxEmpleado=NULL;
    int indiceBuscado;

    if(pArrayListEmployee!=NULL && idBuscado>0)
    {
        indiceBuscado=employee_buscarId(pArrayListEmployee,idBuscado);
        *indiceParaModificar=indiceBuscado;
        auxEmpleado=ll_get(pArrayListEmployee,indiceBuscado);
    }

    return auxEmpleado;
}
Employee* employee_menuModificion(Employee* emp)
{
    int menuOpcion;
    char salida;

    if(emp!=NULL)
    {
        do
        {
            if(!getNumero(&menuOpcion,
                          "\n\n*** Menu de Modificaciones ***"
                          "\n1) Modificar el Nombre."
                          "\n2) Modificar las horas trabajadas."
                          "\n3) Modiciar el sueldo."
                          "\n4) Salir de este menu."
                          "\n\nIngrese una opcion: ",
                          "\nERROR - Ingrese una opcion entre el 1 y el 4.",1,4))
            {
                switch(menuOpcion)
                {
                case 1:
                    if(!getNombre(emp->nombre,"\nIngrese el nuevo NOMBRE: ","\nERROR - Re-ingrese el nombre.",130))
                    {
                        controller_ShowEmployee(emp);
                    }
                    else
                    {
                        printf("\nERROR al modificar el nombre.\n");
                    }
                    break;
                case 2:
                    if(!getNumero(&emp->horasTrabajadas,"\nIngrese las horas trabajadas: ","\nERROR - Re-ingrese las horas.",10,1000))
                    {
                        controller_ShowEmployee(emp);
                    }
                    else
                    {
                        printf("\nERROR al modificar las horas trabajadas.");
                    }
                    break;
                case 3:
                    if(!getNumero(&emp->sueldo,"\nIngrese el nuevo sueldo: ","\nERROR - Re-ingrese el sueldo.",1000,100000))
                    {
                        controller_ShowEmployee(emp);
                    }
                    else
                    {
                        printf("\nERROR al modificar el sueldo.");
                    }
                    break;
                case 4:
                    if(!getDosChar("\nDesea salir del menu de modifiaciones?(S/N): ","\nERROR - Re-ingrese s o n.",'n','s'))
                    {
                        salida='n';
                    }
                    else
                    {
                        salida='s';
                    }
                    break;
                }
            }
        }while(salida!='s');
    }

    return emp;
}
///SORT
int employee_sortByName(void* a,void* b)
{
    int error=0;
    Employee* emp1;
    Employee* emp2;

    if(a!=NULL && b!=NULL)
    {
        emp1=(Employee*)a;
        emp2=(Employee*)b;
        error=strcmp(emp1->nombre,emp2->nombre);
    }

    return error;
}
int employee_sortByHoras(void* a,void* b)
{
    int error=0;
    Employee* emp1;
    Employee* emp2;

    if(a!=NULL && b!=NULL)
    {
        emp1=(Employee*)a;
        emp2=(Employee*)b;
        if(emp1->horasTrabajadas > emp2->horasTrabajadas)
        {
            error=1;
        }
        else
        {
            if(emp1->horasTrabajadas < emp2->horasTrabajadas)
            {
                error=-1;
            }
        }
    }

    return error;
}
int employee_sortBySueldo(void* a,void* b)
{
    int error=0;
    Employee* emp1;
    Employee* emp2;

    if(a!=NULL && b!=NULL)
    {
        emp1=(Employee*)a;
        emp2=(Employee*)b;
        if(emp1->sueldo > emp2->sueldo)
        {
            error=1;
        }
        else
        {
            if(emp1->sueldo < emp2->sueldo)
            {
                error=-1;
            }
        }
    }

    return error;
}
