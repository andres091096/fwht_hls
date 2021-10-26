#include <krnl_fwht.h>
#include <hls_stream.h>
#include <compute.h>
#include <connection.h>

extern "C" {


void write_dataflow(hls::stream<float>& write_stream, float *out){
    for (int i = 0; i < FEATURES; i++)
    {   
        #pragma HLS PIPELINE II=1
        out[i] = write_stream.read();
    }
}

void krnl_fwht(float *In_FWHT, float *Out_FWHT){
#pragma HLS INTERFACE m_axi port=In_FWHT   offset=slave bundle=gmem0
#pragma HLS INTERFACE m_axi port=Out_FWHT   offset=slave bundle=gmem0

#pragma HLS INTERFACE s_axilite port=In_FWHT   bundle=control
#pragma HLS INTERFACE s_axilite port=Out_FWHT   bundle=control
#pragma HLS INTERFACE s_axilite port=return bundle=control

    hls::stream<float> read_stream("input_stream");
    hls::stream<float> out_stream_0;
    hls::stream<float> out_stream_1;
    hls::stream<float> out_stream_2;
    hls::stream<float> out_stream_3;
    hls::stream<float> out_stream_4;
    hls::stream<float> out_stream_5;
    hls::stream<float> out_stream_6;
    hls::stream<float> out_stream_7;
    
#pragma HLS STREAM variable = read_stream depth = 4096
#pragma HLS STREAM variable = out_stream_0 depth = 2
#pragma HLS STREAM variable = out_stream_1 depth = 2
#pragma HLS STREAM variable = out_stream_2 depth = 2
#pragma HLS STREAM variable = out_stream_3 depth = 2
#pragma HLS STREAM variable = out_stream_4 depth = 2
#pragma HLS STREAM variable = out_stream_5 depth = 2
#pragma HLS STREAM variable = out_stream_6 depth = 2
#pragma HLS STREAM variable = out_stream_7 depth = 2

    float prev_buffer0[BUFFER_LENGTH];
    float prev_buffer1[BUFFER_LENGTH/2];
    float prev_buffer2[BUFFER_LENGTH/4];
    float prev_buffer3[BUFFER_LENGTH/8];
    float prev_buffer4[BUFFER_LENGTH/16];
    float prev_buffer5[BUFFER_LENGTH/32];
    float prev_buffer6[BUFFER_LENGTH/64];
    float prev_buffer7[BUFFER_LENGTH/128];

#pragma HLS dataflow
#pragma HLS ALLOCATION instances=fadd limit=11 operation
#pragma HLS ALLOCATION instances=fsub limit=11 operation
    //dataflow pragma instruct compiler to run following APIs in parallel
    read_data(read_stream, In_FWHT);

    Butterfly0_V1(read_stream,  out_stream_0, BUFFER_LENGTH,   0, prev_buffer0);
    Butterfly0_V1(out_stream_0, out_stream_1, BUFFER_LENGTH/2, 0, prev_buffer1);
    Butterfly0_V1(out_stream_1, out_stream_2, BUFFER_LENGTH/4, 0, prev_buffer2);
    Butterfly0_V1(out_stream_2, out_stream_3, BUFFER_LENGTH/8, 0, prev_buffer3);
    Butterfly0_V1(out_stream_3, out_stream_4, BUFFER_LENGTH/16,0, prev_buffer4);
    Butterfly0_V1(out_stream_4, out_stream_5, BUFFER_LENGTH/32,0, prev_buffer5);
    Butterfly0_V1(out_stream_5, out_stream_6, BUFFER_LENGTH/64,0, prev_buffer6);
    last_Butterfly0_V1(out_stream_6, out_stream_7);

    write_dataflow(out_stream_7, Out_FWHT);
    
}
}