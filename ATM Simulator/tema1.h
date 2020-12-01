//Chiricu Miruna-Catalina
//312CB
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef _ATM_
#define _ATM_

typedef struct history { 
	int rez_opera; //1 - SUCCESS, 0 - FAIL
	char opera[20];
	char pin_introdus[6], card_sursa[17], card_dest[17];
	int sum;
	struct history *next_hist;  
} THist, *THis, **AHis;

typedef struct card {
	char card_nr [17];
	char pin[6];
	char exp[6];
	char cvv[4];
	int balance;
	int status, nr_pin_gresit; //1 - ACTIVE, 0 - NEW, -1 - LOCKED
	THis history;
	struct card *next_card;
} TSC, *LSC, **ASC;

typedef struct lc {
	LSC cards;
	int poz;
	struct lc *next_lc;
	
} LCel, *LC, **AC;

#endif
