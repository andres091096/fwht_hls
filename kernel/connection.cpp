#include <connection.h>
#include <krnl_fwht.h>


void write_data(hls::stream<float> out_stream[], float *Out_FWHT)
{
    int index = 0;
    for (int k = 0; k < FEATURES/(kComputeTiles*kComputeTiles); k++)
    {
        for (int j = 0; j < kComputeTiles; j++)
        {
            for (int i = 0; i < kComputeTiles; i++)
            {
                Out_FWHT[index] = out_stream[j].read();
                index++;
            }
        }
    }
}

void read_data(hls::stream<float> &read_stream, float *In_FWHT)
{   
    for (int i = 0; i < FEATURES; i++)
    {
        read_stream.write(In_FWHT[i]);
    }
}

void decimator(hls::stream<float> &input_strem, hls::stream<float> parallell_stream[]){
    
    for (int i = 0; i < FEATURES/kComputeTiles; i++)
    {
        #pragma HLS PIPELINE II=1
        for (int k = 0; k < kComputeTiles; k++)
        {
            #pragma HLS UNROLL
            parallell_stream[k].write(input_strem.read());
        }
    }
}