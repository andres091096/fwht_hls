#define FEATURES 256
#define STREAM_DEPTH 256
#define BUFFER_LENGTH FEATURES/2
#define kComputeTiles 1
#pragma once

extern "C" {
void krnl_fwht(float *In, float *Ou);
}