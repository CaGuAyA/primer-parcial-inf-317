#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void generarSerie(int *vector, int inicio, int fin) {
    for (int i = inicio; i < fin; i++) {
        vector[i - inicio] = (i + 1) * 2;
    }
}

int main(int argc, char *argv[]) {
    int rank, size, N;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        // Solo el proceso 0 obtiene el valor de N
        printf("Ingrese el número de términos (N): ");
        scanf("%d", &N);
    }

    // Difundir el valor de N a todos los procesos
    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int terms_per_process = N / size;
    int remaining_terms = N % size;

    int start = rank * terms_per_process;
    int end = start + terms_per_process;
    if (rank == size - 1) {
        end += remaining_terms; // El último proceso toma los términos restantes
    }

    int *local_vector = (int *)malloc((end - start) * sizeof(int));
    generarSerie(local_vector, start, end);

    int *global_vector = NULL;
    if (rank == 0) {
        global_vector = (int *)malloc(N * sizeof(int));
    }

    // Reunir los resultados de todos los procesos en el proceso 0
    int *recvcounts = (int *)malloc(size * sizeof(int));
    int *displs = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        recvcounts[i] = (i < size - 1) ? terms_per_process : terms_per_process + remaining_terms;
        displs[i] = i * terms_per_process;
    }
    MPI_Gatherv(local_vector, end - start, MPI_INT, global_vector, recvcounts, displs, MPI_INT, 0, MPI_COMM_WORLD);

    // Imprimir el resultado
    if (rank == 0) {
        printf("Serie generada:\n");
        for (int i = 0; i < N; i++) {
            printf("%d ", global_vector[i]);
        }
        printf("\n");
        free(global_vector);
    }

    free(local_vector);
    free(recvcounts);
    free(displs);

    MPI_Finalize();
    return 0;
}