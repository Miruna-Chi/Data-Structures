/*CHIRICU Miruna-Catalina 312CB*/
#include "Struct.h"
#ifndef _FUNCTIIST_
#define _FUNCTIIST_

void* InitS(size_t d)
{ 
  AStiva a = (AStiva)malloc(sizeof(TStiva));
  /* adresa descriptor alocat */
    if (!a) 
    return NULL; 
    a->dime = d;
    VF(a) = NULL;
    return (void*)a;
}

/* test stiva vida */
int VidaS(void *a)               
{ 
  if (!VF(a))
    return 0;
  return 1;
}

/* pune element in varful stivei */
int Push(void *a, void *ae) {     
    TLista aux = NULL;
    aux = malloc (sizeof(TCelula));
    if (!aux)
        return 0;
    aux->info = malloc (sizeof(int));
    if (!aux->info) {
        free(aux);
        return 0;
    }
    memcpy (aux->info, ae, sizeof(int));

    /* copiaza elementul in varful stivei */

    if (!VF(a)) {
        aux->urm = NULL;
        VF(a) = aux;
    }
    else {
        aux->urm = VF(a);
        VF(a) = aux;/* deplaseaza varful stivei */
    }
  	return 1;
}

/* extrage elementul din varful stivei la adresa ae */
int Pop(void *a, void *ae) { 
	if(!VidaS(a)) 
		return 0;
    memcpy(ae, VF(a)->info, sizeof(int));  
    /* copiaza elementul scos din stiva */
    TLista aux = NULL;
    aux = VF(a);
    VF(a) = VF(a)->urm;
    free (aux->info);
    free(aux);
   /* deplaseaza varful stivei */
  return 1;
}

/* elibereaza intregul spatiu ocupat de stiva */
void DistrS(void **aa)           
{ 
    TLista aux = VF(*aa);
    while (aux) {

        VF(*aa) = VF(*aa)->urm;
        free(aux);
        aux = VF(*aa);
    }
    free((AStiva)(*aa));         
}

#endif