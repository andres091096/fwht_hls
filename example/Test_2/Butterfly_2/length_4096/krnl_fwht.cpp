
#include <krnl_fwht.h>
#include <hls_stream.h>
#include <connection.h>
#include <compute.h>

extern "C" {
void krnl_fwht(float *In_FWHT, float *Out_FWHT){
#pragma HLS INTERFACE m_axi port=In_FWHT   offset=slave bundle=gmem0
#pragma HLS INTERFACE m_axi port=Out_FWHT   offset=slave bundle=gmem0

#pragma HLS INTERFACE s_axilite port=In_FWHT   bundle=control
#pragma HLS INTERFACE s_axilite port=Out_FWHT   bundle=control
#pragma HLS INTERFACE s_axilite port=return bundle=control
#pragma HLS dataflow

    hls::stream<float, 1> read_stream;
    hls::stream<float, 1> out_stream_0[kComputeTiles];

    hls::stream<float, 1> pipe0[kComputeTiles];
    hls::stream<float, 1> pipe5[kComputeTiles];
    hls::stream<float, 1> pipe6[kComputeTiles];
    hls::stream<float, 1> pipe7[kComputeTiles];
    hls::stream<float, 1> pipe8[kComputeTiles];
    hls::stream<float, 1> pipe9[kComputeTiles];
    hls::stream<float, 1> pipe10[kComputeTiles];
    hls::stream<float, 1> pipe11[kComputeTiles];
    hls::stream<float, 1> pipe12[kComputeTiles];
    hls::stream<float, 1> pipe13[kComputeTiles];
    hls::stream<float, 1> pipe14[kComputeTiles];
    hls::stream<float, 1> pipe15[kComputeTiles];
    hls::stream<float, 1> pipe16[kComputeTiles];

    float prev_buffer_1_1[FEATURES/2];
    float prev_buffer_1_2[FEATURES/2];
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_1_1 block factor=2 dim=1
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_1_2 block factor=2 dim=1
    float prev_buffer_2_1[FEATURES/4];
    float prev_buffer_2_2[FEATURES/4];
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_2_1 block factor=2 dim=1
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_2_2 block factor=2 dim=1
    float prev_buffer_3_1[FEATURES/8];
    float prev_buffer_3_2[FEATURES/8];
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_3_1 block factor=2 dim=1
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_3_2 block factor=2 dim=1
    float prev_buffer_4_1[FEATURES/16];
    float prev_buffer_4_2[FEATURES/16];
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_4_1 block factor=2 dim=1
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_4_2 block factor=2 dim=1
    float prev_buffer_5_1[FEATURES/32];
    float prev_buffer_5_2[FEATURES/32];
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_5_1 block factor=2 dim=1
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_5_2 block factor=2 dim=1
    float prev_buffer_6_1[FEATURES/64];
    float prev_buffer_6_2[FEATURES/64];
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_6_1 block factor=2 dim=1
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_6_2 block factor=2 dim=1
    float prev_buffer_7_1[FEATURES/128];
    float prev_buffer_7_2[FEATURES/128];
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_7_1 block factor=2 dim=1
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_7_2 block factor=2 dim=1
    float prev_buffer_8_1[FEATURES/256];
    float prev_buffer_8_2[FEATURES/256];
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_8_1 block factor=2 dim=1
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_8_2 block factor=2 dim=1
    float prev_buffer_9_1[FEATURES/512];
    float prev_buffer_9_2[FEATURES/512];
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_9_1 block factor=2 dim=1
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_9_2 block factor=2 dim=1
    float prev_buffer_10_1[FEATURES/1024];
    float prev_buffer_10_2[FEATURES/1024];
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_10_1 block factor=2 dim=1
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_10_2 block factor=2 dim=1

    int index;
    int SIZE_R_BLOCK;
    int k_1;
    int phi_value;
    int FIFO_SIZE;

    #pragma HLS dataflow

    //READ DATA AND PASS THEM TO "K" STREAMS
    read_data(read_stream, In_FWHT);
    decimator(read_stream, pipe0);
    //START URBU BLOCKS
    //U(11)BU^-1(11)
    FIFO_SIZE    = 1024; // = 2^(U_k-1)
    for (unsigned pe = 0; pe < kComputeTiles; pe++)
    {
        #pragma HLS UNROLL
        Butterfly0_V2(pipe0[pe],pipe5[pe],FIFO_SIZE,pe*FIFO_SIZE,prev_buffer_1_1,prev_buffer_1_2);
    }
    //U(10)BU^-1(10)
    FIFO_SIZE    = 512; // = 2^(U_k-1)
    for (unsigned pe = 0; pe < kComputeTiles; pe++)
    {
        #pragma HLS UNROLL
        Butterfly0_V2(pipe5[pe],pipe6[pe],FIFO_SIZE,pe*FIFO_SIZE,prev_buffer_2_1,prev_buffer_2_2);
    }
    //U(9)BU^-1(9)
    FIFO_SIZE    = 256; // = 2^(U_k-1)
    for (unsigned pe = 0; pe < kComputeTiles; pe++)
    {
        #pragma HLS UNROLL
        Butterfly0_V2(pipe6[pe],pipe7[pe],FIFO_SIZE,pe*FIFO_SIZE,prev_buffer_3_1,prev_buffer_3_2);
    }
    //U(8)BU^-1(8)
    FIFO_SIZE    = 128; // = 2^(U_k-1)
    for (unsigned pe = 0; pe < kComputeTiles; pe++)
    {
        #pragma HLS UNROLL
        Butterfly0_V2(pipe7[pe],pipe8[pe],FIFO_SIZE,pe*FIFO_SIZE,prev_buffer_4_1,prev_buffer_4_2);
    }
    //U(7)BU^-1(7)
    FIFO_SIZE    = 64; // = 2^(U_k-1)
    for (unsigned pe = 0; pe < kComputeTiles; pe++)
    {
        #pragma HLS UNROLL
        Butterfly0_V2(pipe8[pe],pipe9[pe],FIFO_SIZE,pe*FIFO_SIZE,prev_buffer_5_1,prev_buffer_5_2);
    }
    //U(6)BU^-1(6)
    FIFO_SIZE    = 32; // = 2^(U_k-1)
    for (unsigned pe = 0; pe < kComputeTiles; pe++)
    {
        #pragma HLS UNROLL
        Butterfly0_V2(pipe9[pe],pipe10[pe],FIFO_SIZE,pe*FIFO_SIZE,prev_buffer_6_1,prev_buffer_6_2);
    }
    //U(5)BU^-1(5)
    FIFO_SIZE    = 16; // = 2^(U_k-1)
    for (unsigned pe = 0; pe < kComputeTiles; pe++)
    {
        #pragma HLS UNROLL
        Butterfly0_V2(pipe10[pe],pipe11[pe],FIFO_SIZE,pe*FIFO_SIZE,prev_buffer_7_1,prev_buffer_7_2);
    }
    //U(4)BU^-1(4)
    FIFO_SIZE    = 8; // = 2^(U_k-1)
    for (unsigned pe = 0; pe < kComputeTiles; pe++)
    {
        #pragma HLS UNROLL
        Butterfly0_V2(pipe11[pe],pipe12[pe],FIFO_SIZE,pe*FIFO_SIZE,prev_buffer_8_1,prev_buffer_8_2);
    }
    //U(3)BU^-1(3)
    FIFO_SIZE    = 4; // = 2^(U_k-1)
    for (unsigned pe = 0; pe < kComputeTiles; pe++)
    {
        #pragma HLS UNROLL
        Butterfly0_V2(pipe12[pe],pipe13[pe],FIFO_SIZE,pe*FIFO_SIZE,prev_buffer_9_1,prev_buffer_9_2);
    }
    //U(2)BU^-1(2)
    FIFO_SIZE    = 2; // = 2^(U_k-1)
    for (unsigned pe = 0; pe < kComputeTiles; pe++)
    {
        #pragma HLS UNROLL
        Butterfly0_V2(pipe13[pe],pipe14[pe],FIFO_SIZE,pe*FIFO_SIZE,prev_buffer_10_1,prev_buffer_10_2);
    }
    //U(1)BU^-1(1)
    last_UBRU_V2(pipe14, pipe15);

    
    // phi(1,0)
    phi<1,1>(pipe15,pipe16);
    
    /////////////////////////// URBU(k,j) 
    //U(1)BR(1)U^-1(1)
    last_URBU_V2(pipe16, out_stream_0);

    write_data(out_stream_0, Out_FWHT);


    //#ifndef __SYNTHESIS__
    //printf("Checkpoint 1 reached\n");
    //#endif
    
}
}