#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <fstream>
#include <string>
#include <unordered_set>

using namespace std;

// Función que genera un arreglo desordenado sin números repetidos
vector<int> desordenado(int tamaño, int min_valor, int max_valor) {
    vector<int> arreglo;

    // Verificar que el rango de valores sea suficiente para generar números únicos
    if (max_valor - min_valor + 1 < tamaño) {
        cerr << "El rango de valores no es lo suficientemente amplio para generar un arreglo sin repetidos." << endl;
        exit(1);
    }

    // Generar números únicos
    for (int i = min_valor; i < min_valor + tamaño; ++i) {
        arreglo.push_back(i);
    }

    // Barajar el arreglo para que esté desordenado
    random_device rd;
    mt19937 g(rd());
    shuffle(arreglo.begin(), arreglo.end(), g);

    return arreglo;
}

// Función que genera un arreglo ordenado sin números repetidos
vector<int> ordenado(int tamaño, int min_valor, int max_valor) {
    vector<int> arreglo;

    // Verificar que el rango de valores sea suficiente para generar números únicos
    if (max_valor - min_valor + 1 < tamaño) {
        cerr << "El rango de valores no es lo suficientemente amplio para generar un arreglo sin repetidos." << endl;
        exit(1);
    }

    // Generar números únicos de forma ordenada
    for (int i = min_valor; i < min_valor + tamaño; ++i) {
        arreglo.push_back(i);
    }

    return arreglo;
}

// Función que genera un arreglo semiordenado sin números repetidos
vector<int> semi_ordenado(int tamaño, int min_valor, int max_valor, double porcentaje_desorden) {
    vector<int> arreglo = ordenado(tamaño, min_valor, max_valor);

    int cantidad_desordenada = static_cast<int>(tamaño * porcentaje_desorden);
    random_device rd;
    mt19937 g(rd());

    // Aplicar desorden a una parte del arreglo
    for (int i = 0; i < cantidad_desordenada; ++i) {
        int idx1 = g() % tamaño;
        int idx2 = g() % tamaño;
        swap(arreglo[idx1], arreglo[idx2]);
    }

    return arreglo;
}

// Función que guarda un arreglo en el archivo
void guardar_arreglo_en_archivo(const vector<int>& arreglo, ofstream& archivo) {
    for (int numero : arreglo) {
        archivo << numero << " ";
    }
    archivo << endl;  // Nueva línea después de cada arreglo
}

int main() {
    int num_arreglos = 20;  // Número de arreglos a generar por cada tipo
    int min_valor = 0;  // Valor mínimo en el rango
    int max_valor = 100000;  // Valor máximo en el rango, amplio para números no repetidos
    int tamaño_min = 5000;  // Tamaño mínimo del arreglo
    int tamaño_max = 5000;  // Tamaño máximo del arreglo

    random_device rd;
    mt19937 g(rd());
    uniform_int_distribution<> distrib_tamaño(tamaño_min, tamaño_max);

    // Guardar los arreglos desordenados
    ofstream archivo_desordenado("desordenado.txt");
    if (!archivo_desordenado.is_open()) {
        cerr << "Error al abrir el archivo desordenado." << endl;
        return 1;
    }

    for (int i = 0; i < num_arreglos; ++i) {
        int tamaño = distrib_tamaño(g);  // Seleccionar un tamaño aleatorio dentro del rango
        vector<int> arreglo = desordenado(tamaño, min_valor, max_valor);
        guardar_arreglo_en_archivo(arreglo, archivo_desordenado);
        cout << "Arreglo desordenado de tamaño " << tamaño << " guardado." << endl;
    }
    archivo_desordenado.close();

    // Guardar los arreglos ordenados
    ofstream archivo_ordenado("ordenado.txt");
    if (!archivo_ordenado.is_open()) {
        cerr << "Error al abrir el archivo ordenado." << endl;
        return 1;
    }

    for (int i = 0; i < num_arreglos; ++i) {
        int tamaño = distrib_tamaño(g);  // Seleccionar un tamaño aleatorio dentro del rango
        vector<int> arreglo = ordenado(tamaño, min_valor, max_valor);
        guardar_arreglo_en_archivo(arreglo, archivo_ordenado);
        cout << "Arreglo ordenado de tamaño " << tamaño << " guardado." << endl;
    }
    archivo_ordenado.close();

    // Guardar los arreglos semiordenados
    ofstream archivo_semi_ordenado("semi_ordenado.txt");
    if (!archivo_semi_ordenado.is_open()) {
        cerr << "Error al abrir el archivo semiordenado." << endl;
        return 1;
    }

    for (int i = 0; i < num_arreglos; ++i) {
        int tamaño = distrib_tamaño(g);  // Seleccionar un tamaño aleatorio dentro del rango
        vector<int> arreglo = semi_ordenado(tamaño, min_valor, max_valor, 0.5);  // 50% desordenado
        guardar_arreglo_en_archivo(arreglo, archivo_semi_ordenado);
        cout << "Arreglo semiordenado de tamaño " << tamaño << " guardado." << endl;
    }
    archivo_semi_ordenado.close();

    cout << "Todos los arreglos de diferentes tamaños han sido guardados en archivos de texto." << endl;

    return 0;
}
