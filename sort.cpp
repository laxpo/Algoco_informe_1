#include <bits/stdc++.h>
#include <chrono>
using namespace std;
using namespace std::chrono;

// Función para leer el arreglo desde la entrada estándar
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
    for (const int& num : arr) {
        cout << num << " ";
    }
    cout << endl;

    // Tomar el tiempo de inicio
    auto start = high_resolution_clock::now();

    // Ordenar el arreglo usando std::sort
    sort(arr.begin(), arr.end());

    // Tomar el tiempo de finalización
    auto stop = high_resolution_clock::now();

    // Calcular el tiempo transcurrido
    auto duration = duration_cast<milliseconds>(stop - start);

    cout << "Arreglo ordenado:\n";
    for (const int& num : arr) {
        cout << num << " ";
    }
    cout << endl;

    cout << "Tiempo tomado por std::sort: " << duration.count() << " milisegundos" << endl;

    return 0;
}
