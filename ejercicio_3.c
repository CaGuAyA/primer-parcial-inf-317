#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void multiplicar(int a, int b, int *resultado) {
    *resultado = 0;
    int abs_b = abs(b);

    #pragma omp parallel for reduction(+:*resultado)
    for (int i = 0; i < abs_b; i++) {
        *resultado += a;
    }
    if (b < 0) {
        *resultado = -(*resultado);
    }
}

void dividir(int a, int b, int *resultado, int *resto) {
    if (b == 0) {
        printf("Error: División por cero.\n");
        exit(1);
    }

    *resultado = 0;
    *resto = abs(a);
    int sign = ((a < 0) ^ (b < 0)) ? -1 : 1;
    int abs_b = abs(b);

    #pragma omp parallel
    {
        int local_result = 0;
        int local_resto = *resto;

        while (local_resto >= abs_b) {
            #pragma omp critical
            {
                if (local_resto >= abs_b) {
                    local_resto -= abs_b;
                    local_result++;
                }
            }
        }

        #pragma omp atomic
        *resultado += local_result;

        #pragma omp single
        *resto = local_resto;
    }

    *resultado *= sign;
    if (a < 0 && *resto != 0) {
        *resto = abs_b - *resto;
    }
}

int main() {
    int a, b, resultado, resto;
    printf("Valor de a: ");
    scanf("%d", &a);
    printf("Valor de b: ");
    scanf("%d", &b);

    multiplicar(a, b, &resultado);
    printf("Multiplicacion: %d * %d = %d\n", a, b, resultado);

    dividir(a, b, &resultado, &resto);
    printf("Division: %d / %d = %d, Resto = %d\n", a, b, resultado, resto);

    return 0;
}