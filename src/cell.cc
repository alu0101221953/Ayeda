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
State Cell::nextState(Lattice& lattice) const {
	// Se obtiene el número de filas y columnas del retículo
	int rows = lattice.getRows();
	int cols = lattice.getCols();

	// Se obtiene el número de células vivas adyacentes
	int liveNeighbors = 0;
	if (border && lattice.getBoundaryType() == 0) {
		for (int i = -1; i <= 1; ++i) {
			for (int j = -1; j <= 1; ++j) {
				// Calcular las coordenadas del vecino
				int neighborX = position.first + i;
				int neighborY = position.second + j;

				// Verificar si el vecino está dentro de los límites del retículo
				if (neighborX >= 0 && neighborX < rows && neighborY >= 0 && neighborY < cols) {
					// Excluir la propia celda actual
					if (!(i == 0 && j == 0)) {
						liveNeighbors += lattice.getCell({neighborX, neighborY}).getState();
					}
				} else {
					// Si el vecino estaría fuera del borde, reflejar el estado de la célula del borde
					// Calculamos las coordenadas del vecino reflejado
					int reflectedX = std::min(std::max(neighborX, 0), rows - 1);
					int reflectedY = std::min(std::max(neighborY, 0), cols - 1);

					liveNeighbors += lattice.getCell({reflectedX, reflectedY}).getState();
				}
			}
		}
	} else {
    for (int i = position.first - 1; i <= position.first + 1; ++i) {
			for (int j = position.second - 1; j <= position.second + 1; ++j) {
				if (i >= 0 && i < rows && j >= 0 && j < cols && !(i == position.first && j == position.second)) {
					// Verificar si la célula está dentro del rango del retículo y no es la célula actual
					liveNeighbors += lattice.getCell({i, j}).getState();
				}
			}
    }
	}

	// Se calcula el siguiente estado de la célula
	if (state == 1) {
		return (liveNeighbors == 2 || liveNeighbors == 3) ? 1 : 0;
	} else {
		return (liveNeighbors == 3) ? 1 : 0;
	}
}

/**
 * @brief Método para establecer si la célula está en el borde
 * @param b Valor booleano que indica si la célula está en el borde
*/
void Cell::setBorder(bool b) {
	border = b;
}

/**
 * @brief Método para obtener si la célula está en el borde
 * @return Valor booleano que indica si la célula está en el borde
*/
bool Cell::isBorder() const {
	return border;
}

/**
 * @brief Método para establecer la posición de la célula
 * @param p Nueva posición de la célula
*/
void Cell::setPosition(Position p) {
	position = p;
}

/**
 * @brief Método para establecer el siguiente estado de la célula
 * @param s Siguiente estado de la célula
*/
void Cell::setNextState(State s) {
	next_state = s;
}

/**
 * @brief Método para obtener el siguiente estado de la célula
 * @return Siguiente estado de la célula
*/
State Cell::getNextState() const {
	return next_state;
}

/**
 * @brief Método para actualizar el estado de la célula
 * De momento no hace nada porque no lo he necesitado
*/
void Cell::updateState() {
	state = next_state;
}

/**
 * @brief Sobrecarga del operador de inserción en flujo para visualización
 * @param os Flujo de salida
 * @param cell Célula a visualizar
 * @return Flujo de salida
*/
std::ostream& operator<<(std::ostream& os, const Cell& cell) {
	// Se visualiza el estado de la célula, si es 1 se pinta una X, si es 0 se pinta un espacio
	if (cell.getState() == 1) {
		os << "X";
	} else {
		os << " ";
	}
	return os;
}