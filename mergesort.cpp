#include <bits/stdc++.h>
#include <chrono>
using namespace std;
using namespace std::chrono;

// Merges two subarrays of arr[].
// First subarray is arr[left..mid]
// Second subarray is arr[mid+1..right]
void merge(vector<int>& arr, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temp vectors
    vector<int> L(n1), R(n2);

    // Copy data to temp vectors L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0;
    int k = left;

    // Merge the temp vectors back into arr[left..right]
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// begin is for left index and end is right index
// of the sub-array of arr to be sorted
void mergeSort(vector<int>& arr, int left, int right)
{
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

// Function to print a vector
void printVector(const vector<int>& arr)
{
    for (int i = 0; i < arr.size(); i++)
        cout << arr[i] << " ";
    cout << endl;
}

// Function to read the array from standard input
vector<int> leer_arreglo_desde_entrada_estandar()
{
    vector<int> arreglo;
    int numero;

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
    printVector(arr);

    // Tomar el tiempo de inicio
    auto start = high_resolution_clock::now();

    // Ordenar el arreglo usando Merge Sort
    mergeSort(arr, 0, arr.size() - 1);

    // Tomar el tiempo de finalización
    auto stop = high_resolution_clock::now();

    // Calcular el tiempo transcurrido
    auto duration = duration_cast<milliseconds>(stop - start);

    cout << "Arreglo ordenado:\n";
    printVector(arr);

    cout << "Tiempo tomado por Merge Sort: " << duration.count() << " milisegundos" << endl;

    return 0;
}
