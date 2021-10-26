#define FEATURES 256
#define kComputeTiles 2
#define STREAM_DEPTH FEATURES/kComputeTiles
#define BUFFER_LENGTH FEATURES/(kComputeTiles*2) //2^(MAX_K-1) 2^(3-1)
constexpr int ComputeTilesExpr = 2;
#pragma once

extern "C" {
void krnl_fwht(float *In, float *Ou);
}