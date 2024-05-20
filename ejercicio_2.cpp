#include <cstdlib>
#include <iostream>
using namespace std;

void sumar(int *a, int *b, int *resultado) {
  *resultado = *a + *b;
}

void restar(int *a, int *b, int *resultado) {
  *resultado = *a - *b;
}

void multiplicar(int *a, int *b, int *resultado) {
  *resultado = 0;
  for (int i = 0; i < abs(*b); i++) {
    *resultado += *a;
  }
  if (*b < 0) {
    *resultado = -(*resultado);
  }
}

void dividir(int *a, int *b, int *resultado, int *resto) {
  if (*b == 0) {
    cerr << "Error: División por cero." << std::endl;
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
  int a , b, resultado, resto;

  cout << "Valor de a: ";
  cin >> a;
  cout << "Valor de b: ";
  cin >> b;

  sumar(&a, &b, &resultado);
  cout << "Suma: " << a << " + " << b << " = " << resultado << endl;

  restar(&a, &b, &resultado);
  cout << "Resta: " << a << " - " << b << " = " << resultado << endl;

  multiplicar(&a, &b, &resultado);
  cout << "Multiplicación: " << a << " * " << b << " = " << resultado << endl;

  dividir(&a, &b, &resultado, &resto);
  cout << "División: " << a << " / " << b << " = " << resultado
       << ", Resto = " << resto << endl;

  return 0;
}
