#include "diccionario.h"

//Funcion Hash -> Se toma del libro "El Lenguaje de Programación C"
/* hash: forma un valor hash para la cadena s */
unsigned tphash(char *s)
{
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

int iniInfo(tInfo* info, char* clave, char* valor)
{
    info=(tInfo*)malloc(sizeof(tInfo));
    if(!info)
        return FALSO;

    info->tamclave = strlen(clave);
    info->clave = (char*)malloc(info->tamclave);
    if(!info->clave)
        return FALSO;
    memcpy(info->clave,clave,info->tamclave);

    info->tamvalor = strlen(valor);
    info->valor = (char*)malloc(info->tamvalor);
    if(!info->valor)
        return FALSO;
    memcpy(info->valor,valor,info->tamvalor);

    return 0;
}

void crear_dic(tDiccionario* dic, int tam)
{
    //Recorro cada elemento e inicializo la lista para cada uno
    int pos=0;
    while(  dic+(sizeof(tDiccionario)*pos) < dic +(sizeof(tDiccionario)*tam)   )
    {
        crear_lista((dic+(sizeof(tDiccionario) * pos))->pl);
        pos++;
    }
}

int poner_dic(tDiccionario *dic, char *clave, char *valor)
{
    //Obtengo posicion
    int pos=tphash(clave);

    //Guardo la info en una estructura
    tInfo *info;

    iniInfo(info, clave, valor);

    //Inserto la estructura con los datos en la lista
    ///Falta que reemplaze el valor en caso de que la clave ya exista

    poner_ord_lista((dic+(sizeof(tDiccionario)*pos))->pl, info, sizeof(tInfo),cmp);

    //El calculo para saber la posicion en el vector puede ser una macro. "sizeof(tInfo)" tambien

    return 0;
}

int obtener_dic(tDiccionario* dic, char* clave, char* valor)
{
    int pos=tphash(clave);

    tInfo *info;
    iniInfo(info, clave, valor);

    //Funcion que retorna la info del nodo en el parametro que le paso
    vernodo((dic+(sizeof(tDiccionario)*pos))->pl, info, sizeof(tInfo));
            /// cuál es el parámetro??

    //Copio el valor en el parametro recibido para el retorno
    strcpy(valor, info->valor);
            /// acaso no se copia el valor en 'iniInfo'?

    return 0;
}

void sacar_dic(tDiccionario* dic, char* clave)
{
    int pos=tphash(clave);

    //Funcion que busca en la lista la clave y elimina el nodo
    eliminarNodo((dic+(sizeof(tDiccionario)*pos))->pl, clave);
}

int recorrer_dic(tDiccionario*, accion, int (*cmp)(const void*, const void*))
{
    //Recorro cada elemento
    int pos=0;
    while((dic+(sizeof(tDiccionario) * pos)) < dic +((sizeof(tDiccionario) * tam)))
    {
        tDiccionario->pl->info
        ///Aca va una funcion que recorra la lista y ejecute para cada elemento la accion que recibo como paramtro
        pos++;
    }
    return 0;
}

void destruir_dic(tDiccionario* dic, size_t tam)
{
    //Recorro cada elemento e inicializo la lista para cada uno
    int pos=0;
    while((dic+(sizeof(tDiccionario) * pos)) < dic +((sizeof(tDiccionario) * tam)))
    {

        ///Elimino la lista -> implica eliminar datos y liberar memoria
        eliminarLista((dic+(sizeof(tDiccionario) * pos))->pl);

        pos++;
    }
}
