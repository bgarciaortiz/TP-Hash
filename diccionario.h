#ifndef DICCIONARIO_H_INCLUDED
#define DICCIONARIO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lista.h"

#define HASHSIZE 10

typedef struct
{
    tLista* pl;         // puntero al arreglo de listas
    unsigned capacidad;     // tLista=tNodo**
}tDiccionario;

typedef struct
{
    char* clave;
    void* valor;
    size_t tamClave;
    size_t tamValor;
}tInfo;

//Funciones

unsigned mihash(char *s);
tDiccionario* crear_dic(size_t tam);
int poner_dic(tDiccionario* pdic, char* clave, const void* valor, size_t tamValor);
int obtener_dic(tDiccionario* dic, char* clave, void* valor, size_t tamValor);
int sacar_dic(tDiccionario* dic, char* clave, void* valor, size_t tamValor);

int recorrer_dic(tDiccionario*, void (*accion)(const void*, const void*), int (*cmp)(const void*,const void*));
void destruir_dic(tDiccionario* dic, size_t tam);

#endif // DICCIONARIO_H_INCLUDED
