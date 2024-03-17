#ifndef DISPERSION_H
#define DISPERSION_H
// Funciones de dispersion para la tabla hash

#include <cstdlib>

/**
 * Clase abstracta DispersionFunction
*/
template<class Key>
class DispersionFunction { // Clase abstracta
	public:
		/**
		 * @brief Funcion de dispersion
		 * @param k Clave a dispersar
		 * @return Valor dispersado
		*/
		virtual unsigned operator()(const Key& k) const = 0;
};

/**
 * Clase dfModulo
 * Funcion de dispersion por modulo
*/
template<class Key>
class dfModulo : public DispersionFunction<Key> {	
	public:
		/**
		 * @brief Constructor
		 * @param n Tamaño de la tabla
		*/
		dfModulo(const unsigned n) : _tableSize(n) {}

		/**
		 * @brief Funcion de dispersion
		 * @param k Clave a dispersar
		 * @return Valor dispersado
		*/
		unsigned operator()(const Key& k) const;
	private:
		unsigned _tableSize;
};

/**
 * Clase dfSuma
 * Funcion de dispersion por suma
*/
template<class Key>
class dfSuma : public DispersionFunction<Key> {
	public:
		/**
		 * @brief Constructor
		 * @param n Tamaño de la tabla
		*/
		dfSuma(const unsigned n) : _tableSize(n) {}

		/**
		 * @brief Funcion de dispersion
		 * @param k Clave a dispersar
		 * @return Valor dispersado
		*/
		unsigned operator()(const Key& k) const;
	private:
		unsigned _tableSize;
};

/**
 * Clase dfPseudoaleatoria
 * Funcion de dispersion pseudoaleatoria
*/
template<class Key>
class dfPseudoaleatoria : public DispersionFunction<Key> {
	public:
		/**
		 * @brief Constructor
		 * @param n Tamaño de la tabla
		*/
		dfPseudoaleatoria(const unsigned n) : _tableSize(n) {}

		/**
		 * @brief Funcion de dispersion
		 * @param k Clave a dispersar
		 * @return Valor dispersado
		*/
		unsigned operator()(const Key& k) const;
	private:
		unsigned _tableSize;
};


// Implementacion de las funciones de dispersion
template<class Key>
unsigned dfModulo<Key>::operator()(const Key& k) const {
	return k % _tableSize;
}

template<class Key>
unsigned dfSuma<Key>::operator()(const Key& k) const {
	unsigned long suma = 0;
    unsigned long aux = k;
	while (aux > 0) {
		suma += aux % 10;
		aux /= 10;
	}
	return suma % _tableSize;
}

template<class Key>
unsigned dfPseudoaleatoria<Key>::operator()(const Key& k) const {
	srand(k);
	return rand() % _tableSize;
}

#endif