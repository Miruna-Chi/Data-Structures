/*CHIRICU Miruna-Catalina 312CB*/
#include "Struct.h"

#ifndef _FUNCTIICO_
#define _FUNCTIICO_

void* InitQ(size_t d)
{ 
	ACoada a = (ACoada)malloc(sizeof(TCoada));
	/* adresa descriptor alocat */
  	if (!a) 
		return NULL; 

 	a->dime = d;
  	a->sf = a->inc = NULL;
  	return (void*)a;
}

/* adauga element la sfarsitul cozii */
int IntrQ(void *a, void *ae)   
{ 
	TLista aux = NULL;
  	aux = (TLista)malloc(sizeof (TCelula));
  	if (!aux)
  		return 0;
  	aux->urm = NULL;
  	aux->info = malloc (DIME(a));

  	if (!aux->info) {
  		free (aux);
  		return 0;
  	}

  	memcpy (aux->info, ae, DIME(a));
  	if (INC(a)) {
  		SF(a)->urm = aux;
  		SF(a) = SF(a)->urm;
  	}
  	else {
  		SF(a) = INC(a) = aux;
  	}
  	/* copiaza elementul la sfarsitul cozii */
  	/* sfarsitul cozii avanseaza */
  	return 1;
}
/* extrage primul element din coada la adresa ae */
int ExtrQ (void *a, void *ae) {
	if (!INC(a)) 
		return 0;
	memcpy (ae, INC(a)->info, DIME (a));
	/* copiaza elementul de la inceputul cozii */
	TLista aux = NULL;
	aux = INC(a);
	INC(a) = INC(a)->urm;
	free (aux->info);
	free(aux);
	
	/* inceputul cozii avanseaza */
	return 1;
} 

/* test coada vida */
int VidaQ(void *a)         
{ 
	if (!INC(a)) 
		return 0;
	return 1;
}

/* elibereaza intregul spatiu ocupat de coada */
void DistrQ(void **aa) { 
	TLista aux = INC(*aa);
	while (INC(*aa) != NULL) {

		INC(*aa) = INC(*aa)->urm;
		if (aux) {
			if (aux->info)
				free(aux->info);
			free(aux);
		}
		aux = INC(*aa);
	}
	free(*aa);
}

#endif