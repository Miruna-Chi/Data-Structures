/*CHIRICU Miruna-Catalina 312CB*/
#include "Struct.h"
#include "functiiCoada-V.c"
#include "functiiStiva-V.c"


#ifndef _TEMA_
#define _TEMA_


unsigned add_lista (ALista incep_dim, unsigned dim_mem, 
	unsigned short PID) {

	unsigned incep_mem = 0;
	unsigned mem_sum = 0;
	TLista p = *incep_dim;
	TLista aux = NULL;
	if (dim_mem > 3 * 1024 * 1024)
		return -1;
	if (((AMem)(p->info))->incep_mem == -1) {
		
		((AMem)(p->info))->PID = PID;
		((AMem)(p->info))->incep_mem = 0;
		((AMem)(p->info))->dim_mem = dim_mem;
		incep_mem = 0;
		p->urm = NULL;
		return 0;
	}
	if (((AMem)(p->info))->incep_mem > 0) {
		if (dim_mem <= ((AMem)(p->info))->incep_mem) {
			
			aux = malloc(sizeof(TCelula));
			if (!aux) {
				printf("Eroare la alocare\n");
				return -2;	
			}
			aux->info = malloc(sizeof(TMem));
			if (!aux->info) {
				printf("Eroare la alocare\n");
				return -2;	
			}
			((AMem)(aux->info))->PID = PID;
			((AMem)(aux->info))->incep_mem = 0;
			((AMem)(aux->info))->dim_mem = dim_mem;
			incep_mem = 0;
			aux->urm = *incep_dim; 
			(*incep_dim) = aux;
			return 0;
		}
	}
	//printf("AJUTOOOR!\n");

	while (p && p->urm) {
		mem_sum += ((AMem)(p->info))->dim_mem;
		if (mem_sum + dim_mem > 3 * 1024 * 1024)
			return -1;
		if ((((AMem)(p->info))->incep_mem
			+ ((AMem)(p->info))->dim_mem) + dim_mem
			<=  (((AMem)(p->urm->info))->incep_mem)) {

			aux = malloc(sizeof(TCelula));
			if (!aux) {
				printf("Eroare la alocare\n");
				return -2;	
			}
			aux->info = malloc(sizeof(TMem));
			if (!aux->info) {
				printf("Eroare la alocare\n");
				return -2;	
			}
			((AMem)(aux->info))->PID = PID;
			((AMem)(aux->info))->incep_mem = 
				((AMem)(p->info))->incep_mem
				+ ((AMem)(p->info))->dim_mem;
			incep_mem = ((AMem)(aux->info))->incep_mem;

			((AMem)(aux->info))->dim_mem = dim_mem;
			
			aux->urm = p->urm;
			p->urm = aux;
			return incep_mem;
		}

		p = p->urm;
	}
	
		while (p->urm) {
			p = p->urm;
		}
		
		aux = malloc(sizeof(TCelula));
			if (!aux) {
				printf("Eroare la alocare\n");
				return -2;	
			}
			aux->info = malloc(sizeof(TMem));
			if (!aux->info) {
				free(aux);
				printf("Eroare la alocare\n");
				return -2;	
			}
			((AMem)(aux->info))->PID = PID;
			((AMem)(aux->info))->incep_mem = 
				((AMem)(p->info))->incep_mem
				+ ((AMem)(p->info))->dim_mem;
			incep_mem = ((AMem)(aux->info))->incep_mem;
			((AMem)(aux->info))->dim_mem = dim_mem;
			aux->urm = NULL;
			p->urm = aux;
	
	return incep_mem;
}

void rem_lista (ALista incep_dim, unsigned short PID) {
	TLista p = NULL, ant = NULL, aux = NULL;

	for (p = *incep_dim; p; ant = p, p = p->urm) {
		if (((AMem)(p->info))->PID == PID) {
			if (!ant) {
				aux = p;
				*incep_dim = p->urm;
				free(aux->info);
				free(aux);
				break;
			}
			else {
				aux = p;
				ant->urm = p->urm;
				free(aux->info);
				free (aux);
				break;
			}
		}
	}
	
	if (!(*incep_dim)) {
		*incep_dim = malloc (sizeof(TCelula));
		if (!*incep_dim) {
			printf("Eroare la alocare\n");
			return;	
		}
		(*incep_dim)->info = (AMem)malloc(sizeof(TMem));
		if (!(*incep_dim)->info) {
			printf("Eroare la alocare\n");
			return;	
		}

		((AMem)((*incep_dim)->info))->PID = 0;
		((AMem)((*incep_dim)->info))->incep_mem = -1;
		((AMem)((*incep_dim)->info))->dim_mem = 0;
		
		(*incep_dim)->urm = NULL;

		
	}

}

unsigned mem_sum (TLista incep_dim) {
	TLista p = NULL;
	unsigned mem = 0;
	for (p = incep_dim; p; p = p->urm) {
		if (p && p->info) 
			if (((AMem)(p->info))->dim_mem)
			mem+= ((AMem)(p->info))->dim_mem;
	}
	return mem;

}

void DistrugeLista (ALista incep_dim) {
	TLista p = NULL, aux = NULL;
	for (p = *incep_dim; p; ) {
		aux = p;
		p = p->urm;
		free(aux->info);
		free(aux);
	}
}

AProces aloc_proc (unsigned short PID, short int prior, unsigned t,
	unsigned T, unsigned long incep_mem, unsigned dim_mem) {

	AProces aux_proc = NULL;
	aux_proc = malloc (sizeof (TProces));
	if (!aux_proc)
		return NULL;
	
	aux_proc->PID = PID;
	aux_proc->prioritate = prior;
	aux_proc->timp_exec = t;
	aux_proc->timp_ramas = t;
	aux_proc->cuanta = T;
	aux_proc->incep_mem = incep_mem;
	aux_proc->dim_mem = dim_mem;
	aux_proc->maxe = dim_mem/4;
	aux_proc->nr_elem = 0;
	return aux_proc;
}

AProces add_proc_in_mem (ALista proc_mem, unsigned short PID, short int prior, 
	unsigned t, unsigned T, unsigned long incep_mem, unsigned dim_mem, 
	FILE *out) {

	TLista aux = NULL;
	aux = (TLista) malloc (sizeof (TCelula));
	if (!aux)
		return NULL;
	AProces aux_proc = NULL;
	aux_proc = malloc (sizeof (TProces));
	if (!aux_proc)
		return NULL;
	
	aux_proc->PID = PID;
	aux_proc->prioritate = prior;
	aux_proc->timp_exec = t;
	aux_proc->timp_ramas = t;
	aux_proc->cuanta = T;
	aux_proc->incep_mem = incep_mem;
	aux_proc->dim_mem = dim_mem;
	aux_proc->maxe = dim_mem/4;
	aux_proc->nr_elem = 0;
	aux_proc->stiva_proc = InitS (4);
	
	aux->info = aux_proc;

	TLista p = *proc_mem, r = *proc_mem, ant = NULL;
	if (r == NULL) {
		*proc_mem = aux;
		(*proc_mem)->urm = NULL;
	}
	else {
		for (; p != NULL; ant = p, p = p->urm) 
			if ((unsigned short)(((AProces)(p->info))->PID) > aux_proc->PID)
				break;
	

		if (!ant && r) {
			aux->urm = r;
			*proc_mem = aux;
		}
		else if (ant){
			aux->urm = p;
			ant->urm = aux;
			aux->urm = p;
		}
	}
	fprintf(out, "Process created successfully: PID: %hu, "
		"Memory starts at 0x%lx.\n", 
		(unsigned short)(aux_proc->PID),
		(unsigned long)(aux_proc->incep_mem));

	return aux_proc;
}

void print_stack (TLista proc_mem, unsigned short PID, FILE *out) {
	TLista p = NULL;
	p = proc_mem;
	void *ae = NULL;
	void *saux = NULL;

	saux = InitS (sizeof(int));
	if (!saux) 
		return;
	ae = malloc (sizeof(int));
	if (!ae) {
		free (saux);
		return;
	}

	for (; p; p = p->urm) 
		if (((AProces)p->info)->PID == PID) 
			break;
	if (!VidaS(((AProces)(p->info))->stiva_proc)) {

		fprintf(out, "Empty stack PID %u.\n", 
			((AProces)p->info)->PID);
		free(ae);
		DistrS(&saux);
		return;
	}
	fprintf(out, "Stack of PID %d:",
		(unsigned short)(((AProces)p->info)->PID));

	while (VF(((AProces)(p->info))->stiva_proc)) {
	
		Pop((((AProces)(p->info))->stiva_proc), ae);
		Push (saux, ae);		
	}
	

	while (VF(saux)) {
		Pop (saux, ae);
		fprintf(out, " %d", (*(int*)ae));
		Push((((AProces)(p->info))->stiva_proc), ae);
		
	}
	fprintf(out, ".\n");
	free(ae);
	DistrS(&saux);
}


int add_elem_stiva (TLista proc_mem, int elem_stiva, unsigned short PID,
	FILE *out) {

	int *ae = NULL;
	ae = (int*) malloc (sizeof(int));
	if (!ae)
		return 1;
	*ae = elem_stiva;

	TLista p = NULL;
	p = proc_mem;
	for (; p; p = p->urm) 
		if (((AProces)(p->info))->PID == PID) {
			
			break;
		}
	if (!p) {
		return 0;
	}
	if (((AProces)(p->info))->nr_elem ==
		((AProces)(p->info))->maxe){
		fprintf(out, "Stack overflow PID %u.\n", ((AProces)(p->info))->PID);
		free(ae);
		return 0;
	}
	Push(((AProces)(p->info))->stiva_proc, ae);
	((AProces)(p->info))->nr_elem++;
	free(ae);
	return 1;
}

int rem_elem_stiva (TLista proc_mem, unsigned short PID, FILE *out) {
	TLista p = NULL;
	p = proc_mem;
	int *ae = NULL;
	ae = (int*)malloc (sizeof(int));
	if (!ae)
		return 0;
	for (; p; p = p->urm) 
		if (((AProces)(p->info))->PID == PID) 
			break;
	if (!p) {
		return 0;
	}
	if (!VidaS((((AProces)(p->info))->stiva_proc))) {
		fprintf(out, "Empty stack PID %u.\n", 
			((AProces)p->info)->PID);
		free(ae);
		return 0;
	}
	//printf("To pop or not to pop? 206\n");
	Pop((((AProces)(p->info))->stiva_proc), ae);
	((AProces)(p->info))->nr_elem--;
	free(ae);
	return 1;
}

void print_cw (void *coada_waiting, FILE *out) {
	void *caux = NULL, *ae = NULL;
	size_t dim = sizeof (TProces);
	int ok = 0;
	caux = InitQ(dim);
	ae = (AProces)malloc (sizeof(TProces));
	if (!ae) {
		DistrQ (&caux);
		return;
	}

	fprintf(out, "Waiting queue:\n[");
	while (INC(coada_waiting)) {
		ExtrQ(coada_waiting, ae);
		IntrQ(caux, ae);
	}
	while (INC(caux)) {
		if (ok)
			fprintf(out, ",\n");
		ok = 1;
			ExtrQ (caux, ae);
			fprintf(out, "(%hu: priority = %hd, remaining_time = %u)",
				((AProces)ae)->PID, 
				((AProces)(ae))->prioritate,
				((AProces)ae)->timp_ramas);
		
			IntrQ (coada_waiting, ae);
		}

	fprintf(out, "]\n");
	

	free (ae);
	DistrQ(&caux);

}

void add_coada_waiting (void *coada_waiting, TLista proc_mem, 
	unsigned short PID, short int prior, unsigned t, FILE *out) {
	TLista p = NULL;
	p = proc_mem;
	void *caux = NULL, *caux2 = NULL, *ae = NULL;
	size_t dim = sizeof (TProces);
	caux = InitQ(dim);
	if (!caux)
		return;
	caux2 = InitQ(dim);
	if (!caux2) {
		DistrQ(&caux);
		return;
	}
	ae = (AProces)malloc (sizeof(TProces));
	if (!ae) {
		DistrQ(&caux);
		DistrQ(&caux2);
		return;
	}

	while (p && ((AProces)(p->info))->PID != PID)
		p = p->urm;
	if (p) {
			
		while (INC(coada_waiting) && ((AProces)(INC(coada_waiting)->info))->
			prioritate > prior) { 
			//cat timp nu intalneste elem. cu prioritate mai mica decat a sa
			ExtrQ (coada_waiting, ae);
			IntrQ (caux, ae);
		}
		if (!INC(coada_waiting)) { 
			//daca a ajuns la inceputul cozii, introducem elem. la inc
			
			while (INC(caux)) {
				ExtrQ (caux, ae);
				IntrQ(coada_waiting, ae);
			}
			IntrQ (coada_waiting, p->info);
			free (ae);
			DistrQ(&caux);
			DistrQ(&caux2);
			return;
		}
			/* daca prioritatea elem. la care a ajuns e mai mica 
			decat a sa, poate trece la inserare */
			
		else if (INC(coada_waiting) && ((AProces)(INC(coada_waiting)->info))
			->prioritate == prior) {
			/* daca prioritatea elem. la care a ajuns e egala cu a sa
			verifica relatia cu timpul */
			/* daca timpul ramas al elem. la care a ajuns e mai mare decat
			al sau, poate trece la inserare */
			if (((AProces)(INC(coada_waiting)->info))->timp_ramas < t) {
			/* daca timpul ramas al elem. la care a ajuns e mai mic decat
			al sau, extragem elemente pana cand ajungem la alta prioritate
			sau la un timp_ramas mai mare decat t */
				while (INC(coada_waiting) && 
					((AProces)(INC(coada_waiting)->info))->prioritate == prior
					&& ((AProces)(INC(coada_waiting)->info))->timp_ramas < t){
					ExtrQ (coada_waiting, ae);
					IntrQ (caux, ae);
				}
				if (INC(coada_waiting) && 
					((AProces)(INC(coada_waiting)->info))->prioritate == prior
					&& ((AProces)(INC(coada_waiting)->info))->timp_ramas == t){

					while (INC(coada_waiting) && 
					((AProces)(INC(coada_waiting)->info))->prioritate == prior
					&& ((AProces)(INC(coada_waiting)->info))->timp_ramas == t
					&& ((AProces)(INC(coada_waiting)->info))->PID < PID) {
						ExtrQ (coada_waiting, ae);
						IntrQ (caux, ae);
					}
				}
			}
			else	if (INC(coada_waiting) && 
					((AProces)(INC(coada_waiting)->info))->prioritate == prior
					&& ((AProces)(INC(coada_waiting)->info))->timp_ramas == t){

					while (INC(coada_waiting) && 
					((AProces)(INC(coada_waiting)->info))->prioritate == prior
					&& ((AProces)(INC(coada_waiting)->info))->timp_ramas == t
					&& ((AProces)(INC(coada_waiting)->info))->PID < PID) {
						ExtrQ (coada_waiting, ae);
						IntrQ (caux, ae);
					}
				}
					
		}
	}
	
	while (INC(coada_waiting)) {
		ExtrQ (coada_waiting, ae);
		IntrQ(caux2, ae);
	}
	while (INC(caux)) {
		ExtrQ (caux, ae);
		IntrQ(coada_waiting, ae);
	}
	IntrQ (coada_waiting, p->info);
	while (INC(caux2)) {
		ExtrQ (caux2, ae);
		IntrQ(coada_waiting, ae);
	}

	free (ae);
	DistrQ(&caux);
	DistrQ(&caux2);
}

void print_cf (void *coada_finished, FILE *out) {
	void *caux = NULL, *ae = NULL;
	size_t dim = sizeof (TProces);
	int ok = 0;

	caux = InitQ(dim);
	ae = (AProces)malloc (sizeof(TProces));
	if (!ae) {
		DistrQ (&caux);
		return;
	}

	fprintf(out, "Finished queue:\n[");
	while (INC(coada_finished)) {
		ExtrQ(coada_finished, ae);
		IntrQ(caux, ae);
	}
	while (INC(caux)) {
		if (ok)
			fprintf(out, ",\n");
		ok = 1;
			ExtrQ (caux, ae);
			fprintf(out, "(%hu: priority = %hd, executed_time = %u)",
				(unsigned short)(((AProces)ae)->PID), 
				(short int)(((AProces)(ae))->prioritate),
				(unsigned)(((AProces)ae)->timp_exec));
			IntrQ (coada_finished, ae);
		}
	
	fprintf(out, "]\n");
	free ((AProces)(ae));
	DistrQ(&caux);

}

int update_timp_lista (ALista proc_mem, unsigned short PID, unsigned T) {
	TLista p = NULL;
	
	for (p = *proc_mem; p; p = p->urm) {
		if (((AProces)(p->info))->PID == PID) 
			((AProces)(p->info))->timp_ramas = T;
		
	}
	return 1;
}

int tot_timp (TLista proc_mem) {
	TLista p = NULL;
	p = proc_mem;
	int total_time = 0;
	for (; p; p = p->urm) {
		total_time += ((AProces)(p->info))->timp_ramas;
	}
	return total_time;
}

unsigned search_proc_mem (TLista proc_mem, unsigned short PID) {
	TLista p = NULL;
	p = proc_mem;
	for (; p; p = p->urm) {
		if ((unsigned short)(((AProces)p->info)->PID) == PID) 
			return (unsigned)(((AProces)p->info)->timp_ramas);
	}
	return 0;
}

int del_elem_lista (ALista proc_mem, unsigned short PID) {
	TLista p = *proc_mem, ant = NULL, aux2 = NULL, aux = NULL;
	
	if (p && ((AProces)(p->info))->PID == PID) {
		aux = p;
		*proc_mem = (*proc_mem)->urm;
		while (((AStiva)(((AProces)(aux->info))->stiva_proc))->vf) {
			aux2 = ((AStiva)(((AProces)(aux->info))->stiva_proc))->vf;
			((AStiva)(((AProces)(aux->info))->stiva_proc))->vf = 
			((AStiva)(((AProces)(aux->info))->stiva_proc))->vf->urm;
			free(aux2->info);
			free(aux2);
		}
		free (((AProces)(aux->info))->stiva_proc);
		free (aux->info);
		free (aux);
	}
	else {
		while  (p && ((AProces)(p->info))->PID != PID) {
			ant = p;
			p = p->urm;
			
		}
		if (p) {
			aux = p;
			ant->urm = p->urm;
			while (((AStiva)(((AProces)(aux->info))->stiva_proc))->vf) {
				aux2 = ((AStiva)(((AProces)(aux->info))->stiva_proc))->vf;
				((AStiva)(((AProces)(aux->info))->stiva_proc))->vf = 
				((AStiva)(((AProces)(aux->info))->stiva_proc))->vf->urm;
				free(aux2->info);
				free(aux2);
			}
			free (((AProces)(aux->info))->stiva_proc);
			free (aux->info);
			free (aux);
		}
	}

	return 0;
}


void run (ALista proc_mem, void *coada_waiting, void *coada_finished, 
	unsigned T, unsigned t, AProces run_proc, int *running,
	short *PIDuri, ALista incep_dim, FILE *out) {
	void *ae = NULL;
	ae = (AProces) malloc (sizeof(TProces));
	if (!ae)
		return;
	//cazurile urmatoare - explicate in README
	while (*running == 1 && t > 0) {
		if (run_proc->timp_ramas > run_proc->cuanta) {
			if (T < t) {
				//nu se poate termina procesul
				run_proc->timp_ramas = run_proc->timp_ramas - run_proc->cuanta;
				//scade timpul_ramas al procesului
				t = t - run_proc->cuanta;
				//scade timpul total
				run_proc->cuanta = T;
				//se reseteaza cuanta
				update_timp_lista(proc_mem, run_proc->PID, 
					run_proc->timp_ramas);
				//se updateaza timpul_ramas in lista
				memcpy (ae, run_proc, sizeof(TProces));
				if (INC(coada_waiting)) {
					//daca exista proces in waiting, atunci mai intai se
					//extrage element si apoi se insereaza
					ExtrQ (coada_waiting, ae);
				
					add_coada_waiting (coada_waiting, *proc_mem, run_proc->PID,
					run_proc->prioritate, run_proc->timp_ramas, out);
				}
				else {
					//daca nu, invers
					add_coada_waiting (coada_waiting, *proc_mem, run_proc->PID,
						run_proc->prioritate, run_proc->timp_ramas, out);
					ExtrQ (coada_waiting, ae);
				}
				memcpy (run_proc, ae, sizeof(TProces));
			}
			else { //T >= t
				if (t < run_proc->cuanta) {

					/* acelasi procedeu ca la primul caz, doar ca 
					se termina timpul total de rulare si va iesi din
					functie. Procesul va ramane in running */
					run_proc->timp_ramas = run_proc->timp_ramas - t;
					run_proc->cuanta = run_proc->cuanta - t;
					t = 0;
					update_timp_lista(proc_mem, run_proc->PID, 
						run_proc->timp_ramas);
	
					}

				else if (t >= run_proc->cuanta) {
					run_proc->timp_ramas = run_proc->timp_ramas - 
					run_proc->cuanta;
					t = t - run_proc->cuanta;
					run_proc->cuanta = T;
					update_timp_lista(proc_mem, run_proc->PID, 
						run_proc->timp_ramas);
					
					memcpy (ae, run_proc, sizeof(TProces));
					if (INC(coada_waiting)) {
						ExtrQ (coada_waiting, ae);
		
						add_coada_waiting (coada_waiting, *proc_mem,
							run_proc->PID, run_proc->prioritate, 
							run_proc->timp_ramas, out);
					}
					else {
						add_coada_waiting (coada_waiting, *proc_mem, 
							run_proc->PID, run_proc->prioritate, 
							run_proc->timp_ramas, out);
						ExtrQ (coada_waiting, ae);
					}
					memcpy (run_proc, ae, sizeof(TProces));
				}
			}
		}
		else if (run_proc->timp_ramas <= run_proc->cuanta) {
			if (T >= t) {
				if (t >= run_proc->cuanta) {
					run_proc->timp_ramas = 0;
					t = t - run_proc->cuanta;
					run_proc ->cuanta = T;
					del_elem_lista (proc_mem, run_proc->PID);
					memcpy (ae, run_proc, sizeof(TProces));
					IntrQ (coada_finished, ae);
					PIDuri [run_proc->PID - 1] = 0;
					
				
					rem_lista (incep_dim, run_proc->PID);

					update_timp_lista(proc_mem, run_proc->PID, 
						run_proc->timp_ramas);
	
					if (ExtrQ (coada_waiting, ae)) {
							memcpy (run_proc, ae, sizeof(TProces));
							update_timp_lista(proc_mem, run_proc->PID, 
								run_proc->timp_ramas);
					}
					else {
						*running = 0;
						free(ae);
						return;
					}

				}
				else if (t < run_proc->cuanta) {
					if (t < run_proc->timp_ramas) {
						run_proc->timp_ramas -= t;
						t = 0;
						run_proc->cuanta = T;
						update_timp_lista(proc_mem, run_proc->PID, 
							run_proc->timp_ramas);
					
						memcpy (ae, run_proc, sizeof(TProces));
						if (INC(coada_waiting)) {
							ExtrQ (coada_waiting, ae);
				
							add_coada_waiting (coada_waiting, *proc_mem, 
								run_proc->PID, run_proc->prioritate, 
								run_proc->timp_ramas, out);
						}
						else {
							add_coada_waiting (coada_waiting, *proc_mem, 
								run_proc->PID, run_proc->prioritate, 
								run_proc->timp_ramas, out);
							ExtrQ (coada_waiting, ae);
						}
						memcpy (run_proc, ae, sizeof(TProces));
					}
				}
			}
			else if (T < t) {
					t = t - run_proc->timp_ramas;
					run_proc->timp_ramas = 0;

					memcpy (ae, run_proc, sizeof(TProces));
					IntrQ (coada_finished, ae);
					PIDuri [run_proc->PID - 1] = 0;
					

				
					rem_lista(incep_dim, run_proc->PID);
					del_elem_lista (proc_mem, run_proc->PID);
					
					if (ExtrQ (coada_waiting, ae)) {
						memcpy (run_proc, ae, sizeof(TProces));
						update_timp_lista(proc_mem, run_proc->PID, 
							run_proc->timp_ramas);
					}
					else {
						*running = 0;
						free(ae);
						return;
					}
			
			}
		}
		update_timp_lista(proc_mem, run_proc->PID, run_proc->timp_ramas);
	}

	free(ae);
}

void DistrugeProcMem (ALista proc_mem) {
	TLista aux = NULL, p = NULL, aux2 = NULL;
	for (p = *proc_mem; p; ) {
		aux = p;
		p = p->urm;
		if (((AProces)(aux->info))->stiva_proc)
		while (((AStiva)(((AProces)(aux->info))->stiva_proc))->vf) {
			aux2 = ((AStiva)(((AProces)(aux->info))->stiva_proc))->vf;
			((AStiva)(((AProces)(aux->info))->stiva_proc))->vf = 
			((AStiva)(((AProces)(aux->info))->stiva_proc))->vf->urm;
			free(aux2->info);
			free(aux2);
		}
		free (((AProces)(aux->info))->stiva_proc);
		free (aux->info);
		free (aux);

	}
}

#endif
