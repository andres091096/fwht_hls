#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <random>
#include <iostream>
#include <krnl_fwht.h>
#define FEATURES 262144

using namespace std;

void fwht(float *temp, float *out_fwht)
{
  float x1; float x2;

  int M; int L;
  int stages = log10(FEATURES)/log10(2); // log2(n)
  M = FEATURES; L = FEATURES;

  for (int k = 0; k < stages; k++){ //Stage loop
    M = M/2;
    for (int J = 0; J < FEATURES; J = J + L) {//Loop2: Split the vector in 2^k new sub_arrays
      for (int i = J; i < J + M; i++) { //Inner Loop
        x1 = temp[i];
        x2 = temp[i+M];
        temp[i] = x1 + x2;
        temp[i+M] = x1 - x2;
      }
    }
    L = L/2;
  }

  for (int i = 0; i < FEATURES; i++){
    out_fwht[i] = temp[i];
  }
}

int main(int argc, char const *argv[])
{
  std::random_device rd;
  std::default_random_engine rng;
  std::uniform_real_distribution<float> dist;

  float *a = (float*)calloc(FEATURES,sizeof(float));
  float *b = (float*)calloc(FEATURES,sizeof(float));
  float *b_ref = (float*)calloc(FEATURES,sizeof(float));

  for (int i = 0; i < FEATURES; i++)
  {
    a[i] = dist(rng)/98.56;
  }
  
  // Run simulation
  krnl_fwht(a, b);
  // Run reference
  fwht(a, b_ref);
  float first_value = b_ref[8];

  for (int i = 0; i < FEATURES; ++i) {
    const auto diff = std::abs(b_ref[i] - b[i]);
    if (diff >= 1e-5) {
      std::cout << "Mismatch at (" << i << "): " << b[i]
                << " (should be " << b_ref[i] << ").\n";
      return 1;
    }
    
  }

  std::cout << "Test ran successfully.\n";
  return 0;
}
