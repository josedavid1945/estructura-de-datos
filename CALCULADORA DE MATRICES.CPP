#include <iostream>
#include <cstdlib> 
using namespace std;

class Matrix {
private:
    int fila;
    int columna;
    static const int MAX_SIZE = 100;
    int matriz[MAX_SIZE][MAX_SIZE];

public:
    // aqui lo q mas me costo entender xddddd (metodo constructor, esto es parte del tad que no se me dejo modificar, )
    Matrix(int i, int j) : fila(i), columna(j) {
        if (i > MAX_SIZE || j > MAX_SIZE) {
            cout << " Tamaño de la matriz excede el límite permitido." << endl;
            exit(1);
        }
        for (int m = 0; m < fila; m++) {
            for (int n = 0; n < columna; n++) {
                matriz[m][n] = 0;
            }
        }
    }

    // Métodos set y get para cualquier elemento de la matriz
    void setElemento(int i, int j, int valor) {
        if (i >= 0 && i < fila && j >= 0 && j < columna) {
            matriz[i][j] = valor;
        } else {
            cout << " indice fuera de los limites de la matriz." << endl;
        }
    }

    int getElemento(int i, int j) const {
        if (i >= 0 && i < fila && j >= 0 && j < columna) {
            return matriz[i][j];
        } else {
            cout << "indice fuera de los limites de la matriz." << endl;
        }
        return 0;
    }

    // Método para obtener el numero de filas
    int getFila() const {
        return fila;
    }

    // Método para obtener el numero de columnas
    int getColumna() const {
        return columna;
    }

    // Método para imprimir la matriz
    void imprimir() const {
        for (int i = 0; i < fila; i++) {
            for (int j = 0; j < columna; j++) {
                cout << matriz[i][j] << " ";
            }
            cout << endl;
        }
    }
};

// Funcion para sumar matrices
void sumarMatriz(const Matrix& A, const Matrix& B, Matrix& R) {
    if (A.getFila() != B.getFila() || A.getColumna() != B.getColumna()) {
        cout << "Las matrices deben tener las mismas dimensiones para sumarse." << endl;
        return;
    }

    for (int i = 0; i < A.getFila(); i++) {
        for (int j = 0; j < A.getColumna(); j++) {
            R.setElemento(i, j, A.getElemento(i, j) + B.getElemento(i, j));
        }
    }
}

// Función para restar matrices
void restarMatriz(const Matrix& A, const Matrix& B, Matrix& R) {
    if (A.getFila() != B.getFila() || A.getColumna() != B.getColumna()) {
        cout << " Las matrices deben tener las mismas dimensiones para restarse." << endl;
        return;
    }

    for (int i = 0; i < A.getFila(); i++) {
        for (int j = 0; j < A.getColumna(); j++) {
            R.setElemento(i, j, A.getElemento(i, j) - B.getElemento(i, j));
        }
    }
}

// Función para multiplicar matrices
void multiplicarMatriz(const Matrix& A, const Matrix& B, Matrix& R) {
    if (A.getColumna() != B.getFila()) {
        cout << " El numero de columnas de la matriz A debe ser igual al numero de filas de la matriz B." << endl;
        return;
    }

    for (int i = 0; i < A.getFila(); i++) {
        for (int j = 0; j < B.getColumna(); j++) {
            int suma = 0;
            for (int k = 0; k < A.getColumna(); k++) {
                suma += A.getElemento(i, k) * B.getElemento(k, j);
            }
            R.setElemento(i, j, suma);
        }
    }
}

// Función para multiplicar una matriz por un escalar
void multiplicarPorEscalar(Matrix& A, int escalar) {
    for (int i = 0; i < A.getFila(); i++) {
        for (int j = 0; j < A.getColumna(); j++) {
            A.setElemento(i, j, A.getElemento(i, j) * escalar);
        }
    }
}

// Función para obtener un submatriz excluyendo una fila y columna (usada en determinantes, ojo pero solo para matrices de mas de 2x2)
Matrix obtenerSubmatriz(const Matrix& mat, int exclFila, int exclColumna) {
    int newFila = mat.getFila() - 1;
    int newColumna = mat.getColumna() - 1;
    Matrix submatriz(newFila, newColumna);

    int sub_i = 0;
    for (int i = 0; i < mat.getFila(); i++) {
        if (i == exclFila) continue;

        int sub_j = 0;
        for (int j = 0; j < mat.getColumna(); j++) {
            if (j == exclColumna) continue;

            submatriz.setElemento(sub_i, sub_j, mat.getElemento(i, j));
            sub_j++;
        }
        sub_i++;
    }

    return submatriz;
}

// Función para calcular el determinante de una matriz
int calcularDeterminante(const Matrix& mat) {
    if (mat.getFila() != mat.getColumna()) {
        cout << "Error: Solo se puede calcular el determinante de matrices cuadradas." << endl;
        return 0;
    }

    int n = mat.getFila();

    //  si la matriz es 1x1
    if (n == 1) {
        return mat.getElemento(0, 0);
    }

    //  si la matriz es 2x2
    if (n == 2) {
        return (mat.getElemento(0, 0) * mat.getElemento(1, 1)) - 
               (mat.getElemento(0, 1) * mat.getElemento(1, 0));
    }

    //calcular el determinante de otro tipo de matrices
    int determinante = 0;
    for (int j = 0; j < n; j++) {
        Matrix submatriz = obtenerSubmatriz(mat, 0, j);
        int nosexd = mat.getElemento(0, j) * calcularDeterminante(submatriz);
        determinante += (j % 2 == 0 ? nosexd : -nosexd); // cambiar signos(creo que si va a resultar, lo vie en un video de media hora)
    }

    return determinante;
}


void menu(Matrix& A, Matrix& B, Matrix& R) {
    int opcion;
    bool bandera = true;
    while (bandera) {
        cout << "Suma de matrices --> 1" << endl;
        cout << "Resta de matrices --> 2" << endl;
        cout << "Multiplicación de matrices --> 3" << endl;
        cout << "Multiplicar por escalar --> 4" << endl;
        cout << "Calcular determinante --> 5" << endl;
        cout << "Salir --> 0" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                sumarMatriz(A, B, R);
                cout << "Resultado de la suma:" << endl;
                R.imprimir();
                system("pause");
                system("cls");
                break;
            case 2:
                restarMatriz(A, B, R);
                cout << "Resultado de la resta:" << endl;
                R.imprimir();
                system("pause");
                system("cls");
                break;
            case 3:
                multiplicarMatriz(A, B, R);
                cout << "Resultado de la multiplicacion:" << endl;
                R.imprimir();
                system("pause");
                system("cls");
                
                break;
            case 4: {
                int escalar;
                cout << "Ingrese el escalar para multiplicar: ";
                cin >> escalar;
                multiplicarPorEscalar(A, escalar);
                cout << "Resultado de la multiplicacion por escalar:" << endl;
                A.imprimir();
                system("cls");
                system("pause");
                break;
            }
            case 5: {
                char matriz;
                cout<<"ingrese la matriz que desea dacar el determinante: ";cin>>matriz;
                if (matriz=='A')
                {
                    int determinanteA = calcularDeterminante(A);
                    cout << "Determinante de la matriz A: " << determinanteA << endl;
                }
                if (matriz=='B')
                {
                    int determinanteB = calcularDeterminante(B);
                    cout << "Determinante de la matriz A: " << determinanteB << endl;
                }
                else
                {
                    cout<<"dicha matriz no existe";
                }
                system("pause");
                system("cls");
                
                break;
            }
            case 0:
                bandera = false;
                break;
            default:
                cout << "Opcion no valida." << endl;
                break;
        }
    }
}

// Función principal
int main(void) {
    int nA, mA, nB, mB;

    //  dimensiones para la matriz A
    cout << "Ingrese el numero de filas para la matriz A: ";
    cin >> nA;
    cout << "Ingrese el numero de columnas para la matriz A: ";
    cin >> mA;
    Matrix A(nA, mA);

    // dimensiones para la matriz B
    cout << "Ingrese el numero de filas para la matriz B: ";
    cin >> nB;
    cout << "Ingrese el numero de columnas para la matriz B: ";
    cin >> mB;
    Matrix B(nB, mB);

    // Inicializar matriz 
    Matrix R(nA, mA);

    // Pedir valores para la matriz A
    for (int i = 0; i < nA; i++) {
        for (int j = 0; j < mA; j++) {
            int valor;
            cout << "Ingrese el valor de la posicion " << i+1 << "|" << j+1 << " de la matriz A: ";
            cin >> valor;
            A.setElemento(i, j, valor);
        }
    }
    system("cls");

    // Pedir valores para la matriz B
    for (int i = 0; i < nB; i++) {
        for (int j = 0; j < mB; j++) {
            int valor;
            cout << "Ingrese el valor de la posicion " << i+1 << "|" << j+1 << " de la matriz B: ";
            cin >> valor;
            B.setElemento(i, j, valor);
        }
    }
    system("cls");

    // Imprimir matrices A y B
    cout << "Matriz A:" << endl;
    A.imprimir();
    cout << "Matriz B:" << endl;
    B.imprimir();

    menu(A, B, R);

    return 0;
    /*fueron 3 horas de prueba y error, y en complicidad con mi compañero miquel lo pudimos hacer lo suficientemente funcional, solo para obtener la matriz 
    transpuesta, el resto es sencillo*/
}
