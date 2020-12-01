/*CHIRICU Miruna-Catalina 312CB*/
#include "Struct.h"
#include "functiiCoada-V.c"
#include "functiiStiva-V.c"
#include "functii.c"




void defrag (TLista proc_mem, ALista incep_dim,
	int max_pid, unsigned short PID, unsigned *incep_mem,
	unsigned dim_mem) {

	TLista p = NULL, ant = NULL;
	
	DistrugeLista(incep_dim);

			*incep_dim = malloc(sizeof(TCelula));
			if (!*incep_dim) {
				printf("Eroare la alocare\n");
				return;	
			}
			(*incep_dim)->info = malloc(sizeof(TMem));
			if (!(*incep_dim)->info) {
				printf("Eroare la alocare\n");
				return;	
			}
	for (p = proc_mem; p; p = p->urm) {
		((AProces)(p->info))->incep_mem = 
		add_lista (incep_dim, ((AProces)(p->info))->dim_mem,
			((AProces)(p->info))->PID);
		ant = p;
	
	}
		*incep_mem = ((AProces)(ant->info))->dim_mem 
			+ ((AProces)(p->info))->incep_mem;

}

int main(int argc, char *argv[]) { 
	void *coada_waiting = NULL, *coada_finished = NULL;
    TLista proc_mem = NULL;
    //proc_mem - lista tututor proceselor din memorie
    AProces run_proc = NULL;
    //run_proc - procesul care ruleaza la un moment dat
    short int T, prior = 0, *PIDuri = NULL, *All_PIDuri = NULL;
    /*T - cuanta, prior - prioritatea citita din fisier.
    *PIDuri = vector cu 0 si 1 care va stii ce procese exista in sistem
    (procesele terminate vor avea intrarea 0)
    *All_PIDuri = vector asemanator cu PIDuri, dar cand se termina un proces
    se adauga 1 la intrarea cu PIDul respectiv (retine numarul de dati in care
    a fost alocat acelasi PID)
    */
    int i, max_pid = -1, running = 0, elem_stiva= 0;
    //max_pid - nu vrem sa ne ducem pana la 32767 in vector
    //running - 0 sau 1: exista sau nu proces running la "add"
    unsigned dim_mem, t = 0, incep_mem = 0, ok = 0, dim_max = 3 *1024*1024;
    /* dim_mem = dimensiunea memoriei fiecarui proces
        incep_mem = inceputul memoriei fiecarui proces
    */
    unsigned long total_time = 0;
    unsigned short PID = 0; //PIDul procesului curent
    char p[20]; //va memora fiecare comanda
    TLista incep_dim;
    /*lista care va memora PIDul, inceputul memoriei si dimensiunea
    memoriei fiecarui proces (din cele neterminate)
    */

    PIDuri = calloc (32768, sizeof(short int)); 
    if (!PIDuri) {
    	printf("Eroare la alocare\n");
    	return 0;
    }
    //PIDurile proceselor curente


    All_PIDuri = calloc (32768, sizeof(short int));
    if (!All_PIDuri) {
    	free(PIDuri);
    	printf("Eroare la alocare\n");
    	return 0;
    }
    //toate PIDurile folosite in sistem (+terminate)
    

    size_t dim = sizeof (TProces);
	coada_waiting = InitQ(dim);
	if (!coada_waiting) {
		free(PIDuri);
    	free (run_proc);
    	free(All_PIDuri);
    
		printf("Eroare la alocare\n");
    	return 0;
	}
	coada_finished = InitQ(dim);
	if (!coada_finished) {
		free(PIDuri);
    	free (run_proc);
    	free(All_PIDuri);
    	DistrQ(&coada_waiting);
		printf("Eroare la alocare\n");
    	return 0;
	}

	incep_dim = malloc (sizeof(TCelula));
	if (!incep_dim) {
		free(PIDuri);
    	free (run_proc);
    	free(All_PIDuri);
    	DistrQ(&coada_waiting);
    	DistrQ(&coada_finished);
		printf("Eroare la alocare\n");
    	return 0;
	}
	

	incep_dim->info = (AMem)malloc(sizeof(TMem));
		if (!incep_dim->info) {
			printf("Eroare la alocare\n");
			return -2;	
		}
	((AMem)(incep_dim->info))->PID = 0;
		((AMem)(incep_dim->info))->incep_mem = -1;
		((AMem)(incep_dim->info))->dim_mem = 0;
		incep_mem = 0;
	incep_dim->urm = NULL;


    char in_file[10];
    strcpy (in_file, argv[1]);
    FILE *in = fopen(in_file, "rt");
	

   	char out_file[10];
    strcpy (out_file, argv[2]);
    FILE *out = fopen(out_file, "wt");

    fscanf (in, "%hd", &T);

    while (fscanf (in, "%s", p) == 1) {
        if (!strcmp(p, "add")) {

        	
            fscanf (in, "%u", &dim_mem);
            fscanf (in, "%d", &t);
            fscanf (in, "%hd", &prior);
            i = 0;
            while (PIDuri[i] != 0)
                i++;
            PID = i + 1;
            if (i + 1 > max_pid)
                max_pid = i + 1;
            PIDuri[i] = 1;
            //luam primul PID liber din vector
            ok = 0;
            if (dim_max < mem_sum(incep_dim) + dim_mem) {
                /* daca suma tuturor dimensiunilor proceselor din memorie
                + noua dimensiune a procesului de adaugat > dimensiunea
                maxima: nu se poate aloca memorie */
            	fprintf(out, "Cannot reserve memory for PID %hu.\n", PID);
            	PIDuri[i] = 0;
            	continue;
            }
            else {
            	incep_mem = add_lista(&incep_dim, dim_mem, PID);
            	if (incep_mem == -1)
            		ok = 0;
            	else ok = 1;
            	if (!ok)
            		defrag (proc_mem, &incep_dim, 
            			max_pid, PID, &incep_mem, dim_mem); 
                //adaugam dimensiuni in lista. daca nu putem => defrag
        	}
            
            add_proc_in_mem(&proc_mem, PID, prior, t, T, 
            	incep_mem, dim_mem, out);
            //adaugam procesul in memorie
           
            All_PIDuri[PID - 1]++;
            //++ la numarul intrarilor aceluiasi PID

            if (running == 0) {
           		running = 1;
           		if (run_proc)
           			free(run_proc);
           		run_proc = aloc_proc (PID, prior, t, T, incep_mem, dim_mem);
                //daca nu exista proces in running, cel nou va fi in running
                if (!run_proc) {
                	free(PIDuri);
    		      	free (run_proc);
    		      	free(All_PIDuri);
    		      	DistrQ(&coada_waiting);
        			DistrugeLista(&incep_dim);
	       			printf("Eroare la alocare\n");
    		      	return 0;
                }

           	}
           	else
           		add_coada_waiting(coada_waiting, proc_mem, PID, prior, t, out);
                //altfel este adaugat in waiting
           		
    	}
        else if (!strcmp(p, "get")) {
        	fscanf (in, "%hu", &PID);
            /* ne folosim de vectorii de PID si de procesul in running
            pentru a nu cauta inutil in lista de memorie*/
          	if (All_PIDuri[PID - 1] == 0)
            	fprintf(out, "Process %hu not found.\n", PID);
          	
          	else if (run_proc->PID == PID) {
            	fprintf(out, "Process %hu is running (remaining_time: ",
            		PID);
            	t = run_proc->timp_ramas;
            	fprintf (out, "%u).\n", t);
         	} 
       		else if (PIDuri[PID - 1] == 1) {
           		fprintf(out, "Process %hu is waiting (remaining_time: ",
           			PID);
           		t = search_proc_mem (proc_mem, PID);
                //daca e necesar, cautam in lista de memorie
           		fprintf (out, "%u).\n", t);
           	}
           	if (All_PIDuri[PID - 1] != 0 && PIDuri[PID - 1] == 0) {
          		for (i = 0; i < All_PIDuri[PID - 1]; i++)
            		fprintf(out, "Process %hu is finished.\n", PID);
          	}
          	else if (All_PIDuri[PID - 1] != 0 && PIDuri[PID - 1] != 0) {
          		for (i = 0; i < All_PIDuri[PID - 1] - 1; i++)
            		fprintf(out, "Process %hu is finished.\n", PID);
          	}
      	} 
      	else if (!strcmp(p, "push")) {
        	fscanf (in, "%hu", &PID);
          	fscanf (in, "%d", &elem_stiva);
         	if (PIDuri[PID - 1] == 0)
            	fprintf(out, "PID %hu not found.\n", PID);
           
          	else 
            	add_elem_stiva(proc_mem, elem_stiva, PID, out);
           		
        }
        else if (!strcmp(p, "pop")) {
        	fscanf (in, "%hu", &PID);
          	if (PIDuri[PID - 1] == 0)
            	fprintf(out, "PID %hu not found.\n", PID);
           
          	else {
            	rem_elem_stiva(proc_mem, PID, out);
          	}
        }
        else if (!strcmp(p, "print")) {
          	fscanf (in, "%s", p);
          	if (!strcmp(p, "waiting")) {
            	print_cw (coada_waiting, out);

        	}
        	else if (!strcmp(p, "finished"))
            	print_cf (coada_finished, out);
          	else if (!strcmp(p, "stack")) {

            	fscanf (in, "%hu", &PID);
            	if (PIDuri[PID - 1] == 0)
            		fprintf(out, "PID %hu not found.\n", PID);
            	else if (run_proc->PID == PID || PIDuri[PID - 1] == 1) {
              		
              		print_stack(proc_mem, PID, out);
              	//cauta in proc_mem. adauga elem
              	}
              	else if (All_PIDuri[PID - 1] != 0 && PIDuri[PID - 1] == 0) {
              		for (i = 0; i < All_PIDuri[PID - 1]; i++)
            			fprintf(out, "Empty stack PID %u.\n", PID);
                    //printeaza stackul de cate ori a gasit procesul 
                    //(useful All_PIDuri)
            	}
            	else if (All_PIDuri[PID - 1] != 0 && PIDuri[PID - 1] == 1) {
              		for (i = 0; i < All_PIDuri[PID - 1] - 1; i++)
            			fprintf(out, "Empty stack PID %u.\n", PID);
                    //printeaza stackul de cate ori a gasit procesul terminat
                    //(useful All_PIDuri)

            	}
         	}
        }
        else if (!strcmp(p, "run")) {
        	fscanf (in, "%u", &t);
        	run (&proc_mem, coada_waiting, coada_finished, T, t, 
        	run_proc, &running, PIDuri, &incep_dim, out);

        }
        else if (!strcmp(p, "finish")) {
        	total_time = tot_timp(proc_mem);
        	fprintf(out, "Total time: %lu\n", total_time);
        	
        }
          
        

    }
   

    free(PIDuri);
    free (run_proc);
    free(All_PIDuri);
    
    DistrugeLista(&incep_dim);
    DistrugeProcMem (&proc_mem);
    DistrQ(&coada_waiting);
    DistrQ(&coada_finished);
   
    


    fclose(in);
    fclose(out);
  	return 0;
}
