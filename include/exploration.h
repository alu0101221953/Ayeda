#ifndef EXPLORATION_H
#define EXPLORATION_H
// Funciones de exploracion para la tabla hash

#include "dispersion.h"

/**
 * Clase abstracta ExplorationFunction
*/
template<class Key>
class ExplorationFunction { // Clase abstracta
	public:
		/**
		 * @brief Funcion de exploracion
		 * @param k Clave a explorar
		 * @param i Intento
		 * @return Posicion explorada
		*/
		virtual unsigned operator()(const Key& k, const unsigned i) const = 0;
		virtual unsigned getExplorations() const = 0;
};

/**
 * Clase efLineal
 * Funcion de exploracion lineal
*/
template<class Key>
class efLineal : public ExplorationFunction<Key> {
	public:
		/**
		 * @brief Funcion de exploracion
		 * @param k Clave a explorar
		 * @param i Intento
		 * @return Posicion explorada
		*/
		unsigned operator()(const Key& k, const unsigned i) const;
		unsigned getExplorations() const { return _explorations; }
	private:
		mutable unsigned _explorations = 0;
};

/**
 * Clase efCuadratica
 * Funcion de exploracion cuadratica
*/
template<class Key>
class efCuadratica : public ExplorationFunction<Key> {
	public:
		/**
		 * @brief Funcion de exploracion
		 * @param k Clave a explorar
		 * @param i Intento
		 * @return Posicion explorada
		*/
		unsigned operator()(const Key& k, const unsigned i) const;
		unsigned getExplorations() const { return _explorations; }
	private:
		mutable unsigned _explorations = 0;
};

/**
 * Clase efDispersionDoble
 * Funcion de exploracion con dispersion doble
*/
template<class Key>
class efDispersionDoble : public ExplorationFunction<Key> {
	public:
		/**
		 * @brief Constructor
		 * @param f Funcion de dispersion
		*/
		efDispersionDoble(const DispersionFunction<Key>* f) : _fd(f) {};

		/**
		 * @brief Destructor
		*/
		~efDispersionDoble();

		/**
		 * @brief Funcion de exploracion
		 * @param k Clave a explorar
		 * @param i Intento
		 * @return Posicion explorada
		*/
		unsigned operator()(const Key& k, const unsigned i) const;

		unsigned getExplorations() const { return _explorations; }
	private:
		const DispersionFunction<Key>* _fd;
		mutable unsigned _explorations = 0;
};

// En la implementación de la estrategia de exploración por redispersión se utiliza el
// generador de números pseudo-aleatorios. Se inicializa la semilla del generador con
// el valor de la clave, srand(k), y se retorna el valor de la i-ésima llamada a rand() como el valor de desplazamiento f(i)(k).
/**
 * Clase efRedispersion
 * Funcion de exploracion con redispersion
*/
template<class Key>
class efRedispersion : public ExplorationFunction<Key> {
	public:
		/**
		 * @brief Constructor
		 * @param 
		*/
		efRedispersion(const unsigned n);

		/**
		 * @brief Destructor
		*/
		~efRedispersion();

		/**
		 * @brief Funcion de exploracion
		 * @param k Clave a explorar
		 * @param i Intento
		 * @return Posicion explorada
		*/
		unsigned operator()(const Key& k, const unsigned i) const;
		unsigned getExplorations() const { return _explorations; }
	private:
		mutable DispersionFunction<Key>* fd;
		unsigned _tableSize;
		mutable unsigned _explorations = 0;
};



// Implementación de las funciones de exploración

template<class Key> 
unsigned efLineal<Key>::operator()(const Key& k, const unsigned i) const {
	_explorations++;
	return i;
}

template<class Key>
unsigned efCuadratica<Key>::operator()(const Key& k, const unsigned i) const {
	_explorations++;
	return (i * i);
}

template<class Key>
efDispersionDoble<Key>::~efDispersionDoble() {
	delete _fd;
}

template<class Key>
unsigned efDispersionDoble<Key>::operator()(const Key& k, const unsigned i) const {
	_explorations++;
	return i * (*_fd)(k);
}

template<class Key>
efRedispersion<Key>::efRedispersion(const unsigned n) : _tableSize(n) {
	switch (rand() % 3) {
		case 0: fd = new dfSuma<Key>(n); 
			break;
		case 1: fd = new dfPseudoaleatoria<Key>(n); 
			break;
		case 2: fd = new dfSuma<Key>(n); 
			break;
	}
}

template<class Key>
efRedispersion<Key>::~efRedispersion() {
	delete fd;
}

template<class Key>
unsigned efRedispersion<Key>::operator()(const Key& k, const unsigned i) const {
	_explorations++;
	srand(static_cast<unsigned>(k));
	return (*fd)(k) % _tableSize;
}

#endif