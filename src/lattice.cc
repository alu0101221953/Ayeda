/**
 * @file lattice.cc
 * @brief Fichero de implementación de la clase Lattice
 
*/

#include "lattice.h"

/**
 * @brief Constructor de la clase Lattice
 * @param size Tamaño del retículo
 * @param b_type Tipo de frontera (0: abierta fría, 1: abierta caliente, 2: periódica)
 * @param init_file Nombre del archivo de inicialización
*/
Lattice::Lattice(int size, BoundaryType b_type, const std::string& init_file) : boundary_type(b_type) {
  // Se carga la configuración inicial del autómata celular
  if (init_file != "") {
    loadInitialConfiguration(init_file);

  } else {
    if (boundary_type == 0) { // Frontera abierta fría, una celula al principio y al final con estado 0
      cells.insert(cells.begin(), Cell(0, 0));
      for (int i = 1; i < size + 1; i++) {
        cells.push_back(Cell(i, 0));
      }
      cells.push_back(Cell(size + 2, 0));
      cells[0].setBorder(true);
      cells[size + 2].setBorder(true);
    } else if (boundary_type == 1) { // Frontera abierta caliente, una celula al principio y al final con estado 1
      cells.insert(cells.begin(), Cell(0, 1));
      for (int i = 1; i < size + 1; i++) {
        cells.push_back(Cell(i, 0));
      }
      cells.push_back(Cell(size + 2, 1));
      cells[0].setBorder(true);
      cells[size + 2].setBorder(true);
    } else if (boundary_type == 2) { // Frontera periodica, la primera y la última célula son vecinas
      for (int i = 0; i < size; i++) {
        cells.push_back(Cell(i, 0));
      }
    } 
    // La celula central se inicializa en estado 1
    cells[cells.size() / 2].setState(1);
  }
}

/**
 * @brief Método para cargar la configuración inicial del autómata celular
 * @param init_file Nombre del archivo de inicialización
*/
void Lattice::loadInitialConfiguration(const std::string& init_file) {
  std::ifstream file(init_file);
  // El fichero es basicamente una lista de estados de las celulas: 00100
  if (boundary_type == 0) {
    cells.insert(cells.begin(), Cell(0, 0));
  } else if (boundary_type == 1) {
    cells.insert(cells.begin(), Cell(0, 1));
  }
  if (file.is_open()) {
    std::string line;
    std::getline(file, line);
    if (boundary_type == 0 || boundary_type == 1) {
      for (unsigned int i = 0; i < line.size(); i++) {
        cells.push_back(Cell(i + 1, line[i] - '0'));
      }
    } else if (boundary_type == 2) {
      for (unsigned int i = 0; i < line.size(); i++) {
        cells.push_back(Cell(i, line[i] - '0'));
      }
    }
    file.close();
  } else {
    std::cerr << "Error: No se pudo abrir el archivo " << init_file << std::endl;
  }
  if (boundary_type == 0) {
    cells.push_back(Cell(cells.size() + 1, 0));
    cells[0].setBorder(true);
    cells[cells.size() - 1].setBorder(true);
  } else if (boundary_type == 1) {
    cells.push_back(Cell(cells.size() + 1, 1));
    cells[0].setBorder(true);
    cells[cells.size() - 1].setBorder(true);
  }
}

/**
 * @brief Método para acceder a una célula específica en el retículo
 * @param pos Posición de la célula en el retículo
 * @return Célula en la posición pos
*/
const Cell& Lattice::getCell(const Position& pos) const {
  return cells[pos];
}

/**
 * @brief Método para avanzar a la siguiente generación del autómata
*/
void Lattice::nextGeneration() {
  // Se calcula el siguiente estado de cada célula y se guarda en un vector auxiliar
  std::vector<State> next_states;
  // Se recorren todas las células del retículo teniendo en cuenta el tipo de frontera
  for (unsigned int i = 0; i < cells.size(); i++) {
    next_states.push_back(cells[i].nextState(*this));
  }
  // Se actualiza el estado de cada célula
  for (unsigned int i = 0; i < cells.size(); i++) {
    cells[i].setState(next_states[i]);
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
 * @brief Método para obtener el tamaño del retículo
 * @return Tamaño del retículo
*/
int Lattice::getSize() const {
  return cells.size();
}

/**
 * @brief Método para obtener el número de células vivas
 * @return Número de células vivas
*/
int Lattice::getPopulation() const {
  int population = 0;
  for (const Cell& cell : cells) {
    if (cell.getState() == 1) {
      population++;
    }
  }
  return population;
}

/**
 * @brief Sobrecarga del operador de inserción en flujo para visualización
 * @param os Flujo de salida
 * @param lattice Retículo a visualizar
 * @return Flujo de salida
*/
std::ostream& operator<<(std::ostream& os, const Lattice& lattice) {
  for (const Cell& cell : lattice.cells) {
    os << cell;
  }
  return os;
}