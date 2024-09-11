#include <bits/stdc++.h>
#include <chrono>
using namespace std;
using namespace std::chrono;

// Función para leer una matriz desde un archivo
vector<vector<long long>> leer_matriz_desde_archivo(ifstream &archivo, int &filas, int &columnas) {
    archivo >> filas >> columnas;  // Leer las dimensiones de la matriz

    vector<vector<long long>> matriz(filas, vector<long long>(columnas));

    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            archivo >> matriz[i][j];
        }
    }

    return matriz;
}

// Función para multiplicar dos matrices
vector<vector<long long>> mulMat(const vector<vector<long long>> &mat1, const vector<vector<long long>> &mat2) {
    int R1 = mat1.size();
    int C1 = mat1[0].size();
    int R2 = mat2.size();
    int C2 = mat2[0].size();

    vector<vector<long long>> rslt(R1, vector<long long>(C2, 0));

    for (int i = 0; i < R1; ++i) {
        for (int j = 0; j < C2; ++j) {
            for (int k = 0; k < C1; ++k) {
                // Acumulamos el producto en una variable temporal para evitar desbordamientos
                long long producto = mat1[i][k] * mat2[k][j];
                rslt[i][j] += producto;
            }
        }
    }

    return rslt;
}

// Función para imprimir una matriz
void printMatrix(const vector<vector<long long>> &matrix) {
    for (const auto &row : matrix) {
        for (long long val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

int main() {
    string archivo1 = "matriz1.txt";  // Nombre del archivo de la primera matriz
    string archivo2 = "matriz2.txt";  // Nombre del archivo de la segunda matriz

    ifstream archivo_1(archivo1);
    ifstream archivo_2(archivo2);

    if (!archivo_1.is_open() || !archivo_2.is_open()) {
        cerr << "Error al abrir uno de los archivos." << endl;
        return 1;
    }

    int filas1, columnas1, filas2, columnas2;

    vector<vector<long long>> mat1 = leer_matriz_desde_archivo(archivo_1, filas1, columnas1);
    vector<vector<long long>> mat2 = leer_matriz_desde_archivo(archivo_2, filas2, columnas2);

    archivo_1.close();
    archivo_2.close();

    if (columnas1 != filas2) {
        cerr << "El número de columnas de la primera matriz debe ser igual al número de filas de la segunda matriz." << endl;
        return 1;
    }

    // Tomar el tiempo de inicio
    auto start = high_resolution_clock::now();

    // Multiplicar las matrices
    vector<vector<long long>> resultado = mulMat(mat1, mat2);

    // Tomar el tiempo de finalización
    auto stop = high_resolution_clock::now();

    // Calcular el tiempo transcurrido
    auto duration = duration_cast<milliseconds>(stop - start);

    cout << "Resultado de la multiplicación de matrices:" << endl;
    printMatrix(resultado);

    cout << "Tiempo tomado para la multiplicación de matrices: " << duration.count() << " milisegundos" << endl;

    return 0;
}
