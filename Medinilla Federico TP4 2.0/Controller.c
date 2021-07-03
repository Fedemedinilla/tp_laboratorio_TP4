#include <stdio.h>
#include <stdlib.h>
#include "misFuncionesGet.h"
#include "parser.h"
#include "LinkedList.h"
#include "Employee.h"
#include "Controller.h"


/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromText(char* path ,LinkedList* pArrayListEmployee)
{
    int error=1;
    char sobreescribe;
    FILE* f;

    if(path!=NULL && pArrayListEmployee!=NULL)
    {
        f=fopen(path,"r");
        if(f!=NULL)
        {
            if(!ll_isEmpty(pArrayListEmployee))
            {
                if(!getDosChar("\nEl fichero ya tiene datos cargados. Desea sobreescribirlos?(S/N): ","\nERROR - Re-ingrese 's' o 'n'.",'n','s'))
                {
                    sobreescribe='n';
                }
                else
                {
                    sobreescribe='s';
                }
            }
            if(ll_isEmpty(pArrayListEmployee) || sobreescribe=='s')
            {
                ll_clear(pArrayListEmployee);
                parser_EmployeeFromText(f,pArrayListEmployee);
                error=0;
            }
        }
    }
    fclose(f);

    return error;
}

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromBinary(char* path ,LinkedList* pArrayListEmployee)
{
    int error=1;
    char sobreescribe;
    FILE* f;

    if(path!=NULL && pArrayListEmployee!=NULL)
    {
        f=fopen(path,"rb");
        if(f!=NULL)
        {
            if(!ll_isEmpty(pArrayListEmployee))
            {
                if(!getDosChar("\nEl fichero ya tiene datos cargados. Desea sobreescribirlos?(S/N): ","\nERROR - Re-ingrese 's' o 'n'.",'n','s'))
                {
                    sobreescribe='n';
                }
                else
                {
                    sobreescribe='s';
                }
            }
            if(ll_isEmpty(pArrayListEmployee) || sobreescribe=='s')
            {
                ll_clear(pArrayListEmployee);
                parser_EmployeeFromBinary(f,pArrayListEmployee);
                error=0;
            }
        }
    }
    fclose(f);

    return error;
}

/** \brief Alta de empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_addEmployee(char* msg,LinkedList* pArrayListEmployee,int* id)
{
    int error=1;
    int auxId;
    Employee* auxEmpleado=NULL;

    printf(msg);
    if(pArrayListEmployee!=NULL && employee_buscarUltimoId(pArrayListEmployee,&auxId)==0)
    {
        printf("El siguiente id es: %d",auxId);
        auxEmpleado=employee_new();
        if(auxEmpleado!=NULL)
        {
            if(!getNombre(auxEmpleado->nombre,"\nIngrese el NOMBRE: ","\nERROR - Re-ingrese el nombre.",128)
               &&!getNumero(&auxEmpleado->horasTrabajadas,"\nIngrese el numero de HORAS TRABAJADAS(10-1000): ","\nERROR - Re-ingrese un numero valido.",10,1000)
               &&!getNumero(&auxEmpleado->sueldo,"\nIngrese el SUELDO(1000-100000): ","\nERROR - Re-ingrese el sueldo.",1000,100000))
            {
                auxEmpleado->id=auxId;

                printf("\nEste es el empleado que desea agregar?\n");
                controller_ShowEmployee(auxEmpleado);
                if(!getDosChar("\nIngrese S para confirmar o N para negar: ","ERROR - Re-ingrese S o N.",'s','n'))
                {
                    if(!ll_add(pArrayListEmployee,auxEmpleado))
                    {
                        *id=auxId+1;
                        auxEmpleado=NULL;
                        error=0;
                    }
                }
            }
        }
    }

    return error;
}

/** \brief Modificar datos de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_editEmployee(LinkedList* pArrayListEmployee)
{
    int error=1;
    Employee* auxEmpleado=NULL;
    Employee* auxEmpleado2=NULL;
    int idParaModificar;
    int indiceParaModificar;
    int tam=ll_len(pArrayListEmployee);

    if(pArrayListEmployee!=NULL && tam>0 && !ll_isEmpty(pArrayListEmployee))
    {
        controller_ListEmployees(pArrayListEmployee);
        if(!getNumero(&idParaModificar,"\nIngrese el ID que quiere modificar: ","\nERROR - Re-ingrese un ID valido.",1,tam))
        {
            auxEmpleado=employee_buscarXid(pArrayListEmployee,idParaModificar,&indiceParaModificar);
            controller_ShowEmployee(auxEmpleado);
            if(!getDosChar("\nEste es el empleado que desea modificar?(S/N): ","\nERROR - Re-ingrese S o N.",'s','n'))
            {
                auxEmpleado2=employee_menuModificion(auxEmpleado);
                if(auxEmpleado2->id>0)
                {
                    if(!ll_set(pArrayListEmployee,indiceParaModificar,auxEmpleado))
                    {
                        auxEmpleado=NULL;
                        auxEmpleado2=NULL;
                        error=0;
                    }
                }
            }
        }
    }
    else
    {
        printf("ERROR La lista esta vacia o no existe.\n");
    }

    return error;
}

/** \brief Baja de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_removeEmployee(LinkedList* pArrayListEmployee)
{
    int error=1;
    Employee* auxEmpleado=NULL;
    int idParaBorrar;
    int indiceParaBorrar;

    if(pArrayListEmployee!=NULL)
    {
        controller_ListEmployees(pArrayListEmployee);
        if(!getNumero(&idParaBorrar,"\nIngrese el ID del empleado para borrar: ","\nERROR - Re-ingrese un ID valido.",1,1000))
        {
            auxEmpleado=employee_buscarXid(pArrayListEmployee,idParaBorrar,&indiceParaBorrar);
            controller_ShowEmployee(auxEmpleado);
            if(!getDosChar("\nEste es el empleado que desea eliminar de la faz de la tierra?(S/N): ","\nERROR - Re-ingrese s o n.",'s','n'))
            {
                if(ll_remove(pArrayListEmployee,indiceParaBorrar)==0)
                {
                    auxEmpleado=NULL;
                    error=0;
                }
                else
                {
                    error=1;
                }
            }
            else
            {
                error=1;
            }
        }
    }

    return error;
}
/** \brief Muestra un empleado
 *
 * \param emp Employee*
 * \return int
 *
 */
int controller_ShowEmployee(Employee* emp)
{
    int error=1;
    int id;
    char nombre[128];
    int horasTrabajadas;
    int sueldo;

    if(emp!=NULL)
    {
        if(!employee_getId(emp,&id)
        &&!employee_getNombre(emp,nombre)
        &&!employee_getHorasTrabajadas(emp,&horasTrabajadas)
        &&!employee_getSueldo(emp,&sueldo))
        {
            printf("\n%3d %s %4d %4d\n",id,nombre,horasTrabajadas,sueldo);
            error=0;
        }
    }

    return error;
}
/** \brief Listar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_ListEmployees(LinkedList* pArrayListEmployee)
{
    int error=1;
    Employee* auxEmpleado=NULL;

    if(pArrayListEmployee!=NULL)
    {
        printf("\n|ID|  |Nombre|  |Horas|  |Sueldo|\n");
        for(int i=0;i<ll_len(pArrayListEmployee);i++)
        {
            auxEmpleado=(Employee*) ll_get(pArrayListEmployee,i);
            controller_ShowEmployee(auxEmpleado);
            error=0;
        }
    }

    return error;
}

/** \brief Ordenar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
    int error=1;
    int menuOpcion;

    if(pArrayListEmployee!=NULL)
    {
        if(!getNumero(&menuOpcion,
                      "\n*** Menu de Ordenamiento ***\n\n"
                      "\n1) Ordenar por NOMBRE ASCENDENTE++"
                      "\n2) Ordenar por NOMBRE DESCENDENTE--"
                      "\n\n3) Ordenar por HORAS TRABAJADAS ASCENDENTE++"
                      "\n4) Ordenar por HORAS TRABAJADAS DESCENDENTE--"
                      "\n\n5) Ordenar por SUELDO ASCENDENTE++"
                      "\n6) Ordenar por SUELDO DESCENDENTE--"
                      "\n\nIngrese una opcion: ",
                      "\nERROR - Ingrese una opcion valida entre el 1 y el 6.",1,6))
        {
            switch(menuOpcion)
            {
            case 1:
                printf("\n*** Ordenando empleados por nombre ASCENDENTE ***\n");
                if(!ll_sort(pArrayListEmployee,employee_sortByName,1))
                {
                    printf("\nEmpleados ordenados por nombre ASCENDENTE.");
                }
                else
                {
                    printf("\nERROR al ordenar los empleados correctamente.");
                }
                break;
            case 2:
                printf("\n*** Ordenando empleados por nombre DESCENDENTE ***\n");
                if(!ll_sort(pArrayListEmployee,employee_sortByName,0))
                {
                    printf("\nEmpleados ordenados por nombre DESCENDENTE.");
                }
                else
                {
                    printf("\nERROR al ordenar los empleados correctamente.");
                }
                break;
            case 3:
                printf("\n*** Ordenando empleados por horas trabajadas ASCENDENTE***\n");
                if(!ll_sort(pArrayListEmployee,employee_sortByHoras,1))
                {
                    printf("\nEmpleados ordenados por horas trabajadas ASCENDENTE.");
                }
                else
                {
                    printf("\nERROR al ordenar los empleados correctamente.");
                }
                break;
            case 4:
                printf("\n*** Ordenando empleados por horas trabajadas DESCENDENTE ***\n");
                if(!ll_sort(pArrayListEmployee,employee_sortByHoras,0))
                {
                    printf("\nEmpleados ordenados por horas trabajadas DESCENDENTE.");
                }
                else
                {
                    printf("\nERROR al ordenar los empleados correctamente.");
                }
                break;
            case 5:
                printf("\n*** Ordenando empleados por el sueldo ASCENDENTE ***\n");
                if(!ll_sort(pArrayListEmployee,employee_sortBySueldo,1))
                {
                    printf("\nEmpleados ordenados por el sueldo ASCENDENTE.");
                }
                else
                {
                    printf("\nERROR al ordenar los empleados correctamente.");
                }
                break;
            case 6:
                printf("\n*** Ordenando empleados por el sueldo DESCENDENTE ***\n");
                if(!ll_sort(pArrayListEmployee,employee_sortBySueldo,0))
                {
                    printf("\nEmpleados ordenados por el sueldo DESCENDENTE.");
                }
                else
                {
                    printf("\nERROR al ordenar los empleados correctamente.");
                }
                break;
            }
        }
        error=0;
    }

    return error;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char* path ,LinkedList* pArrayListEmployee)
{
    int error=1;
    FILE* f;
    Employee* auxEmpleado=NULL;
    char confirma = 's';

    if(path!=NULL && pArrayListEmployee!=NULL)
    {
        f=fopen(path,"r");
        if(f!=NULL)
        {
            if(!getDosChar("\nEl archivo ya tiene datos cargados, desea sobreescribirlos?(S/N): ","\nERROR - Ingrese S o N.",'s','n'))
            {
                confirma='s';
            }
            else
            {
                confirma='n';
            }
        }
        fclose(f);

        if(confirma=='s')
        {
            f=fopen(path,"w");
            if(f!=NULL)
            {
                fprintf(f,"Id,Nombre,HorasTrabajadas,Sueldo\n");
                for(int i=0;i<ll_len(pArrayListEmployee);i++)
                {
                    auxEmpleado=(Employee*)ll_get(pArrayListEmployee,i);
                    if(auxEmpleado!=NULL)
                    {
                        fprintf(f,"%d,%s,%d,%d\n",auxEmpleado->id,auxEmpleado->nombre,auxEmpleado->horasTrabajadas,auxEmpleado->sueldo);
                        auxEmpleado=NULL;
                        error=0;
                    }
                    else
                    {
                        printf("\nERROR con el FPRINTF");
                        error=1;
                        break;
                    }
                }
            }
        }
    }
    fclose(f);

    return error;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsBinary(char* path , LinkedList* pArrayListEmployee)
{
    int error=1;
    Employee* auxEmpleado=NULL;
    FILE* f;
    char confirma='s';

    if(path!=NULL && pArrayListEmployee!=NULL)
    {
        f=fopen(path,"rb");
        if(f!=NULL)
        {
            if(!getDosChar("\nEl archivo ya tiene datos cargados, desea sobreescribirlos?(S/N): ","\nERROR - Ingrese S o N.",'s','n'))
            {
                confirma='s';
            }
            else
            {
                confirma='n';
            }
        }
        fclose(f);

        if(confirma=='s')
        {
            f=fopen(path,"wb");
            if(f!=NULL)
            {
                for(int i=0;i<ll_len(pArrayListEmployee);i++)
                {
                    auxEmpleado=(Employee*)ll_get(pArrayListEmployee,i);
                    if(auxEmpleado!=NULL)
                    {
                        if(fwrite(auxEmpleado,sizeof(Employee),1,f)<1)
                        {
                            break;
                        }
                        else
                        {
                            error=0;
                        }
                    }
                }
            }
        }
    }
    fclose(f);

    return error;
}
int traspasarEmpleados(LinkedList* lista)
{
    LinkedList* listaNueva=NULL;
    int error=1;

    if(lista!=NULL)
    {
        listaNueva=ll_newLinkedList();
        if(menuTraspaso(lista,listaNueva))
        {
            printf("\nOperaciones de traspaso realizadas con exito!\n");
        }
        else
        {
            printf("\nERROR al realizar las operaciones de traspaso.\n");
        }
    }

    return error;
}
int menuTraspaso(LinkedList* lista, LinkedList* listaNueva)
{
    int error=1;
    char salida;
    int menuOpcion;
    LinkedList* listaClonada=NULL;
    LinkedList* listaCortada=NULL;

    int idElegido;
    int indiceBuscado;
    int indiceBuscado2;

    int pushIdAnterior;

    void* employeeAux=NULL;
    void* employeeParaMeter=NULL;

    int idFrom;
    int idTo;
    int indiceFrom;
    int indiceTo;

    if(lista!=NULL && listaNueva!=NULL)
    {
        printf("\n=== La nueva lista ha sido creada con exito y ya puede ir completandola ===\n");
        do
        {
            if(!getNumero(&menuOpcion,
                "\n**** Menu de traspasos ****\n\n"
                "1) TRASPASAR empleado a la lista NUEVA.(ll_contains() + ll_pop())\n"
                "2) TRASPASAR empleado a la lista VIEJA.(ll_contains() + ll_push())\n"
                "3) MOSTRAR la lista NUEVA.\n\n"
                "4) CLONAR la lista original.(ll_containsAll() + ll_clone())\n"
                "5) MOSTRAR la lista CLONADA.\n\n"
                "6) CORTAR la lista original.(ll_containsAll() + ll_subList())\n"
                "7) MOSTRAR la lista CORTADA.\n\n"
                "8) SALIR de este menu.\n\n"
                "Ingrese una opcion: ",
                "\nERROR ingrese una opcion del 1 al 6.\n",1,8))
            {
                switch(menuOpcion)
                {
                case 1:
                    printf("\n=== LISTA VIEJA ===\n");
                    if(!controller_ListEmployees(lista))
                    {
                        printf("\nLista mostrada con exito.\n");
                        if(!getNumero(&idElegido,"Ingrese el ID del empleado que quiere traspasar: ","ERROR ingrese un id VALIDO.",1,5000))
                        {
                            employeeAux=employee_buscarXid(lista,idElegido,&indiceBuscado);
                            indiceBuscado=ll_indexOf(lista,employeeAux);
                            if(ll_contains(lista,employeeAux) && indiceBuscado!=0)
                            {
                                controller_ShowEmployee(employeeAux);
                                if(!getDosChar("\nEste es el empleado que desea traspasar?(S/N): ","\nERROR Ingrese S para aceptar, o N para negar.\n",'s','n'))
                                {
                                    employeeParaMeter=ll_pop(lista,indiceBuscado);
                                    if(!ll_add(listaNueva,employeeParaMeter))
                                    {
                                        printf("\n\n*** EMPLEADO TRASPASADO CORRECTAMENTE ***\n\n");
                                        controller_ListEmployees(listaNueva);
                                    }
                                    else
                                    {
                                        printf("\nERROR al realizar el traspaso del empleado.");
                                    }
                                }
                                else
                                {
                                    printf("\nVolviendo al menu anterior.\n");
                                }
                            }
                            else
                            {
                                printf("\nERROR El empleado no existe.\n");
                            }
                        }
                    }
                    else
                    {
                        printf("\nERROR al mostrar la lista.\n");
                    }
                    break;
                case 2:
                    printf("\n=== LISTA NUEVA ===\n");
                    if(!controller_ListEmployees(listaNueva))
                    {
                        printf("\nLista mostrada con exito.\n");
                        if(!getNumero(&idElegido,"Ingrese el ID del empleado que quiere traspasar: ","\nERROR ingrese un id VALIDO.\n",1,5000))
                        {
                            employeeParaMeter=employee_buscarXid(listaNueva,idElegido,&indiceBuscado);
                            indiceBuscado=ll_indexOf(listaNueva,employeeParaMeter);
                            if(ll_contains(listaNueva,employeeParaMeter) && indiceBuscado!=0)
                            {
                                controller_ShowEmployee(employeeParaMeter);
                                if(!getDosChar("\nEste es el empleado que desea traspasar?(S/N): ","\nERROR Ingrese S para aceptar, o N para negar.\n",'s','n'))
                                {
                                    controller_ListEmployees(lista);
                                    printf("\n\n*** Luego de que empleado desea agregarlo? ***\n");
                                    if(!getNumero(&pushIdAnterior,"\nIngrese el ID del empleado ANTERIOR: ","\nERROR Ingrese un ID VALIDO.",1,5000))
                                    {
                                        employeeAux=employee_buscarXid(lista,pushIdAnterior,&indiceBuscado2);
                                        indiceBuscado2=ll_indexOf(lista,employeeAux);
                                        if(ll_contains(lista,employeeAux) && indiceBuscado2!=0)
                                        {
                                            ll_push(lista,indiceBuscado2+1,employeeParaMeter);
                                            ll_remove(listaNueva,indiceBuscado);
                                            printf("\n\nEl empleado ha sido traspasado correctamente.\n\n");
                                        }
                                    }
                                }
                                else
                                {
                                    printf("\nVolviendo al menu anterior.\n");
                                }
                            }
                            else
                            {
                                printf("\nERROR El empleado no existe.\n");
                            }
                        }
                    }
                    else
                    {
                        printf("\nERROR al mostrar la lista.\n");
                    }
                    break;
                case 3:
                    if(!controller_ListEmployees(listaNueva))
                    {
                        printf("\nLa nueva lista fue mostrada con exito!");
                    }
                    else
                    {
                        printf("\nERROR al mostrar la nueva lista.");
                    }
                    break;
                case 4:
                    printf("\n\n=== CLONACION ===\n\n");
                    if(!getDosChar("\nDesea clonar la lista VIEJA?(S/N): \n","\nERROR Ingrese S para confirmar o N para negar.\n",'s','n'))
                    {
                        listaClonada=ll_newLinkedList();
                        if(listaClonada!=NULL)
                        {
                            listaClonada=ll_clone(lista);
                            if(ll_containsAll(listaClonada,lista))
                            {
                                printf("\nLa lista fue clonada con exito! Y contiene todos los elementos correctamente.\n");
                                if(!getDosChar("\nQuiere ver la LISTA CLONADA?(S/N): ","\nERROR Ingrese S para confirmar o N para negar.\n",'s','n'))
                                {
                                    controller_ListEmployees(listaClonada);
                                }
                            }
                            else if(ll_containsAll(listaClonada,lista)==-1)
                            {
                                printf("\nERROR Alguno de los punteros fallo al clonarse.");
                            }
                            else
                            {
                                printf("\nERROR La lista no fue clonada correctamente.");
                            }
                        }
                        else
                        {
                            printf("\nERROR al crear la nueva lista, no se pudo encontrar espacio suficiente.\n");
                        }
                    }
                    break;
                case 5:
                    if(!controller_ListEmployees(listaClonada))
                    {
                        printf("\nLista clonada mostrada con exito!\n");
                    }
                    else
                    {
                        printf("\nERROR al mostrar la lista clonada.");
                    }
                    break;
                case 6:
                    printf("\n\n=== CORTAR LISTA ===\n\n");
                    if(!controller_ListEmployees(lista))
                    {
                        if(!getNumero(&idFrom,"Ingrese el ID DESDE donde quiere EMPEZAR a recortar la lista: ","\nERROR ingrese un id VALIDO.\n",1,5000))
                        {
                            employeeAux=employee_buscarXid(lista,idFrom,&indiceFrom);
                            indiceFrom=ll_indexOf(lista,employeeAux);
                            if(ll_contains(lista,employeeAux) && indiceFrom!=0)
                            {
                                if(!getNumero(&idTo,"\nAhora ingrese el ID HASTA donde quiere TERMINAR de recortar la lista: ","\nERROR Ingrese un ID VALIDO.",1,5000))
                                {
                                    employeeAux=employee_buscarXid(lista,idTo,&indiceTo);
                                    indiceTo=ll_indexOf(lista,employeeAux);
                                    if(ll_contains(lista,employeeAux) && indiceTo!=0)
                                    {
                                        listaCortada=ll_subList(lista,indiceFrom,indiceTo+1);
                                        if(listaCortada!=NULL)
                                        {
                                            printf("\nLa lista recortada se ha creado con exito!\n");
                                            if(!getDosChar("\nDesea ver la lista?(S/N): ","\nERROR Ingrese S para confirmar o N para negar.\n",'s','n'))
                                            {
                                                if(!controller_ListEmployees(listaCortada))
                                                {
                                                    printf("\nLista cortada y mostrada con exito!\n");
                                                }
                                                else
                                                {
                                                    printf("\nERROR al mostrar la lista cortada.\n");
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                            else
                            {
                                printf("\nERROR El empleado no existe.\n");
                            }
                        }
                    }
                    else
                    {
                        printf("\nERROR al mostrar la lista.\n");
                    }
                    break;
                case 7:
                    if(!controller_ListEmployees(listaCortada))
                    {
                        printf("\nLista cortada mostrada con exito!\n");
                    }
                    else
                    {
                        printf("\nERROR al mostrar la lista cortada.");
                    }
                    break;
                case 8:
                    if(!getDosChar("\nDesea salir del menu de TRASPASOS?","\nERROR Ingrese S para si, o N para no.\n",'s','n'))
                    {
                        salida='s';
                    }
                    else
                    {
                        salida='n';
                    }
                    break;
                }
            }
        }while(salida!='s');
    }
    ll_deleteLinkedList(listaNueva);
    ll_deleteLinkedList(listaClonada);
    ll_deleteLinkedList(listaCortada);

    return error;
}

