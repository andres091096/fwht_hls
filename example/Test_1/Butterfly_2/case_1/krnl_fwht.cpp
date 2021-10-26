#include <hls_stream.h>
#include <krnl_fwht.h>
#include <compute.h>
#include <connection.h>

extern "C" {

void krnl_fwht(float *In_FWHT, float *Out_FWHT){
#pragma HLS INTERFACE m_axi port=In_FWHT   offset=slave bundle=gmem0
#pragma HLS INTERFACE m_axi port=Out_FWHT  offset=slave bundle=gmem0

#pragma HLS INTERFACE s_axilite port=In_FWHT   bundle=control
#pragma HLS INTERFACE s_axilite port=Out_FWHT   bundle=control
#pragma HLS INTERFACE s_axilite port=return bundle=control


    hls::stream<float> input_strem;
    #pragma HLS STREAM variable=input_strem depth=1
    hls::stream<float> pipe0[kComputeTiles];
    #pragma HLS STREAM variable=pipe0 depth=1
    hls::stream<float> pipe1[kComputeTiles];
    #pragma HLS STREAM variable=pipe1 depth=1
    hls::stream<float> pipe2[kComputeTiles];
    #pragma HLS STREAM variable=pipe2 depth=1
    hls::stream<float> pipe3[kComputeTiles];
    #pragma HLS STREAM variable=pipe3 depth=1
    hls::stream<float> pipe4[kComputeTiles];
    #pragma HLS STREAM variable=pipe4 depth=1
    hls::stream<float> pipe5[kComputeTiles];
    #pragma HLS STREAM variable=pipe5 depth=1
    hls::stream<float> pipe6[kComputeTiles];
    #pragma HLS STREAM variable=pipe6 depth=1
    hls::stream<float> pipe7[kComputeTiles];
    #pragma HLS STREAM variable=pipe7 depth=1
    hls::stream<float> pipe8[kComputeTiles];
    #pragma HLS STREAM variable=pipe8 depth=1
    hls::stream<float> pipe9[kComputeTiles];
    #pragma HLS STREAM variable=pipe9 depth=1
    hls::stream<float> pipe10[kComputeTiles];
    #pragma HLS STREAM variable=pipe10 depth=1
    hls::stream<float> pipe11[kComputeTiles];
    #pragma HLS STREAM variable=pipe11 depth=1
    hls::stream<float> pipe12[kComputeTiles];
    #pragma HLS STREAM variable=pipe12 depth=1
    hls::stream<float> out_stream_0[kComputeTiles];
    #pragma HLS STREAM variable=out_stream_0 depth=1


    float prev_buffer_1_1[STREAM_DEPTH];
    float prev_buffer_1_2[STREAM_DEPTH];
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_1_1 block factor=2 dim=1
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_1_2 block factor=2 dim=1
    float prev_buffer_2_1[STREAM_DEPTH/2];
    float prev_buffer_2_2[STREAM_DEPTH/2];
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_2_1 block factor=2 dim=1
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_2_2 block factor=2 dim=1
    float prev_buffer_3_1[STREAM_DEPTH/4];
    float prev_buffer_3_2[STREAM_DEPTH/4];
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_3_1 block factor=2 dim=1
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_3_2 block factor=2 dim=1
    float prev_buffer_4_1[STREAM_DEPTH/8];
    float prev_buffer_4_2[STREAM_DEPTH/8];
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_4_1 block factor=2 dim=1
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_4_2 block factor=2 dim=1
    float prev_buffer_5_1[STREAM_DEPTH/16];
    float prev_buffer_5_2[STREAM_DEPTH/16];
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_5_1 block factor=2 dim=1
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_5_2 block factor=2 dim=1
    float prev_buffer_6_1[STREAM_DEPTH/32];
    float prev_buffer_6_2[STREAM_DEPTH/32];
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_6_1 block factor=2 dim=1
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_6_2 block factor=2 dim=1
    float prev_buffer_7_1[STREAM_DEPTH/64];
    float prev_buffer_7_2[STREAM_DEPTH/64];
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_7_1 block factor=2 dim=1
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_7_2 block factor=2 dim=1
    float prev_buffer_8_1[STREAM_DEPTH/128];
    float prev_buffer_8_2[STREAM_DEPTH/128];
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_8_1 block factor=2 dim=1
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_8_2 block factor=2 dim=1
    float prev_buffer_9_1[STREAM_DEPTH/256];
    float prev_buffer_9_2[STREAM_DEPTH/256];
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_9_1 block factor=2 dim=1
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_9_2 block factor=2 dim=1
    float prev_buffer_10_1[STREAM_DEPTH/512];
    float prev_buffer_10_2[STREAM_DEPTH/512];
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_10_1 block factor=2 dim=1
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_10_2 block factor=2 dim=1
    

    #pragma HLS dataflow
    //READ DATA AND PASS THEM TO "K" STREAMS
    read_data(input_strem, In_FWHT);
    decimator(input_strem, pipe0);
    
    //START URBU BLOCKS
    //U(7)BU^-1(7)
    for (unsigned pe = 0; pe < kComputeTiles; pe++)
    {
        #pragma HLS UNROLL
        Butterfly0_V2(pipe0[pe],pipe1[pe],64,pe*64,prev_buffer_1_1, prev_buffer_1_2);
    }
    //U(6)BU^-1(6)
    for (unsigned pe = 0; pe < kComputeTiles; pe++)
    {
        #pragma HLS UNROLL
        Butterfly0_V2(pipe1[pe],pipe2[pe],32,pe*32,prev_buffer_2_1, prev_buffer_2_2);
    }
    //U(5)BU^-1(5)
    for (unsigned pe = 0; pe < kComputeTiles; pe++)
    {
        #pragma HLS UNROLL
        Butterfly0_V2(pipe2[pe],pipe3[pe],16,pe*16,prev_buffer_3_1,prev_buffer_3_2);
    }
    //U(4)BU^-1(4)
    for (unsigned pe = 0; pe < kComputeTiles; pe++)
    {
        #pragma HLS UNROLL
        Butterfly0_V2(pipe3[pe],pipe4[pe],8,pe*8,prev_buffer_4_1,prev_buffer_4_2);
    }
    //U(3)BU^-1(3)
    for (unsigned pe = 0; pe < kComputeTiles; pe++)
    {
        #pragma HLS UNROLL
        Butterfly0_V2(pipe4[pe],pipe5[pe],4,pe*4,prev_buffer_5_1,prev_buffer_5_2);
    }
    //U(2)BU^-1(2)
    for (unsigned pe = 0; pe < kComputeTiles; pe++)
    {
        #pragma HLS UNROLL
        Butterfly0_V2(pipe5[pe],pipe6[pe],2,pe*2,prev_buffer_6_1,prev_buffer_6_2);
    }

    //U(1)BR(1)U^-1(1)
    last_UBRU_V2(pipe6, pipe7);

    /////////////////////////// phi(k,j) 
    // phi(1,0)
    phi<1,1>(pipe7,pipe8);
    
    /////////////////////////// URBU(k,j) 
    //U(1)BR(1)U^-1(1)
    last_URBU_V2(pipe8, out_stream_0);

    write_data(out_stream_0, Out_FWHT);
    
    //#ifndef __SYNTHESIS__
    //printf("Checkpoint 1 reached\n");
    //#endif

}
}