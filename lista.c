#include "lista.h"

int cmp(const void* a, const void* b)
{
    const int* var1=a;
    const int* var2=b;
    return (*var1)-(*var2);
}

void crear_lista(tLista* pl)
{
    (*pl)=NULL;
}

int lista_vacia(tLista* pl)
{
    return !*pl;
}

int lista_llena(tLista* pl, size_t tam)
{
    void* aux=malloc(sizeof(tNodo)+tam);
    free(aux);
    return !aux;
}

int poner_pri_lista(tLista* pl, const void* pd, size_t tam)
{
    tNodo* nue=(tNodo*)malloc(sizeof(tNodo)+tam);
    if(!nue)
        return FALSO;   // sin memoria
    nue->info=nue+1;

    memcpy(nue->info,pd,tam);
    nue->tam=tam;

    nue->sig=*pl;
    *pl=nue;

    return VERDADERO;
}

int poner_ult_lista(tLista* pl, const void* pd, size_t tam)
{
    tNodo* nue=(tNodo*)malloc(sizeof(tNodo)+tam);
    if(!nue)
        return FALSO;   // sin memoria
    nue->info=nue+1;

    while(*pl)
        pl=&(*pl)->sig;

    memcpy(nue->info,pd,tam);
    nue->tam=tam;

    nue->sig=*pl;
    *pl=nue;

    return VERDADERO;
}

int sacar_pri_lista(tLista* pl, void* pd, size_t tam)
{
    tNodo* elim=*pl;
    if(!elim)
        return FALSO;   // sin memoria

    memcpy(pd, elim->info, MINIMO(tam, elim->tam));

    *pl=elim->sig;
    free(elim);
    return VERDADERO;
}

int sacar_ult_lista(tLista* pl, void* pd, size_t tam)
{
    tNodo* elim;
    if(!*pl)
        return FALSO;   // sin memoria
    while((*pl)->sig)
        pl=&(*pl)->sig;

    elim=*pl;
    memcpy(pd,elim->info,MINIMO(tam,elim->tam));

    *pl=elim->sig;
    free(elim);
    return VERDADERO;
}

int poner_ord_lista(tLista* pl, const void* pd, size_t tam, int (*cmp)(const void*, const void*))
{
    tNodo* nue;
    int comp;
    while(  *pl && (comp=cmp(pd, (*pl)->info)>0) )
        pl=&(*pl)->sig;
    if( *pl && comp==0  )
        return FALSO;   // duplicado
    nue=(tNodo*)malloc(sizeof(tNodo)+tam);
    if(!nue)
        return FALSO;   // sin memoria

    nue->info=nue+1;
    memcpy(nue->info,pd,tam);
    nue->tam=tam;

    nue->sig=*pl;
    *pl=nue;
    return VERDADERO;
}

int sacar_elem_ord_lista(tLista* pl, void* pd, size_t tam, int (*cmp)(const void*, const void*))
{
    tNodo* elim;
    int comp;
    if(!*pl)
        return FALSO;   // lista vacia
    while(*pl && (comp=cmp((*pl)->info,pd)>0))
        pl=&(*pl)->sig;
    if(!*pl || comp)
        return FALSO;   // lista vacia o duplicado

    elim=*pl;
    memcpy(pd,elim->info,MINIMO(tam,elim->tam));

    *pl=elim->sig;
    free(elim);
    return VERDADERO;
}
