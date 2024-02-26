/**
 * @file main.cc
 * @brief Programa principal que implementa el juego de la vida
 * @version 1.0
 * @date 18/02/2024
 * @author Víctor Cánovas del Pino alu0101221953
 */

#include <iostream>
#include <string>
#include <chrono>
#include <thread>  
#include <atomic>

#include "lattice.h"

bool flag;

int main(int argc, char* argv[]) {

	// Se comprueba que el número de argumentos sea correcto
	if (argc < 5) {
		std::cerr << "Error: Número de argumentos incorrecto" << std::endl;
		std::cerr << "Uso: " << argv[0] << " -size <M> <N> [-init <file>] -border <b>" << std::endl;
		return 1;
	}

	// Se inicializan las variables
	int rows, cols;
	std::string filename;
	BoundaryType boundary_type;
	flag = false;
	// Se leen los argumentos
	for (int i = 1; i < argc; i++) {
		if (std::string(argv[i]) == "-size") {
			rows = std::stoi(argv[i + 1]);
			cols = std::stoi(argv[i + 2]);
			if (rows <= 0 || cols <= 0) {
				std::cerr << "Error: Número de filas y columnas debe ser mayor que 0" << std::endl;
				return 1;
			}
			else if (std::string(argv[i + 3]) != "-init" && std::string(argv[i + 3]) != "-border") {
				std::cerr << "Error: Argumentos incorrectos" << std::endl;
				std::cerr << "Uso: " << argv[0] << " -size <M> <N> [-init <file>] -border <b>" << std::endl;
				return 1;
			}
		} else if (std::string(argv[i]) == "-init") {
			filename = argv[i + 1];
		} else if (std::string(argv[i]) == "-border" || std::string(argv[i]) == "-b") {
			if (std::string(argv[i + 1]) == "reflective") {
				boundary_type = 0;
			} else if (std::string(argv[i + 1]) == "noborder") {
				boundary_type = 1;
			} else {
				std::cerr << "Error: Tipo de frontera incorrecto" << std::endl;
				std::cerr << "Uso: " << argv[0] << " -size <M> <N> [-init <file>] -border <b>" << std::endl;
				return 1;
			}
		}
	}

	if (filename.empty()) {
		Lattice lattice(rows, cols, boundary_type);
		std::cout << lattice << std::endl;

		// Se inicia el bucle de simulación
		char key;
		while (true) {
			std::cin >> key;
			if (key == 'x') {
				break;
			} else if (key == 'n') {
				lattice.nextGeneration();
				std::cout << lattice << std::endl;
				if (flag) {
					std::cout << "Población: " << lattice.getPopulation() << std::endl;
				}
			} else if (key == 'L') {
				for (int i = 0; i < 5; i++) {
					lattice.nextGeneration();
					std::cout << lattice << std::endl;
					if (flag) {
						std::cout << "Población: " << lattice.getPopulation() << std::endl;
					}
				}
			} else if (key == 'c') {
				flag = true;
			} else if (key == 's') {
				std::string output;
				std::cout << "Introduce el nombre del fichero: ";
				std::cin >> output;
				std::ofstream file(output);
				file << lattice;
				file.close();
			}
		}
	} else {
		Lattice lattice(filename.c_str(), boundary_type);
		std::cout << lattice << std::endl;

		// Se inicia el bucle de simulación
		char key;
		while (true) {
			std::cin >> key;
			if (key == 'x') {
				break;
			} else if (key == 'n') {
				lattice.nextGeneration();
				std::cout << lattice << std::endl;
				if (flag) {
					std::cout << "Población: " << lattice.getPopulation() << std::endl;
				}
			} else if (key == 'L') {
				for (int i = 0; i < 5; i++) {
					lattice.nextGeneration();
					std::cout << lattice << std::endl;
					if (flag) {
						std::cout << "Población: " << lattice.getPopulation() << std::endl;
					}
				}
			} else if (key == 'c') {
				flag = true;
			} else if (key == 's') {
				std::string filename;
				std::cout << "Introduce el nombre del fichero: ";
				std::cin >> filename;
				std::ofstream file(filename);
				file << lattice;
				file.close();
			}
		}
	}
	return 0;
}