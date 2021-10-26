#define FEATURES 16 // n = 4 
#define kComputeTiles 2
#define STREAM_DEPTH FEATURES/kComputeTiles
#define BUFFER_LENGTH kComputeTiles/2 //2^(MAX_K-1)

#pragma once

extern "C" {
void krnl_fwht(float *In, float *Ou);
}