#include <stdio.h>
#include <complex.h>
#include <fftw3.h>

int main( void ){
  int N=4, n;

  double *a, *_b;
  fftw_complex *b;
  a = (double*) fftw_malloc(sizeof(double) * N);
  _b = (double*) fftw_malloc(sizeof(double) * N * 2);
  b = (fftw_complex*)_b ;//(fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);

  fftw_plan plan;
  // plan = fftw_plan_dft_r2c_1d( N, a, b, FFTW_FORWARD, FFTW_ESTIMATE );
  plan = fftw_plan_dft_r2c_1d( N, a, b, FFTW_ESTIMATE );

  a[0] = 1.0; a[1] = 2.0; a[2] = 3.0; a[3] = 4.0;

  //
  printf("--- input value\n");
  for( n=0; n<N; n++ ){
    printf("  [%d] %lf\n", n, a[n]);
  }

  fftw_execute(plan);

  //
  printf("--- output value\n");
  for( n=0; n<N; n++ ){
    printf("  [%d] %lf, %lf\n", n, _b[2*n], _b[2*n+1]);
  }

  plan = fftw_plan_dft_c2r_1d( N, b, a, FFTW_ESTIMATE );
  fftw_execute(plan);

  printf("--- retransform value\n");
  for( n=0; n<N; n++ ){
    printf("  [%d] %lf\n", n, a[n]);
  }

  if(plan) fftw_destroy_plan(plan);
  fftw_free(a); fftw_free(b);

  return 0;
}
