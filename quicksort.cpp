#include <bits/stdc++.h>
#include <chrono>
using namespace std;
using namespace std::chrono;

// Función de partición para QuickSort
int partition(vector<int>& vec, int low, int high) {

    // Seleccionar el último elemento como pivote
    int pivot = vec[high];

    // Índice de elemento justo antes del último elemento
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        // Si el elemento actual es menor o igual al pivote
        if (vec[j] <= pivot) {
            i++;
            swap(vec[i], vec[j]);
        }
    }

    // Colocar el pivote en su posición
    swap(vec[i + 1], vec[high]);

    // Devolver el índice de partición
    return (i + 1);
}

// Función recursiva para QuickSort
void quickSort(vector<int>& vec, int low, int high) {

    if (low < high) {
        // Encontrar el índice de partición
        int pi = partition(vec, low, high);

        // Ordenar los elementos antes y después de la partición
        quickSort(vec, low, pi - 1);
        quickSort(vec, pi + 1, high);
    }
}

// Función para leer el arreglo desde la entrada estándar
vector<int> leer_arreglo_desde_entrada_estandar() {
    vector<int> arreglo;
    int numero;

    // Leer números hasta que no haya más
    while (cin >> numero) {
        arreglo.push_back(numero);
    }

    return arreglo;
}

// Función para imprimir un vector
void printVector(const vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++)
        cout << arr[i] << " ";
    cout << endl;
}

int main() {
    // Leer el arreglo desde la entrada estándar
    vector<int> vec = leer_arreglo_desde_entrada_estandar();

    if (vec.empty()) {
        cerr << "El arreglo está vacío o no se pudieron leer los números." << endl;
        return 1;
    }

    cout << "Arreglo original:\n";
    printVector(vec);

    // Medir el tiempo de inicio
    auto start = high_resolution_clock::now();

    // Llamar a QuickSort para el vector vec
    quickSort(vec, 0, vec.size() - 1);

    // Medir el tiempo de finalización
    auto stop = high_resolution_clock::now();

    // Calcular el tiempo transcurrido
    auto duration = duration_cast<milliseconds>(stop - start);

    cout << "Arreglo ordenado:\n";
    printVector(vec);

    cout << "Tiempo tomado por QuickSort: " << duration.count() << " milisegundos" << endl;

    return 0;
}
