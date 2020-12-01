/*CHIRICU Miruna-Catalina 312CB*/

Punctaj checker local: 105
Update: pe vmchecker ruleaza pana la testul 8: de acolo valgrindul dureaza
foarte mult


		~ functii.c
	
	add_lista:
(exista lista cu inceputul memoriei si dimensiunea pentru toate procesele
curente)
- adauga elemente in lista care pastreaza inceputul si dimensiunea fiecarui
proces astfel:
	+ la inceput, daca nu mai sunt alte intrari in lista
	+ la inceput, daca dimensiunea memoriei procesului curent este mai
mica decat inceputul memoriei primului proces din lista si inceputul memoriei
primului proces este >0
	+ intre doua elemente, daca dimensiunea memoriei procesului curent
este <= cu (incep_mem (pentru proc urmator) - incep_mem a - dim_mem
(pentru procesul de dinaintea sa)
	+ la sfarsit, daca nu au fost indeplinite conditiile anterioare

	rem_lista:
(pentru aceeasi lista)
- sterge procesul cu pidul PID din lista cu inceputul memoriei si dimensiunea
fiecarui proces
- daca a ajuns sa nu mai aiba elemente, il aloca iar pe primul

	mem_sum:
(pentru aceeasi lista)
- calculeaza suma dimensiunilor proceselor din memorie (care nu s-au terminat)
pentru a verifica relatia memoriei totale ocupate fata de dimensiunea maxima
(3 MiB)

	DistrugeLista:
(pentru aceeasi lista)
- elibereaza memoria

	aloc_proc:
- aloca meoria necesara pentru un nou proces
- seteaza campurile date
- necesar pentru procesul curent (care ruleaza)
	
	add_proc_in_mem:
(pentru lista cu toate procesele din memorie - neterminate)
- aloca meoria necesara pentru un nou proces (+ stiva)
- il insereaza in lista, ordonat, crescator in functie de PID

	print_stack:
- pentru afisarea stivei unui proces, cream o stiva auxiliara in care
memoram (pop + push) elementele din stiva, dupa care le punem din nou in stiva 
originala si eliberam stiva auxiliara
- exista conditie pentru stiva vida

	add_elem_stiva:
- adauga element in stiva unui proces
- daca numarul de elemente e egal cu dimensiunea memoriei procesului /4
atunci afiseaza mesaj (maxe = dim_mem/4): nu poate sa adauge(push) alt element

	rem_elem_stiva:
- sterge elem. din stiva
- afiseaza mesaj daca nu sunt elemente in stiva (nu poate sa faca pop)

	print_cw si print_cf:
- printeaza coada_waiting/coada_finished
- asemanator cu procedeul de la print_stack:
	+se foloseste o coada auxiliara in care se insereaza toate elementele
cozii originale, se afiseaza, dupa care se adauga la loc in coada (IntrQ,
ExtrQ)
	
	add_coada_waiting:
- pentru a adauga elemente in coada_waiting, avem nevoie de doua cozi
auxiliare, una in care vor fi memorate elementele de dinaintea elementului
ce urmeaza sa fie introdus, iar cealalta le memoreaza pe cele de dupa element
pentru ca la sfarsit sa putem sa cream inapoi coada_waiting (caux + ae + caux2)
- se insereaza ordonat in lista, respectand cerinta
- mai multe detalii in comentarii

	update_timp_lista:
- timpul ramas al unui proces trebuie updatat de fiecare data cand ruleaza
(in lista cu toate procesele care ocupa memorie in sistem)

	tot_timp:
- calculeaza totalul timpului ramas (pentru finish)

	search_proc_mem:
- cauta un anumit proces in memorie

	del_elem_lista:
- sterge un proces din memorie cand se termina

	run:
- ia urmatoarele cazuri posibile:
	I. timp_ramas al procesului > cuanta procesului
	(procesul nu se poate termina)
		1. (T < timpul total ramas de rulare (t)) 
			+ nu se poate termina procesul => trece in waiting
			+ se updateaza timpul in lista, se scad: timpul total,
			timpul ramas, cuanta procesului se reseteaza
			+ daca nu mai sunt procese in waiting, se reruleaza
			acelasi proces 
		2. (T >= t)
		      a) (t < cuanta)
			+ se termina timpul total de rulare
			+ procesul ramane in running
		      b) (t >= cuanta)
			+ asemanator cu cazul 1.
	II. timp_ramas al procesului <= cuanta 
	(procesul se poate termina)
		1. (T >= t)
		      a) (t >= cuanta)
			+ se termina timpul procesului => trece in finished
			+ se sterge din lista de memorie
			+ se sterge din lista cu inceputurile si dimensiunile
			memoriei
			+ se incearca extragerea din waiting, iar daca nu mai
			este niciun proces, iese din functie
		      b) (t < cuanta)
			+ asemanator cazului I.1), doar ca se termina timpul
			total de rulare
		2. (T < t) 
			+ se termina timpul procesului => trece in finished
			+ se sterge din lista de memorie
			+ se sterge din lista cu inceputurile si dimensiunile
			memoriei
			+ se incearca extragerea din waiting, iar daca nu mai
			este niciun proces, iese din functie

	DistrugeProcMem:
- elibereaza memoria alocata pentru lista proceselor din mem
	


		~ Tema2.c


	defrag:
- ia lista ordonata dupa PIDuri a proceselor din memorie, recreaza lista
cu dimensiunea si inceputul memoriei fiecarui proces
- updateaza inceputul memoriei procesului in lista (ordonata dupa PIDuri)
- prin pointer, intoarce inceputul memoriei noului proces care va fi alocat

	



		
		
			


