/**
 * @file cell.h
 * @brief Fichero de cabecera para la clase Cell
 * 
*/

#ifndef CELL_H
#define CELL_H

#include <utility>
#include <iostream>

using Position = int;
using State = int;

class Lattice;
class Cell {
  private:
    Position position; // Posición de la célula en el retículo
    State state;       // Estado de la célula (0 o 1)
    bool border = false;

  public:
    // Constructor
    Cell(const Position& pos, const State& initial_state = 0);

    // Método para acceder al estado de la célula
    State getState() const;

    // Método para modificar el estado de la célula
    void setState(State new_state);

    // Método para calcular el siguiente estado de la célula
    State nextState(const Lattice& lattice) const;

    // Método para actualizar el estado de la célula
    void updateState();

    // Método para establecer si la célula está en el borde
    void setBorder(bool b);

    // Método para establecer la posición de la célula
    void setPosition(Position p);
    
    // Sobrecarga del operador de inserción en flujo para visualización
    friend std::ostream& operator<<(std::ostream& os, const Cell& cell);
};

#endif // CELL_H