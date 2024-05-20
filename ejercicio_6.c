#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

double random_double() {
    return (double)rand() / RAND_MAX;
}

int main(int argc, char *argv[]) {
    int rank, tamaño, i;
    long long int numero_puntos_por_procesar, total_puntos_en_circulo, puntos_globales_en_el_circulo;
    double x, y;
    double pi_estimado;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &tamaño);

    if (argc != 2) {
        if (rank == 0) {
            printf("Usando: %s <numero_de_puntos>\n", argv[0]);
        }
        MPI_Finalize();
        exit(0);
    }

    long long int num_points = atoll(argv[1]);
    numero_puntos_por_procesar = num_points / tamaño;

    // Seed the random number generator uniquely for each process
    srand(time(NULL) + rank);

    total_puntos_en_circulo = 0;

    for (i = 0; i < numero_puntos_por_procesar; i++) {
        x = random_double();
        y = random_double();
        if (x * x + y * y <= 1.0) {
            total_puntos_en_circulo++;
        }
    }

    // Reduce all partial counts to get the global count
    MPI_Reduce(&total_puntos_en_circulo, &puntos_globales_en_el_circulo, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        pi_estimado = (4.0 * puntos_globales_en_el_circulo) / num_points;
        printf("Valor estimado de PI: %f\n", pi_estimado);
    }

    MPI_Finalize();
    return 0;
}   