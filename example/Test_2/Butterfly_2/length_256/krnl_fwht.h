#define FEATURES 256 // n = 8 
#define kComputeTiles 2
#define STREAM_DEPTH FEATURES/kComputeTiles
#define BUFFER_LENGTH kComputeTiles/2 //2^(MAX_K-1) 2^(4-1)
#pragma once

extern "C" {
void krnl_fwht(float *In, float *Ou);
}