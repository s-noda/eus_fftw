#include <stdio.h>
#include <complex.h>
#include <fftw3.h>

extern "C" {
int fft_forward(double* in, double* out, int N) {
  fftw_plan plan;
  fftw_complex* cout = (fftw_complex*)out;
  plan = fftw_plan_dft_r2c_1d( N, in, cout, FFTW_ESTIMATE );
  fftw_execute(plan);
  return N;
}
}

extern "C" {
int fft_backward(double* in, double* out, int N) {
  fftw_plan plan;
  fftw_complex* cout = (fftw_complex*)out;
  plan = fftw_plan_dft_c2r_1d( N, cout, in, FFTW_ESTIMATE );
  fftw_execute(plan);
  return N;
}
}
