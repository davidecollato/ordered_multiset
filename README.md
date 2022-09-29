# Multiset Ordinato

Questa repository contiene il progetto del corso di Programmazione C++ (Unimib) dell'appello del 26 Settembre 2022. Questo consisteva nella scrittura di una classe che rappresentasse un multiset ordinato minimizzando l'uso della memoria, cioè implementarlo come un array dinamico di coppie <valore, occorrenze> anziché usando una struttura a lista (puntatore a next).
La traccia del progetto è contenuta nel file Esame-220926.pdf.


# Files

La cartella contiene:

 - multiset.h in cui è descritto il funzionamento della classe;
 - element_not_found.h, element_not_found.cpp che sono due file con lo scopo di implementare un'eccezione custom che vado a lanciare quando provo a rimuovere dal multiset ordinato un elemento non presente al suo interno;
 - main.cpp dove sono stati svolti test sulla classe, specializzandola su differenti tipi di dato, primitivi e custom
 - il makefile per eseguire la compilazione automatica del progetto (contiene anche l'istruzione per compilare in modalità release);
 - il doxyfile, che, avendo installato doxygen e lanciandolo da terminale, permette la creazione della documentazione del progetto;
 - la relazione in cui viene brevemente riassunto come è stata implementata la classe;
 - il pdf contenente il testo dell'appello d'esame.

## Osservazioni 

Nell'implementazione del metodo che aggiunge una o più occorrenze di un valore (add)  e nel metodo che rimuove un'occorrenza di un valore (remove) se questo è presente nel multiset, vado a creare un ordered_multiset temporaneo rispettivamente di _size+1 o _size-1 (se rimuovo un'occorrenza di un elemento che possiede una sola occorrenza, allora lo elimino dal multiset). Ad esempio nel caso della add eseguo le seguenti istruzioni:

    ordered_multiset tmp(*this);
	tmp.clear();
	tmp._head = new element[_size + 1];
	tmp._size = _size + 1;

e in seguito eseguo i vari assegnamenti per riempire l'array temporaneo con l'elemento che voglio inserire (seguendo l'ordinamento) ed eseguo una swap per cui alla fine ```this``` è il multiset modificato, mentre ```tmp``` contiene il vecchio stato di this. Poiché ```tmp``` è un dato automatico, uscendo di scope viene automaticamente deallocato dal distruttore. Ora, benché nell'esecuzione degli assegnamenti potrei avere delle eccezioni, in quanto sto trattando dei dati generici, non necessito di un blocco try-catch in quanto, anche quando venisse generata un'eccezione, viene prima deallocato tutto dallo stack, ```tmp``` compreso, evitando in questo modo memory leak. Questo fenomeno è detto **stack unwinding** (non affrontato a lezione, ma provando a scatenare eccezioni on purpose questo è esattamente quello che accade).
Se volete evitare rogne per questa storia dello stack unwinding, un'alternativa potrebbe essere creare un costruttore di ordered_multiset privato che prende in input la size con cui inizializzare l'array. A quel punto l'istruzione sopra diventerebbe

    ordered_multiset tmp(_size+1);

Mettere comunque i vari assegnamenti in un blocco try-catch non viene considerato errore.

## Valutazione progetto 
Il progetto ha ricevuto

 - Una penalizzazione nella relazione per un errore sintattico (-1) (corretto);
 - main.cpp: Molti test strutturati bene anche su tipi custom (point, contact, multiset) (+1)
