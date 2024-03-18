#include <iostream>
#include "hash_table.h"

/**
 * @brief Clase que representa un NIF
*/
class NIF { 
	private:
		long _nif;
	public:
		/**
		 * @brief Constructor por defecto
		*/
		NIF() : _nif(rand() % 100000000) {};
		/**
		 * @brief Constructor con parametro
		 * @param n NIF
		*/
		explicit NIF(long n) : _nif(n) {};
		/**
		 * @brief Sobrecarga de operadores
		*/
		bool operator==(const NIF& n) const { return _nif == n._nif; };
		bool operator!=(const NIF& n) const { return _nif != n._nif; };
		bool operator<(const NIF& n) const { return _nif < n._nif; };
		bool operator>(const NIF& n) const { return _nif > n._nif; };
		bool operator<=(const NIF& n) const { return _nif <= n._nif; };
		bool operator>=(const NIF& n) const { return _nif >= n._nif; };
		operator long() const { return _nif; };
		friend std::ostream& operator<<(std::ostream& os, const NIF& n) {
			os << n._nif;
			return os;
		}
};

void openHash(unsigned tableSize, int dispersionFunctionCode) {

	HashTable<NIF, dynamicSequence<NIF>>* ht = nullptr;
	DispersionFunction<NIF>* df = nullptr;

	switch (dispersionFunctionCode) {
		case 0:
			df = new dfModulo<NIF>(tableSize);
			break;
		case 1:
			df = new dfSuma<NIF>(tableSize);
			break;
		case 2:
			df = new dfPseudoaleatoria<NIF>(tableSize);
			break;
		default:
			std::cerr << "Error: Codigo de funcion de dispersion invalido" << std::endl;
			return;
	}

	ht = new HashTable<NIF, dynamicSequence<NIF>>(tableSize, *df);

	while (true) {
	system("clear");
		std::cout << "Indique la acción a realizar:" << std::endl;
		int option;
		std::cout << "1. Insertar manualmente" << std::endl;
		std::cout << "2. Insertar aleatoriamente" << std::endl;
		std::cout << "3. Buscar" << std::endl;
		std::cout << "4. Mostrar tabla" << std::endl;
		std::cout << "5. Salir" << std::endl;
		std::cin >> option;
		long nif;
		switch (option) {
			case 1:
				system("clear");
				std::cout << "Introduzca el NIF a insertar: ";
				std::cin >> nif;
				ht->insert(NIF(nif));
				break;
			case 2:
				system("clear");
				ht->insert(NIF());
				break;
			case 3:
				system("clear");
				std::cout << "Introduzca el NIF a buscar: ";
				std::cin >> nif;
				if (ht->search(NIF(nif))) std::cout << "Encontrado" << std::endl;
				else std::cout << "No encontrado" << std::endl;
				std::cout << "Presione Enter para continuar...";
				getchar();
				getchar();
				break;
			case 4:
				system("clear");
				ht->print();
				std::cout << "Elementos: " << ht->getElements() << "\n";
				std::cout << "Presione Enter para continuar...";
				getchar();
				getchar();
				break;
			case 5:
				system("clear");
				return;
			default:
				std::cerr << "Error: Opcion invalida" << std::endl;
				break;
		}
	}
}

void closeHash(unsigned tableSize, int dispersionFunctionCode, unsigned blockSize, int explorationFunctionCode, unsigned num) {
	DispersionFunction<NIF>* df = nullptr;
	DispersionFunction<NIF>* df2 = nullptr;
	ExplorationFunction<NIF>* ef = nullptr;

	switch (dispersionFunctionCode) {
		case 0:
			df = new dfModulo<NIF>(tableSize);
			break;
		case 1:
			df = new dfSuma<NIF>(tableSize);
			break;
		case 2:
			df = new dfPseudoaleatoria<NIF>(tableSize);
			break;
		default:
			std::cerr << "Error: Codigo de funcion de dispersion invalido" << std::endl;
			return;
	}

	switch (explorationFunctionCode) {
		case 0:
			ef = new efLineal<NIF>();
			break;
		case 1:
			ef = new efCuadratica<NIF>();
			break;
		case 2:
			std::cout << "Introduzca el segundo codigo de funcion de dispersion: ";
			int code;
			std::cin >> code;
			std::cout << "0. Modulo" << std::endl;
			std::cout << "1. Suma" << std::endl;
			std::cout << "2. Pseudoaleatoria" << std::endl;
			switch (code) {
				case 0:
					df2 = new dfModulo<NIF>(tableSize);
					break;
				case 1:
					df2 = new dfSuma<NIF>(tableSize);
					break;
				case 2:
					df2 = new dfPseudoaleatoria<NIF>(tableSize);
					break;
				default:
					std::cerr << "Error: Codigo de funcion de dispersion invalido" << std::endl;
					return;
			}
			ef = new efDispersionDoble<NIF>(df2);
			break;
		case 3:
			ef = new efRedispersion<NIF>(tableSize);
			break;
		default:
			std::cerr << "Error: Codigo de funcion de exploracion invalido" << std::endl;
			return;
	}

	HashTable<NIF, staticSequence<NIF>>* ht = new HashTable<NIF, staticSequence<NIF>>(tableSize, blockSize, *df, *ef);

	while (true) {
		system("clear");
		std::cout << "Indique la acción a realizar:" << std::endl;
		int option;
		std::cout << "1. Insertar manualmente" << std::endl;
		std::cout << "2. Insertar aleatoriamente" << std::endl;
		std::cout << "3. Buscar" << std::endl;
		std::cout << "4. Mostrar tabla" << std::endl;
		std::cout << "5. Salir" << std::endl;
		std::cin >> option;
		long nif;
		switch (option) {
			case 1:
				system("clear");
				std::cout << "Introduzca el NIF a insertar: ";
				std::cin >> nif;
				ht->insert(NIF(nif));
				break;
			case 2:
				system("clear");
				for (unsigned i = 0; i < num; i++) {
					if (ht->isFull()) break;
					ht->insert(NIF());
				}
				std::cout << "Se han insertado " << ht->getElements() << " elementos\n";
				std::cout << "Presione Enter para continuar...";
				getchar();
				getchar();
				break;
			case 3:
				system("clear");
				std::cout << "Introduzca el NIF a buscar: ";
				std::cin >> nif;
				if (ht->search(NIF(nif))) std::cout << "Encontrado" << std::endl;
				else std::cout << "No encontrado" << std::endl;
				std::cout << "Presione Enter para continuar...";
				getchar();
				getchar();
				break;
			case 4:
				system("clear");
				ht->print();
				std::cout << "Elementos: " << ht->getElements() << "\n";
				std::cout << "Numero de exploraciones: " << ht->getNumberOfExplorations() << "\n";
				std::cout << "Presione Enter para continuar...";
				getchar();
				getchar();
				break;
			case 5:
				system("clear");
				return;
			default:
				std::cerr << "Error: Opcion invalida" << std::endl;
				break;
		}
	}
}

int main(int argc, char *argv[]) {
	unsigned tableSize = 0;
	unsigned blockSize = 0;
	std::string hashTechnique;
	int dispersionFunctionCode;
	int explorationFunctionCode;
	unsigned num = 0;

	if (argc < 7) {
		std::cerr << "Error: Numero de argumentos invalido" << std::endl;
		return 1;
	}

	// Analizar argumentos
	for (int i = 1; i < argc; i++) {
		std::string arg = argv[i];
		if (arg == "-ts") {
			if (i + 1 < argc) {
				tableSize = std::stoi(argv[i + 1]);
				i++;
			}
		} else if (arg == "-fd") {
			if (i + 1 < argc) {
				dispersionFunctionCode = std::stoi(argv[i + 1]);
				i++;
			}
		} else if (arg == "-hash") {
			if (i + 1 < argc) {
				hashTechnique = argv[i + 1];
				i++;
			}
		}
	}

	if (hashTechnique == "close") {
		if (argc < 11) {
			std::cerr << "Error: Numero de argumentos invalido" << std::endl;
			return 1;
		}
		for (int i = 1; i < argc; i++) {
			std::string arg = argv[i];
			if (arg == "-bs") {
				if (i + 1 < argc) {
					blockSize = std::stoi(argv[i + 1]);
					i++;
				}
			} else if (arg == "-fe") {
				if (i + 1 < argc) {
					explorationFunctionCode = std::stoi(argv[i + 1]);
					i++;
				}
			}
		}
	}

	// Hay 2 argumentos mas: -num <n>
	for (int i = 1; i < argc; i++) {
		std::string arg = argv[i];
		if (arg == "-num") {
			if (i + 1 < argc) {
				num = std::stoi(argv[i + 1]);
				i++;
			}
		}
	}

	if (hashTechnique == "open") {
		openHash(tableSize, dispersionFunctionCode);
	} else {
		closeHash(tableSize, dispersionFunctionCode, blockSize, explorationFunctionCode, num);
	}
  return 0;
}