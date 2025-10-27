#include "diccionario.h"

int main()
{
    tDiccionario* hasmap=crear_dic(HASHSIZE);

    poner_dic(hasmap,"a","b",1);

    return 0;
}
