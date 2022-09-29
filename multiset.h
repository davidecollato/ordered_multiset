#ifndef OMSET_H
#define OMSET_H

#include "element_not_found.h"
#include <algorithm>
#include <ostream>
#include <iostream>
#include <iterator> // std::bidirectional_iterator_tag
#include <cstddef>  // std::ptrdiff_t
#include <cassert>

/**
	@brief Classe ordered_multiset
	
	La classe implementa un ordered_multiset di elementi generici T.
	
	Si è utilizzata come struttura di supporto una struct element che contiene
	un dato di tipo T, value, e un unsigned int, ocnumber, che rappresenta il numero di occorrenze associate al valore value.
	In questo modo il multiset è visto come un array di coppie <valore, occorrenze>.
*/

template <typename T, typename Eql, typename Comp>
class ordered_multiset {
	
public:
	
	typedef unsigned int size_type; ///< tipo del dato _size e del dato ocnumber
	typedef T value_type; ///< tipo del dato value membro della struct element
	
private:

	/**
		@brief Struct Element
		
		Struttura dati di supporto che rappresenta l'elemento contenuto nel multiset ordinato, formato da un valore e il suo numero 
		di occorrenze
	*/
	
	struct element {
		
		value_type value; ///< valore dell'elemento
		size_type ocnumber; ///< numero di occorrenze dell'elemento
		
		/**
			@brief Costruttore di default
			
			Costruttore di default. Può lanciare un'eccezione in quanto inizializza il dato membro di tipo T
			con il suo costruttore di default.
			
			@throw std::bad_alloc possibile eccezione di allocamento
			
			@post ocnumber == 0
		*/
		element() : ocnumber(0) {}
		
		/**
			@brief Costruttore secondario
			
			Costruttore di default che prende come parametri un dato di tipo T e uno di tipo unsigned int 
			con cui inizializzare i dati membro della struct.
			
			@param v valore con cui inizializzare value
			@param ocn numero di occorrenze di v con cui inizializzo ocnumber
			
			@post value == v
			@post ocnumber == ocn
		*/
		element(const value_type &v, size_type ocn) : value(v), ocnumber(ocn) {}
		
		/**
			@brief Costruttore secondario
			
			Costruttore di default che prende come parametro un dato di tipo T 
			con cui inizializzo il dato membro della struct value e, non essendo specificato, pongo il numero di occorrenze a 1
			
			@param v valore con cui inizializzare value
			
			@post value == v
			@post ocnumber == 1
		*/
		explicit element(const value_type &v) : value(v), ocnumber(1) {}
		
		/**
			@brief Copy constructor.
			
			Copy constructor. Copiamo i dati membro a membro. In questo caso 
			essendo una struttura dati di supporto a ordered_multiset, accettiamo la condivisione dei dati.
			
			@param other struct element da copiare
			
			@post value == other.value
			@post ocnumber == other.ocnumber
		*/
		element(const element &other) : value(other.value), ocnumber(other.ocnumber) {}
		
		/**
			@brief Distruttore
			
			Distruttore della classe element. Non avendo allocaato nulla sullo heap, il costruttore è vuoto.
		*/
		~element() {}
		
		/**
			@brief Operatore di assegnamento
			
			Operatore di assegnamento. Assegna ai dati membro di this il valore dei dati membro di other.
			
			@param other element da copiare
			
			@return reference all'element this
			
			@post value == other.value
			@post ocnumber == other.ocnumber
		*/
		element &operator=(const element &other) {
			
			if(this != &other) {
				
				value = other.value;
				ocnumber = other.ocnumber;
				
			}
			
			return *this;
			
		}
		
	}; //fine struct element
	
	element *_head; ///< Puntatore che punta al primo elemento del multiset ordinato
	size_type _size; ///< Numero di elementi contenuti nel multiset ordinato (senza ripetizioni)
	Eql _equals; ///< Funtore di uguaglianza
	Comp _compare; ///< Funtore di confronto
	
	/**
		@brief Metodo find
	
		Metodo prende in input un valore e restituisce un puntatore all'elemento che contiene il valore desiderato. 
		Se tale elemento non esiste, viene restituito nullptr.
		
		@param v valore desiderato che voglio cercare
		
		@post puntatore all'element che ha il valore v come dato membro
	*/
	element* find(const value_type &v) const {
		
		for(size_type i = 0; i < _size; ++i) {
			
			if(_equals(_head[i].value, v)) {
				
				return &_head[i];
				
			}
			
		}
		
		return nullptr;
		
	}
	
public: 
	
	/**
		@brief Costruttore di default
		
		Costruttore di default. Inizializzo _head a nullptr e _size a 0.
		
		@post _head == nullptr
		@post _size == 0
	*/
	ordered_multiset() : _head(nullptr), _size(0) {}
	
	/**
		@brief Distruttore
		
		Distruttore della classe ordered_multiset. Rimuove dallo heap l'array dinamico allocato in precedenza. 
		Fa uso del metodo clear.
		
		@post _head == nullptr
		@post _size == 0
	*/
	~ordered_multiset() {
		
		clear();
		
	}
	
	/**
		@brief Metodo clear
		
		Metodo di supporto per il distruttore il cui compito è svuotare il multiset di tutti i suoi elementi. 
		Chiama la delete sul puntatore _head, che richiama il distruttore di element sugli element 
		contenuti nel multiset, e poi porta tutto in uno stato coerente, ponendo _head a nullptr e azzerando la _size.
		
		@post _head == nullptr
		@post _size == 0
	*/
	void clear() {
		
		delete[] _head;
		_head = nullptr;
		_size = 0;
		
	}
	
	/**
		@brief Metodo swap
		
		Metodo swap che agisce tra due ordered_multiset scambiandone il contenuto.
		
		@param other ordered_multiset con cui scambiare i dati membro.
	*/
	void swap(ordered_multiset &other) {
		
		std::swap(_head, other._head);
		std::swap(_size, other._size);
		
	}
	
	/**
		@brief Operatore di assegnamento
		
		Operatore di assegnamento che copia il contenuto di other in *this.
		
		@param other ordered_multiset da copiare
		
		@return reference al ordered_multiset this
		
		@post _size == other._size
	*/
	ordered_multiset& operator=(const ordered_multiset &other) {
		
		if(this != &other) {
			
			ordered_multiset tmp(other);
			swap(tmp);
			
		}
		
		return *this;
		
	}
	
	/**
		@brief Copy constructor
		
		Copy constructor della classe ordered_multiset che inizializza il multiset ordinato this con il contenuto di other.
		Viene creato un array dinamico avente lunghezza pari alla lunghezza dell'array di other e, in un blocco try-catch, 
		vengono copiati in this gli elementi di other e viene settata la _size di this uguale alla _size di other. 
		Se un assegnamento fallisce, per non avere un oggetto in uno stato non coerente, viene chiamata la clear su this 
		e si restituisce l'eccezione al chiamante.
		
		@param other ordered_multiset da copiare
		
		@throw std::bad_alloc possibile eccezione di allocamento
		
		@post _size == other._size
	*/
	ordered_multiset(const ordered_multiset &other) : _head(nullptr), _size(0) {
		
		_head = new element[other._size];
		
		try {
			
			for(size_type i = 0; i < other._size; ++i) {
				
				_head[i] = other._head[i];
				
			}
			
			_size = other._size;
			
		} catch(...) {
			
			clear();
			throw;
			
		}
		
	}
	
	/**
		@brief Metodo tot_elementi
		
		Metodo che ritorna per copia il numero totale di elementi contenuti nel multiset ordinato. 
		Ritornandolo per copia, non è modificabile dall'utente.
		
		@return numero totale di elementi contenuti nel ordered_multiset
	*/
	size_type tot_elementi() const {
		
		size_type tot = 0;
		
		for(size_type i = 0; i < _size; ++i) {
			
			tot += occurrencies(_head[i].value);
			
		}
		
		return tot;
		
	}
	
	/**
		@brief Metodo occurrencies
		
		Metodo che prende come parametro un valore e, se esso è contenuto nel multiset ordinato, allora 
		ne ritorna il numero di occorrenze, altrimenti ritorna 0. 
		Ritornando il numero di occorrenze per copia, non è modificabile dall'utente.
		
		@param v valore di cui voglio conoscere le occorrenze
		
		@return numero di occorrenze di v
	*/
	size_type occurrencies(const value_type &v) const {
		
		for(size_type i = 0; i < _size; ++i) {
			
			if(_equals(v, _head[i].value)) {
				
				return _head[i].ocnumber;
				
			}
			
		}
		
		return 0;
		
	}
	
	/**
		@Metodo add
		
		Metodo che prende come parameto un valore e lo aggiunge al multiset ordinato, seguendo la policy d'ordine implementata 
		dall'utente.
		Se invece il valore che voglio inserire è già presente all'interno del multiset, ne aggiunge un'occorrenza.
		L'aggiunta del valore nel multiset avviene attraverso la creazione di un multiset temporaneo tmp (creato con 
		copy constructor da this) che viene successivamente svuotato e la cui _size viene aumentata di 1, in modo da accogliere 
		il nuovo elemento. Successivamente cerco l'indice (index) in cui inserire il nuovo elemento, se questo non viene trovato, 
		allora il nuovo elemento deve essere inserito in coda al multiset tmp, quindi pongo index = this->_size. 
		A questo punto riempio tmp con gli elementi contenuti in this fino a index, nella posizione index-esima inserisco 
		l'elemento (inizializzato con il valore di input e avente 1 occorrenza) e poi inserisco gli elementi che mancano. 
		Per finire eseguo una swap dei dati di this con quelli di tmp, per cui ora this è un multiset ordinato con il nuovo 
		valore inserito e invece tmp contiene i vecchi dati di this. Uscendo dallo scope del metodo, tmp viene eliminato dal 
		distruttore.

		Lavorando su un dato temporaneo, non necessito di un blocco try-catch, in quanto i dati di this non vengono 
		modificati se non con la swap, però se arrivo a quel punto vuol dire che tutto è andato per il verso giusto.
		
		@param valore da inserire nel ordered_multiset (seguendo l'ordine)
		
		@throw std::bad_alloc possibile eccezione di di allocazione
	*/
	void add(const value_type &v) {

		if(occurrencies(v) > 0) {
			
			element *e = find(v);
			e->ocnumber += 1;
			
		} else {

			ordered_multiset tmp(*this);
			tmp.clear();
			tmp._head = new element[_size + 1];
			tmp._size = _size + 1;

			size_type index = 0;
			
			for(size_type i = 0; i < _size; ++i) {

				if(_compare(v, _head[i].value)) { //cerco l'indice in cui inserire l'elemento v
					
					index = i + 1;
					
				}
			}
			
			if(_size != 0 && _compare(v, _head[_size - 1].value)) { //se non lo trovo, devo inserirlo in coda
				
				index = _size;
				
			}

			for(size_type i = 0; i < index; ++i) {

				tmp._head[i] = _head[i];
				
			}
			
			element e(v);
			tmp._head[index] = e;
			
			for(size_type i = index + 1; i < _size + 1; ++i) {
				
				tmp._head[i] = _head[i-1];
				
			}
			
			swap(tmp);
			
		}
		
	}
	
	/**
		@brief Metodo add
		
		Metodo che prende come valore un parametro di tipo T che rappresenta il valore che voglio aggiungere al 
		multiset (seguendo la policy specificata dall'utente) e un unsigned int che rappresenta il numero di 
		occorrenze che voglio aggiungerne.
		La logica con cui l'inserimento è gestito è la stessa del metodo add che non prende come 
		parametro il numero di occorrenze che voglio aggiungere.
		
		@param v valore da inserire nel ordered_multiset (seguendo l'ordine)
		@param ocn occorrenze del valore da inserire
		
		@throw std::bad_alloc possibile eccezione di allocazione
	*/
	void add(const value_type &v, size_type ocn) {

		if(occurrencies(v) > 0) {
			
			element *e = find(v);
			e->ocnumber += ocn;
			
		} else {

			ordered_multiset tmp(*this);
			tmp.clear();
			tmp._head = new element[_size + 1];
			tmp._size = _size + 1;

			size_type index = 0;
			
			for(size_type i = 0; i < _size; ++i) {

				if(_compare(v, _head[i].value)) {
					
					index = i + 1;
					
				}
			}
			
			if(_size != 0 && _compare(v, _head[_size - 1].value)) {
				
				index = _size;
				
			}
			
			for(size_type i = 0; i < index; ++i) {
				
				tmp._head[i] = _head[i];
				
			}
			
			element e(v, ocn);
			tmp._head[index] = e;
			
			for(size_type i = index + 1; i < _size + 1; ++i) {
				
				tmp._head[i] = _head[i-1];
				
			}
			
			swap(tmp);
			
		}
		
	}
	
	/**
		@brief Metodo remove
		
		Metodo che prende in input un dato di tipo T che rappresenta il valore da rimuovere; se tale valore 
		è presente nel multiset, allora ne rimuove un'occorrenza, altrimenti lancia un'eccezione custom per segnalare 
		all'utente che tale valore non è presente nel multiset.
		La logica con cui gestisco la rimozione è la seguente: se il valore v non è inserito 
		nel multiset (il suo numero di occorrenze è zero) lancio l'eccezione custom al chiamante, altrimenti, se 
		il valore è effettivamente inserito nel multiset ordinato, mi si presentano due strade da percorrere. 
		La prima è se il valore v ha 1 sola occorrenza all'interno del multiset ordinato, devo quindi rimuovere 
		l'unica occorrenza del valore v dal multiset, cioè devo eliminare v dal multiset ordinato. 
		Allora creo un multiset ordinato temporaneo di _size pari a this->_size - 1, quindi vi ricopio dentro 
		tutti i dati di this eccetto il valore che voglio rimuovere e infine eseguo la swap tra this e tmp. 
		Per cui ora this è un multiset ordinato con il valore preso come parametro rimosso e invece tmp contiene 
		i vecchi dati di this. Uscendo dallo scope del metodo, tmp viene eliminato dal distruttore.

		Lavorando su un dato temporaneo, non necessito di un blocco try-catch, in quanto i dati di this 
		non vengono modificati se non con la swap, però se arrivo a quel punto vuol dire che tutto è andato per il verso giusto.

		Se invece il numero di occorrenze del valore v è maggiore di 1, allora semplicemente ne 
		diminuisco di 1 il numero di occorrenze.
		
		@param v valore di cui rimuovere l'occorrenza
	*/
	void remove(const value_type &v) {
		
		if(occurrencies(v) == 0) {
			
			throw element_not_found("Elemento non trovato");
			
		} else {
			
			for(size_type i = 0; i < _size; ++i) {
				
				if(_equals(_head[i].value, v)) {
					
					if(_head[i].ocnumber == 1) {
						
						ordered_multiset tmp(*this);
						tmp.clear();
						tmp._head = new element[_size - 1];
						tmp._size = _size - 1;
						
						size_type index = 0;
						
						for(size_type i = 0; i < _size; ++i) {
							
							if(!_equals(_head[i].value, v)) {
								
								tmp._head[index++] = _head[i];
								
							}
							
						}
						
						swap(tmp);
						
					} else {
						
						_head[i].ocnumber -= 1;
						
					}
					
					break;
					
				}
				
			}
			
		}
		
	}
	
	/**
		@Metodo contains
		
		Metodo che ritorna true se l'elemento in input è contenuto nel ordered_multiset. 
		Fa uso del metodo privato find, infatti il metodo find restituisce il puntatore all'elemento 
		che ha il valore v come dato membro (se esiste, altrimenti ritorna nullptr), che salvo nella variabile e. 
		Quindi faccio ritornare al metodo il risultato dell'operazione logica (e != nullptr) che ritrona true 
		se è un puntatore diverso da nullptr, cioè se il valore v è contenuto nel multiset. 
		Ritornando il booleano per copia, questi non è modificabile dall'utente.
		
		@param v valore che voglio sapere se sia contenuto nel multiset
		
		@return true se il valore v è contenuto nel multiset ordinato, altrimenti false
	*/
	bool contains(const value_type &v) const {
		
		element *e = find(v);
		return (e != nullptr);
		
	}
	
	/**
		@brief Costruttore con iteratori
		
		Costruttore che costruisce un ordered_multiset a partire da una coppia di iteratori. 
		Gli iteratori possono essere di qualunque tipo. 
		La logica del metodo è quella di scorrere sugli iteratori (dall'iteratore di inizio sequenza a 
		quello di fine sequenza) ed aggiungere, tramite i metodo add, al multiset ordinato 
		il valore puntato dall'iteratore (l'iteratore è implementato come un puntatore alla struct element). 
		Se l'aggiunta di un qualche elemento dovesse fallire, allora richiamo il metodo clear per 
		riportare this in uno stato coerente, non rischiando di avere un multiset ordinato riempito solo in parte.
		
		@param b iteratore di inizio sequenza
		@param e iteratore di fine sequenza
		
		@throw std::bad_alloc possibile eccezione di allocazione
	*/
	template <typename Iter>
	ordered_multiset(Iter b, Iter e) : _head(nullptr), _size(0) {
		
		try {
			
			for(; b != e; ++b) {
				
				add(static_cast<T>(*b));
				
			}
			
		} catch(...) {
			
			clear();
			throw;
			
		}
		
	}
	
	/**
		@brief Operatore di uguaglianza
		
		Operatore di uguaglianza che ritorna true se i multiset ordinati other e this, contengono gli stessi valori 
		con le stesse occorrenze anche in caso di policy di ordinamento differente. 
		Il metodo esegue un controllo anzitutto sul numero di elementi totale di this e di other: se questi 
		dovessero essere differenti, allora certamente i due multiset ordinati sono differenti, e quindi ritorno false.
		Se invece hanno lo stesso numero totale di elementi (ossia la cardinalità del multiset ordinato, quindi 
		la somma di tutte le occorrenze) allora controllo, dentro ad un ciclo for, se l'i-esimo elemento di this 
		ha lo stesso numero di occorrenze sia in this che in other. Se ciò non avviene, ritorno false, altrimenti ritorno true.
		Si noti che il multiset ordinato preso come parametro dal metodo è templato sul funtore 
		di ordinamento, di modo che other possa avere un ordinamento differente da this.
		
		@param other ordered_multiset da comparare con this
		
		@return true se other e this contengono gli stessi valori con le stesse occorrenze
	*/
	template <typename CompOther>
	bool operator==(const ordered_multiset<T, Eql, CompOther> &other) const {
		
		if(tot_elementi() != other.tot_elementi()) {
			
			return false;
			
		}
		
		for(size_type i = 0; i < _size; ++i) {
			
			if(occurrencies(_head[i].value) != other.occurrencies(_head[i].value)) {
				
				return false;
				
			}
			
		}
		
		return true;
		
	}
	
	/**
		@brief Operatore di stream
		
		Funzione globale che implementa l'operatore di stream, stampando il multiset ordinato 
		come coppie di valore con le sue occorrenze:
		{<X1, occorrenzeX1>, ..., <Xn, occorrenzeXn>}. La keyword friend è messa per poter accedere ai dati privati della classe.
		
		@param os stream di output
		@param ms ordered_multiset da spedire sullo stream
		
		@return lo stream di output
	*/
	friend std::ostream &operator<<(std::ostream &os, const ordered_multiset &ms) {
		
		os << "{";
		
		if(ms._size > 0) {
			for(size_type i = 0; i < ms._size - 1; ++i) {
			
				os << "<" << ms._head[i].value << ", " << ms._head[i].ocnumber << ">, ";
				
			}
		}
		
		if(ms._size > 0) {
			
			os << "<" << ms._head[ms._size - 1].value << ", " << ms._head[ms._size - 1].ocnumber << ">";
			
		}
		
		os << "}";
		return os;
		
	}
	
	/**
		@brief Classe const_iterator di tipo bidirectional
		
		Iteratore const di tipo bidirectional. Ho implementato solamente il const_iterator in quanto 
		nel testo dell'esame viene specificato che deve essere un iteratore di sola lettura. 
		Ho implementato un iteratore di tipo bidirectional in quanto, non essendo gli elementi 
		del multiset in un ordine casuale, ma ordinati secondo un preciso ordine specificato dalla policy 
		di ordinamento, ho ritrenuto che potesse aver senso oltre a scorrere in avanti il multiset anche scorrere in verso opposto.
	*/
	class const_iterator {
		//	
	public:
		typedef std::bidirectional_iterator_tag 		iterator_category;
		typedef T                         				value_type;
		typedef ptrdiff_t                 				difference_type;
		typedef const T*                  				pointer;
		typedef const T&                  				reference;

	
		const_iterator() : ptr(nullptr), count(0) {}
		
		const_iterator(const const_iterator &other) : ptr(other.ptr), count(other.count) {}

		const_iterator& operator=(const const_iterator &other) {
			
			ptr = other.ptr;
			count = other.count;
			return *this;
			
		}

		~const_iterator() {}

		// Ritorna il dato riferito dall'iteratore (dereferenziamento)
		reference operator*() const {
			
			return ptr->value;
			
		}

		// Ritorna il puntatore al dato riferito dall'iteratore
		pointer operator->() const {
			
			return &(ptr->value);
			
		}
		
		// Operatore di iterazione post-incremento
		/**
			@brief Operatore di iterazione post-incremento
			
			Operatore di post-incremento che sfrutta la variabile contatore inserita come dato membro nella classe const_iterator. 
			La logica di implementazione è fondamentalmente la stessa dell'operatore di pre-incremento, 
			ciò che cambia è che, dovendo ritornare lo stato precedente di ptr (e non lo stato modificato come 
			nel caso dell'operatore di pre-incremento), salvo in un const_iterator temporaneo il vecchio stato 
			di this, opero su this, e ritorno tmp, cioè il vecchio stato di this.
			
			@return il vecchio stato di this (ossia il puntatore a element non modificato dall'operatore)
		*/
		const_iterator operator++(int) {
			
			const_iterator tmp(*this);
			
			if(count == 0) {
				
				count = ptr->ocnumber;
				
			}
			
			if(count > 0 && --count == 0) {
				
				++ptr;
				count = 0;
				
			}
			
			return tmp;
			
		}

		// Operatore di iterazione pre-incremento
		/**
			@brief Operatore di iterazione pre-incremento
			
			Operatore di pre-incremento che sfrutta la variabile contatore inserita come dato membro nella classe const_iterator. 
			La logica è la seguente: se la variabile contatore è pari a 0 (cioè è la prima volta che eseguo 
			questa operazione, in quanto la variabile contatore è inizializzata a zero dal costruttore privato e da quello di default) 
			allora pongo la variabile contatore count pari al numero di occorrenze del valore contenuto 
			nell'elemento puntato da ptr (ptr è un puntatore a element). 
			A questo punto il puntatore ptr continua a puntare allo stesso valore fino a quando ho esaurito 
			il numero di occorrenze del valore: solo a quel punto, cioè quando è soddisfatta la condizione del secondo if, 
			permetto a ptr di spostarsi all'elemento successivo del multiset, non prima però di aver 
			settato a 0 la variabile contatore.
			
			@return reference a ptr (modificato)
		*/
		const_iterator& operator++() {
			
			if(count == 0) {
				
				count = ptr->ocnumber;
				
			}
			
			if(count > 0 && --count == 0) {
				
				++ptr;
				count = 0;
				
			}
			
			return *this;
			
		}
		
		// Operatore di iterazione post-decremento
		/**
			@brief Operatore di iterazione post-decremento
			
			Operatore di post-decremento che sfrutta la variabile contatore inserita come dato membro nella classe const_iterator. 
			La logica di implementazione è fondamentalmente la stessa dell'operatore di pre-decremento, 
			ciò che cambia è che, dovendo ritornare lo stato precedente di ptr (e non lo stato modificato 
			come nel caso dell'operatore di pre-decremento), salvo in un const_iterator temporaneo il vecchio 
			stato di this, opero su this, e ritorno tmp, cioè il vecchio stato di this.
			
			@return il vecchio stato di this (ossia il puntatore a element non modificato dall'operatore)
		*/
		const_iterator operator--(int) {
			
			const_iterator tmp(*this);
			
			++count;
			
			if(count == 1) {
				
				--ptr;
				
			}else if(count > ptr->ocnumber) {
				
				--ptr;
				count = 1;
				
			}

			return tmp;
		}

		// Operatore di iterazione pre-decremento
		/**
			@brief Operatore di iterazione pre-decremento
			
			Operatore di pre-decremento che sfrutta la variabile contatore inserita come dato membro nella classe const_iterator. 
			La logica è la seguente: incrementiamo la variabile count. 
			Se count vale 1 (ossia sono entrato nel metodo con count == 0) allora semplicemente mi sposto 
			a sinistra (ora count vale 1); se invece count supera il numero di occorrenze dell'elemento a cui sto puntando, 
			decremento ptr e setto count a 1.
			Il primo if serve in realtà per gestire il caso in cui, ad esempio, inizializzo un iteratore 
			con end() e poi lo decremento. Inizializzando il vettore con end(), il puntatore ptr dell'iteratore punta all'elemento appena fuori dal multiset e il numero di occorrenze sono pari a zero. Se decremento tale iteratore, allora, poiché count vale zero, setto count a 1 e sposto il puntatore dall'elemento appena fuori dal multiset all'ultimo elemento del multiset.
			
			@return reference a ptr (modificato)
		*/
		const_iterator &operator--() {
			
			++count;
			
			if(count == 1) {
				
				--ptr;
				
			} else if(count > ptr->ocnumber) {
				
				--ptr;
				count = 1;
				
			}
			
			return *this;
			
		}

		// Uguaglianza
		/**
			@brief Operatore di uguaglianza
			
			Operatore di uguaglianza che ritorna true se due iteratori sono uguali. La logica dell'operatore è la seguente: 
			anzitutto, tramite copy constructor, creo una copia di *this, tmp, e una copia dell'iteratore passato 
			come parametro, temp. A seguire utilizzo l'operatore di pre-decremento sia su tmp che su temp e in seguito 
			ritorno true se i dati membro di tmp e di temp (quindi ptr e count, ricordiamo che tmp contiene gli stessi elementi 
			di *this e temp contiene gli stessi elementi di other) sono uguali, altrimenti ritorniamo false. 
			L'idea è che se, decrementando i due iteratori di partenza, ottengo degli iteratori uguali, allora questi 
			puntavano alla stessa occorrenza del valore. Così facendo, ad esempio, due iteratori che puntano allo stesso 
			elemento ma ad una diversa occorrenza sono diversi, mentre invece in questo caso particolare
			
				ordered_multiset<int, int_eql, int_cresc> o;
				o.add(2);
				ordered_multiset<int, int_eql, int_cresc>::const_iterator begin, end;
				begin = o.begin();
				end = o.end();
				--end;
				assert(begin == end);
			
			la condizione della assert è vera. Perchè tanta attenzione su questo caso particolare? 
			Perché quando inizializzo gli iteratori begin e end, questi hanno count == 0. 
			Decrementando end, questo punta allo stesso elemento di begin ma, per come ho scritto l'operatore di decremento, 
			ora end.count == 1 e, se mi fossi limitato semplicemente a controllare che begin.count == end.count allora 
			avrei ottenuto che begin ed end non sarebbero stati uguali pur puntando allo stesso elemento, cosa altamente 
			sbagliata da un punto di vista logico. 
			Decrementando prima entrambi i puntatori, le rispettive count vengono settate a 1 e quindi ho l'uguaglianza desiderata.
			
			@param other iteratore da confrontare con this
			
			@return true se i due iteratori sono uguali, false altrimenti
		*/
		bool operator==(const const_iterator &other) const {
			
			const_iterator tmp(*this);
			const_iterator temp(other);
			
			--tmp;
			--temp;
			
			if(tmp.ptr == temp.ptr && tmp.count == temp.count) {
				
				return true;
				
			}
			
			return false;
			
		}
		
		// Diversita'
		bool operator!=(const const_iterator &other) const {
			
			return !(*this == other);
			
		}

	private:
		//Dati membro
		const element *ptr; ///< puntatore ad un elemento
		size_type count; ///< variabile contatore di appoggio (serve per post e pre incremento)

		// La classe container deve essere messa friend dell'iteratore per poter
		// usare il costruttore di inizializzazione.
		friend class ordered_multiset; // !!! Da cambiare il nome!

		// Costruttore privato di inizializzazione usato dalla classe container
		// tipicamente nei metodi begin e end
		const_iterator(const element *e) : ptr(e), count(0) {}
		
		// !!! Eventuali altri metodi privati
		
	}; // classe const_iterator
	
	// Ritorna l'iteratore all'inizio della sequenza dati
	const_iterator begin() const {
		return const_iterator(_head);
	}
	
	// Ritorna l'iteratore alla fine della sequenza dati
	const_iterator end() const {
		return const_iterator(_head + _size);
	}
	
};

#endif