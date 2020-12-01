/*CHIRICU Miruna-Catalina 312CB*/
#include "TCoada.h"
#include "TStiva.h"

#ifndef _STRUCT_
#define _STRUCT_

typedef struct lista {
	void *info;
	struct lista *urm;
} TCelula, *TLista, **ALista;

typedef struct memorie {
	unsigned short PID;
	unsigned incep_mem;
	unsigned dim_mem;
} TMem, *AMem;
	
typedef struct coada {
	size_t dime; //dim element
	TLista inc;
	TLista sf;
} TCoada, *ACoada;

#define INC(a) 	(((ACoada)(a))->inc)
#define SF(a) 	(((ACoada)(a))->sf)
#define DIME(a) (((ACoada)(a))->dime)

typedef struct stiva {
	size_t dime;
	TLista vf;
} TStiva, *AStiva;

#define VF(a) 	(((AStiva)(a))->vf)
#define DIMENS(a) (((AStiva)(a))->dime)

typedef struct proces {
	unsigned short PID; //mumăr natural cuprins între [1 - 32767]
	short int prioritate; //număr natural cuprins intre [0 - 127]
	unsigned timp_exec; //număr natural pozitiv pe 32 de biți
	unsigned cuanta;
	unsigned timp_ramas;
	unsigned long incep_mem;
	unsigned dim_mem; //număr natural pozitiv <= 3 * (1024 ^ 2)
	unsigned maxe; //max elem. din stiva procesului
	unsigned nr_elem;
	void* stiva_proc; //stiva procesului
} TProces, *AProces;

#endif