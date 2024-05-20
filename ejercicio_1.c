#include <stdio.h>
#include <stdlib.h>

void sumar(int *a, int *b, int *resultado) {
    *resultado = *a + *b; 
}

void restar(int *a, int *b, int *resultado) {
    *resultado = *a - *b; 
}

void multiplicar(int *a, int *b, int *resultado) {
  *resultado = 0;
  for (int i = 0; i < *b; i++) {
    *resultado += *a;
  }
  if (*b < 0) {
    *resultado = -(*resultado);
  }
}

void dividir(int *a, int *b, int *resultado, int *resto) {
  if (*b == 0) {
    printf("Error: División por cero.\n");
    exit(1);
  }

  *resultado = 0;
  *resto = abs(*a);
  int sign = ((*a < 0) ^ (*b < 0)) ? -1 : 1;

  while (*resto >= abs(*b)) {
    *resto -= abs(*b);
    (*resultado)++;
  }

  *resultado *= sign;
  if (*a < 0 && *resto != 0) {
    *resto = abs(*b) - *resto;
  }
}

int main() {
  int a ,b, resultado, resto;
  printf("Valor de a: ");
  scanf("%d", &a);
  printf("Valor de b: ");
  scanf("%d", &b);

  sumar(&a, &b, &resultado);
  printf("Suma: %d + %d = %d\n", a, b, resultado);

  restar(&a, &b, &resultado);
  printf("Resta: %d - %d = %d\n", a, b, resultado);

  multiplicar(&a, &b, &resultado);
  printf("Multiplicación: %d * %d = %d\n", a, b, resultado);

  dividir(&a, &b, &resultado, &resto);
  printf("División: %d / %d = %d, Resto = %d\n", a, b, resultado, resto);

  return 0;
}