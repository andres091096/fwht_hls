#include <hls_stream.h>

#define FEATURES 256
#define kComputeTiles 4
#define STREAM_DEPTH FEATURES/kComputeTiles
#define BUFFER_LENGTH FEATURES/(kComputeTiles*2) //2^(MAX_K-1) 2^(3-1)
constexpr int ComputeTilesExpr = kComputeTiles;
#pragma once

extern "C" {
void krnl_fwht(float *In, float *Ou);
}