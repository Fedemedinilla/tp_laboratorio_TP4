#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "LinkedList.h"
#include "Employee.h"

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromText(FILE* pFile , LinkedList* pArrayListEmployee)
{
    int error=0;
    char buffer[4][20];
    Employee* auxEmpleado=NULL;

    if(pFile!=NULL && pArrayListEmployee!=NULL)
    {
        fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",buffer[0],buffer[1],buffer[2],buffer[3]);
        while(!feof(pFile))
        {
            if(fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",buffer[0],buffer[1],buffer[2],buffer[3])==4)
            {
                auxEmpleado=employee_newParametros(buffer[0],buffer[1],buffer[2],buffer[3]);
                if(auxEmpleado!=NULL)
                {
                    if(!ll_add(pArrayListEmployee,auxEmpleado))
                    {
                        auxEmpleado=NULL;
                        error=1;
                    }
                }
            }
        }
    }

    return error;
}

/** \brief Parsea los datos los datos de los empleados desde el archivo data.bin (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromBinary(FILE* pFile , LinkedList* pArrayListEmployee)
{
    int error=1;
    Employee* auxEmpleado=NULL;

    if(pFile!=NULL && pArrayListEmployee!=NULL)
    {
        while(!feof(pFile))
        {
            auxEmpleado=employee_new();
            if(auxEmpleado!=NULL)
            {
                if(fread(auxEmpleado,sizeof(Employee),1,pFile)==1)
                {
                    if(!ll_add(pArrayListEmployee,auxEmpleado))
                    {
                        auxEmpleado=NULL;
                        error=0;
                    }
                }
            }
        }
    }

    return error;
}
