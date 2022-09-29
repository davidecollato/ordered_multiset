#ifndef ELEMENT_NOT_FOUND_H
#define ELEMENT_NOT_FOUND_H

#include <stdexcept>
#include <string>

/**
	@brief Eccezione custom element_not_found
	
	Eccezione custom element_not_found derivata dalla classe std::logic_error. Questa eccezione viene lanciata in particolare nel metodo remove quando si cerca di rimuovere un elemento che non è più presente nel multiset ordinato.
	Si è scelto di derivare l'eccezione dalla classe std::logic_error in quanto il tentativo di rimuovere un elemento non presente nel multiset ordinato è un'azione prevedibile dal programmatore.
*/

class element_not_found : public std::logic_error {
	
public:

	/**
		@brief Costruttore secondario
		
		Costruttore che istanzia un'eccezione di elemento non trovato, inizializzandola con il suo messaggio d'errore
		
		@param mex messaggio dell'errore
	*/
	element_not_found(const std::string &mex);
	
};

#endif
