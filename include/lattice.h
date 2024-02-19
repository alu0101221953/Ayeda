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
    std::vector<Cell> cells; // Vector que contiene las células del retículo
    BoundaryType boundary_type; // Tipo de frontera (abierto, periódico)

  public:
    // Constructor
    Lattice(int size, BoundaryType b_type, const std::string& init_file = "");

    // Método para cargar la configuración inicial del autómata celular
    void loadInitialConfiguration(const std::string& init_file);

    // Método para acceder a una célula específica en el retículo
    const Cell& getCell(const Position& pos) const;

    // Método para avanzar a la siguiente generación del autómata
    void nextGeneration();

    BoundaryType getBoundaryType() const;

    // Método para obtener el tamaño del retículo
    int getSize() const;

    // Metodo para obtener el número de células vivas
    int getPopulation() const;

    // Sobrecarga del operador de inserción en flujo para visualización
    friend std::ostream& operator<<(std::ostream& os, const Lattice& lattice);
};

#endif // LATTICE_H