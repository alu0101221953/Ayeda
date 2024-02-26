/**
 * @file cell.h
 * @brief Fichero de cabecera para la clase Cell
 * 
*/

#ifndef CELL_H
#define CELL_H

#include <utility>
#include <iostream>
#include <utility>
#include <vector>

typedef std::pair<int, int> Position;
typedef int State;

class Lattice;
class Cell {
  private:
    Position position; // Posición de la célula en el retículo
    State state;       // Estado de la célula (0 o 1)
    State next_state;  // Siguiente estado de la célula
    bool border = false;

  public:
    // Constructor
    Cell(const Position& pos, const State& initial_state = 0);

    // Método para acceder al estado de la célula
    State getState() const;

    // Método para modificar el estado de la célula
    void setState(State new_state);

    // Método para calcular el siguiente estado de la célula
    State nextState(Lattice& lattice) const;

    // Método para actualizar el estado de la célula
    void updateState();

    // Método para establecer si la célula está en el borde
    void setBorder(bool b);

    // Método para obtener si la célula está en el borde
    bool isBorder() const;

    // Método para establecer el siguiente estado de la célula
    void setNextState(State s);

    // Método para obtener el siguiente estado de la célula
    State getNextState() const;

    // Método para establecer la posición de la célula
    void setPosition(Position p);
    
    // Sobrecarga del operador de inserción en flujo para visualización
    friend std::ostream& operator<<(std::ostream& os, const Cell& cell);
};

#endif // CELL_H