#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "sequence.h"
#include "dispersion.h"
#include "exploration.h"

#include <vector>
#include <iostream>
#include <cstdlib>

template<class Key, class Container=staticSequence<Key>>
class HashTable {
    public:
			/**
			 * @brief Constructor
			 * @param size Tamaño de la tabla
			 * @param blockSize Tamaño de los bloques
			 * @param dispersion Función de dispersión
			 * @param exploration Función de exploración
			*/
			HashTable(unsigned size, unsigned blockSize, DispersionFunction<Key>& dispersion, ExplorationFunction<Key>& exploration);

			/**
			 * @brief Destructor
			*/
			~HashTable() = default;

			/**
			 * @brief Busca un valor en la tabla
			 * @param k Valor a buscar
			 * @return true si lo encuentra, false en otro caso
			*/
			bool search(const Key& k) const;

			/**
			 * @brief Inserta un valor en la tabla
			 * @param k Valor a insertar
			 * @return true si lo inserta, false en otro caso
			*/
			bool insert(const Key& k);

			/**
			 * @brief Imprime la tabla
			*/
			void print();

            unsigned getElements() const { return _elements; }
    private:
			unsigned _tableSize;
			unsigned _blockSize;
			Container** _table;
			DispersionFunction<Key>& _dispersion;
			ExplorationFunction<Key>& _exploration;
            unsigned _elements;
};

template<class Key, class Container>
HashTable<Key, Container>::HashTable(unsigned size, unsigned blockSize, DispersionFunction<Key>& dispersion, ExplorationFunction<Key>& exploration) 
    : _tableSize(size), _blockSize(blockSize), _dispersion(dispersion), _exploration(exploration) {
    _table = new Container*[_tableSize];
    for (unsigned i = 0; i < _tableSize; i++) {
        _table[i] = new Container(_blockSize);
    }
    _elements = 0;
}

template<class Key, class Container>
bool HashTable<Key, Container>::search(const Key& k) const {
    unsigned index = _dispersion(k);
    return _table[index]->search(k);
}

template<class Key, class Container>
bool HashTable<Key, Container>::insert(const Key& k) {
    if (!search(k)) {
        unsigned index = _dispersion(k);
        if (_table[index]->isFull()) {
            unsigned i = 0;
            unsigned newIndex = _exploration(k, i);
            while (_table[newIndex]->isFull() && i < _tableSize) {
                newIndex = _exploration(k, i);
                i++;
            }
            if (i < _tableSize) {
                _elements++;
                return _table[newIndex]->insert(k);
            } else {
                std::cerr << "Error: No hay espacio disponible en la tabla para insertar el elemento" << std::endl;
                return false;
            }
        } else {
            _elements++;
            return _table[index]->insert(k);
        }
    } else {
        return false;
    }
}

template<class Key, class Container>
void HashTable<Key, Container>::print() {
    for (unsigned i = 0; i < _tableSize; i++) {
        std::cout << i << ": ";
        _table[i]->print();
    }
}

// Especialización parcial para dispersión abierta con contenedor dynamicSequence
template<class Key>
class HashTable<Key, dynamicSequence<Key>> {
    public:
        /**
         * @brief Constructor
         * @param size Tamaño de la tabla
         * @param dispersion Función de dispersión
        */
        HashTable(unsigned size, DispersionFunction<Key>& dispersion);

        /**
         * @brief Destructor
        */
        ~HashTable();

        /**
         * @brief Busca un valor en la tabla
         * @param k Valor a buscar
         * @return true si lo encuentra, false en otro caso
        */
        bool search(const Key& k) const;

        /**
         * @brief Inserta un valor en la tabla
         * @param k Valor a insertar
         * @return true si lo inserta, false en otro caso
        */
        bool insert(const Key& k);

        /**
         * @brief Imprime la tabla
        */
        void print();

        unsigned getElements() const { return _elements; }
    private:
        unsigned _tableSize;
        dynamicSequence<Key>** _table;
        DispersionFunction<Key>& _dispersion;
        unsigned _elements;
};

template<class Key>
HashTable<Key, dynamicSequence<Key>>::HashTable(unsigned size, DispersionFunction<Key>& dispersion) 
    : _tableSize(size), _dispersion(dispersion) {
    _table = new dynamicSequence<Key>*[_tableSize];
    for (unsigned i = 0; i < _tableSize; i++) {
        _table[i] = new dynamicSequence<Key>();
    }
    _elements = 0;
}

template<class Key>
HashTable<Key, dynamicSequence<Key>>::~HashTable() {
    for (unsigned i = 0; i < _tableSize; i++) {
        delete _table[i];
    }
    delete[] _table;
}

template<class Key>
bool HashTable<Key, dynamicSequence<Key>>::search(const Key& k) const {
    unsigned index = _dispersion(k);
    return _table[index]->search(k);
}

template<class Key>
bool HashTable<Key, dynamicSequence<Key>>::insert(const Key& k) {
    unsigned index = _dispersion(k);
    if (_table[index]->insert(k)) {
        _elements++;
        return true;
    } else {
        return false;
    }
}

template<class Key>
void HashTable<Key, dynamicSequence<Key>>::print() {
    for (unsigned i = 0; i < _tableSize; i++) {
        std::cout << i << ": ";
        _table[i]->print();
    }
}

#endif