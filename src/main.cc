#include <iostream>
#include "hash_table.h"


// 12. El programa principal aceptará las siguientes opciones por línea de comandos:

//     a. -ts <s>, s es el tamaño de la tabla.

//     b. -fd <f>, f es el código que identifica a una función de dispersión.

//     c. -hash <open|close>, indica la técnica de dispersión a utilizar. Implica el tipo de
//     secuencia utilizada para el parámetro Container.

//     d. -bs <s>, s es el tamaño del bloque. Sólo para dispersión cerrada.

//     e. -fe <f>, f es el código que identifica a una función de exploración. Sólo para
//     dispersión cerrada.

// 13. Se crea el objeto que implementa la función de dispersión elegida, y si es el caso, también
// se crea el objeto que implementa la función de exploración.

// 14. Se crea la tabla hash, con la versión adecuada de la plantilla según el valor indicado en la
// opción -hash, invocando al constructor con los parámetros indicados por línea de
// comandos. Se utiliza una clase nif como tipo de dato Key en la plantilla.

// 15. El tipo de dato nif representa la parte numérica del número de identificación fiscal.
// Encapsula un número entero de 8 dígitos, e implementa las operaciones necesarias para
// poder utilizarlo como tipo de dato Key.

//     a. El constructor por defecto crea e inicializa un dato nif con un valor aleatorio.

//     b. Constructor de cambio de tipo a partir de un dato entero long.

//     c. Sobrecarga de los operadores de comparación utilizados.

//     d. Sobrecarga del operador de cambio de tipo, que permite convertir un dato de tipo
//     nif en un entero para realizar las operaciones numéricas.
    
//     nif::operator long();

class NIF { // El tipo de dato nif representa la parte numérica del número de identificación fiscal, tiene 8 dígitos
	private:
		long _nif;
	public:
		NIF() : _nif(rand() % 100000000) {};
		explicit NIF(long n) : _nif(n) {};
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

void closeHash(unsigned tableSize, int dispersionFunctionCode, unsigned blockSize, int explorationFunctionCode) {
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

	if (hashTechnique == "open") {
		openHash(tableSize, dispersionFunctionCode);
	} else {
		closeHash(tableSize, dispersionFunctionCode, blockSize, explorationFunctionCode);
	}
  return 0;
}