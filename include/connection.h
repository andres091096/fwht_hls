#include <hls_stream.h>
#include <krnl_fwht.h>

template <int T, int L>
void phi(hls::stream<float> input_stream[], hls::stream<float> out_stream[]){
    int index;
    #pragma HLS dataflow
    for (int i = 0; i < FEATURES/(T*kComputeTiles); i++)
    {
        for (int j = 0; j < T; j++)
        {
            if (i%2){
                index = 0;
                for (int k = 0; k < kComputeTiles/L; k++)
                {
                    #pragma HLS UNROLL
                    for (int k0 = 0; k0 < L; k0++)
                    {
                        if (k%2){
                            const float temp = input_stream[index].read();
                            out_stream[index-L].write(temp);
                        }
                        else{
                            const float temp = input_stream[index].read();
                            out_stream[index+L].write(temp);
                        }
                        index++;
                    }
                }
            }
            else{
                for (int k = 0; k < kComputeTiles; k++)
                {
                    #pragma HLS UNROLL
                    const float temp = input_stream[k].read();
                    out_stream[k].write(temp);
                }
            }
        }
    }
}

void write_data(hls::stream<float> out_stream[], float *Out_FWHT);
void read_data(hls::stream<float> &read_stream, float *In_FWHT);
void decimator(hls::stream<float> &input_strem, hls::stream<float> parallell_stream[]);