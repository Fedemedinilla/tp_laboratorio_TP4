#ifndef MISFUNCIONESGET_H_INCLUDED
#define MISFUNCIONESGET_H_INCLUDED

/** \brief recibe y devuelve un string verificado
 *
 * \param char[] el string que sobreescribe
 * \param int el tamaño del string
 * \return int 1 si hubo un error, o 0 si esta todo bien
 *
 */
int getString(char[],int);

/** \brief recibe y devuelve un string verificado
 *
 * \param char[] el string que sobreescribe
 * \param char[] mensaje para el usuario
 * \param char[] mensaje de error para el usuario
 * \param int el tamaño del string
 * \return int 1 si hubo un error, o 0 si esta todo bien
 *
 */
int getNombre(char[],char[],char[],int);

/** \brief recibe y devuelve un int por puntero
 *
 * \param int* puntero donde se va a dejar el resultado
 * \return int 1 si hubo un error, o 0 si esta todo bien
 *
 */
int getInt(int*);

/** \brief recibe y devuelve un float por puntero
 *
 * \param float* puntero donde se va a dejar el resultado
 * \return int 1 si hubo un error, o 0 si esta todo bien
 *
 */
int getFloat(float*);
/** \brief comprueba si lo recibido es un integer
 *
 * \param char[] string para comprobar
 * \param int tamaño del string a comprobar
 * \return int 1 si hubo un error, o 0 si esta todo bien
*
 */
int esNumerica(char[],int);
/** \brief comprueba si lo recibido es un float
 *
 * \param char[] string para comprobar
 * \param int tamaño del string a comprobar
 * \return int 1 si hubo un error, o 0 si esta todo bien
*
 */
int esFlotante(char[],int);
/** \brief realiza un input para el usuario, usando las funciones de verificacion internamente
 *
 * \param int* el puntero donde deja el resultado
 * \param char[] mensaje para el usuario
 * \param char[] mensaje de error para el usuario
 * \param int minimo
 * \param int maximo
 * \return int 1 si hubo un error, o 0 si esta todo bien
 *
 */
int getNumero(int*,char[],char[],int,int);
/** \brief realiza un input para el usuario, usando las funciones de verificacion internamente
 *
 * \param float* el puntero donde deja el resultado
 * \param char[] mensaje para el usuario
 * \param char[] mensaje de error para el usuario
 * \param int minimo
 * \param int maximo
 * \return int 1 si hubo un error, o 0 si esta todo bien
 *
 */
int getFlotante(float*,char[],char[],int,int);
/** \brief verifica si lo ingresado son letras
 *
 * \param string char* el string a comprobar
 * \return int 1 si hubo un error, o 0 si esta todo bien
 *
 */
int esCaracter(char* string);
/** \brief verifica si lo ingresado es un caracter
 *
 * \param resultado char* donde deja el resultado
 * \return int 1 si hubo un error, o 0 si esta todo bien
 *
 */
int getChar(char* resultado);
/** \brief realiza un input para el usuario
 *
 * \param resultado char* resultado
 * \param msg[] char mensaje para el usuario
 * \param msgError[] char mensaje de error para el usuario
 * \param min char minimo
 * \param max char maximo
 * \return int 1 si hubo un error, o 0 si esta todo bien
 *
 */
int getCaracter(char* resultado, char msg[], char msgError[], char min, char max);
/** \brief realiza la verificacion de dos caracteres
 *
 * \param msg[] char mensaje para el usuario
 * \param msgError[] char mensaje de error para el usuario
 * \param char1 char primer caracter a verficiar
 * \param char2 char segundo caracter a verificar
 * \return int 0 si es afirmativo, o 1 si es negativo
 *
 */
int getDosChar(char msg[], char msgError[], char char1, char char2);
void getPath(char* msg,char* path);

#endif // MISFUNCIONESGET_H_INCLUDED
