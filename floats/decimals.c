/* Testando o comportaemnto de _Decimal64.

   Compilar com:

     gcc -O0 -o decimals decimals.c

  OBS: Infelizmente printf() não suporta os tipos _Decimal32 e _Decimal64.
       Existe uma extensão da eglibc chamada libdfp, mas é preciso recompilar a libc
       manualmente.
*/
#include <stdio.h>

#define SHOW_RESULT(c) \
  printf("[%s]\n", ((c))?"yes":"NO!")

/* Falha ao subtrair 3 vezes o valor 0.4 de 1.2, por exemplo */
void testfp1(_Decimal64 x, _Decimal64 a)
{
  printf("Subtraindo 3 vezes 0.4 de 1.2... ");

  x -= a;
  x -= a;
  x -= a;

  /* Neste ponto x deveria ser 0.0, certo? ERRADO! */
  /* o sufixo 'dd' no valor literal significa _Decimal64. */
  SHOW_RESULT(x == 0.0dd);
}

void testfp2(_Decimal64 a, _Decimal64 b, _Decimal64 c)
{
  _Decimal64 x;
  _Decimal64 y;

  printf("Associatividade com adição... ");

  /* Associatividade para adição (e subtração) falha */
  x = (a + b) + c;
  y = a + (b + c);

  /* Neste ponto x deveria ser igual a y, certo? ERRADO! */
  SHOW_RESULT(x == y);
}

void testfp3(_Decimal64 a, _Decimal64 b, _Decimal64 c)
{
  _Decimal64 x;
  _Decimal64 y;

  printf("Associatividade com multiplicação... ");

  /* Associatividade para multiplicação tb falha */
  x = (a * b) * c;
  y = a * (b * c);

  /* Neste ponto x deveria ser igual a y, certo? ERRADO! */ 
  SHOW_RESULT(x == y);
}

void testfp4(_Decimal64 a, _Decimal64 b, _Decimal64 c)
{
  _Decimal64 x;
  _Decimal64 y;

  printf("Distribuição... ");

  /* Distribuição também falha. */
  x = (a + b) * c;
  y = (a * c) + (b * c);

  /* Neste ponto x deveria ser igual a y, certo? ERRADO! */
  SHOW_RESULT(x == y);
}

void main(void)
{
  testfp1(1.2dd, 0.4dd);
  testfp2(0.1dd, 0.2dd, 0.3dd);
  testfp3(0.1dd, 0.2dd, 0.3dd);
  testfp4(0.1dd, 0.2dd, 0.3dd);
}
