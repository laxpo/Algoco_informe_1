#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <stdexcept>

using namespace std;
using namespace std::chrono;

typedef long long lld;

// Función para leer una matriz desde un archivo
vector<vector<lld>> leer_matriz_desde_archivo(const string& nombre_archivo) {
    ifstream archivo(nombre_archivo);
    if (!archivo.is_open()) {
        throw invalid_argument("No se pudo abrir el archivo: " + nombre_archivo);
    }

    int filas, columnas;
    archivo >> filas >> columnas;
    vector<vector<lld>> matriz(filas, vector<lld>(columnas));

    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            archivo >> matriz[i][j];
        }
    }

    archivo.close();
    return matriz;
}

// Función para sumar matrices
vector<vector<lld>> sumar_matrices(const vector<vector<lld>>& A, const vector<vector<lld>>& B) {
    int n = A.size();
    vector<vector<lld>> C(n, vector<lld>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}

// Función para restar matrices
vector<vector<lld>> restar_matrices(const vector<vector<lld>>& A, const vector<vector<lld>>& B) {
    int n = A.size();
    vector<vector<lld>> C(n, vector<lld>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    return C;
}

// Algoritmo de Strassen para multiplicar matrices
vector<vector<lld>> strassen(const vector<vector<lld>>& A, const vector<vector<lld>>& B) {
    int n = A.size();
    vector<vector<lld>> C(n, vector<lld>(n));

    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return C;
    }

    int newSize = n / 2;
    vector<vector<lld>> A11(newSize, vector<lld>(newSize));
    vector<vector<lld>> A12(newSize, vector<lld>(newSize));
    vector<vector<lld>> A21(newSize, vector<lld>(newSize));
    vector<vector<lld>> A22(newSize, vector<lld>(newSize));
    vector<vector<lld>> B11(newSize, vector<lld>(newSize));
    vector<vector<lld>> B12(newSize, vector<lld>(newSize));
    vector<vector<lld>> B21(newSize, vector<lld>(newSize));
    vector<vector<lld>> B22(newSize, vector<lld>(newSize));

    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }

    auto M1 = strassen(sumar_matrices(A11, A22), sumar_matrices(B11, B22));
    auto M2 = strassen(sumar_matrices(A21, A22), B11);
    auto M3 = strassen(A11, restar_matrices(B12, B22));
    auto M4 = strassen(A22, restar_matrices(B21, B11));
    auto M5 = strassen(sumar_matrices(A11, A12), B22);
    auto M6 = strassen(restar_matrices(A21, A11), sumar_matrices(B11, B12));
    auto M7 = strassen(restar_matrices(A12, A22), sumar_matrices(B21, B22));

    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i][j] = M1[i][j] + M4[i][j] - M5[i][j] + M7[i][j];
            C[i][j + newSize] = M3[i][j] + M5[i][j];
            C[i + newSize][j] = M2[i][j] + M4[i][j];
            C[i + newSize][j + newSize] = M1[i][j] - M2[i][j] + M3[i][j] + M6[i][j];
        }
    }

    return C;
}

// Función para imprimir una matriz
void imprimir_matriz(const vector<vector<lld>>& matriz) {
    for (const auto& fila : matriz) {
        for (lld elemento : fila) {
            cout << elemento << "\t";
        }
        cout << endl;
    }
}

int main() {
    try {
        // Leer matrices desde los archivos
        vector<vector<lld>> A = leer_matriz_desde_archivo("matriz1.txt");
        vector<vector<lld>> B = leer_matriz_desde_archivo("matriz2.txt");

        if (A.size() != A[0].size() || B.size() != B[0].size() || A.size() != B.size()) {
            throw invalid_argument("Las matrices deben ser cuadradas y de la misma dimensión.");
        }

        // Medir el tiempo de ejecución del algoritmo de Strassen
        auto inicio = high_resolution_clock::now();
        vector<vector<lld>> C = strassen(A, B);
        auto fin = high_resolution_clock::now();

        // Imprimir la matriz resultante
        cout << "Matriz resultante:\n";
        imprimir_matriz(C);

        // Medir la duración
        auto duracion = duration_cast<milliseconds>(fin - inicio);
        cout << "Tiempo tomado para la multiplicación de matrices: " << duracion.count() << " milisegundos" << endl;
    }
    catch (const exception& e) {
        cerr << e.what() << endl;
        return 1;
    }

    return 0;
}
