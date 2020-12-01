//Chiricu Miruna-Catalina
//312CB
#include "tema1.h"

THis AlocHis (int rez, char *op) {
	THis aux = (THis)malloc(sizeof(THist));
	if (!aux) 
		return NULL;
	aux->rez_opera = rez;

	strcpy (aux->opera, op);
	aux->next_hist = NULL;
	return aux;
}

LSC AlocCard (char *card_num, char *pin, char *exp, char *cvv) {
	LSC aux = (LSC)malloc(sizeof(TSC));
	if (!aux)
		return NULL;
	strcpy(aux->card_nr, card_num);
	strcpy(aux->pin, pin);
	strcpy(aux->exp, exp);
	strcpy(aux->cvv, cvv);
	aux->balance = 0;
	aux->status = 0;
	aux->nr_pin_gresit = 0;

	aux->next_card = NULL;
	aux->history = NULL;
	return aux;
}

int search (LC L, char *card_numb) {
	LSC q;
	for (; L; L = L->next_lc)
		if (L->cards)
			for (q = L->cards; q; q = q->next_card)
				if (!strcmp(q->card_nr, card_numb)) {
					return 0;
				}
		
	return 1;
}

int Aloclsc (AC aL, char *card_num, char *pin, char *exp, 
			char *cvv, int poz, int poz_max, FILE *out) 
{
	int i;
	LC aux_lc = NULL;
	LSC ca = NULL;

	LC p = *aL;
	
	if (!p) {
		aux_lc = (LC)malloc(sizeof(LCel));
		if (!aux_lc) 
			return 0;
		*aL = aux_lc;

		if (poz == 0) {
			ca = AlocCard (card_num, pin, exp, cvv);
			if (!ca)
				return 0;
			(*aL)->cards = ca;
		}
		else (*aL)->cards = NULL;

		(*aL)->poz = 0;
		(*aL)->next_lc = NULL;
		p = *aL;
		for (i = 1; i <= poz; i++) {
			
			aux_lc = (LC)malloc(sizeof(LCel));

			if (!aux_lc) 
				return 0;

			aux_lc->cards = NULL;
			aux_lc->poz = i;
			aux_lc->next_lc = NULL;

			p->next_lc = aux_lc;
			p = p->next_lc;
			if (i == poz) {
				ca = AlocCard (card_num, pin, exp, cvv);
				if (!ca)
					return 0;
				p->cards = ca;
			
			}
			

		}
	}
	else if (poz > poz_max) {
		i = 0;
		while (i < poz_max) {
			p = p->next_lc;
			i++;
		}
		for (i = poz_max; i < poz; i++) {
			
			aux_lc = (LC)malloc(sizeof(LCel));

			if (!aux_lc) 
				return 0;

			aux_lc->cards = NULL;
			aux_lc->poz = i;
			aux_lc->next_lc = NULL;

			p->next_lc = aux_lc;
			p = p->next_lc;
			
			p->poz = i + 1;
		}
		if (i == poz) {
				ca = AlocCard (card_num, pin, exp, cvv);
				if (!ca)
					return 0;
				
				p->cards = ca;
				
			}
		
		
	} 
	else if (poz <= poz_max) {
		while (p && p->poz < poz)
			p = p->next_lc;
		ca = AlocCard (card_num, pin, exp, cvv);
		//ca->next_card = NULL;
		if (!ca)
			return 0;
		
		if (!p->cards) {
			p->cards = ca;
		}
		else {
			
				if (!search(p, ca->card_nr)) {
					fprintf (out, "The card already exists\n");
					free (ca);
					return 0;
					
				}

		
			
			ca->next_card = p->cards;
			p->cards = ca;
			
		
		}
	}

	return 1;
}

int Aloclsc2 (AC aL, char *card_num, char *pin, char *exp, 
			char *cvv, int poz, int poz_max, FILE *out) 
{
	int i;
	LC aux_lc = NULL;
	//printf("36 alocare1\n");
	LSC ca = NULL;

	LC p = *aL;
	LSC q = NULL;
	if (!p) {
		aux_lc = (LC)malloc(sizeof(LCel));
		if (!aux_lc) 
			return 0;
		*aL = aux_lc;

		if (poz == 0) {
			ca = AlocCard (card_num, pin, exp, cvv);
			if (!ca)
				return 0;
			(*aL)->cards = ca;
		}
		else (*aL)->cards = NULL;

		(*aL)->poz = 0;
		(*aL)->next_lc = NULL;
		p = *aL;
		for (i = 1; i <= poz; i++) {
			
			aux_lc = (LC)malloc(sizeof(LCel));

			if (!aux_lc) 
				return 0;

			aux_lc->cards = NULL;
			aux_lc->poz = i;
			aux_lc->next_lc = NULL;

			p->next_lc = aux_lc;
			p = p->next_lc;
			if (i == poz) {
				ca = AlocCard (card_num, pin, exp, cvv);
				if (!ca)
					return 0;
				p->cards = ca;
			
			}
			

		}
	}
	else if (poz > poz_max) {
		i = 0;
		while (i < poz_max) {
			p = p->next_lc;
			i++;
		}
		for (i = poz_max; i < poz; i++) {
			
			aux_lc = (LC)malloc(sizeof(LCel));

			if (!aux_lc) 
				return 0;

			aux_lc->cards = NULL;
			aux_lc->poz = i;
			aux_lc->next_lc = NULL;

			p->next_lc = aux_lc;
			p = p->next_lc;
			
			p->poz = i + 1;
		}
		if (i == poz) {
				ca = AlocCard (card_num, pin, exp, cvv);
				if (!ca)
					return 0;
				
				p->cards = ca;
				
			}
		
		
	} 
	else if (poz <= poz_max) {
		while (p && p->poz < poz)
			p = p->next_lc;
		ca = AlocCard (card_num, pin, exp, cvv);
		if (!ca)
			return 0;
		if (!p->cards)
			p->cards = ca;
		else {
			int ok = 1;
			for (q = p->cards; q; q = q->next_card) {
				if (!strcmp(q->card_nr, ca->card_nr))
					ok = 0;
				//printf ("line 117\n");
			}
			if (ok && p->cards->next_card) {
				ca->next_card = p->cards;
				p->cards = ca;
			}
			else if (ok) {
				p->cards->next_card = ca;
			}
			else  {fprintf (out, "The card already exists\n");
				free (ca);
			}
		}
	}

	return 1;
}



int invalid_pin (char *pin) {
	if (pin[0] < '0' || pin[0] > '9' || pin[1] < '0' || pin[1] > '9' ||
		pin[2] < '0' || pin[2] > '9' || pin[3] < '0' || pin[3] > '9')
		return 0;
	if (pin[4] != '\0')
		return 0;
	return 1;
}

int inv_pin (LC L, int poz, char *card_num, char *pin,
			int *stats, FILE *out)
{
	LSC p;
	THis q;
	int a = 1;

	

	while (L && L->poz < poz)
		L = L->next_lc;

	int ok = 1, ok2 = 1;
	if (L && L->cards)
	for (p = L->cards; p; p = p->next_card) {
		if (!strcmp(card_num, p->card_nr)) {
			if (strcmp(pin, p->pin))
				{	p->nr_pin_gresit++;
					ok = 0;
					if (p->nr_pin_gresit == 3) {

						p->status = -1;

					}
			}
			if (!invalid_pin(pin) || !ok || p->status == -1)
				a = 0;
			
			if (p->status == 0) 
				ok2 = 0;
			q = AlocHis (a, "insert_card");


			*stats = p->status;
			if (!q)
				return 0;

			if (p->history){
	
				
				q->next_hist = p->history;

				p->history = q;
				strcpy(p->history->pin_introdus, pin);

			}
			else { 
	
				p->history = q;
				strcpy(p->history->pin_introdus, pin);
				p->history->next_hist = NULL;
			}
			break;
		} 
	}

	if (!invalid_pin(pin) || !ok)
		return 0; 
	if (!ok2)
		fprintf(out, "You must change your PIN.\n");


	return 1;
}

void cancel (LC L, int poz, char *card_num, FILE *out) {
	LSC p;
	THis q;
	//int a = 1;

	

	while (L && L->poz < poz)
		L = L->next_lc;

	if (L && L->cards)
	for (p = L->cards; p; p = p->next_card) {
		if (!strcmp(card_num, p->card_nr)) {
			q = AlocHis (1, "cancel");
			if (!q)
				return;
			p->nr_pin_gresit = 0;
			if (p->history){
				q->next_hist = p->history;
				p->history = q;

			}
			else { 
	
				p->history = q;
				p->history->next_hist = NULL;
			}
			break;
		}
	}
}

void unblock_card (LC L, int poz, char *card_num, FILE *out) {
	LSC p;
	//int a = 1;

	

	while (L && L->poz < poz)
		L = L->next_lc;

	if (L && L->cards)
	for (p = L->cards; p; p = p->next_card) {
		if (!strcmp(card_num, p->card_nr)) {
			p->nr_pin_gresit = 0;
			p->status = 1;
		}
	}
}

void pin_change (LC L, int poz, char *card_num, char *pin, FILE *out) {
	LSC p;
	THis q;
	int ok = 1;
	//int a = 1;

	if (!invalid_pin(pin)) {
		ok = 0;
		fprintf (out, "Invalid PIN\n");
	}

	while (L && L->poz < poz)
		L = L->next_lc;

	if (L && L->cards)
	for (p = L->cards; p; p = p->next_card) {
		if (!strcmp(card_num, p->card_nr)) {
			if (ok) {
				strcpy (p->pin, pin);
				p->status = 1;
			}
			q = AlocHis (ok, "pin_change");
			if (!q)
				return;
			
			if (p->history){
				q->next_hist = p->history;
				p->history = q;
				strcpy(q->pin_introdus, pin);

			}
			else { 
	
				p->history = q;
				strcpy(q->pin_introdus, pin);
				p->history->next_hist = NULL;
			}
			break;


		}
	}
}

void balance_inquiry (LC L, int poz, char *card_num, FILE *out) {
	LSC p;
	THis q;
	//int a = 1;

	

	while (L && L->poz < poz)
		L = L->next_lc;

	if (L && L->cards)
	for (p = L->cards; p; p = p->next_card) {
		if (!strcmp(card_num, p->card_nr)) {
			fprintf(out, "%d\n", p->balance);

			q = AlocHis (1, "balance_inquiry");
			if (!q)
				return;
			if (p->history){
				q->next_hist = p->history;
				p->history = q;

			}
			else { 
	
				p->history = q;
				p->history->next_hist = NULL;
			}
			break;
		}
	}
}

void recharge (LC L, int poz, char *card_num, int suma, FILE *out) {
	LSC p;
	THis q;
	//int a = 1;

	

	while (L && L->poz < poz)
		L = L->next_lc;

	if (L && L->cards)
	for (p = L->cards; p; p = p->next_card) {
		if (!strcmp(card_num, p->card_nr)) {

			if (suma % 10 == 0) {
				q = AlocHis (1, "recharge");
				if (!q)
				return;

				if (p->history){
					q->next_hist = p->history;
					p->history = q;
					p->balance += suma;
					p->history->sum = suma;
				}
				else { 
					p->history = q;
					p->balance += suma;
					p->history->sum = suma;
					p->history->next_hist = NULL;
				}
				fprintf(out, "%d\n", p->balance);
			}
			
			else {
				q = AlocHis (0, "recharge");
				fprintf(out, "The added amount must be multiple of 10\n");
				if (!q)
					return;
				if (p->history){
					q->next_hist = p->history;
					p->history = q;
					p->history->sum = suma;

				}
				else { 
	
					p->history = q;
					p->history->sum = suma;
					p->history->next_hist = NULL;
				}
				break;
			}
				
		}
	}
}

void cash_withdrawal (LC L, int poz, char *card_num, int suma, 
	FILE *out) 
{
	LSC p;
	THis q;
	//int a = 1;

	

	while (L && L->poz < poz)
		L = L->next_lc;

	if (L && L->cards)
	for (p = L->cards; p; p = p->next_card) {
		if (!strcmp(card_num, p->card_nr)) {

			if (suma % 10 == 0) {
				if (suma <= p->balance) {
					q = AlocHis (1, "cash_withdrawal");
					if (!q)
					return;

					if (p->history){
						q->next_hist = p->history;
						p->history = q;
						p->balance -= suma;
						p->history->sum = suma;
					}
					else { 
						p->history = q;
						p->balance -= suma;
						p->history->sum = suma;
						p->history->next_hist = NULL;
					}
					fprintf(out, "%d\n", p->balance);
				}
				else {
					fprintf(out, "Insufficient funds\n");
					q = AlocHis (0, "cash_withdrawal");
					if (!q)
						return;
					if (p->history){
						q->next_hist = p->history;
						p->history = q;
						p->history->sum = suma;

					}
					else { 
	
						p->history = q;
						p->history->sum = suma;
						p->history->next_hist = NULL;
					}
				}
			}
			
			else {
				fprintf(out, "The requested amount must be multiple of 10\n");
				q = AlocHis (0, "cash_withdrawal");
				
				if (!q)
					return;
				if (p->history){
					q->next_hist = p->history;
					p->history = q;
					p->history->sum = suma;

				}
				else { 
	
					p->history = q;
					p->history->sum = suma;
					p->history->next_hist = NULL;
				}
			
			}
				
		}
	}
}

void transfer_funds (LC L, int poz, int poz2, char *card_num, char *card_numb,
	int suma, FILE *out) 
{	LC L2 = L;
	LSC p;
	THis q;
	int ok = 0;

	

	while (L && L->poz < poz)
		L = L->next_lc;

	if (L && L->cards)
	for (p = L->cards; p; p = p->next_card) {
		if (!strcmp(card_num, p->card_nr)) {

			if (suma % 10 == 0) {
				if (suma <= p->balance) {
					ok = 1;
					q = AlocHis (1, "transfer_funds");
					if (!q)
					return;

					if (p->history){
						q->next_hist = p->history;
						p->history = q;
						strcpy(p->history->card_dest, card_numb);
						strcpy(p->history->card_sursa, card_num);
						p->balance -= suma;
						p->history->sum = suma;
					}
					else { 
						p->history = q;
						p->balance -= suma;
						p->history->sum = suma;
						strcpy(p->history->card_dest, card_numb);
						strcpy(p->history->card_sursa, card_num);
						p->history->next_hist = NULL;
					}
					fprintf(out, "%d\n", p->balance);
				}
				else {
					fprintf(out, "Insufficient funds\n");
					q = AlocHis (0, "transfer_funds");
					if (!q)
						return;
					if (p->history){
						q->next_hist = p->history;
						p->history = q;
						strcpy(p->history->card_dest, card_numb);
						strcpy(p->history->card_sursa, card_num);
						p->history->sum = suma;

					}
					else { 
	
						p->history = q;
						p->history->sum = suma;
						strcpy(p->history->card_dest, card_numb);
						strcpy(p->history->card_sursa, card_num);
						p->history->next_hist = NULL;
					}
				}
			}
			
			else {
				fprintf(out,"The transferred amount must be multiple of 10\n");
				q = AlocHis (0, "transfer_funds");
				
				if (!q)
					return;
				if (p->history){
					q->next_hist = p->history;
					p->history = q;
					strcpy(p->history->card_dest, card_numb);
					strcpy(p->history->card_sursa, card_num);
					p->history->sum = suma;

				}
				else { 
	
					p->history = q;
					p->history->sum = suma;
					strcpy(p->history->card_dest, card_numb);
					strcpy(p->history->card_sursa, card_num);
					p->history->next_hist = NULL;
				}
			
			}
			break;	

		}
	}

	if(ok) {
		L = L2;
		while (L && L->poz < poz2)
			L = L->next_lc;

		if (L && L->cards)
		for (p = L->cards; p; p = p->next_card) {
			if (!strcmp(card_numb, p->card_nr)) {

					q = AlocHis (1, "transfer_funds");
					if (!q)
					return;

					if (p->history){
						q->next_hist = p->history;
						p->history = q;
						p->balance += suma;
						strcpy(p->history->card_dest, card_numb);
						strcpy(p->history->card_sursa, card_num);
						p->history->sum = suma;
					}
					else { 
						p->history = q;
						p->balance += suma;
						p->history->sum = suma;
						strcpy(p->history->card_dest, card_numb);
						strcpy(p->history->card_sursa, card_num);
						p->history->next_hist = NULL;
					}
				break;
				//fprintf(out, "%d\n", p->balance);
			}
		}
	}
}

void reverse_transaction (LC L, int poz, int poz2, char *card_num, 
	char *card_numb, int suma, FILE *out) 
{	LC L2 = L;
	LSC p;
	THis q, ant = NULL, aux;
	int ok = 0;

	while (L && L->poz < poz2)
		L = L->next_lc;

	if (L && L->cards)
	for (p = L->cards; p; p = p->next_card)
		if (!strcmp(card_numb, p->card_nr)) {

			if (suma <= p->balance) {
				ok = 1;
				p->balance -= suma;

				for (q = p->history, ant = NULL; q; ant = q, q = q->next_hist)
					if (!strcmp(q->opera, "transfer_funds") &&
						!strcmp (q->card_dest, card_numb)){
						if (ant == NULL) {
							aux = p->history;
							p->history = q->next_hist;
					
							free (aux);

						}
						else {
							ant->next_hist = q->next_hist;
							free(q);
						}
						break;

					}
				
			}
			break;
		}		
	L = L2;
	while (L && L->poz < poz)
	L = L->next_lc;

	if (L && L->cards)
		for (p = L->cards; p; p = p->next_card)
			if (!strcmp(card_num, p->card_nr)) {

				if (!ok) {
					fprintf(out, "The transaction cannot be reversed\n");
					
				}	
				else {
					q = AlocHis (1, "reverse_transaction");
					if (!q)
						return;
					if (p->history){
						q->next_hist = p->history;
						p->history = q;
						strcpy(p->history->card_dest, card_numb);
						strcpy(p->history->card_sursa, card_num);
						p->history->sum = suma;
						p->balance +=suma;
					}
					else { 
	
						p->history = q;
						p->history->sum = suma;
						strcpy(p->history->card_dest, card_numb);
						strcpy(p->history->card_sursa, card_num);
						p->history->next_hist = NULL;
						p->balance +=suma;
					}
				}
			}
}




void cautare (LC L, int poz, char *card_num, FILE *out) {
	LSC p;
	THis q;

	while (L && L->poz < poz)
		L = L->next_lc;

	if (L && L->cards)
	for (p = L->cards; p; p = p->next_card) {
		if (!strcmp(card_num, p->card_nr)) {
			fprintf(out, "(card number: %s, PIN: %s, expiry date: %s," 
	 				" CVV: %s, balance: %d, ", p->card_nr, p->pin, p->exp,
	 				p->cvv, p->balance);
	 			if (p->status == 0)
	 				fprintf (out, "status: NEW, ");
	 			else if (p->status == -1)
	 				fprintf (out, "status: LOCKED, ");
	 			else if (p->status == 1)
	 				fprintf (out, "status: ACTIVE, ");

	 			if (!p->history) {
	 					fprintf(out, "history: [])\n");
	 				}
	 				else {
	 					fprintf(out, "history: [");
	 					for (q = p->history; q != NULL; q = q->next_hist) {
	 						if (q->rez_opera)
	 							fprintf(out, "(SUCCESS, ");
	 						else fprintf(out, "(FAIL, ");
	 						if (!strcmp (q->opera, "insert_card"))
	 							fprintf(out, "insert_card %s %s)", 
	 								p->card_nr, q->pin_introdus);
	 						else if (!strcmp (q->opera, "cancel"))
	 							fprintf(out, "cancel %s)", p->card_nr);
	 						else if (!strcmp (q->opera, "pin_change"))
	 							fprintf(out, "pin_change %s %s)", p->card_nr,
	 								q->pin_introdus);
	 						else if (!strcmp (q->opera, "balance_inquiry"))
	 							fprintf(out, "balance_inquiry %s)", 
	 								p->card_nr);
	 						else if (!strcmp (q->opera, "recharge"))
	 							fprintf(out, "recharge %s %d)", 
	 								p->card_nr, q->sum);
	 						else if (!strcmp (q->opera, "cash_withdrawal"))
	 							fprintf(out, "cash_withdrawal %s %d)", 
	 								p->card_nr, q->sum);
	 						else if (!strcmp (q->opera, "transfer_funds"))
	 							fprintf(out, "transfer_funds %s %s %d)", 
	 								q->card_sursa, q->card_dest, q->sum);
	 						else if (!strcmp (q->opera, "reverse_transaction"))
	 							fprintf(out, "reverse_transaction %s %s %d)", 
	 								q->card_sursa, q->card_dest, q->sum);
	 						if (q->next_hist)
	 							fprintf(out, ", ");
	 					}
	 					fprintf(out, "])\n");
				}
		
		}
	}
}

void afisare (LC L, int poz_max, FILE *out) {
	int i;
	LSC p;
	THis q;
	if (L)
		for (i = 0; i <= poz_max; i++) {
	 		
		 	if (L->cards) {
		 		fprintf(out, "pos%d: [\n", i);
	 			for (p = L->cards; p!= NULL; p = p->next_card) {
	 				fprintf(out, "(card number: %s, PIN: %s, expiry date: %s," 
	 					" CVV: %s, balance: %d, ", p->card_nr, p->pin, p->exp,
		 				p->cvv, p->balance);
	 				if (p->status == 0)
	 					fprintf (out, "status: NEW, ");
	 				else if (p->status == -1)
		 				fprintf (out, "status: LOCKED, ");
		 			else if (p->status == 1)
	 					fprintf (out, "status: ACTIVE, ");

	 				if (!p->history) {
	 					fprintf(out, "history: [])\n");
	 				}
	 				else {
	 					fprintf(out, "history: [");
	 					for (q = p->history; q != NULL; q = q->next_hist) {
	 						if (q->rez_opera)
	 							fprintf(out, "(SUCCESS, ");
	 						else fprintf(out, "(FAIL, ");
	 						if (!strcmp (q->opera, "insert_card"))
	 							fprintf(out, "insert_card %s %s)", 
	 								p->card_nr, q->pin_introdus);
	 						else if (!strcmp (q->opera, "cancel"))
	 							fprintf(out, "cancel %s)", p->card_nr);
	 						else if (!strcmp (q->opera, "pin_change"))
	 							fprintf(out, "pin_change %s %s)", p->card_nr,
	 								q->pin_introdus);
	 						else if (!strcmp (q->opera, "balance_inquiry"))
	 							fprintf(out, "balance_inquiry %s)", 
	 								p->card_nr);
	 						else if (!strcmp (q->opera, "recharge"))
	 							fprintf(out, "recharge %s %d)", 
	 								p->card_nr, q->sum);
	 						else if (!strcmp (q->opera, "cash_withdrawal"))
	 							fprintf(out, "cash_withdrawal %s %d)", 
	 								p->card_nr, q->sum);
	 						else if (!strcmp (q->opera, "transfer_funds"))
	 							fprintf(out, "transfer_funds %s %s %d)", 
	 								q->card_sursa, q->card_dest, q->sum);
	 						else if (!strcmp (q->opera, "reverse_transaction"))
	 							fprintf(out, "reverse_transaction %s %s %d)",
	 							q->card_sursa, q->card_dest, q->sum);  
	 						if (q->next_hist)
	 							fprintf(out, ", ");
	 					}

	 					
	 					fprintf(out, "])\n");
	 				}	
	 			

	 			}

	 		fprintf(out, "]\n");
	 		}
	 		else fprintf(out, "pos%d: []\n", i);
	 		L = L->next_lc;
	 	}
}

void distrugere (AC L, int poz_max) {
	int i;
	LC aux3;
	LSC p, aux;
	THis q, aux2;
	if (*L)
		for (i = 0; i <= poz_max && (*L); i++) {
			if ((*L)->cards)
				for (p = (*L)->cards; p;) {
					if (p->history)
						for (q = p->history; q;) {
							aux2 = q;
							q = q->next_hist;
							free(aux2);
							printf("%d ", i);
						}
					aux = p;
					p = p->next_card;
					free (aux);
					printf("%d ", i);
				}
			aux3 = (*L);
			(*L) = (*L)->next_lc;
			free(aux3);
			printf("%d ", i);
		}
}

void eliminare (AC L, char *card_num, int poz, int old_poz_max) {
	LC p = *L, aux4;
	LSC ant = NULL, q = NULL;
	THis aux2, aux;

	while (p && p->poz < poz)
		p = p->next_lc;

	//printf ("poz = %d card_num = \n", p->poz, p->cards->card_nr);

	if (!p->cards) {
		
		return;
	}

	else {
		for (q = p->cards, ant = NULL; q; ant = q, q = q->next_card) {
			if (!strcmp(q->card_nr, card_num)) {

				break;
			}
				
		}
		
		if (q) {
			printf ("230 llll\n");
			if (q->history)
					for (aux2 = q->history; aux2;) {
						aux = aux2;
						aux2 = aux2->next_hist;
						free(aux);
							
					}
			
			if (!ant)
				if (q->next_card)
					p->cards = q->next_card;
				else p->cards = NULL;
			else ant->next_card = q->next_card;
			free (q);

				
		}
		

		
	}
	p = *L;
	while (p && p->poz < old_poz_max)
		p = p->next_lc;

	if (old_poz_max == 0) {
		p = p->next_lc;
	}
	for ( ; p && p->next_lc; ) {
		aux4 = p->next_lc;
		p->next_lc = p->next_lc->next_lc;
		p = p->next_lc;
		free (aux4);

	}
}

int suma_cifrelor (char *p) {
	int s = 0, i;
	for (i = 0; i < 17; i++)
		if (p[i] == '9') 
			s+= 9;
		else if (p[i] == '8')
			s+= 8;
		else if (p[i] == '7')
			s+= 7;
		else if (p[i] == '6')
			s+= 6;
		else if (p[i] == '5')
			s+= 5;
		else if (p[i] == '4')
			s+= 4;
		else if (p[i] == '3')
			s+= 3;
		else if (p[i] == '2')
			s+= 2;
		else if (p[i] == '1')
			s+= 1;
	
	return s;

}
void elim_inceput_lista (ASC aL) {
	LSC aux;
	aux = (LSC)malloc(sizeof(TSC));
	strcpy(aux->card_nr, (*aL)->next_card->card_nr);
	strcpy(aux->pin, (*aL)->next_card->pin);
	strcpy(aux->exp, (*aL)->next_card->exp);
	strcpy(aux->cvv, (*aL)->next_card->cvv);
	aux->balance = (*aL)->next_card->balance;
	aux->status = (*aL)->next_card->status;
	aux->nr_pin_gresit = (*aL)->next_card->nr_pin_gresit;
	aux->history = (*aL)->next_card->history;
	aux->next_card = (*aL)->next_card->next_card;
	*aL = aux;
}

LC redimensionare (LC L, int nr_max_carduri, int *poz_max, FILE *out) {
	LSC r, aux = NULL, s;
	LC p, aux_lc = NULL;
	int i, poz;
	
	p = L;
	for (i = 0; i <= *poz_max; i++) {
		if (p->cards) {
			for (r = p->cards; r; r = r->next_card) {
				s = (LSC)malloc(sizeof(TSC));
				if (!s)
					return NULL;
				strcpy(s->card_nr, r->card_nr);
				strcpy(s->pin, r->pin);
				strcpy(s->exp, r->exp);
				strcpy(s->cvv, r->cvv);
				s->balance = r->balance;
				s->status = r->status;
				s->nr_pin_gresit = r->nr_pin_gresit;
				s->history = r->history;
				if (!aux) {
					aux = s;
					aux->next_card = NULL;
				}
				else {
					s->next_card = aux;
					aux = s;
				}
			}
		}
		p = p->next_lc;
	}
	
	//distrugere(&L, *poz_max);

	for (s = aux; s; s = s->next_card) {
		poz = suma_cifrelor (s->card_nr) % nr_max_carduri;
		Aloclsc2 (&aux_lc, s->card_nr, s->pin, s->exp, s->cvv, poz, *poz_max, out);
		if (*poz_max < poz)
				*poz_max = poz;
	}

	p = aux_lc;
	for (i = 0; i < *poz_max; i++) {
		if (p->cards) {
			for (r = p->cards; r; r = r->next_card) {
				for (s = aux; s; s = s->next_card) 
					if (!strcmp(s->card_nr, r->card_nr)) {
						r->balance = s->balance;
						r->history = s->history;
					}
			}
		}
		p = p->next_lc;

	}

 	return aux_lc;
}

