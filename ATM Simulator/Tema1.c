//Chiricu Miruna-Catalina
//312CB
#include "functii1.c" //alocare, inserare, afisare, distrugere, elim
//#include "operatii1.c"



int main () {
	LC lista_completa = NULL;
	//LSC q = NULL;
	int poz_max = 0, poz, old_poz_max = 0, nr_max_carduri, stats = 0, suma;
	char card_num[17], card_numb[17], card_dest[17], cvv[4];
	char p[20], pin[6], exp[6];
	int poz2, nr_carduri = 0, ok = 0;
	
	strcpy (card_numb, "0000");
	char input_filename[] = "input.in";
    FILE *in = fopen(input_filename, "rt");

    fscanf (in, "%d", &nr_max_carduri);
	char output_filename[] = "output.out";
    FILE *out = fopen(output_filename, "wt");

    while (fscanf (in, "%s", p) == 1) {

    	
		if (!strcmp (p, "show")) {
			fscanf (in, "%s", card_numb);

			
			if (strlen(card_numb) == 16) {
				if (feof(in))
					break;
				poz = suma_cifrelor (card_numb) % nr_max_carduri;
				printf("%d\n", poz);
				cautare (lista_completa, poz, card_numb, out);
				
			}
			else {
				
				afisare (lista_completa, poz_max, out);
				//fscanf (in, "%s", p);

				strcpy(p, card_numb);
			}

		}
		if (!strcmp (p, "add_card")) {
			fscanf (in, "%s", card_num);
			fscanf (in, "%s", pin);
			fscanf (in, "%s", exp);
			fscanf (in, "%s", cvv);

			//printf ("%s %s %s %s\n", card_num, pin, exp, cvv);
			poz = suma_cifrelor (card_num) % nr_max_carduri;
			//printf ("%d\n", poz);
			//nr_carduri++;
			if (nr_carduri == nr_max_carduri)
				if(search (lista_completa, card_num)) {
					//nr_carduri++;
					ok = 1;
					break;
				}
				else Aloclsc (&lista_completa, card_num, pin, exp, cvv,
				poz, poz_max, out);
			else if (Aloclsc (&lista_completa, card_num, pin, exp, cvv,
				poz, poz_max, out))
				nr_carduri++;

			if (poz > poz_max)
				poz_max = poz;
			//printf ("%d\n", poz_max);
			

		}
		
		if (!strcmp (p, "delete_card")) {
			//printf ("line 84");
			nr_carduri--;
			fscanf (in, "%s", card_num);
			//printf("%s\n", card_num );
			poz = suma_cifrelor (card_num) % nr_max_carduri;
			eliminare (&lista_completa, card_num, poz, old_poz_max);
			if (poz_max > old_poz_max)
				poz_max = old_poz_max;
			
		}
		old_poz_max = poz_max;

		if (!strcmp (p, "insert_card")) {
			fscanf (in, "%s %s", card_num, pin);
			poz = suma_cifrelor (card_num) % nr_max_carduri;
			
		if (!inv_pin (lista_completa, poz, card_num, pin, &stats, out))
				fprintf (out, "Invalid PIN\n");
			if (stats == -1)
				fprintf(out, "The card is blocked. Please"
					" contact the administrator.\n");

			

		}

		if (!strcmp (p, "cancel")) {
			fscanf (in, "%s ", card_num);
			poz = suma_cifrelor (card_num) % nr_max_carduri;
			cancel (lista_completa, poz, card_num, out);

		}

		if (!strcmp (p, "unblock_card")) {
			fscanf (in, "%s ", card_num);
			poz = suma_cifrelor (card_num) % nr_max_carduri;
			unblock_card (lista_completa, poz, card_num, out);

		}

		if (!strcmp (p, "pin_change")) {
			fscanf (in, "%s %s", card_num, pin);
			poz = suma_cifrelor (card_num) % nr_max_carduri;
			
			pin_change (lista_completa, poz, card_num, pin, out);
		}

		if (!strcmp (p, "balance_inquiry")) {
			fscanf (in, "%s", card_num);
			poz = suma_cifrelor (card_num) % nr_max_carduri;
			
			balance_inquiry (lista_completa, poz, card_num, out);
		}

		if (!strcmp (p, "recharge")) {
			fscanf (in, "%s %d", card_num, &suma);
			poz = suma_cifrelor (card_num) % nr_max_carduri;
			
			recharge (lista_completa, poz, card_num, suma, out);
		}

		if (!strcmp (p, "cash_withdrawal")) {
			fscanf (in, "%s %d", card_num, &suma);
			poz = suma_cifrelor (card_num) % nr_max_carduri;
			
			cash_withdrawal (lista_completa, poz, card_num, suma, out);
		}

		if (!strcmp (p, "transfer_funds")) {
			fscanf (in, "%s %s %d", card_num, card_dest, &suma);
			poz = suma_cifrelor (card_num) % nr_max_carduri;
			poz2 = suma_cifrelor (card_dest) % nr_max_carduri;
			
			transfer_funds (lista_completa, poz, poz2, card_num, 
				card_dest, suma, out);
		}

		if (!strcmp (p, "reverse_transaction")) {
			fscanf (in, "%s %s %d", card_num, card_dest, &suma);
			poz = suma_cifrelor (card_num) % nr_max_carduri;
			poz2 = suma_cifrelor (card_dest) % nr_max_carduri;
			printf("card_num %s card_dest %s\npoz %d poz2 %d\n",
			 card_num, card_dest, poz, poz2);
			reverse_transaction (lista_completa, poz, poz2, card_num, 
				card_dest, suma, out);
		}
		strcpy (card_numb, "0000");



	}
	
	printf("nr_carduri == %d\n", nr_carduri);

	
	while (nr_carduri > nr_max_carduri ||
		(nr_carduri == nr_max_carduri && ok)) {
		if (ok)
			nr_carduri++;
		ok = 0;
			nr_max_carduri = 2 * nr_max_carduri;
			printf("nr_carduri %d\n", nr_carduri);
			lista_completa = redimensionare (lista_completa, nr_max_carduri,
			 &poz_max, out);
			
			//printf("poz_max %d\n", poz_max);
			poz = suma_cifrelor (card_num) % nr_max_carduri;
			printf("card_num %s poz_main = %d\n", 
				card_num, poz);

			Aloclsc (&lista_completa, card_num, pin, exp, cvv,
				poz, poz_max, out);

			if (poz_max < poz)
				poz_max = poz;
		//	afisare (lista_completa, poz_max, out);

	while (fscanf (in, "%s", p) == 1) {
    	
		if (!strcmp (p, "show")) {
			fscanf (in, "%s", card_numb);

			//printf("p = %s car\n",p);
			if (strlen(card_numb) == 16) {
				if (feof(in))
					break;
				poz = suma_cifrelor (card_numb) % nr_max_carduri;
				//printf("%d\n", poz);
				cautare (lista_completa, poz, card_numb, out);
				
			}
			else {
				
				afisare (lista_completa, poz_max, out);
				//fscanf (in, "%s", p);

				strcpy(p, card_numb);
			}

		}
		if (!strcmp (p, "add_card")) {
			fscanf (in, "%s", card_num);
			fscanf (in, "%s", pin);
			fscanf (in, "%s", exp);
			fscanf (in, "%s", cvv);

			//printf ("%s %s %s %s\n", card_num, pin, exp, cvv);
			poz = suma_cifrelor (card_num) % nr_max_carduri;
			//printf ("%d\n", poz);
			
			if (nr_carduri == nr_max_carduri)
				if(search (lista_completa, card_num)) {
					nr_carduri++;
					break;
				}
				else Aloclsc (&lista_completa, card_num, pin, exp, cvv,
				poz, poz_max, out);
			else if (Aloclsc (&lista_completa, card_num, pin, exp, cvv,
				poz, poz_max, out))
				nr_carduri++;
					

				

			if (poz > poz_max)
				poz_max = poz;
			//printf ("%d\n", poz_max);
			

		}
		
		if (!strcmp (p, "delete_card")) {
			//printf ("line 84");
			fscanf (in, "%s", card_num);
		//	printf("%s\n", card_num );
			poz = suma_cifrelor (card_num) % nr_max_carduri;
			eliminare (&lista_completa, card_num, poz, old_poz_max);
			if (poz_max > old_poz_max)
				poz_max = old_poz_max;
			nr_carduri--;
		}
		old_poz_max = poz_max;

		if (!strcmp (p, "insert_card")) {
			fscanf (in, "%s %s", card_num, pin);
			poz = suma_cifrelor (card_num) % nr_max_carduri;
			
		if (!inv_pin (lista_completa, poz, card_num, pin, &stats, out))
				fprintf (out, "Invalid PIN\n");
			if (stats == -1)
				fprintf(out, "The card is blocked. Please"
					" contact the administrator.\n");

			

		}

		if (!strcmp (p, "cancel")) {
			fscanf (in, "%s ", card_num);
			poz = suma_cifrelor (card_num) % nr_max_carduri;
			cancel (lista_completa, poz, card_num, out);

		}

		if (!strcmp (p, "unblock_card")) {
			fscanf (in, "%s ", card_num);
			poz = suma_cifrelor (card_num) % nr_max_carduri;
			unblock_card (lista_completa, poz, card_num, out);

		}

		if (!strcmp (p, "pin_change")) {
			fscanf (in, "%s %s", card_num, pin);
			poz = suma_cifrelor (card_num) % nr_max_carduri;
			
			pin_change (lista_completa, poz, card_num, pin, out);
		}

		if (!strcmp (p, "balance_inquiry")) {
			fscanf (in, "%s", card_num);
			poz = suma_cifrelor (card_num) % nr_max_carduri;
			
			balance_inquiry (lista_completa, poz, card_num, out);
		}

		if (!strcmp (p, "recharge")) {
			fscanf (in, "%s %d", card_num, &suma);
			poz = suma_cifrelor (card_num) % nr_max_carduri;
			
			recharge (lista_completa, poz, card_num, suma, out);
		}

		if (!strcmp (p, "cash_withdrawal")) {
			fscanf (in, "%s %d", card_num, &suma);
			poz = suma_cifrelor (card_num) % nr_max_carduri;
			
			cash_withdrawal (lista_completa, poz, card_num, suma, out);
		}

		if (!strcmp (p, "transfer_funds")) {
			fscanf (in, "%s %s %d", card_num, card_dest, &suma);
			poz = suma_cifrelor (card_num) % nr_max_carduri;
			poz2 = suma_cifrelor (card_dest) % nr_max_carduri;
			
			transfer_funds (lista_completa, poz, poz2, card_num, 
				card_dest, suma, out);
		}

		if (!strcmp (p, "reverse_transaction")) {
			fscanf (in, "%s %s %d", card_num, card_dest, &suma);
			poz = suma_cifrelor (card_num) % nr_max_carduri;
			poz2 = suma_cifrelor (card_dest) % nr_max_carduri;
			printf("card_num %s card_dest %s\npoz %d poz2 %d\n",
			 card_num, card_dest, poz, poz2);
			reverse_transaction (lista_completa, poz, poz2, card_num, 
				card_dest, suma, out);
		}
		strcpy (card_numb, "0000");



	}
			
	}


	
	fclose(in);
	fclose(out);
	distrugere (&lista_completa, nr_max_carduri);
return 0;
}
