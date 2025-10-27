#include "diccionario.h"

//Funcion Hash -> Se toma del libro "El Lenguaje de Programación C"
///* hash: forma un valor hash para la cadena s */

unsigned mihash(char *s)
{
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

int iniInfo(tInfo* info, char* clave, const void* valor, size_t tamValor)
{
    info->tamClave = strlen(clave)+1;
    info->clave = (char*)malloc(info->tamClave);
    if(!info->clave)
        return FALSO;   // sin memoria
    strcpy(info->clave,clave);

    info->valor=malloc(tamValor);
    if(!info->valor)
    {
        free(info->clave);
        return FALSO;   // sin memoria
    }
    info->tamValor=tamValor;
    memcpy(info->valor,valor,info->tamValor);

    return VERDADERO;
}

tDiccionario* crear_dic(size_t capacidad)   // tDiccionario*=tLista**=tNodo***
{
    tDiccionario* dic=(tDiccionario*)malloc(sizeof(tDiccionario));  // asigna memoria al diccionario
    if(!dic)
        return FALSO;   // sin memoria para diccionario

    dic->pl=(tLista*)malloc(sizeof(tLista)*capacidad);  // asigna [HASHSIZE] listas
    if(!dic->pl)
    {
        free(dic);
        return FALSO;   // sin memoria para listas
    }

    dic->capacidad=capacidad;

    for(int i=0; i<capacidad; i++)
        crear_lista(&dic->pl[i]);

    return dic;
}

int poner_dic(tDiccionario* pdic, char* clave, const void* valor, size_t tamValor)
{
    unsigned posicion=mihash(clave);
    tLista* plista=&pdic->pl[posicion];
    tNodo* actual=(*plista);

    while(actual && (cmp(((tInfo*)actual->info)->clave,clave)))
    {
        actual=actual->sig;
    }
    if(actual && (!cmp(((tInfo*)actual->info)->clave,clave)))
    {
        tInfo* pInfo=(tInfo*)actual->info;
        free(pInfo->valor);
        pInfo->valor=malloc(tamValor);
        if(!pInfo->valor)
            return FALSO;
        memcpy(pInfo->valor,valor,tamValor);
        pInfo->tamValor=tamValor;
    }
    else
    {
        tInfo* info=(tInfo*)malloc(sizeof(tInfo));
        if(!info)
            return FALSO;
        iniInfo(info,clave,valor,tamValor);
        poner_ord_lista(plista,info,sizeof(tInfo*),cmp);
    }
    return VERDADERO;
}

int obtener_dic(tDiccionario* dic, char* clave, void* valor, size_t tamValor)
{
    unsigned posicion=mihash(clave);
    tLista* plista=&dic->pl[posicion];
    tNodo* actual=(*plista);

    while(actual && (cmp(((tInfo*)actual->info)->clave,clave)))
    {
        actual=actual->sig;     // si no encuentra la clave sigue al siguente nodo de la lista
    }
    if(actual && (!cmp(((tInfo*)actual->info)->clave,clave)))
    {
        memcpy(valor,((tInfo*)actual->info)->valor,MINIMO(((tInfo*)actual->info)->tamValor,tamValor));
    }
    else
    {
        return FALSO;   // clave no encontrada
    }
    return VERDADERO;
}

int sacar_dic(tDiccionario* dic, char* clave, void* valor, size_t tamValor)
{
    unsigned posicion=mihash(clave);
    tLista* plista=&dic->pl[posicion];
    tNodo* actual=(*plista);

    while(actual && (cmp(((tInfo*)actual->info)->clave,clave)))
    {
        actual=actual->sig;
    }
    if(actual && (!cmp(((tInfo*)actual->info)->clave,clave)))
    {
        tInfo* info_ext;
        if(!sacar_elem_ord_lista(plista,&info_ext,sizeof(tInfo*),cmp))
        {
            return FALSO;
        }
        memcpy(valor,info_ext->valor,MINIMO(info_ext->tamValor,tamValor));
        free(info_ext->valor);
        free(info_ext->clave);
        free(info_ext);
        return VERDADERO;
    }
    else
    {
        return FALSO;
    }
}
