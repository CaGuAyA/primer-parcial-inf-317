#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void generarSerie(int *vector, int inicio, int fin) {
    for (int i = inicio; i < fin; i++) {
        vector[i] = (i + 1) * 2;
    }
}

int main() {
    int N, M;
    printf("Ingrese el número de términos (N): ");
    scanf("%d", &N);
    printf("Ingrese el número de procesadores (M): ");
    scanf("%d", &M);

    int *serie = (int *)malloc(N * sizeof(int));

    int terms_per_thread = N / M;
    int remaining_terms = N % M;

    #pragma omp parallel num_threads(M)
    {
        int id = omp_get_thread_num();
        int start = id * terms_per_thread;
        int end = start + terms_per_thread;
        if (id == M - 1) {
            end += remaining_terms; // El último hilo toma los términos restantes
        }
        generarSerie(serie, start, end);
    }

    // Imprimir la serie generada
    printf("Serie generada:\n");
    for (int i = 0; i < N; i++) {
        printf("%d ", serie[i]);
    }
    printf("\n");

    free(serie);
    return 0;
}