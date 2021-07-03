#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "misFuncionesGet.h"

int getString(char cadena[],int len)
{
	int error=1;
	char auxiliar[5001];

	if(cadena!=NULL && len>0)
	{
		fflush(stdin);
		if(fgets(auxiliar,sizeof(auxiliar),stdin)!=NULL)
		{
			if(auxiliar[strnlen(auxiliar,sizeof(auxiliar))-1] == '\n')
			{
				auxiliar[strnlen(auxiliar,sizeof(auxiliar))-1] = '\0';
			}
			if(strnlen(auxiliar,sizeof(auxiliar))<=len)
			{
				strncpy(cadena,auxiliar,len);
				error=0;
			}
		}
	}
	return error;
}
int getInt(int* resultado)
{
	int error=1;
	char auxiliar[5001];

	if(resultado!=NULL
		&& getString(auxiliar,sizeof(auxiliar))==0
		&& esNumerica(auxiliar,sizeof(auxiliar)))
	{
		*resultado=atoi(auxiliar);
		error=0;
	}
	return error;
}
int getFloat(float* resultado)
{
	int error=1;
	char auxiliar[5001];

	if(resultado!=NULL
		&& getString(auxiliar,sizeof(auxiliar))==0
		&& esFlotante(auxiliar,sizeof(auxiliar)))
	{
		*resultado=atof(auxiliar);
		error=0;
	}
	return error;
}
int esNumerica(char cadena[],int len)
{
	int error=1;
	int i;

	for(i=0;i<len && cadena[i]!='\0';i++)
	{
		if(cadena[i]=='-' || cadena[i]=='+')
		{
			continue;
		}
		if(cadena[i]>'9' || cadena[i]<'0')
		{
			error=0;
			break;
		}
	}
	return error;
}
int esFlotante(char cadena[],int len)
{
	int error=1;
	int i;

	for(i=0;i<len && cadena[i]!='\0';i++)
	{
		if(cadena[i]==',' || cadena[i]=='.')
		{
			continue;
		}
		if(cadena[i]>'9' || cadena[i]<'0')
		{
			error=0;
			break;
		}
	}
	return error;
}
int getNumero(int* resultado,char msg[],char msgError[],int min,int max)
{
	int error=1;
	int auxiliar;

	if(resultado!=NULL
			&& msg!=NULL
			&& msgError!=NULL
			&& min<=max)
	{
		do
		{
			printf("%s",msg);
			if(getInt(&auxiliar)==0
					&& auxiliar>=min
					&& auxiliar<=max)
			{
				*resultado=auxiliar;
				error=0;
				break;
			}
			printf("%s",msgError);
		}while(error!=0);
	}
	return error;
}
int getFlotante(float* resultado,char msg[],char msgError[],int min,int max)
{
	int error=1;
	float auxiliar;

	if(resultado!=NULL
			&& msg!=NULL
			&& msgError!=NULL
			&& min<=max)
	{
		do
		{
			printf("%s",msg);
			if(getFloat(&auxiliar)==0
					&& auxiliar>=min
					&& auxiliar<=max)
			{
				*resultado=auxiliar;
				error=0;
				break;
			}
			printf("%s",msgError);
		}while(error!=0);
	}
	return error;
}
int getNombre(char nombre[], char inputMsg[],char errorMsg[], int tam)
{
	int error=1;
    char auxiliar[51];
    int len;

    printf("%s",inputMsg);
    fflush(stdin);
    scanf("%[^\n]",auxiliar);
    strlwr(auxiliar);
    len=strlen(auxiliar);

    auxiliar[0]=toupper(auxiliar[0]);

    while(strlen(auxiliar)>tam-1)
    {
        printf("%s",errorMsg);
        fflush(stdin);
        scanf("%[^\n]",auxiliar);
        strlwr(auxiliar);
        len=strlen(auxiliar);

        auxiliar[0]=toupper(auxiliar[0]);

        for(int i=0;i<len;i++)
        {
            if(isspace(auxiliar[i]))
            {
            	auxiliar[i+1]=toupper(auxiliar[i+1]);
            }
        }
    }
    for(int i=0;i<tam;i++)
    {
        if(isspace(auxiliar[i]))
        {
        	auxiliar[i+1]=toupper(auxiliar[i+1]);
        }
    }
    strcpy(nombre,auxiliar);
    error=0;
    return error;
}
int getChar(char* resultado)
{
    int error=1;
	char auxiliar[51];

	scanf("%s",auxiliar);
	if(esCaracter(auxiliar))
	{
		*resultado=*auxiliar;
		error=0;
	}
	return error;
}
int esCaracter(char* string)
{
    int error=1;
	int i=0;

	if(string!=NULL && strlen(string)>0)
	{
		while(string[i] !='\0')
		{
			string[i]=tolower(string[i]);
			if(string[i]<'a'||string[i]>'z')
			{
				error=0;
				break;
			}
			i++;
		}
	}
	return error;
}

int getCaracter(char* resultado, char msg[], char msgError[], char min, char max)
{
    int error=1;
	char auxiliarChar;

	if(resultado!=NULL && msg!=NULL && msgError!=NULL && min<=max)
	{
        printf("%s",msg);

        if(getChar(&auxiliarChar)==1 && auxiliarChar>=min && auxiliarChar<=max)
        {
            *resultado=auxiliarChar;
            error=0;
        }
        printf("%s",msgError);
        fflush(stdin);
	}
	return error;
}

int getDosChar(char msg[], char msgError[], char char1, char char2)
{
    int error=-1;
	char auxiliarChar;

	if(msg!=NULL && msgError!=NULL && char1!=char2)
	{
        while(error==-1)
        {
            printf(msg);
            getChar(&auxiliarChar);
            if(auxiliarChar==char1)
            {
                error=0;
            }
            else if(auxiliarChar==char2)
            {
                error=1;
            }
            else if(auxiliarChar!=char1 && auxiliarChar!=char2)
            {
                printf(msgError);
                error=-1;
            }
        }
	}
	fflush(stdin);

	return error;
}
void getPath(char* msg,char* path)
{
    if(msg!=NULL && path!=NULL)
    {
        printf(msg);
        fflush(stdin);
        gets(path);
    }
}
