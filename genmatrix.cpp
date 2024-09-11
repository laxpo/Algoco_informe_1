#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <string>

using namespace std;

// Función que genera una matriz de tamaño `filas` x `columnas` con valores aleatorios en el rango [min_valor, max_valor]
vector<vector<int>> generar_matriz(int filas, int columnas, int min_valor, int max_valor) {
    vector<vector<int>> matriz(filas, vector<int>(columnas));
    random_device rd;
    mt19937 g(rd());
    uniform_int_distribution<> distrib(min_valor, max_valor);

    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            matriz[i][j] = distrib(g);
        }
    }

    return matriz;
}

// Función que guarda una matriz en un archivo
void guardar_matriz_en_archivo(const vector<vector<int>>& matriz, ofstream& archivo) {
    int filas = matriz.size();
    int columnas = matriz[0].size();

    archivo << filas << " " << columnas << endl;  // Guardar dimensiones de la matriz

    for (const auto& fila : matriz) {
        for (int numero : fila) {
            archivo << numero << " ";
        }
        archivo << endl;  // Nueva línea después de cada fila
    }
}

// Función para generar y guardar matrices
void generar_y_guardar_matrices(const string& nombre_archivo, int num_matrices, int min_filas, int max_filas, int min_columnas, int max_columnas, int min_valor, int max_valor) {
    random_device rd;
    mt19937 g(rd());
    uniform_int_distribution<> distrib_filas(min_filas, max_filas);
    uniform_int_distribution<> distrib_columnas(min_columnas, max_columnas);

    ofstream archivo(nombre_archivo);
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo " << nombre_archivo << endl;
        return;
    }

    for (int i = 0; i < num_matrices; ++i) {
        int filas = distrib_filas(g);
        int columnas = distrib_columnas(g);
        vector<vector<int>> matriz = generar_matriz(filas, columnas, min_valor, max_valor);
        guardar_matriz_en_archivo(matriz, archivo);
        cout << "Matriz de tamaño " << filas << "x" << columnas << " guardada en " << nombre_archivo << endl;
    }

    archivo.close();
}

int main() {
    int num_matrices = 1;  // Número de matrices a generar
    int min_filas = 64;      // Número mínimo de filas
    int max_filas = 64;     // Número máximo de filas
    int min_columnas = 64;  // Número mínimo de columnas
    int max_columnas = 64; // Número máximo de columnas
    int min_valor = 1;     // Valor mínimo en el rango
    int max_valor = 100;   // Valor máximo en el rango

    generar_y_guardar_matrices("matriz1.txt", num_matrices, min_filas, max_filas, min_columnas, max_columnas, min_valor, max_valor);
    generar_y_guardar_matrices("matriz2.txt", num_matrices, min_filas, max_filas, min_columnas, max_columnas, min_valor, max_valor);

    return 0;
}
