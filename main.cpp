#include "multiset.h"
#include "element_not_found.h"
#include <iostream>
#include <cassert>
#include <string>
#include <cmath>

struct int_eql {
	
	bool operator()(int a, int b) const {
		
		return a==b;
		
	}
	
};

struct int_decresc {
	
	bool operator()(int a, int b) const {
		
		return a < b;
		
	}
	
};

struct int_cresc {
	
	bool operator()(int a, int b) const {
		
		return a > b;
		
	}
	
};

void test_int() {
	
	std::cout << "\033[1;33m*******Test metodi fondamentali per un multiset ordinato di interi*******\033[0m\n" << std::endl;
	
	//test costruttore di default
	ordered_multiset<int, int_eql, int_decresc> m1;
	assert(m1.tot_elementi() == 0);
	
	//test stanpa multiset ordinato vuoto
	std::cout << "\033[1;32mProviamo a stampare il multiset ordinato vuoto m1: \033[0m" << std::endl;
	std::cout << "\033[1;32mm1: \033[0m" << m1 << std::endl;
	
	//test per la add
	std::cout << "\033[1;32mAggiungiamo qualche elemento a m1\033[0m" << std::endl;
	m1.add(3);
	m1.add(3);
	m1.add(7);
	m1.add(-5);
	m1.add(10,3); //test per la add con occorrenze
	m1.add(1);
	m1.add(13);
	assert(m1.tot_elementi() == 9);
	
	std::cout << "\033[1;32m Stampa del multiset m1 (ordinato in maniera decrescente) \033[0m" << std::endl;
	std::cout << "\033[1;32m m1: \033[0m" << m1 << std::endl;
	
	//test swap
	std::cout << "\033[1;32m Ho instanziato un multiset ordinato vuoto. Proviamo ad utilizzare la funzione swap per scambiare i suoi dati membro con quelli di m1 \033[0m" << std::endl;
	ordered_multiset<int, int_eql, int_decresc> mswap_test;
	std::cout << "\033[1;32m m1: \033[0m" << m1 << std::endl;
	std::cout << "\033[1;32m mswap_test: \033[0m" << mswap_test << std::endl;
	std::cout << "\033[1;32m Eseguiamo la swap. \033[0m" << std::endl;
	m1.swap(mswap_test);
	std::cout << "\033[1;32m m1: \033[0m" << m1 << std::endl;
	std::cout << "\033[1;32m mswap_test: \033[0m" << mswap_test << std::endl;
	std::cout << "\033[1;32m Aggiungiamo un elemento al nostro attuale m1 . . . \033[0m" << std::endl;
	m1.add(19);
	std::cout << "\033[1;32m m1: \033[0m" << m1 << std::endl;
	std::cout << "\033[1;32m. . . e rimettiamo le cose a posto \033[0m" << std::endl;
	m1.swap(mswap_test);
	std::cout << "\033[1;32m m1: \033[0m" << m1 << std::endl;
	std::cout << "\033[1;32m mswap_test: \033[0m" << mswap_test << std::endl;
	
	//test differente ordinamento
	ordered_multiset<int, int_eql, int_cresc> m2;
	assert(m2.tot_elementi() == 0);
	
	m2.add(3);
	m2.add(-5);
	m2.add(3);
	m2.add(10,3);
	m2.add(7);
	m2.add(1);
	m2.add(13);
	assert(m2.tot_elementi() == 9);
	
	std::cout << "\033[1;32m Stampa del multiset m2 (ordinato in maniera crescente)\033[0m" << std::endl;
	std::cout << "\033[1;32m m2: \033[0m" << m2 << std::endl;
	
	//test operatore di uguaglianza
	std::cout << "\033[1;32m Controlliamo se m1 e m2, benchè ordinati in maniera differente, sono uguali: \033[0m";
	if(m1 == m2) {
		
		std::cout << "Sì, sono uguali" << std::endl;
		
	} else {
		
		std::cout << "No, non sono uguali" << std::endl;
		
	}
	
	//test remove
	std::cout << "\033[1;32m Rimuoviamo da m2 un'occorrenza di 10 e un'occorrenza di -5\033[0m" << std::endl;
	m2.remove(10);
	m2.remove(-5);
	assert(m2.tot_elementi() == 7);
	std::cout << "\033[1;32m m2: \033[0m" << m2 << std::endl;
	//test eccezione remove
	std::cout << "\033[1;32m Proviamo a rimuove nuovamente -5. Poichè -5 non è più presente in m2, dovrebbe lanciare un'eccezione.\033[0m" << std::endl;
	try {
		
		m2.remove(-5);
		
	} catch(const element_not_found(&mex)) {

		std::cout << "\033[1;32m Eccezione catturata correttamente: \033[0m" << mex.what() << std::endl;
		
	}
	
	//test clear
	m2.clear();
	ordered_multiset<int, int_eql, int_decresc> mtest_clear;
	assert(m2 == mtest_clear);
	
	//test copy ctor
	std::cout << "\033[1;32m Costruisco un multiset ordinato m3 con il copy ctor, copiando i dati da m1\033[0m" << std::endl;
	ordered_multiset<int, int_eql, int_decresc> m3(m1);
	assert(m1 == m3);
	std::cout << "\033[1;32m m1: \033[0m" << m1 << std::endl;
	std::cout << "\033[1;32m m3: \033[0m" << m3 << std::endl;
	
	//test operatore di assegnamento
	std::cout << "\033[1;32m Costruisco un multiset ordinato m4 con l'operatore di assegnamento, copiando i dati da m1\033[0m" << std::endl;
	ordered_multiset<int, int_eql, int_decresc> m4;
	m4 = m4; //test autoassegnamento
	m4 = m1;
	assert(m1 == m4);
	std::cout << "\033[1;32m m1: \033[0m" << m1 << std::endl;
	std::cout << "\033[1;32mm4: \033[0m" << m4 << std::endl;
	
	//test metodo contains
	bool cont1 = m4.contains(13);
	assert(cont1 == true);
	bool cont2 = m4.contains(99);
	assert(cont2 == false);
	
	//test costruttore con iteratori
	int a[10] = {2, 6, 7, 1, 1, 5, 5, 2, 2, 10};
	
	std::cout << "\033[1;32m Creazione di un ordered_multiset usando gli iteratori (crescente)\033[0m" << std::endl;
	ordered_multiset<int, int_eql, int_cresc> m5(a, a + 10);
	assert(m5.tot_elementi() == 10);
	std::cout << "\033[1;32m m5: \033[0m" << m5 << std::endl;
	std::cout << "\033[1;32m Creazione di un ordered_multiset usando gli iteratori (decrescente)\033[0m" << std::endl;
	ordered_multiset<int, int_eql, int_decresc> m6(a, a + 10);
	assert(m6.tot_elementi() == 10);
	std::cout << "\033[1;32m m6: \033[0m" << m6 << std::endl;
	
	//stampa con gli iteratori
	std::cout << "\033[1;32m Stampiamo il contenuto di m5 facendo uso degli iteratori: \033[0m" << std::endl;
	ordered_multiset<int, int_eql, int_cresc>::const_iterator b, e;
	for(b = m5.begin(), e = m5.end(); b != e; ++b) {
		
		std::cout << *b << " ";
		
	}
	std::cout << std::endl;
	
	//test operatore decremento iteratori
	std::cout << "\033[1;32m Stampiamo il contenuto di m5 al contrario facendo uso degli iteratori: \033[0m" << std::endl;
	ordered_multiset<int, int_eql, int_cresc>::const_iterator it_beg = m5.end(), it_end = m5.begin();
	--it_beg;
	--it_end;
	
	for(; it_beg != it_end; --it_beg) {
		
		std::cout << *it_beg << " ";
		
	}
	std::cout << std::endl;
	
	//test metodo tot_elementi
	unsigned int tot = m5.tot_elementi();
	assert(tot == 10);
	
	//test constness	
	//const ordered_multiset<int, int_eql, int_cresc> m7(a, a + 10);
	//non posso esguire la add su un ordered_multiset const
	//m7.add(13);
	//non posso eseguire la remove su un ordered_multiset const
	//m7.remove(1);
	//non posso eseguire la clear su un ordered_multiset const
	//m7.clear();
	
	std::cout << std::endl;

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct string_eql {
	
	bool operator()(const std::string &a, const std::string &b) const {
		
		return (a == b);
		
	}
	
};

struct string_decresc {
	
	bool operator()(const std::string &a, const std::string &b) const {
		
		return (a.length() < b.length());
		
	}
	
};

struct string_cresc {
	
	bool operator()(const std::string &a, const std::string &b) const {
		
		//std::cout << a << ", " << a.length() << ", " << b << ", " << b.length() << std::endl;
		return (a.length() > b.length());
		
	}
	
};

void test_string() {
	
	std::cout << "\033[1;33m*******Test metodi fondamentali per un multiset ordinato di stringhe*******\033[0m\n" << std::endl;
	
	//test costruttore di defaut
	ordered_multiset<std::string, string_eql, string_decresc> m1;
	assert(m1.tot_elementi() == 0);
	
	//test stanpa multiset ordinato vuoto
	std::cout << "\033[1;32m Proviamo a stampare il multiset ordinato vuoto m1: \033[0m" << std::endl;
	std::cout << "\033[1;32m m1: \033[0m" << m1 << std::endl;
	
	//test per la add
	std::cout << "\033[1;32m Aggiungiamo qualche elemento a m1\033[0m" << std::endl;
	m1.add("Colazione");
	m1.add("Croissant");
	m1.add("Latte e cereali");
	m1.add("Croissant");
	m1.add("Ace");
	m1.add("Avena");
	m1.add("Fetta biscottata");
	m1.add("Caffelatte", 4);
	assert(m1.tot_elementi() == 11);
	
	std::cout << "\033[1;32m Stampa del multiset m1 (ordinato in maniera decrescente)\033[0m" << std::endl;
	std::cout << "\033[1;32m m1: \033[0m" << m1 << std::endl;
	
	//test swap
	std::cout << "\033[1;32m Ho instanziato un multiset ordinato vuoto. Proviamo ad utilizzare la funzione swap per scambiare i suoi dati membro con quelli di m1\033[0m" << std::endl;
	ordered_multiset<std::string, string_eql, string_decresc> mswap_test;
	std::cout << "\033[1;32m m1: \033[0m" << m1 << std::endl;
	std::cout << "\033[1;32m mswap_test: \033[0m" << mswap_test << std::endl;
	std::cout << "\033[1;32m Eseguiamo la swap.\033[0m" << std::endl;
	m1.swap(mswap_test);
	std::cout << "\033[1;32m m1: \033[0m" << m1 << std::endl;
	std::cout << "\033[1;32m mswap_test: \033[0m" << mswap_test << std::endl;
	std::cout << "\033[1;32m Aggiungiamo un elemento al nostro attuale m1 . . . \033[0m" << std::endl;
	m1.add("Genoveffo");
	std::cout << "\033[1;32m m1: \033[0m" << m1 << std::endl;
	std::cout << "\033[1;32m. . . e rimettiamo le cose a posto\033[0m" << std::endl;
	m1.swap(mswap_test);
	std::cout << "\033[1;32m m1: \033[0m" << m1 << std::endl;
	std::cout << "\033[1;32m mswap_test: \033[0m" << mswap_test << std::endl;
	
	//test differente ordinamento
	ordered_multiset<std::string, string_eql, string_cresc> m2;
	assert(m2.tot_elementi() == 0);
	
	m2.add("Colazione");
	m2.add("Croissant");
	m2.add("Latte e cereali");
	m2.add("Croissant");
	m2.add("Ace");
	m2.add("Avena");
	m2.add("Fetta biscottata");
	m2.add("Caffelatte", 4);
	assert(m2.tot_elementi() == 11);
	
	std::cout << "\033[1;32m Stampa del multiset m2 (ordinato in maniera crescente)\033[0m" << std::endl;
	std::cout << "\033[1;32m m2: \033[0m" << m2 << std::endl;
	
	//test operatore di uguaglianza
	std::cout << "\033[1;32m Controlliamo se m1 e m2, benchè ordinati in maniera differente, sono uguali: \033[0m";
	if(m1 == m2) {
		
		std::cout << "Sì, sono uguali" << std::endl;
		
	} else {
		
		std::cout << "No, non sono uguali" << std::endl;
		
	}
	
	//test remove
	std::cout << "\033[1;32m Rimuoviamo da m2 un'occorrenza di 'Caffelatte' e un'occorrenza di 'Avena'\033[0m" << std::endl;
	m2.remove("Caffelatte");
	m2.remove("Avena");
	assert(m2.tot_elementi() == 9);
	std::cout << "\033[1;32m m2: \033[0m" << m2 << std::endl;
	//test eccezione remove
	std::cout << "\033[1;32m Proviamo a rimuove nuovamente 'Avena'. Poichè 'Avena' non è più presente in m2, dovrebbe lanciare un'eccezione.\033[0m" << std::endl;
	try {
		
		m2.remove("Avena");
		
	} catch(const element_not_found(&mex)) {

		std::cout << "\033[1;32m Eccezione catturata correttamente: \033[0m" << mex.what() << std::endl;
		
	}
	
	//test clear
	m2.clear();
	ordered_multiset<std::string, string_eql, string_decresc> mtest_clear;
	assert(m2 == mtest_clear);
	
	//test copy ctor
	std::cout << "\033[1;32m Costruisco un multiset ordinato m3 con il copy ctor, copiando i dati da m1\033[0m" << std::endl;
	ordered_multiset<std::string, string_eql, string_decresc> m3(m1);
	assert(m1 == m3);
	std::cout << "\033[1;32m m1: \033[0m" << m1 << std::endl;
	std::cout << "\033[1;32m m3: \033[0m" << m3 << std::endl;
	
	//test operatore di assegnamento
	std::cout << "\033[1;32m Costruisco un multiset ordinato m4 con l'operatore di assegnamento, copiando i dati da m1\033[0m" << std::endl;
	ordered_multiset<std::string, string_eql, string_decresc> m4;
	m4 = m4; //test autoassegnamento;
	m4 = m1;
	assert(m1 == m4);
	std::cout << "\033[1;32m m1: \033[0m" << m1 << std::endl;
	std::cout << "\033[1;32m m4: \033[0m" << m4 << std::endl;
	
	//test metodo contains
	bool cont1 = m4.contains("Ace");
	assert(cont1 == true);
	bool cont2 = m4.contains("Banana");
	assert(cont2 == false);
	
	//test costruttore con iteratori
	std::string a[10] = {"Mario", "Davide", "Gianluigi", "Chiara", "Vale", "Ale", "Pablo", "Francesco", "Francesco", "Lorenzo"};
	
	std::cout << "\033[1;32m Creazione di un ordered_multiset usando gli iteratori (crescente)\033[0m" << std::endl;
	ordered_multiset<std::string, string_eql, string_cresc> m5(a, a + 10);
	assert(m5.tot_elementi() == 10);
	std::cout << "\033[1;32m m5: \033[0m" << m5 << std::endl;
	std::cout << "\033[1;32m Creazione di un ordered_multiset usando gli iteratori (decrescente)\033[0m" << std::endl;
	ordered_multiset<std::string, string_eql, string_decresc> m6(a, a + 10);
	assert(m6.tot_elementi() == 10);
	std::cout << "\033[1;32m m6: \033[0m" << m6 << std::endl;
	
	//stampa con gli iteratori
	std::cout << "\033[1;32m Stampiamo il contenuto di m5 facendo uso degli iteratori: \033[0m" << std::endl;
	ordered_multiset<std::string, string_eql, string_cresc>::const_iterator b, e;
	for(b = m5.begin(), e = m5.end(); b != e; ++b) {
		
		std::cout << *b << " ";
		
	}
	std::cout << std::endl;
	
	//test operatore decremento iteratori
	std::cout << "\033[1;32m Stampiamo il contenuto di m5 al contrario facendo uso degli iteratori: \033[0m" << std::endl;
	ordered_multiset<std::string, string_eql, string_cresc>::const_iterator it_beg = m5.end(), it_end = m5.begin();
	--it_beg;
	--it_end;
	
	for(; it_beg != it_end; --it_beg) {
		
		std::cout << *it_beg << " ";
		
	}
	std::cout << std::endl;
	
	//test metodo tot_elementi
	unsigned int tot = m5.tot_elementi();
	assert(tot == 10);
	
	//test constness
	//const ordered_multiset<std::string, string_eql, string_cresc> m7(a, a + 10);
	//non posso esguire la add su un ordered_multiset const
	//m7.add("Luca");
	//non posso eseguire la remove su un ordered_multiset const
	//m7.remove("Francesco");
	//non posso eseguire la clear su un ordered_multiset const
	//m7.clear();
	
	std::cout << std::endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Z3_eql {
	
	bool operator()(int a, int b) const {
		
		while(a < 0) {
			
			a += 3;
			
		}
		
		while(b < 0) {
			
			b += 3;
			
		}
		
		return (a % 3 == b % 3);
		
	}
	
};

void test_Z3() {
	
	std::cout << "\033[1;33m*******Test metodi fondamentali per un multiset ordinato che vuole imitare il gruppo degli interi congrui modulo 3 Z_3*******\033[0m\n" << std::endl;
	std::cout << "\033[1;33m*Per ottenere una rappresentazione più vicina a quella matematicamente standard, i primi interi ad essere aggiunti ad un multiset ordinato saranno 0, 1, 2 (per convenzione, si scelgono come rappresentanti delle classi di equivalenza in Z_3 i numeri 0, 1, 2).*\033[0m\n" << std::endl;
	
	//test costruttore di defaut
	ordered_multiset<int, Z3_eql, int_decresc> m1;
	assert(m1.tot_elementi() == 0);
	
	//test stanpa multiset ordinato vuoto
	std::cout << "\033[1;32m Proviamo a stampare il multiset ordinato vuoto m1: \033[0m" << std::endl;
	std::cout << "\033[1;32m m1: \033[0m" << m1 << std::endl;
	
	//test per la add
	std::cout << "\033[1;32m Aggiungiamo qualche elemento a m1\033[0m" << std::endl;
	m1.add(0);
	m1.add(1);
	m1.add(2);
	m1.add(27);
	m1.add(9);
	m1.add(14);
	m1.add(13);
	m1.add(7, 3);
	assert(m1.tot_elementi() == 10);
	
	std::cout << "\033[1;32m Stampa del multiset m1 (ordinato in maniera decrescente)\033[0m" << std::endl;
	std::cout << "\033[1;32m m1: \033[0m" << m1 << std::endl;
	
	//test swap
	std::cout << "\033[1;32m Ho instanziato un multiset ordinato vuoto. Proviamo ad utilizzare la funzione swap per scambiare i suoi dati membro con quelli di m1\033[0m" << std::endl;
	ordered_multiset<int, Z3_eql, int_decresc> mswap_test;
	std::cout << "\033[1;32m m1: \033[0m" << m1 << std::endl;
	std::cout << "\033[1;32m mswap_test: \033[0m" << mswap_test << std::endl;
	std::cout << "\033[1;32m Eseguiamo la swap.\033[0m" << std::endl;
	m1.swap(mswap_test);
	std::cout << "\033[1;32m m1: \033[0m" << m1 << std::endl;
	std::cout << "\033[1;32m mswap_test: " << mswap_test << std::endl;
	std::cout << "\033[1;32m Aggiungiamo un elemento al nostro attuale m1 . . . \033[0m" << std::endl;
	m1.add(4);
	std::cout << "\033[1;32m m1: \033[0m" << m1 << std::endl;
	std::cout << "\033[1;32m . . . e rimettiamo le cose a posto\033[0m" << std::endl;
	m1.swap(mswap_test);
	std::cout << "\033[1;32m m1: \033[0m" << m1 << std::endl;
	std::cout << "\033[1;32m mswap_test: \033[0m" << mswap_test << std::endl;
	
	//test differente ordinamento
	ordered_multiset<int, Z3_eql, int_cresc> m2;
	assert(m2.tot_elementi() == 0);
	
	m2.add(0);
	m2.add(1);
	m2.add(2);
	m2.add(10, 3);
	m2.add(9);
	m2.add(24);
	m2.add(19);
	m2.add(11);
	assert(m2.tot_elementi() == 10);
	
	std::cout << "\033[1;32m Stampa del multiset m2 (ordinato in maniera crescente)\033[0m" << std::endl;
	std::cout << "\033[1;32m m2: \033[0m" << m2 << std::endl;
	
	//test operatore di uguaglianza
	std::cout << "\033[1;32m Controlliamo se m1 e m2, benchè ordinati in maniera differente, sono uguali: \033[0m";
	if(m1 == m2) {
		
		std::cout << "Sì, sono uguali" << std::endl;
		
	} else {
		
		std::cout << "No, non sono uguali" << std::endl;
		
	}
	
	//test remove
	std::cout << "\033[1;32m Rimuoviamo da m2 un'occorrenza di 0 e un'occorrenza di 1\033[0m" << std::endl;
	m2.remove(0);
	m2.remove(1);
	assert(m2.tot_elementi() == 8);
	std::cout << "\033[1;32m m2: \033[0m" << m2 << std::endl;
	//test eccezione remove
	std::cout << "\033[1;32m Rimuoviamo altre due occorrenze di 0 da m2, cioè quelle rimaste.\033[0m" << std::endl;
	
	m2.remove(0);
	m2.remove(0);
	assert(m2.tot_elementi() == 6);
	std::cout << "\033[1;32m m2: \033[0m" << m2 << std::endl;
	
	std::cout << "\033[1;32m Proviamo a rimuovere un'altra occorrenza di 0. Poichè 0 non è più presente in m2, dovrebbe lanciare un'eccezione.\033[0m" << std::endl;
	try {
		
		m2.remove(0);
		
	} catch(const element_not_found(&mex)) {

		std::cout << "\033[1;32m Eccezione catturata correttamente: \033[0m" << mex.what() << std::endl;
		
	}
	
	//test clear
	m2.clear();
	ordered_multiset<int, Z3_eql, int_decresc> mtest_clear;
	assert(m2 == mtest_clear);
	
	//test copy ctor
	std::cout << "\033[1;32m Costruisco un multiset ordinato m3 con il copy ctor, copiando i dati da m1\033[0m" << std::endl;
	ordered_multiset<int, Z3_eql, int_decresc> m3(m1);
	assert(m1 == m3);
	std::cout << "\033[1;32m m1: \033[0m" << m1 << std::endl;
	std::cout << "\033[1;32m m3: \033[0m" << m3 << std::endl;
	
	//test operatore di assegnamento
	std::cout << "\033[1;32m Costruisco un multiset ordinato m4 con l'operatore di assegnamento, copiando i dati da m1\033[0m" << std::endl;
	ordered_multiset<int, Z3_eql, int_decresc> m4;
	m4 = m4; //test autoassegnamento
	m4 = m1;
	assert(m1 == m4);
	std::cout << "\033[1;32m m1: \033[0m" << m1 << std::endl;
	std::cout << "\033[1;32m m4: \033[0m" << m4 << std::endl;
	
	//test metodo contains
	bool cont1 = m4.contains(0);
	assert(cont1 == true);
	//Non ha senso perché ogni numero è contenuto nel multiset Z_3, per come è definito il metodo contains.
	//bool cont2 = m4.contains(99);
	//assert(cont2 == false);
	
	//test costruttore con iteratori
	int a[10] = {0, 1, 2, -15, -1, -112, -55, -23, -90, -69};
	
	std::cout << "\033[1;32m Creazione di un ordered_multiset usando gli iteratori (crescente)\033[0m" << std::endl;
	ordered_multiset<int, Z3_eql, int_cresc> m5(a, a + 10);
	assert(m5.tot_elementi() == 10);
	std::cout << "\033[1;32m m5: \033[0m" << m5 << std::endl;
	std::cout << "\033[1;32m Creazione di un ordered_multiset usando gli iteratori (decrescente)\033[0m" << std::endl;
	ordered_multiset<int, Z3_eql, int_decresc> m6(a, a + 10);
	assert(m6.tot_elementi() == 10);
	std::cout << "\033[1;32m m6: \033[0m" << m6 << std::endl;
	
	//stampa con gli iteratori
	std::cout << "\033[1;32m Stampiamo il contenuto di m5 facendo uso degli iteratori: \033[0m" << std::endl;
	ordered_multiset<int, Z3_eql, int_cresc>::const_iterator b, e;
	for(b = m5.begin(), e = m5.end(); b != e; ++b) {
		
		std::cout << *b << " ";
		
	}
	std::cout << std::endl;
	
	//test operatore decremento iteratori
	std::cout << "\033[1;32m Stampiamo il contenuto di m5 al contrario facendo uso degli iteratori: \033[0m" << std::endl;
	ordered_multiset<int, Z3_eql, int_cresc>::const_iterator it_beg = m5.end(), it_end = m5.begin();
	--it_beg;
	--it_end;
	
	for(; it_beg != it_end; --it_beg) {
		
		std::cout << *it_beg << " ";
		
	}
	std::cout << std::endl;
	
	//test metodo tot_elementi
	unsigned int tot = m5.tot_elementi();
	assert(tot == 10);
	
	//test constness
	//const ordered_multiset<int, Z3_eql, int_cresc> m7(a, a + 10);
	//non posso esguire la add su un ordered_multiset const
	//m7.add(56);
	//non posso eseguire la remove su un ordered_multiset const
	//m7.remove(49);
	//non posso eseguire la clear su un ordered_multiset const
	//m7.clear();
	
	std::cout << std::endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct point {
	
	double x;
	double y;
	
	point(double ascissa, double ordinata) : x(ascissa), y(ordinata) {}
	
	point() : x(0), y(0) {}
	
};

struct point_eql {
	
	bool operator()(const point &p, const point &q) const {
		
		return (std::fabs(p.x - q.x) < std::numeric_limits<float>::epsilon() && std::fabs(p.y - q.y) < std::numeric_limits<float>::epsilon());
		
	}
	
};

struct point_decresc {
	
	bool operator()(const point &p, const point &q) const {
		
		return (p.x < q.x);
		
	}
	
};

struct point_cresc {
	
	bool operator()(const point &p, const point &q) const {
		
		return (p.x > q.x);
		
	}
	
};

std::ostream &operator<<(std::ostream &os, const point &p) {
	os << "(" << p.x << ", " << p.y << ")";
	return os;
};

void test_point() {
	
	std::cout << "\033[1;33m*******Test metodi fondamentali per un multiset ordinato di dati custom point*******\033[0m\n" << std::endl;
	std::cout << "\033[1;33m*Il dato custom point vuole imitare un punto a coordinate double nel piano cartesiano*\033[0m\n" << std::endl;
	
	//test costruttore di defaut
	ordered_multiset<point, point_eql, point_decresc> m1;
	assert(m1.tot_elementi() == 0);
	
	//test stanpa multiset ordinato vuoto
	std::cout << "\033[1;32m Proviamo a stampare il multiset ordinato vuoto m1: \033[0m" << std::endl;
	std::cout << "\033[1;32m m1: \033[0m" << m1 << std::endl;
	
	//test per la add
	std::cout << "\033[1;32m Aggiungiamo qualche elemento a m1\033[0m" << std::endl;
	m1.add(point(24.26, 53.72));
	m1.add(point(19.61, 65.87));
	m1.add(point(2.25, 88.48));
	m1.add(point(24.26, 53.72));
	m1.add(point(87.58, 72.83));
	m1.add(point(29.11, 61.37));
	m1.add(point(34.81, 56.66));
	m1.add(point(79.34, 34.85), 4);
	assert(m1.tot_elementi() == 11);
	
	std::cout << "\033[1;32m Stampa del multiset m1 (ordinato in maniera decrescente)\033[0m" << std::endl;
	std::cout << "\033[1;32m m1: \033[0m" << m1 << std::endl;
	
	//test swap
	std::cout << "\033[1;32m Ho instanziato un multiset ordinato vuoto. Proviamo ad utilizzare la funzione swap per scambiare i suoi dati membro con quelli di m1\033[0m" << std::endl;
	ordered_multiset<point, point_eql, point_decresc> mswap_test;
	std::cout << "\033[1;32m m1: \033[0m" << m1 << std::endl;
	std::cout << "\033[1;32m mswap_test: \033[0m" << mswap_test << std::endl;
	std::cout << "\033[1;32m Eseguiamo la swap.\033[0m" << std::endl;
	m1.swap(mswap_test);
	std::cout << "\033[1;32m m1: \033[0m" << m1 << std::endl;
	std::cout << "\033[1;32m mswap_test: \033[0m" << mswap_test << std::endl;
	std::cout << "\033[1;32m Aggiungiamo un elemento al nostro attuale m1 . . . \033[0m" << std::endl;
	m1.add(point(0,0));
	std::cout << "\033[1;32m m1: \033[0m" << m1 << std::endl;
	std::cout << "\033[1;32m . . . e rimettiamo le cose a posto\033[0m" << std::endl;
	m1.swap(mswap_test);
	std::cout << "\033[1;32m m1: \033[0m" << m1 << std::endl;
	std::cout << "\033[1;32m mswap_test: \033[0m" << mswap_test << std::endl;
	
	//test differente ordinamento
	ordered_multiset<point, point_eql, point_cresc> m2;
	assert(m2.tot_elementi() == 0);
	
	m2.add(point(24.26, 53.72));
	m2.add(point(79.34, 34.85), 4);
	m2.add(point(24.26, 53.72));
	m2.add(point(2.25, 88.48));
	m2.add(point(19.61, 65.87));
	m2.add(point(29.11, 61.37));
	m2.add(point(87.58, 72.83));
	m2.add(point(34.81, 56.66));
	assert(m2.tot_elementi() == 11);
	
	std::cout << "\033[1;32m Stampa del multiset m2 (ordinato in maniera crescente)\033[0m" << std::endl;
	std::cout << "\033[1;32m m2: \033[0m" << m2 << std::endl;
	
	//test operatore di uguaglianza
	std::cout << "\033[1;32m Controlliamo se m1 e m2, benchè ordinati in maniera differente, sono uguali: \033[0m";
	if(m1 == m2) {
		
		std::cout << "Sì, sono uguali" << std::endl;
		
	} else {
		
		std::cout << "No, non sono uguali" << std::endl;
		
	}
	
	//test remove
	std::cout << "\033[1;32m Rimuoviamo da m2 un'occorrenza di (79.34, 34.85) e un'occorrenza di (87.58, 72.83)\033[0m" << std::endl;
	m2.remove(point(79.34, 34.85));
	m2.remove(point(87.58, 72.83));
	assert(m2.tot_elementi() == 9);
	std::cout << "\033[1;32m m2: \033[0m" << m2 << std::endl;
	//test eccezione remove
	std::cout << "\033[1;32m Proviamo a rimuove nuovamente il punto (87.58, 72.83). Poichè il punto (87.58, 72.83) non è più presente in m2, dovrebbe lanciare un'eccezione.\033[0m" << std::endl;
	try {
		
		m2.remove(point(87.58, 72.83));
		
	} catch(const element_not_found(&mex)) {

		std::cout << "\033[1;32m Eccezione catturata correttamente: \033[0m" << mex.what() << std::endl;
		
	}
	
	//test clear
	m2.clear();
	ordered_multiset<point, point_eql, point_decresc> mtest_clear;
	assert(m2 == mtest_clear);
	
	//test copy ctor
	std::cout << "\033[1;32m Costruisco un multiset ordinato m3 con il copy ctor, copiando i dati da m1\033[0m" << std::endl;
	ordered_multiset<point, point_eql, point_decresc> m3(m1);
	assert(m1 == m3);
	std::cout << "\033[1;32m m1: \033[0m" << m1 << std::endl;
	std::cout << "\033[1;32m m3: \033[0m" << m3 << std::endl;
	
	//test operatore di assegnamento
	std::cout << "\033[1;32m Costruisco un multiset ordinato m4 con l'operatore di assegnamento, copiando i dati da m1\033[0m" << std::endl;
	ordered_multiset<point, point_eql, point_decresc> m4;
	m4 = m4; //test autoassegnamento
	m4 = m1;
	assert(m1 == m4);
	std::cout << "\033[1;32m m1: \033[0m" << m1 << std::endl;
	std::cout << "\033[1;32m m4: \033[0m" << m4 << std::endl;
	
	//test metodo contains
	bool cont1 = m4.contains(point(34.81, 56.66));
	assert(cont1 == true);
	bool cont2 = m4.contains(point(0, 0));
	assert(cont2 == false);
	
	//test costruttore con iteratori
	point a[10] = {point(50.91, 16.61), point(), point(-36.59, 130.05), point(-70.01, -30.26), point(), point(7.78, 192.32), point(15, 25.08), point(-54.43, 68.76), point(43.73, -31.97), point(-36.59, 130.05)};
	
	std::cout << "\033[1;32m Creazione di un ordered_multiset usando gli iteratori (crescente)\033[0m" << std::endl;
	ordered_multiset<point, point_eql, point_cresc> m5(a, a + 10);
	assert(m5.tot_elementi() == 10);
	std::cout << "\033[1;32m m5: \033[0m" << m5 << std::endl;
	std::cout << "\033[1;32m Creazione di un ordered_multiset usando gli iteratori (decrescente)\033[0m" << std::endl;
	ordered_multiset<point, point_eql, point_decresc> m6(a, a + 10);
	assert(m6.tot_elementi() == 10);
	std::cout << "\033[1;32m m6: \033[0m" << m6 << std::endl;
	
	//stampa con gli iteratori
	std::cout << "\033[1;32m Stampiamo il contenuto di m5 facendo uso degli iteratori: \033[0m" << std::endl;
	ordered_multiset<point, point_eql, point_cresc>::const_iterator b, e;
	for(b = m5.begin(), e = m5.end(); b != e; ++b) {
		
		std::cout << *b << " ";
		
	}
	std::cout << std::endl;
	
	//test operatore decremento iteratori
	std::cout << "\033[1;32m Stampiamo il contenuto di m5 al contrario facendo uso degli iteratori: \033[0m" << std::endl;
	ordered_multiset<point, point_eql, point_cresc>::const_iterator it_beg = m5.end(), it_end = m5.begin();
	--it_beg;
	--it_end;
	
	for(; it_beg != it_end; --it_beg) {
		
		std::cout << *it_beg << " ";
		
	}
	std::cout << std::endl;
	
	//test metodo tot_elementi
	unsigned int tot = m5.tot_elementi();
	assert(tot == 10);
	
	//test constness
	//const ordered_multiset<point, point_eql, point_cresc> m7(a, a + 10);
	//non posso esguire la add su un ordered_multiset const
	//m7.add(point(54.32, 78.09));
	//non posso eseguire la remove su un ordered_multiset const
	//m7.remove(point());
	//non posso eseguire la clear su un ordered_multiset const
	//m7.clear();
	
	std::cout << std::endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct contact {
	
	std::string name;
	std::string lastname;
	std::string number;
	
	contact() : name(" "), lastname(" "), number(" ") {}
	
	contact(const std::string &n, const std::string &l, const std::string pn) : name(n), lastname(l), number(pn) {}
	
};

struct contact_eql {
	
	bool operator()(const contact &c1, const contact &c2) const {
		
		return (c1.name == c2.name) && (c1.lastname == c2.lastname) && (c1.number == c2.number);
		
	}
	
};

struct sort_by_lastname {
	
	bool operator()(const contact &c1, const contact &c2) const {
		
		return (c1.lastname > c2.lastname);
		
	}
	
};

struct sort_by_name {
	
	bool operator()(const contact &c1, const contact &c2) const {
		
		return (c1.name > c2.name);
		
	}
	
};

std::ostream &operator<<(std::ostream &os, const contact &c) {
	
	os << "("; 
	
	if(c.name != " " && c.lastname != " "  && c.number != " ") {
		
		os << c.name << ", " << c.lastname << ", " << c.number;
		
	}
	
	os << ")";
	return os;
};

void test_contact() {
	
	std::cout << "\033[1;33m*******Test metodi fondamentali per un multiset ordinato di contatti*******\033[0m\n" << std::endl;
	std::cout << "\033[1;33m*Il contatto è implementato come una stringa avente come dati membro tre stringhe (nome, cognome e numero di telefono).*\033[0m\n" << std::endl; 
	
	//test costruttore di defaut
	ordered_multiset<contact, contact_eql, sort_by_lastname> m1;
	assert(m1.tot_elementi() == 0);
	
	//test stanpa multiset ordinato vuoto
	std::cout << "\033[1;32m Proviamo a stampare il multiset ordinato vuoto m1: \033[0m" << std::endl;
	std::cout << "\033[1;32m m1: \033[0m" << m1 << std::endl;
	
	//test per la add
	std::cout << "\033[1;32m Aggiungiamo qualche elemento a m1\033[0m" << std::endl;
	m1.add(contact("Mario", "Draghi", "3891893467"));
	m1.add(contact("Barack", "Obama", "9874563452"));
	m1.add(contact("Mario", "Draghi", "3891893467"));
	m1.add(contact("Boris", "Johnson", "4739876578"));
	m1.add(contact("Angela", "Merkel", "2674563896"));
	m1.add(contact("Joe", "Biden", "5603427865"));
	m1.add(contact("Vladimir", "Putin", "7659453212"));
	m1.add(contact("Sergio", "Mattarella", "3465674890"), 4);
	assert(m1.tot_elementi() == 11);
	
	std::cout << "\033[1;32m Stampa del multiset m1 (cognomi in ordine alfabetico)\033[0m" << std::endl;
	std::cout << "\033[1;32m m1: \033[0m" << m1 << std::endl;
	
	//test swap
	std::cout << "\033[1;32m Ho instanziato un multiset ordinato vuoto. Proviamo ad utilizzare la funzione swap per scambiare i suoi dati membro con quelli di m1\033[0m" << std::endl;
	ordered_multiset<contact, contact_eql, sort_by_lastname> mswap_test;
	std::cout << "\033[1;32m m1: \033[0m" << m1 << std::endl;
	std::cout << "\033[1;32m mswap_test: \033[0m" << mswap_test << std::endl;
	std::cout << "\033[1;32m Eseguiamo la swap.\033[0m" << std::endl;
	m1.swap(mswap_test);
	std::cout << "\033[1;32m m1: \033[0m" << m1 << std::endl;
	std::cout << "\033[1;32m mswap_test: \033[0m" << mswap_test << std::endl;
	std::cout << "\033[1;32m Aggiungiamo un elemento al nostro attuale m1 . . . \033[0m" << std::endl;
	m1.add(contact());
	std::cout << "\033[1;32m m1: \033[0m" << m1 << std::endl;
	std::cout << "\033[1;32m . . . e rimettiamo le cose a posto\033[0m" << std::endl;
	m1.swap(mswap_test);
	std::cout << "\033[1;32m m1: \033[0m" << m1 << std::endl;
	std::cout << "\033[1;32m mswap_test: \033[0m" << mswap_test << std::endl;
	
	//test differente ordinamento
	ordered_multiset<contact, contact_eql, sort_by_name> m2;
	assert(m2.tot_elementi() == 0);
	
	m2.add(contact("Mario", "Draghi", "3891893467"));
	m2.add(contact("Barack", "Obama", "9874563452"));
	m2.add(contact("Mario", "Draghi", "3891893467"));
	m2.add(contact("Boris", "Johnson", "4739876578"));
	m2.add(contact("Angela", "Merkel", "2674563896"));
	m2.add(contact("Joe", "Biden", "5603427865"));
	m2.add(contact("Vladimir", "Putin", "7659453212"));
	m2.add(contact("Sergio", "Mattarella", "3465674890"), 4);
	assert(m2.tot_elementi() == 11);
	
	std::cout << "\033[1;32m Stampa del multiset m2 (nomi in ordine afabetico)\033[0m" << std::endl;
	std::cout << "\033[1;32m m2: \033[0m" << m2 << std::endl;
	
	//test operatore di uguaglianza
	std::cout << "\033[1;32m Controlliamo se m1 e m2, benchè ordinati in maniera differente, sono uguali: \033[0m";
	if(m1 == m2) {
		
		std::cout << "Sì, sono uguali" << std::endl;
		
	} else {
		
		std::cout << "No, non sono uguali" << std::endl;
		
	}
	
	//test remove
	std::cout << "\033[1;32m Rimuoviamo da m2 un'occorrenza di 'Sergio Mattarella' e un'occorrenza di 'Vladimir Putin'\033[0m" << std::endl;
	m2.remove(contact("Sergio", "Mattarella", "3465674890"));
	m2.remove(contact("Vladimir", "Putin", "7659453212"));
	assert(m2.tot_elementi() == 9);
	std::cout << "\033[1;32m m2: \033[0m" << m2 << std::endl;
	//test eccezione remove
	std::cout << "\033[1;32m Proviamo a rimuove nuovamente 'Vladimir Putin'. Poichè 'Vladimir Putin' non è più presente in m2, dovrebbe lanciare un'eccezione.\033[0m" << std::endl;
	try {
		
		m2.remove(contact("Vladimir", "Putin", "7659453212"));
		
	} catch(const element_not_found(&mex)) {

		std::cout << "\033[1;32m Eccezione catturata correttamente: \033[0m" << mex.what() << std::endl;
		
	}
	
	//test clear
	m2.clear();
	ordered_multiset<contact, contact_eql, sort_by_lastname> mtest_clear;
	assert(m2 == mtest_clear);
	
	//test copy ctor
	std::cout << "\033[1;32m Costruisco un multiset ordinato m3 con il copy ctor, copiando i dati da m1" << std::endl;
	ordered_multiset<contact, contact_eql, sort_by_lastname> m3(m1);
	assert(m1 == m3);
	std::cout << "\033[1;32m m1: \033[0m" << m1 << std::endl;
	std::cout << "\033[1;32m m3: \033[0m" << m3 << std::endl;
	
	//test operatore di assegnamento
	std::cout << "\033[1;32m Costruisco un multiset ordinato m4 con l'operatore di assegnamento, copiando i dati da m1\033[0m" << std::endl;
	ordered_multiset<contact, contact_eql, sort_by_lastname> m4;
	m4 = m4; //test autoassegnamento;
	m4 = m1;
	assert(m1 == m4);
	std::cout << "\033[1;32m m1: \033[0m" << m1 << std::endl;
	std::cout << "\033[1;32m m4: \033[0m" << m4 << std::endl;
	
	//test metodo contains
	bool cont1 = m4.contains(contact("Mario", "Draghi", "3891893467"));
	assert(cont1 == true);
	bool cont2 = m4.contains(contact("Emmanuel", "Macron", "8764539891"));
	assert(cont2 == false);
	
	//test costruttore con iteratori
	contact a[10] = {contact("Bruce", "Wayne", "4341239890"), contact("Tony", "Stark", "7860985673"), contact("Clark", "Kent", "3452341289"), contact("Bruce", "Banner", "2316785654"), contact("Arthur", "Curry", "9832374564"), contact("Clark", "Kent", "3452341289"), contact("Steve", "Rogers", "3215654899"), contact("Sailor", "Moon", "6745618344"), contact("Barry", "Allen", "7093417833"), contact("Thor", "Odinson", "0456783291")};
	
	std::cout << "\033[1;32m Creazione di un ordered_multiset usando gli iteratori (cognomi in ordine alfabetico)\033[0m" << std::endl;
	ordered_multiset<contact, contact_eql, sort_by_lastname> m5(a, a + 10);
	assert(m5.tot_elementi() == 10);
	std::cout << "\033[1;32m m5: \033[0m" << m5 << std::endl;
	std::cout << "\033[1;32m Creazione di un ordered_multiset usando gli iteratori (nomi in ordine alfabetico)\033[0m" << std::endl;
	ordered_multiset<contact, contact_eql, sort_by_name> m6(a, a + 10);
	assert(m6.tot_elementi() == 10);
	std::cout << "\033[1;32m m6: \033[0m" << m6 << std::endl;
	
	//stampa con gli iteratori
	std::cout << "\033[1;32m Stampiamo il contenuto di m5 facendo uso degli iteratori: \033[0m" << std::endl;
	ordered_multiset<contact, contact_eql, sort_by_lastname>::const_iterator b, e;
	for(b = m5.begin(), e = m5.end(); b != e; ++b) {
		
		std::cout << *b << " ";
		
	}
	std::cout << std::endl;
	
	//test operatore decremento iteratori
	std::cout << "\033[1;32m Stampiamo il contenuto di m5 al contrario facendo uso degli iteratori: \033[0m" << std::endl;
	ordered_multiset<contact, contact_eql, sort_by_lastname>::const_iterator it_beg = m5.end(), it_end = m5.begin();
	--it_beg;
	--it_end;
	
	for(; it_beg != it_end; --it_beg) {
		
		std::cout << *it_beg << " ";
		
	}
	std::cout << std::endl;
	
	//test metodo tot_elementi
	unsigned int tot = m5.tot_elementi();
	assert(tot == 10);
	
	//test constness
	//const ordered_multiset<std::string, string_eql, string_cresc> m7(a, a + 10);
	//non posso esguire la add su un ordered_multiset const
	//m7.add("Luca");
	//non posso eseguire la remove su un ordered_multiset const
	//m7.remove("Francesco");
	//non posso eseguire la clear su un ordered_multiset const
	//m7.clear();
	
	std::cout << std::endl;
	
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct multimulti_eql {
	
	template <typename T, typename Eql, typename Comp>
	bool operator()(const ordered_multiset<T, Eql, Comp> &m1, const ordered_multiset<T, Eql, Comp> &m2) const {
		
		return (m1 == m2);
		
	}
	
};

struct multimulti_decresc {
	
	template <typename T, typename Eql, typename Comp>
	bool operator()(const ordered_multiset<T, Eql, Comp> &m1, const ordered_multiset<T, Eql, Comp> &m2) const {
		
		return m1.tot_elementi() < m2.tot_elementi();
		
	}
	
};

struct multimulti_cresc {
	
	template <typename T, typename Eql, typename Comp>
	bool operator()(const ordered_multiset<T, Eql, Comp> &m1, const ordered_multiset<T, Eql, Comp> &m2) const {
		
		return m1.tot_elementi() > m2.tot_elementi();
		
	}
	
};

void test_multimulti_int() {
	
	std::cout << "\033[1;33m*******Test metodi fondamentali per un multiset ordinato di multiset ordinati di interi*******\033[0m\n" << std::endl;
	
	//test costruttore di defaut
	ordered_multiset<ordered_multiset<int, int_eql, int_decresc>, multimulti_eql, multimulti_decresc> multi_m1;
	assert(multi_m1.tot_elementi() == 0);
	
	//test stanpa multiset ordinato vuoto
	std::cout << "\033[1;32m Proviamo a stampare il multiset ordinato (in maniera decrescente) vuoto multi_m1: \033[0m" << std::endl;
	std::cout << "\033[1;32m multi_m1: \033[0m" << multi_m1 << std::endl;
	
	//test add
	std::cout << "\033[1;32m Stampiamo un multiset di multiset vuoti.\033[0m" << std::endl;
	ordered_multiset<int, int_eql, int_decresc> m1, m2, m3;
	multi_m1.add(m1);
	multi_m1.add(m2);
	multi_m1.add(m3);
	assert(multi_m1.tot_elementi() == 3);
	std::cout << "\033[1;32m Ho aggiunto 3 multiset vuoti. Ne stampo il risultato\033[0m" << std::endl;
	std::cout << "\033[1;32m multi_m1: \033[0m" << multi_m1 << std::endl;
	
	std::cout << "\033[1;32m Inizializzamo i tre multiset vuoti con dei valori\033[0m" << std::endl;
	//m1
	m1.add(3);
	m1.add(67);
	m1.add(17, 2);
	assert(m1.tot_elementi() == 4);
	std::cout << "\033[1;32m m1: \033[0m" << m1 << std::endl;
	
	//m2
	m2 = m1;
	m2.add(5);
	m2.add(17);
	m2.add(88,3);
	assert(m2.tot_elementi() == 9);
	std::cout << "\033[1;32m m2: \033[0m" << m2 << std::endl;
	
	//m3
	int a[10] = {1, 5, 99, 112, -34, 99, 0, 5, -69, 2};
	ordered_multiset<int, int_eql, int_decresc> m4(a, a + 10);
	m3 = m4;
	assert(m3.tot_elementi() == 10);
	std::cout << "\033[1;32m m3: \033[0m" << m3 << std::endl;
	
	std::cout << "\033[1;32m Cancelliamo il vecchio contenuto di multi_m1 e aggiungiamo i 3 multiset m1, m2, m3 a cui ho aggiunto dei valori\033[0m" << std::endl;
	//test clear
	multi_m1.clear();
	multi_m1.add(m1);
	multi_m1.add(m2);
	multi_m1.add(m3);
	std::cout << "\033[1;32m multi_m1: \033[0m" << multi_m1 << std::endl;
	
	std::cout << "\033[1;32m Aggiungiamo un multiset ordinato a multi_m1\033[0m" << std::endl;
	ordered_multiset<int, int_eql, int_decresc> m5;
	m5.add(3);
	m5.add(3);
	m5.add(7);
	m5.add(5);
	m5.add(10,3);
	m5.add(1);
	m5.add(13);
	assert(m5.tot_elementi() == 9);
	multi_m1.add(m5, 3); //test add con occorrenze
	assert(multi_m1.tot_elementi() == 6);
	
	std::cout << "\033[1;32m Stampa del multiset multi_m1 (ordinato in maniera decrescente)\033[0m" << std::endl;
	std::cout << "\033[1;32m multi_m1: \033[0m" << multi_m1 << std::endl;
	
	//test swap
	std::cout << "\033[1;32m Ho instanziato un multiset ordinato vuoto. Proviamo ad utilizzare la funzione swap per scambiare i suoi dati membro con quelli di m1\033[0m" << std::endl;
	ordered_multiset<ordered_multiset<int, int_eql, int_decresc>, multimulti_eql, multimulti_decresc> mswap_test;
	std::cout << "\033[1;32m multi_m1: \033[0m" << multi_m1 << std::endl;
	std::cout << "\033[1;32m mswap_test: \033[0m" << mswap_test << std::endl;
	std::cout << "\033[1;32m Eseguiamo la swap.\033[0m" << std::endl;
	multi_m1.swap(mswap_test);
	std::cout << "\033[1;32m multi_m1: \033[0m" << multi_m1 << std::endl;
	std::cout << "\033[1;32m mswap_test: \033[0m" << mswap_test << std::endl;
	std::cout << "\033[1;32m Aggiungiamo un elemento al nostro attuale m1 . . . \033[0m" << std::endl;
	ordered_multiset<int, int_eql, int_decresc> mswap_helper;
	multi_m1.add(mswap_helper);
	std::cout << "\033[1;32m multi_m1: \033[0m" << multi_m1 << std::endl;
	std::cout << "\033[1;32m . . . e rimettiamo le cose a posto\033[0m" << std::endl;
	multi_m1.swap(mswap_test);
	std::cout << "\033[1;32m multi_m1: \033[0m" << multi_m1 << std::endl;
	std::cout << "\033[1;32m mswap_test: \033[0m" << mswap_test << std::endl;
	
	//test differente ordinamento
	ordered_multiset<ordered_multiset<int, int_eql, int_decresc>, multimulti_eql, multimulti_cresc> multi_m2;
	assert(multi_m2.tot_elementi() == 0);
	
	multi_m2.add(m1);
	multi_m2.add(m2);
	multi_m2.add(m3);
	multi_m2.add(m5, 3);
	assert(multi_m2.tot_elementi() == 6);
	
	std::cout << "\033[1;32m Stampa del multiset multi_m2 (ordinato in maniera crescente)\033[0m" << std::endl;
	std::cout << "\033[1;32m multi_m2: \033[0m" << multi_m2 << std::endl;
	
	//test operatore di uguaglianza
	std::cout << "\033[1;32m Controlliamo se multi_m1 e multi_m2, benchè ordinati in maniera differente, sono uguali: \033[0m";
	if(multi_m1 == multi_m2) {
		
		std::cout << "Sì, sono uguali" << std::endl;
		
	} else {
		
		std::cout << "No, non sono uguali" << std::endl;
		
	}
	
	//test remove
	std::cout << "\033[1;32m Rimuoviamo da multi_m2 un'occorrenza di m1 e un'occorrenza di m5\033[0m" << std::endl;
	multi_m2.remove(m1);
	multi_m2.remove(m5);
	assert(multi_m2.tot_elementi() == 4);
	std::cout << "\033[1;32m multi_m2: \033[0m" << multi_m2 << std::endl;
	//test eccezione remove
	std::cout << "\033[1;32m Proviamo a rimuove nuovamente il multiset ordinato m1. Poichè il multiset ordinato m1 non è più presente in multi_m2, dovrebbe lanciare un'eccezione.\033[0m" << std::endl;
	try {
		
		multi_m2.remove(m1);
		
	} catch(const element_not_found(&mex)) {

		std::cout << "\033[1;32m Eccezione catturata correttamente: \033[0m" << mex.what() << std::endl;
		
	}
	
	//test clear
	multi_m2.clear();
	ordered_multiset<ordered_multiset<int, int_eql, int_decresc>, multimulti_eql, multimulti_decresc> mtest_clear;
	assert(multi_m2 == mtest_clear);

	//test copy ctor
	std::cout << "\033[1;32m Costruisco un multiset di multiset di interi ordinato multi_m3 con il copy ctor, copiando i dati da multi_m1. Per testare il corretto funzionamento del metodo ho utilizzato un'assert anzichè una stampa.\033[0m" << std::endl;
	ordered_multiset<ordered_multiset<int, int_eql, int_decresc>, multimulti_eql, multimulti_decresc> multi_m3(multi_m1);
	assert(multi_m1 == multi_m3);
	//std::cout << "multi_m1: " << multi_m1 << std::endl;
	//std::cout << "multi_m3: " << multi_m3 << std::endl;
	
	//test operatore di assegnamento
	std::cout << "\033[1;32m Costruisco un multiset di multiset di interi ordinato multi_m4 con l'operatore di assegnamento, copiando i dati da multi_m1. Per testare il corretto funzionamento del metodo ho utilizzato un'assert anzichè una stampa.\033[0m" << std::endl;
	ordered_multiset<ordered_multiset<int, int_eql, int_decresc>, multimulti_eql, multimulti_decresc> multi_m4;
	multi_m4 = multi_m4; //test autoassegnamento
	multi_m4 = multi_m1;
	assert(multi_m1 == multi_m4);
	//std::cout << "multi_m1: " << multi_m1 << std::endl;
	//std::cout << "multi_m4: " << multi_m4 << std::endl;
	
	//test metodo contains
	bool cont1 = multi_m4.contains(m1);
	assert(cont1 == true);
	ordered_multiset<int, int_eql, int_decresc> m;
	bool cont2 = multi_m4.contains(m);
	assert(cont2 == false);
	
	//test costruttore con iteratori
	ordered_multiset<int, int_eql, int_decresc> am[4] = {m1, m2, m2, m5};
	
	std::cout << "\033[1;32m Creazione di un ordered_multiset usando gli iteratori (crescente)\033[0m" << std::endl;
	ordered_multiset<ordered_multiset<int, int_eql, int_decresc>, multimulti_eql, multimulti_cresc> multi_m6(am, am + 4);
	assert(multi_m6.tot_elementi() == 4);
	std::cout << "\033[1;32m multi_m6: \033[0m" << multi_m6 << std::endl;
	
	std::cout << "\033[1;32m Creazione di un ordered_multiset usando gli iteratori (decrescente)\033[0m" << std::endl;
	ordered_multiset<ordered_multiset<int, int_eql, int_decresc>, multimulti_eql, multimulti_decresc> multi_m7(am, am + 4);
	assert(multi_m7.tot_elementi() == 4);
	std::cout << "\033[1;32m multi_m7: \033[0m" << multi_m7 << std::endl;
	
	//stampa con gli iteratori
	std::cout << "\033[1;32m Stampiamo il contenuto di multi_m6 facendo uso degli iteratori: \033[0m" << std::endl;
	ordered_multiset<ordered_multiset<int, int_eql, int_decresc>, multimulti_eql, multimulti_cresc>::const_iterator b, e;
	ordered_multiset<int, int_eql, int_decresc>::const_iterator bm, em;
	for(b = multi_m6.begin(), e = multi_m6.end(); b != e; ++b) {
		
		for(bm = (*b).begin(), em = (*b).end(); bm != em; ++bm) {
		
			std::cout << *bm << " ";
			
		}
		
	}
	std::cout << std::endl;
	
	//test operatore decremento iteratori
	std::cout << "\033[1;32m Stampiamo il contenuto di multi_m6 al contrario facendo uso degli iteratori: \033[0m" << std::endl;
	ordered_multiset<ordered_multiset<int, int_eql, int_decresc>, multimulti_eql, multimulti_cresc>::const_iterator 
	mult_it_beg = multi_m6.end(), mult_it_end = multi_m6.begin();
	--mult_it_beg;
	--mult_it_end;
	ordered_multiset<int, int_eql, int_decresc>::const_iterator it_beg, it_end;
	
	for(; mult_it_beg != mult_it_end; --mult_it_beg) {
		
		//it_beg = (*mult_it_beg).end();
		//it_end = (*mult_it_beg).begin();
		//--it_beg;
		//--it_end;
		for(it_beg = --(*mult_it_beg).end(), it_end = --(*mult_it_beg).begin(); it_beg != it_end; --it_beg) {
		
			std::cout << *it_beg << " ";
			
		}
		
	}
	std::cout << std::endl;
	
	//test metodo tot_elementi
	unsigned int tot = multi_m6.tot_elementi();
	assert(tot == 4);
	
	//test constness
	const ordered_multiset<ordered_multiset<int, int_eql, int_decresc>, multimulti_eql, multimulti_cresc> multi_m8(am, am + 4);
	//non posso esguire la add su un ordered_multiset const
	//ordered_multiset<int, int_eql, int_decresc> m;
	//multi_m8.add(m);
	//non posso eseguire la remove su un ordered_multiset const
	//multi_m8.remove(m2);
	//non posso eseguire la clear su un ordered_multiset const
	//multi_m8.clear();
	
	std::cout << std::endl;
	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {

	test_int();
	
	test_string();
	
	test_Z3();
	
	test_point();
	
	test_contact();
	
	test_multimulti_int();
	
	return 0;
	
}