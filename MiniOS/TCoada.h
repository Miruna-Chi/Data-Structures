/*CHIRICU Miruna-Catalina 312CB*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include <time.h>

#ifndef _FUNCTII_
#define _FUNCTII_
  typedef int (*TF1)(void *);
  typedef int (*TF2)(void *, void *);
#endif

#ifndef COADA
#define COADA

void* InitQ(size_t d); 
/* creeaza coada vida cu elemente de dimensiune */
int IntrQ(void* a, void* ae); 
/* adauga element la sfarsitul cozii */
int ExtrQ(void* a, void* ae); 
/* extrage primul element din coada la adresa ae */
int VidaQ(void* a);           
/* test coada vida */
void DistrQ(void** aa);       
/* elibereaza intregul spatiu ocupat de coada */

#endif
