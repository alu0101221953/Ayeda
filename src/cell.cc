/**
 * @file cell.cc
 * @brief Fichero de implementación de la clase Cell
*/

#include "cell.h"
#include "lattice.h"

/**
 * @brief Constructor de la clase Cell
 * @param pos Posición de la célula en el retículo
 * @param initial_state Estado inicial de la célula
*/
Cell::Cell(const Position& pos, const State& initial_state) : position(pos), state(initial_state) {}

/**
 * @brief Método para acceder al estado de la célula
 * @return Estado de la célula
*/
State Cell::getState() const {
	return state;
}

/**
 * @brief Método para modificar el estado de la célula
 * @param new_state Nuevo estado de la célula
*/
void Cell::setState(State new_state) {
	state = new_state;
}	

/**
 * @brief Método para calcular el siguiente estado de la célula
 * @param lattice Retículo al que pertenece la célula
 * @return Siguiente estado de la célula
*/
State Cell::nextState(const Lattice& lattice) const {
	int size = lattice.getSize();
	State left_neighbor, right_neighbor;
	if (lattice.getBoundaryType() == 0 || lattice.getBoundaryType() == 1) {
		if (border) {
			left_neighbor = 0;
			right_neighbor = 0;
		} else {
			if (position == 0) {
				left_neighbor = 0;
				right_neighbor = lattice.getCell(position + 1).getState();
			} else if (position == size + 2) {
				left_neighbor = lattice.getCell(position - 1).getState();
				right_neighbor = 0;
			} else {
				left_neighbor = lattice.getCell(position - 1).getState();
				right_neighbor = lattice.getCell(position + 1).getState();
			}
		}
	}
	else {
		if (position == 0) {
			left_neighbor = lattice.getCell(size - 1).getState();
			right_neighbor = lattice.getCell(position + 1).getState();
		} else if (position == size - 1) {
			left_neighbor = lattice.getCell(position - 1).getState();
			right_neighbor = lattice.getCell(0).getState();
		} else {
			left_neighbor = lattice.getCell(position - 1).getState();
			right_neighbor = lattice.getCell(position + 1).getState();
		}
	}
	State result;
	return result = left_neighbor ^ (state || right_neighbor);
}

/**
 * @brief Método para establecer si la célula está en el borde
 * @param b Valor booleano que indica si la célula está en el borde
*/
void Cell::setBorder(bool b) {
	border = b;
}

/**
 * @brief Método para establecer la posición de la célula
 * @param p Nueva posición de la célula
*/
void Cell::setPosition(Position p) {
	position = p;
}

/**
 * @brief Método para actualizar el estado de la célula
 * De momento no hace nada porque no lo he necesitado
*/
void Cell::updateState() {
	state = 0;
}

/**
 * @brief Sobrecarga del operador de inserción en flujo para visualización
 * @param os Flujo de salida
 * @param cell Célula a visualizar
 * @return Flujo de salida
*/
std::ostream& operator<<(std::ostream& os, const Cell& cell) {
	os << cell.state;
	return os;
}