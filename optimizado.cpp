#include <bits/stdc++.h>
#include <chrono>
using namespace std;
using namespace std::chrono;

// Función para leer una matriz desde un archivo
vector<vector<long long>> leer_matriz_desde_archivo(const string& nombre_archivo) {
    ifstream archivo(nombre_archivo);
    if (!archivo.is_open()) {
        throw invalid_argument("No se pudo abrir el archivo: " + nombre_archivo);
    }

    int filas, columnas;
    archivo >> filas >> columnas;

    vector<vector<long long>> matriz(filas, vector<long long>(columnas));

    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            archivo >> matriz[i][j];
        }
    }

    archivo.close();
    return matriz;
}

// Función para trasponer una matriz
vector<vector<long long>> transponer_matriz(const vector<vector<long long>>& matriz) {
    int filas = matriz.size();
    int columnas = matriz[0].size();
    vector<vector<long long>> traspuesta(columnas, vector<long long>(filas));

    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            traspuesta[j][i] = matriz[i][j];
        }
    }
    return traspuesta;
}

// Función para multiplicar dos matrices con optimización de trasposición
vector<vector<long long>> multiplicar_matrices(const vector<vector<long long>>& mat1, const vector<vector<long long>>& mat2) {
    int filas1 = mat1.size();
    int columnas1 = mat1[0].size();
    int filas2 = mat2.size();
    int columnas2 = mat2[0].size();

    // Comprobar si las dimensiones son válidas para la multiplicación
    if (columnas1 != filas2) {
        throw invalid_argument("El número de columnas de la primera matriz debe ser igual al número de filas de la segunda matriz.");
    }

    // Transponer la segunda matriz para optimizar el acceso
    vector<vector<long long>> mat2_traspuesta = transponer_matriz(mat2);

    vector<vector<long long>> resultado(filas1, vector<long long>(columnas2, 0));

    for (int i = 0; i < filas1; i++) {
        for (int j = 0; j < columnas2; j++) {
            for (int k = 0; k < columnas1; k++) {
                resultado[i][j] += mat1[i][k] * mat2_traspuesta[j][k];
            }
        }
    }

    return resultado;
}

// Función para imprimir una matriz
void imprimir_matriz(const vector<vector<long long>>& matriz) {
    for (const auto& fila : matriz) {
        for (long long elemento : fila) {
            cout << elemento << "\t";
        }
        cout << endl;
    }
}

int main() {
    try {
        // Leer las matrices desde los archivos
        vector<vector<long long>> mat1 = leer_matriz_desde_archivo("matriz1.txt");
        vector<vector<long long>> mat2 = leer_matriz_desde_archivo("matriz2.txt");

        // Medir el tiempo de la multiplicación de matrices
        auto inicio = high_resolution_clock::now();

        vector<vector<long long>> resultado = multiplicar_matrices(mat1, mat2);

        auto fin = high_resolution_clock::now();
        auto duracion = duration_cast<milliseconds>(fin - inicio);

        // Imprimir la matriz resultado
        cout << "Matriz resultante:\n";
        imprimir_matriz(resultado);

        cout << "Tiempo tomado para la multiplicación de matrices: " << duracion.count() << " milisegundos" << endl;
    }
    catch (const exception& e) {
        cerr << e.what() << endl;
        return 1;
    }

    return 0;
}
