/*CHIRICU Miruna-Catalina 312CB*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include <time.h>

#ifndef _FUNCTII_
#define _FUNCTII_
  typedef int (* TF2)(const void *, const void *);
#endif

#ifndef STIVA
#define STIVA

void* InitS(size_t d);    
/* initializeaza stiva cu elem.de dimensiune */
int Push(void* a, void* ae);  
/* pune element in varful stivei */
int Pop (void* a, void* ae);  
/* extrage elementul din varful stivei la adresa ae */
int Top (void* a, void* ae);  
/* copiaza elementul din varful stivei la adresa ae */
int VidaS(void* a);           
/* test stiva vida */
void DistrS (void** aa);      
/* elibereaza intregul spatiu ocupat de stiva */
#endif
