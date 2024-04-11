#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>

using namespace std;

struct Vectores {
    vector<double> precios;
    vector<string> productos;
    vector<int> busquedas;

    Vectores(int max_size) {
        precios.resize(max_size);
        productos.resize(max_size);
        busquedas.resize(max_size);
    }
};

void merge(vector<double>& precios, int left, int right, int middle) {
    int n1 = middle - left + 1;
    int n2 = right - middle;

    std::vector<double> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = precios[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = precios[middle + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] >= R[j]) {
            precios[k] = L[i];
            i++;
        }
        else {
            precios[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        precios[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        precios[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<double>& precios, int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;
        mergeSort(precios, left, middle);
        mergeSort(precios, middle + 1, right);
        merge(precios, left, right, middle);
    }
}

void mergePRD(vector<string>& productos, int left, int right, int middle) {
    int n1 = middle - left + 1;
    int n2 = right - middle;

    vector<string> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = productos[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = productos[middle + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] >= R[j]) {
            productos[k] = L[i];
            i++;
        }
        else {
            productos[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        productos[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        productos[k] = R[j];
        j++;
        k++;
    }
}

void mergeSortPRD(vector<string>& productos, int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;
        mergeSortPRD(productos, left, middle);
        mergeSortPRD(productos, middle + 1, right);
        mergePRD(productos, left, right, middle);
    }
}

void mergeBUS(vector<int>& busquedas, int left, int right, int middle) {
    int n1 = middle - left + 1;
    int n2 = right - middle;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = busquedas[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = busquedas[middle + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] >= R[j]) {
            busquedas[k] = L[i];
            i++;
        }
        else {
            busquedas[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        busquedas[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        busquedas[k] = R[j];
        j++;
        k++;
    }
}

void mergeSortBUS(vector<int>& busquedas, int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;
        mergeSortBUS(busquedas, left, middle);
        mergeSortBUS(busquedas, middle + 1, right);
        mergeBUS(busquedas, left, right, middle);
    }
}

int main() {
    int max_size, opc, a = 0;

    cout << "Ingresa el numero de productos: \n";
    cin >> max_size;

    Vectores datos(max_size);

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(200, 1500);

    cout << "Ingresa el nombre de los productos:";
    cin.ignore();
    for (int i = 0; i < max_size; i++) {
        cout << "Producto" << i + 1 << " : \n" ;
        getline(cin, datos.productos[i]);
    }

    cout << "Ingresa el precio de los productos:";
    for (int i = 0; i < max_size; i++) {
        cout << datos.productos[i] << ": \n";
        cin >> datos.precios[i];
    }

    do {
        cout << "De que manera quieres ordenar los datos?\n";
        cout << "1-Por nombre A-Z\n2-Por nombre Z-A\n3-Por precio, ascendente\n4-Por precio, descendente\n5-Mostrar busquedas globales\n6-Salir";
        cin >> opc;

        switch (opc) {
        case 1:
            mergeSortPRD(datos.productos, 0, max_size - 1);
            for (int i = 0; i < max_size; i++) {
                cout << datos.productos[i] << endl;
            }
            break;

        case 2:
            mergeSortPRD(datos.productos, 0, max_size - 1);
            for (int i = max_size - 1; i >= 0; i--) {
                cout << datos.productos[i] << endl;
            }
            break;

        case 3:
            mergeSort(datos.precios, 0, max_size - 1);
            for (int i = 0; i < max_size; i++) {
                cout << datos.precios[i] << endl;
            }
            break;

        case 4:
            mergeSort(datos.precios, 0, max_size - 1);
            for (int i = max_size - 1; i >= 0; i--) {
                cout << datos.precios[i] << endl;
            }
            break;

        case 5:
            cout << "\nMás relevantes" << std::endl;
            for (int i = 0; i < max_size; i++) {
                datos.busquedas[i] = dis(gen);
            }
            mergeSortBUS(datos.busquedas, 0, max_size - 1);
            for (int i = 0; i < max_size; i++) {
                cout << datos.productos[i] << " tienes:" << datos.busquedas[i] << endl;
            }
            break;

        case 6:
            a = 1;
            break;
        }
    } while (a == 1);

    return 0;
}
