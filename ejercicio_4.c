#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void multiplicarMatrizVector(int **matriz, int *vector, int *resultado, int N) {
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        int suma = 0;
        for (int j = 0; j < N; j++) {
            suma += vector[j] * matriz[j][i];
        }
        resultado[i] = suma;
    }
}

int main() {
    // Valores predefinidos

    /*
    int N = 4;
    int **matriz;
    int *vector;
    int *resultado;

    // Reservar memoria para la matriz, el vector y el resultado
    matriz = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++) {
        matriz[i] = (int *)malloc(N * sizeof(int));
    }
    vector = (int *)malloc(N * sizeof(int));
    resultado = (int *)malloc(N * sizeof(int));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matriz[i][j] = i + j;
        }
        vector[i] = i;
        resultado[i] = 0;  // Inicializar el resultado en 0
    }
    */

    // Para leer los valores
    int N, **matriz, *vector, *resultado;

    printf("Escriba el tamanio de N: ");
    scanf("%d", &N);

    // Reservamos memoria
    matriz = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++) {
        matriz[i] = (int *)malloc(N * sizeof(int));
    }
    vector = (int *)malloc(N * sizeof(int));
    resultado = (int *)malloc(N * sizeof(int));

    printf("\tLectura de Matriz:\n");
    for (int i = 0; i < N; i++) {
        printf("Lectura de la fila %d\n", i+1);
        for (int j = 0; j < N; j++) {
            printf("Posicion [%d, %d]: ", i+1, j+1);
            scanf("%d", &matriz[i][j]);
        }
        vector[i] = i;
        resultado[i] = 0;
    }

    printf("\n\tLectura de vector\n");
    for (int i=0; i<N; i++) {
        printf("Posicion [%d]: ", i+1);
        scanf("%d", &vector[i]);
    }

    multiplicarMatrizVector(matriz, vector, resultado, N);

    printf("\n\tResultado:\n");
    for (int i = 0; i < N; i++) {
        printf("Posicion [%d]: %d\n", i, resultado[i]);
    }

    for (int i = 0; i < N; i++) {
        free(matriz[i]);
    }

    free(matriz);
    free(vector);
    free(resultado);

    return 0;
}