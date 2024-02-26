/**
 * @file lattice.cc
 * @brief Fichero de implementación de la clase Lattice
 
*/

#include "lattice.h"

/**
 * @brief Constructor de la clase Lattice
 * @param rows Número de filas del retículo
 * @param cols Número de columnas del retículo
 * @param b_type Tipo de frontera (0: abierta fría, 1: abierta caliente, 2: periódica)
*/
Lattice::Lattice(int rows, int cols, BoundaryType b_type) : boundary_type(b_type) {
  _rows = rows;
  _cols = cols;
  cells.resize(rows);
  for (int i = 0; i < rows; i++) {
    cells[i].resize(cols, Cell({i, 0}, 0));
  }

  // Se establecen las posiciones de las células
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      cells[i][j].setPosition({i, j});
    }
  }

  // Se establecen las células en el borde
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (i == 0 || i == rows - 1 || j == 0 || j == cols - 1) {
        cells[i][j].setBorder(true);
      }
    }
  }

  // Ahora se establecen las celulas vivas
  std::cout << "Introduce el número de células vivas: ";
  int n;
  std::cin >> n;
  for (int i = 0; i < n; i++) {
    int x, y;
    std::cout << "Introduce la posición de la célula " << i + 1 << " (x, y): ";
    std::cin >> x >> y;
		// Se comprueba que la posición sea válida o que no esté ya ocupada
		if (x < 0 || x >= rows || y < 0 || y >= cols || cells[x][y].getState() == 1) {
			std::cerr << "Error: Posición inválida o ya ocupada" << std::endl;
			i--;
		} else {
    	cells[x][y].setState(1);
		}
  }
}

/**
 * @brief Constructor de la clase Lattice a partir de un fichero
 * @param filename Nombre del fichero
*/
Lattice::Lattice(const char* filename, BoundaryType b_type) : boundary_type(b_type){
  std::ifstream file(filename);
  if (file.is_open()) { 
    std::string line;
    _rows = 0;
    _cols = 0;
    while (std::getline(file, line)) {
      _rows++;
      if (_cols == 0) {
        _cols = line.size();
      }
      cells.push_back(std::vector<Cell>());
      for (int i = 0; i < _cols; i++) {
        cells[_rows - 1].push_back(Cell({_rows - 1, i}, line[i] - '0'));
      }
    }
  } else {
    std::cerr << "Error: No se pudo abrir el fichero" << std::endl;
  }

  // Se establecen las células en el borde
  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _cols; j++) {
      if (i == 0 || i == _rows - 1 || j == 0 || j == _cols - 1) {
        cells[i][j].setBorder(true);
      }
    }
  }
}

/**
 * @brief Método para acceder a una célula específica en el retículo
 * @param pos Posición de la célula en el retículo
 * @return Célula en la posición pos
*/
const Cell& Lattice::getCell(const Position& pos) const {
  return cells[pos.first][pos.second];
}

/**
 * @brief Método para avanzar a la siguiente generación del autómata
*/
void Lattice::nextGeneration() {
  // Se calcula el siguiente estado de cada célula
  for (int i = 0; i < getRows(); i++) {
    for (int j = 0; j < getCols(); j++) {
      cells[i][j].setNextState(cells[i][j].nextState(*this));
    }
  }
  // Se actualiza el estado de cada célula
  for (int i = 0; i < getRows(); i++) {
    for (int j = 0; j < getCols(); j++) {
      cells[i][j].updateState();
    }
  }
  // Comprobar si es necesario aumentar el tamaño del retículo, si alguna célula en el borde está viva se aumenta en ese lado
  for (int i = 0; i < getRows(); i++) {
    for (int j = 0; j < getCols(); j++) {
      if (cells[i][j].getState() == 1 && cells[i][j].isBorder() && boundary_type == 1) {
        if (i == 0) {
          increaseSize(0);
        } else if (i == getRows() - 1) {
          increaseSize(1);
        } else if (j == 0) {
          increaseSize(2);
        } else if (j == getCols() - 1) {
          increaseSize(3);
        }
      }
    }
  }
}

/**
 * @brief Método que aumenta el tamaño del retículo
*/
void Lattice::increaseSize(int d) {
	// Aumentar el número de filas y columnas según la dirección d
	_rows += (d == 0 || d == 1);
	_cols += (d == 2 || d == 3);

	// Agregar una fila en la dirección norte (fila 0)
	if (d == 0) {
		cells.insert(cells.begin(), std::vector<Cell>(_cols, Cell({0, 0}, 0)));
	}
	// Agregar una fila en la dirección sur (última fila)
	else if (d == 1) {
		cells.push_back(std::vector<Cell>(_cols, Cell({_rows - 1, 0}, 0)));
	}
	// Agregar una columna en la dirección oeste (al principio de cada fila)
	else if (d == 2) {
		for (int i = 0; i < _rows; ++i) {
			cells[i].insert(cells[i].begin(), Cell({i, 0}, 0));
		}
	}
	// Agregar una columna en la dirección este (al final de cada fila)
	else if (d == 3) {
		for (int i = 0; i < _rows; ++i) {
			cells[i].push_back(Cell({i, _cols - 1}, 0));
		}
	}

	// Actualizar las posiciones
	for (int i = 0; i < _rows; ++i) {
		for (int j = 0; j < _cols; ++j) {
			cells[i][j].setPosition(Position(i, j));
		}
	}

	// Limpiar las células en el borde y actualizarlas los bordes nuevos
	for (int i = 0; i < _rows; ++i) {
		for (int j = 0; j < _cols; ++j) {
			if (i == 0 || i == _rows - 1 || j == 0 || j == _cols - 1) {
				cells[i][j].setBorder(true);
			}
			else {
				cells[i][j].setBorder(false);
			}
		}
	}
}

/**
 * @brief Método para obtener el tipo de frontera del retículo
 * @return Tipo de frontera
*/
BoundaryType Lattice::getBoundaryType() const {
  return boundary_type;
}


/**
 * @brief Método para obtener el número de columnas del retículo
 * @return Número de columnas del retículo
*/
int Lattice::getCols() const {
  return _cols;
}

/**
 * @brief Método para obtener el número de filas del retículo
 * @return Número de filas del retículo
*/
int Lattice::getRows() const {
  return _rows;
}

/**
 * @brief Método para obtener el número de células vivas
 * @return Número de células vivas
*/
std::size_t Lattice::getPopulation() const {
  int population = 0;
  for (int i = 0; i < getRows(); i++) {
    for (int j = 0; j < getCols(); j++) {
      population += cells[i][j].getState();
    }
  }
  return population;
}

/**
 * @brief Sobrecarga del operador de acceso a elementos para acceder a una célula específica en el retículo
 * @param pos Posición de la célula en el retículo
 * @return Célula en la posición pos
*/
const Cell& Lattice::operator[](const Position& pos) const {
  return cells[pos.first][pos.second];
}

/**
 * @brief Sobrecarga del operador de inserción en flujo para visualización
 * @param os Flujo de salida
 * @param lattice Retículo a visualizar
 * @return Flujo de salida
*/
std::ostream& operator<<(std::ostream& os, const Lattice& lattice) {
  for (int i = 0; i < lattice.getRows(); i++) {
    for (int j = 0; j < lattice.getCols(); j++) {
      if (lattice.getCell({i, j}).getState() == 1) {
        os << "X";
      }
      else {
        os << ".";
      }
    }
    os << std::endl;
  }
  return os;
}