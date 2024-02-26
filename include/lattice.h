/**
 * @file lattice.h
 * @brief Fichero de cabecera para la clase Lattice
*/

#ifndef LATTICE_H
#define LATTICE_H

#include <vector>
#include <iostream>
#include <fstream>
#include "cell.h"

using BoundaryType = int;

class Lattice {
  private:
    std::vector<std::vector<Cell>> cells; // Retículo de células
    BoundaryType boundary_type; // Tipo de frontera (abierto, periódico)
    int _rows; // Número de filas
    int _cols; // Número de columnas

  public:
    // Constructor de la clase Lattice
    Lattice(int rows, int cols, BoundaryType b_type);

    // Constructor de la clase Lattice a partir de un fichero
    Lattice(const char* filename, BoundaryType b_type);

    // Método para acceder a una célula específica en el retículo
    const Cell& getCell(const Position& pos) const;

    // Método para avanzar a la siguiente generación del autómata
    void nextGeneration();

    // Método que aumenta el tamaño del retículo
    void increaseSize(int);

    // Método para obtener el tipo de frontera
    BoundaryType getBoundaryType() const;

    // Método para obtener el número de columnas
    int getCols() const;

    // Método para obtener el número de filas
    int getRows() const;

    // Metodo para obtener el número de células vivas
    std::size_t getPopulation() const;

    // Sobrecarga del operador de acceso a elementos para acceder a una célula específica en el retículo
    const Cell& operator[](const Position&) const;

    // Sobrecarga del operador de inserción en flujo para visualización
    friend std::ostream& operator<<(std::ostream& os, const Lattice& lattice);
};

#endif // LATTICE_H