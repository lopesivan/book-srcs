/* Testando o comportaemnto de ponto-flutuante.

   Compilar com:

     gcc -O0 -o proprieties proprieties.c
*/
#include <stdio.h>

#define SHOW_RESULT(c) \
  printf("[%s]\n", ((c))?"yes":"NO!")

/* Falha ao subtrair 3 vezes o valor 0.4 de 1.2, por exemplo */
void testfp1(double x, double a)
{
  printf("x = %.2f - %.2f - %.2f - %.2f; x = 0.0? ", x, a, a, a);

  x -= a;
  x -= a;
  x -= a;

  /* Neste ponto x deveria ser 0.0, certo? ERRADO! */
  SHOW_RESULT(x == 0.0);
}

void testfp2(double a, double b, double c)
{
  double x;
  double y;

  printf("x = (%.2f + %.2f) + %.2f; y = %.2f + (%.2f + %.2f); x == y ? ", a, b, c, a, b, c);

  /* Associatividade para adição (e subtração) falha */
  x = (a + b) + c;
  y = a + (b + c);

  /* Neste ponto x deveria ser igual a y, certo? ERRADO! */
  SHOW_RESULT(x == y);
}

void testfp3(double a, double b, double c)
{
  double x;
  double y;

  printf("x = (%.2f * %.2f) * %.2f; y = %.2f * (%.2f * %.2f); x == y? ", a, b, c, a, b, c);

  /* Associatividade para multiplicação tb falha */
  x = (a * b) * c;
  y = a * (b * c);

  /* Neste ponto x deveria ser igual a y, certo? ERRADO! */ 
  SHOW_RESULT(x == y);
}

void testfp4(double a, double b, double c)
{
  double x;
  double y;

  printf("x = (%.2f + %.2f) * %.2f; y = (%.2f * %.2f) + (%.2f * %.2f); x == y? ", a, b, c, a, b, c);

  /* Distribuição também falha. */
  x = (a + b) * c;
  y = (a * c) + (b * c);

  /* Neste ponto x deveria ser igual a y, certo? ERRADO! */
  SHOW_RESULT(x == y);
}

void main(void)
{
  testfp1(1.2, 0.4);
  testfp2(0.1, 0.2, 0.3);
  testfp3(0.1, 0.2, 0.3);
  testfp4(0.1, 0.2, 0.3);
}
