#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define MASTER 0

void calcular_fibonacci(int rank, int n) {
    int a = 0, b = 1, sig, i;
    
    if (n == 0) {
        sig = a;
    } else if (n == 1) {
        sig = b;
    } else {
        for (i = 2; i <= n; ++i) {
            sig = a + b;
            a = b;
            b = sig;
        }
    }
    MPI_Send(&sig, 1, MPI_INT, MASTER, 0, MPI_COMM_WORLD);
}

int main(int argc, char *argv[]) {
    int rank, size, n, term;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == MASTER) {
        printf("Ingrese el número de términos de Fibonacci (n): ");
        scanf("%d", &n);

        int *serie_fibonacci = (int *)malloc(n * sizeof(int));

        for (int i = 0; i < n; ++i) {
            int slave = (i % (size - 1)) + 1;
            MPI_Send(&i, 1, MPI_INT, slave, 0, MPI_COMM_WORLD);
            MPI_Recv(&term, 1, MPI_INT, slave, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            serie_fibonacci[i] = term;
        }

        printf("Serie de Fibonacci hasta el término %d:\n", n);
        for (int i = 0; i < n; ++i) {
            printf("%d ", serie_fibonacci[i]);
        }
        printf("\n");

        free(serie_fibonacci);
    } else {
        while (1) {
            MPI_Recv(&term, 1, MPI_INT, MASTER, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            if (term < 0) break;
            calcular_fibonacci(rank, term);
        }
    }

    MPI_Finalize();
    return 0;
}
