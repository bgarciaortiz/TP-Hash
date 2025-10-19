#ifndef DICCIONARIO_H_INCLUDED
#define DICCIONARIO_H_INCLUDED

#include "lista.h"

#define HASHSIZE 1000

typedef struct{
    tLista *pl;
}tDiccionario;

        /// typedef tLista* t_diccionario; ????

typedef struct
{
    char* clave;
    size_t tamclave;
    char* valor;
    size_t tamvalor;
}tInfo;

//Funciones


//------ pendientes de implementación-----------------------

int vernodo(tDiccionario* pl, void* pd, size_t tam);
int eliminarNodo(tDiccionario* pl, char* clave);

//-------------------------------------------------------

unsigned tphash(char *s);
void crear_dic(tDiccionario*, int tam); //Recibe un puntero a diccionario y el tamaño
int poner_dic(tDiccionario*, char*, char*); //Recibo un puntero al diccionario, un puntero a la clave(que luego va a ser hasheada) y un puntero a la info
int obtener_dic(tDiccionario*, char*, char*); //Recibo un *p a diccionario, la clave(que tengo que hashear) y devuelvo el valor (Devolver retornando o en el parametro???) --> voy a devolver en el parametro y usar el return para manejo de errores
int sacar_dic(tDiccionario*, char*); //Recibo un *p a diccionario y la clave
int recorrer_dic(tDiccionario*, accion, int (*cmp)(const void*,const void*)); //Recibo un *p a diccionario, la accion y una func comparacion(puede ser null y ejecutar para todos)
void destruir_dic(tDiccionario* dic, size_t tam); //Recibo un *p a diccionario

#endif // DICCIONARIO_H_INCLUDED
