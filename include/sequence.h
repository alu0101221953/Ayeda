#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <vector>
#include <iostream>
#include <cstdlib>

template<class Key>
class Sequence {
	public:
		/**
		 * @brief Busca un valor en la secuencia
		 * @param k Valor a buscar
		 * @return true si lo encuentra, false en otro caso
		*/
		virtual bool search(const Key& k) const = 0;

		/**
		 * @brief Inserta un valor en la secuencia
		 * @param k Valor a insertar
		 * @return true si lo inserta, false en otro caso
		*/
		virtual bool insert(const Key& k) = 0;
};

/**
 * Clase dynamicSequence
 * Secuencia dinamica, dispersion abierta
*/
template<class Key>
class dynamicSequence : public Sequence<Key> {
	public:
		/**
		 * @brief Constructor
		*/
		dynamicSequence();

		/**
		 * @brief Busca un valor en la secuencia
		 * @param k Valor a buscar
		 * @return true si lo encuentra, false en otro caso
		*/
		bool search(const Key& k) const;

		/**
		 * @brief Inserta un valor en la secuencia
		 * @param k Valor a insertar
		 * @return true si lo inserta, false en otro caso
		*/
		bool insert(const Key& k);

		/**
		 * @brief Imprime la secuencia
		*/
		void print();
	private:
		std::vector<Key> _sequence;
};

template<class Key>
dynamicSequence<Key>::dynamicSequence() {
	_sequence.clear();
}

template<class Key>
bool dynamicSequence<Key>::search(const Key& k) const {
	for (unsigned i = 0; i < _sequence.size(); i++) {
		if (_sequence.at(i) == k) return true;
	}
	return false;
}

template<class Key>
bool dynamicSequence<Key>::insert(const Key& k) {
	if (search(k)) return false;
	else {
		_sequence.push_back(k);
		return true;
	}
	return false;
}

template<class Key>
void dynamicSequence<Key>::print() {
	for (unsigned i = 0; i < _sequence.size(); i++) {
		std::cout << _sequence[i] << " ";
	}
	std::cout << std::endl;
}

/**
 * Class staticSequence
 * Secuencia estatica, dispersion cerrada
*/
template<class Key>
class staticSequence : public Sequence<Key> {
	public:
		/**
		 * @brief Constructor
		 * @param n Tamaño de la secuencia
		 * @param m Tamaño del bloque
		*/
		staticSequence(const unsigned b);

		/**
		 * @brief Busca un valor en la secuencia
		 * @param k Valor a buscar
		 * @return true si lo encuentra, false en otro caso
		*/
		bool search(const Key& k) const;

		/**
		 * @brief Inserta un valor en la secuencia
		 * @param k Valor a insertar
		 * @return true si lo inserta, false en otro caso
		*/
		bool insert(const Key& k);

		/**
		 * @brief Comprueba si la secuencia esta llena
		 * @return true si esta llena, false en otro caso
		*/
		bool isFull() const;

		/**
		 * @brief Imprime la secuencia
		*/
		void print();
	private:
		std::vector<Key> _sequence;
		unsigned _blockSize;
};

template<class Key>
staticSequence<Key>::staticSequence(const unsigned b) {
	_blockSize = b;
	_sequence.clear();
}

template<class Key>
bool staticSequence<Key>::search(const Key& k) const {
	if (_sequence.size() == 0) return false;
	for (unsigned i = 0; i < _blockSize; i++) {
		if (_sequence[i] == k) return true;
	}
	return false;
}

template<class Key>
bool staticSequence<Key>::insert(const Key& k) {
	if (search(k)) return false;
	if (isFull()) return false;
	_sequence.push_back(k);
	return true;
}

template<class Key>
bool staticSequence<Key>::isFull() const {
	return _sequence.size() == _blockSize;
}

template<class Key>
void staticSequence<Key>::print() {
	for (unsigned i = 0; i < _sequence.size(); i++) {
		std::cout << _sequence[i] << " ";
	}
	std::cout << std::endl;
}

#endif