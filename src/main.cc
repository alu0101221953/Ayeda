/**
 * @file main.cc
 * @brief Programa principal que implementa el autómata celular
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

std::atomic<bool> stop_flag(false);

/**
 * @brief Espera a que se pulse una tecla para terminar el programa
 */
void waitForKeypress() {	
	char key;
	while (true) {
		std::cin >> key;
		if (key == 'q') {
			stop_flag = true;
			break;
		}
	}
}

int main(int argc, char* argv[]) {
  // Comprobar que se han proporcionado los argumentos necesarios
	if (argc < 5) {
		std::cerr << "Uso: " << argv[0] << " -size <n> -border <b [v]> [-init <file>]" << std::endl;
		return 1;
	}

  // Variables para almacenar los argumentos
	int size;
	BoundaryType boundary_type;
	std::string init_file;

	// Procesar los argumentos
	for (int i = 1; i < argc; ++i) {
		std::string arg = argv[i];
		if (arg == "-size") {
			if (i + 1 < argc) {
						size = std::stoi(argv[i + 1]);
			} else {
				std::cerr << "Error: Falta el tamaño del retículo después de -size" << std::endl;
				return 1;
			}
		} else if (arg == "-border" || arg == "-b") {
			if (i + 1 < argc) {
				if (std::string(argv[i + 1]) == "open") {
					if (i + 2 < argc) {
						if (std::string(argv[i + 2]) == "0") {
							boundary_type = 0;
						} else if (std::string(argv[i + 2]) == "1") {
							boundary_type = 1;
						} else {
							std::cerr << "Error: Tipo de frontera no reconocido" << std::endl;
							return 1;
						}
					} else {
						std::cerr << "Error: Falta el tipo de frontera después de -border" << std::endl;
						return 1;
					}
				} else if (std::string(argv[i + 1]) == "periodic") {
					boundary_type = 2;
				} else {
					std::cerr << "Error: Tipo de frontera no reconocido" << std::endl;
					return 1;
				}
			} else {
				std::cerr << "Error: Falta el tipo de frontera después de -border" << std::endl;
				return 1;
			}
		} else if (arg == "-init") {
				if (i + 1 < argc) {
						init_file = argv[i + 1];
				} else {
					std::cerr << "Error: Falta el nombre del archivo de inicialización después de -init" << std::endl;
					return 1;
			}
		}
	}

	// Crear el autómata celular
	Lattice lattice(size, boundary_type, init_file);

	std::cout << "Estado inicial: " << lattice << " Células vivas: " << lattice.getPopulation() << std::endl;
	std::cout << "Pulsa enter para empezar" << std::endl;
	std::cin.get();
	std::thread key_thread(waitForKeypress);
	std::cout << "Pulsa 'q' para terminar" << std::endl;
	while(!stop_flag) {
		lattice.nextGeneration();
		std::cout << lattice << std::endl;
		std::cout << "Células vivas: " << lattice.getPopulation() << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}

	key_thread.join();

	return 0;
}