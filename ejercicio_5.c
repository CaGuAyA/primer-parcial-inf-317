#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void leerMatrizVector(int **matriz, int *vector, int N) {
    printf("Ingrese la matriz %dx%d:\n", N, N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &(*matriz)[i * N + j]);
        }
    }

    printf("Ingrese el vector de dimension %d:\n", N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &vector[i]);
    }
}

void imprimirResultado(int *resultado, int N) {
    printf("Resultado:\n");
    for (int i = 0; i < N; i++) {
        printf("%d\n", resultado[i]);
    }
}

int main(int argc, char *argv[]) {
    int rank, size;
    int N;
    int *matriz = NULL;
    int *vector = NULL;
    int *resultado = NULL;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        printf("Ingrese la dimension N: ");
        scanf("%d", &N);

        matriz = (int *)malloc(N * N * sizeof(int));
        vector = (int *)malloc(N * sizeof(int));
        resultado = (int *)malloc(N * sizeof(int));

        leerMatrizVector(&matriz, vector, N);
    }

    // Broadcast the size N to all processes
    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank != 0) {
        vector = (int *)malloc(N * sizeof(int));
    }

    // Broadcast the vector to all processes
    MPI_Bcast(vector, N, MPI_INT, 0, MPI_COMM_WORLD);

    int rows_per_process = N / size;
    int remaining_rows = N % size;

    int *local_matriz = (int *)malloc(rows_per_process * N * sizeof(int));
    int *local_resultado = (int *)malloc(rows_per_process * sizeof(int));

    // Scatter the rows of the matrix to all processes
    MPI_Scatter(matriz, rows_per_process * N, MPI_INT, local_matriz, rows_per_process * N, MPI_INT, 0, MPI_COMM_WORLD);

    // Handle remaining rows in process 0
    if (rank == 0 && remaining_rows > 0) {
        for (int i = size * rows_per_process; i < N; i++) {
            for (int j = 0; j < N; j++) {
                resultado[i] += matriz[i * N + j] * vector[j];
            }
        }
    }

    // Each process computes its part of the result
    for (int i = 0; i < rows_per_process; i++) {
        local_resultado[i] = 0;
        for (int j = 0; j < N; j++) {
            local_resultado[i] += local_matriz[i * N + j] * vector[j];
        }
    }

    // Gather the results from all processes
    MPI_Gather(local_resultado, rows_per_process, MPI_INT, resultado, rows_per_process, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        imprimirResultado(resultado, N);
    }

    // Liberar memoria
    if (matriz) free(matriz);
    if (vector) free(vector);
    if (resultado) free(resultado);
    free(local_matriz);
    free(local_resultado);

    MPI_Finalize();
    return 0;
}



