#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "misFuncionesGet.h"
#include "LinkedList.h"
#include "Controller.h"
#include "Employee.h"

int main()
{
    int menuOpcion = 0;
    char salida = 'n';
    char path[21];
    int idActual=1;

    LinkedList* listaEmpleados = ll_newLinkedList();

    if(listaEmpleados!=NULL)
    {
        do
        {
            if(!getNumero(&menuOpcion,
                "\n**** TP3 MENU ****\n\n"
                "1) CARGAR datos en modo TEXTO.\n"
                "2) CARGAR datos en modo BINARIO.\n"
                "3) ALTA empleado.\n"
                "4) MODIFICAR empleado.\n"
                "5) BAJA de empleado.\n"
                "6) LISTA de empleados.\n"
                "7) ORDENAR empleados\n"
                "8) GUARDAR en modo texto.\n"
                "9) GUARDAR en modo binario.\n"
                "10) SALIR del programa.\n"
                "===== TP4 =====\n"
                "11) Menu de TRASPASOS.\n"
                "Ingrese una opcion: ",
                "\nERROR - Re-ingrese una opcion entre 1 y 10.\n",1,11))
            {
                switch(menuOpcion)
                {
                    case 1:
                        getPath("\n**Bienvenido a la carga de datos en modo texto**\nIngrese el nombre del archivo(data.csv): ",path);
                        if(!controller_loadFromText(path,listaEmpleados))
                        {
                            printf("\nEl archivo a sido cargado con exito!\n");
                        }
                        else
                        {
                            printf("\nERROR al cargar el archivo.\n");
                        }
                        break;
                    case 2:
                        getPath("\n**Bienvenido a la carga de datos en modo binario**\nIngrese el nombre del archivo(data.bin): ",path);
                        if(!controller_loadFromBinary(path,listaEmpleados))
                        {
                            printf("\nEl archivo a sido cargado con exito!\n");
                        }
                        else
                        {
                            printf("\nERROR al cargar el archivo.\n");
                        }
                        break;
                    case 3:
                        if(!controller_addEmployee("\n**Bienvenido al alta empleado**\nComplete los campos a continuacion:\n",listaEmpleados,&idActual))
                        {
                            printf("\nSe realizo el ALTA correctamente.");
                        }
                        else
                        {
                            printf("\nERROR al cargar el ALTA.");
                        }
                        break;
                    case 4:
                        if(!controller_editEmployee(listaEmpleados))
                        {
                            printf("\nModificacion realizada con exito.");
                        }
                        else
                        {
                            printf("\nERROR al realizar la modifiacion.");
                        }
                        break;
                    case 5:
                        if(!controller_removeEmployee(listaEmpleados))
                        {
                            printf("\nEmpleado dado de baja con exito.");
                        }
                        else
                        {
                            printf("\nERROR al dar de baja al empleado.");
                        }
                        break;
                    case 6:
                        if(!controller_ListEmployees(listaEmpleados))
                        {
                            printf("\nEmpleados listados correctamente.");
                        }
                        else
                        {
                            printf("\nERROR al listar los empleados.");
                        }
                        break;
                    case 7:
                        if(!controller_sortEmployee(listaEmpleados))
                        {
                            printf("\nOrdenamiento realizado con exito.");
                        }
                        else
                        {
                            printf("\nERROR al ordenar los empleados.");
                        }
                        break;
                    case 8:
                        getPath("\n*** Bienvenido al guardado en modo de texto ***\nIngrese el nombre del archivo: ",path);
                        if(!controller_saveAsText(path,listaEmpleados))
                        {
                            printf("\nEl archivo se guardo con exito!");
                        }
                        else
                        {
                            printf("\nERROR al guardar el archivo.");
                        }
                        break;
                    case 9:
                        getPath("\n*** Bienvenido al guardado en modo binario ***\nIngrese el nombre del archivo: ",path);
                        if(!controller_saveAsBinary(path,listaEmpleados))
                        {
                            printf("\nEl archivo se guardo con exito!");
                        }
                        else
                        {
                            printf("\nERROR al guardar el archivo.");
                        }
                        break;
                    case 10:
                        if(!getDosChar("\nDesea salir del programa?(S/N): ","\nERROR - Ingrese S o N.",'s','n'))
                        {
                            salida='s';
                        }
                        else
                        {
                            salida='n';
                        }
                        break;
                    case 11:
                        if(!traspasarEmpleados(listaEmpleados))
                        {

                        }
                        else
                        {

                        }
                        break;
                }
            }
        }while(salida != 's');
    }

    return 0;
}
