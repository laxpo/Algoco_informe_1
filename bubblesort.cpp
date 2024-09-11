#include <bits/stdc++.h>
#include <chrono>
using namespace std;
using namespace std::chrono;

// Optimized version of Bubble Sort
void bubbleSort(vector<int>& arr)
{
    int n = arr.size();
    bool swapped;
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped)
            break;
    }
}

// Function to print an array
void printArray(const vector<int>& arr)
{
    for (int num : arr)
        cout << num << " ";
    cout << endl;
}

// Function to read the array from standard input
vector<int> leer_arreglo_desde_entrada_estandar()
{
    vector<int> arreglo;
    int numero;

    cout << "Introduce los números del arreglo separados por espacios (Ctrl+D para finalizar la entrada):" << endl;
    while (cin >> numero) {
        arreglo.push_back(numero);
    }

    return arreglo;
}

int main()
{
    // Leer el arreglo desde la entrada estándar
    vector<int> arr = leer_arreglo_desde_entrada_estandar();

    if (arr.empty()) {
        cerr << "El arreglo está vacío o no se pudieron leer los números." << endl;
        return 1;
    }

    cout << "Arreglo original:\n";
    printArray(arr);

    // Tomar el tiempo de inicio
    auto start = high_resolution_clock::now();

    // Ordenar el arreglo usando Bubble Sort
    bubbleSort(arr);

    // Tomar el tiempo de finalización
    auto stop = high_resolution_clock::now();

    // Calcular el tiempo transcurrido
    auto duration = duration_cast<milliseconds>(stop - start);

    cout << "Arreglo ordenado:\n";
    printArray(arr);

    cout << "Tiempo tomado por Bubble Sort: " << duration.count() << " milisegundos" << endl;

    return 0;
}
