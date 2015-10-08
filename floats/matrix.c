#include <x86intrin.h>

void matrix4x4_mult_scalar1(float *r, const float *a, const float *b)
{
  /* Transpondo a matriz 'a' e multiplicando as linhas das duas... */

  r[0]  = (b[0] * a[0]) + (b[1] * a[4]) + (b[2] * a[8])  + (b[3] * a[12]);
  r[1]  = (b[0] * a[1]) + (b[1] * a[5]) + (b[2] * a[9])  + (b[3] * a[13]);
  r[2]  = (b[0] * a[2]) + (b[1] * a[6]) + (b[2] * a[10]) + (b[3] * a[14]);
  r[3]  = (b[0] * a[3]) + (b[1] * a[7]) + (b[2] * a[11]) + (b[3] * a[15]);

  r[4]  = (b[4] * a[0]) + (b[5] * a[4]) + (b[6] * a[8])  + (b[7] * a[12]);
  r[5]  = (b[4] * a[1]) + (b[5] * a[5]) + (b[6] * a[9])  + (b[7] * a[13]);
  r[6]  = (b[4] * a[2]) + (b[5] * a[6]) + (b[6] * a[10]) + (b[7] * a[14]);
  r[7]  = (b[4] * a[3]) + (b[5] * a[7]) + (b[6] * a[11]) + (b[7] * a[15]);

  r[8]  = (b[8] * a[0]) + (b[9] * a[4]) + (b[10] * a[8])  + (b[11] * a[12]);
  r[9]  = (b[8] * a[1]) + (b[9] * a[5]) + (b[10] * a[9])  + (b[11] * a[13]);
  r[10] = (b[8] * a[2]) + (b[9] * a[6]) + (b[10] * a[10]) + (b[11] * a[14]);
  r[11] = (b[8] * a[3]) + (b[9] * a[7]) + (b[10] * a[11]) + (b[11] * a[15]);

  r[12] = (b[12] * a[0]) + (b[13] * a[4]) + (b[14] * a[8])  + (b[15] * a[12]);
  r[13] = (b[12] * a[1]) + (b[13] * a[5]) + (b[14] * a[9])  + (b[15] * a[13]);
  r[14] = (b[12] * a[2]) + (b[13] * a[6]) + (b[14] * a[10]) + (b[15] * a[14]);
  r[15] = (b[12] * a[3]) + (b[13] * a[7]) + (b[14] * a[11]) + (b[15] * a[15]);
}

void matrix4x4_mult_scalar2(float *r, const float *a, const float *b)
{
  int i, j;

  for (i = 0; i < 16; i += 4)
    for (j = 0; j < 4; j++)
      r[i + j] = (b[i] * a[j]) + 
                 (b[i + 1] *a[j + 4]) + 
                 (b[i + 2] *a[j + 8]) + 
                 (b[i + 3] *a[j + 12]);
}

void matrix4x4_mult_vect(float *r, const float *a, const float *b)
{
  __m128 a_line, b_line, r_line;
  int i, j;

  for (i = 0; i < 16; i += 4) 
  {
    b_line = _mm_load_ps(b);
    a_line = _mm_set1_ps(a[i]);
    r_line = _mm_mul_ps(a_line, b_line);

    for (j = 1; j < 4; j++) 
    {
      b_line = _mm_load_ps(&b[j*4]);
      a_line = _mm_set1_ps(a[i+j]);
      r_line = _mm_add_ps(_mm_mul_ps(a_line, b_line), r_line);
    }

    _mm_store_ps(&r[i], r_line);
  }
}
