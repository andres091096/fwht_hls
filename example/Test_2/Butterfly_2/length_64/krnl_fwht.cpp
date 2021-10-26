#include <krnl_fwht.h>
#include <hls_stream.h>
#include <compute.h>
#include <connection.h>

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
    hls::stream<float, 1> pipe1[kComputeTiles];
    hls::stream<float, 1> pipe2[kComputeTiles];
    hls::stream<float, 1> pipe3[kComputeTiles];
    hls::stream<float, 1> pipe4[kComputeTiles];
    hls::stream<float, 1> pipe5[kComputeTiles];
    hls::stream<float, 1> pipe6[kComputeTiles];

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

    int index;
    int SIZE_R_BLOCK;
    int k_1;
    int phi_value;
    int FIFO_SIZE;

    #pragma HLS dataflow

    //READ DATA AND PASS THEM TO "K" STREAMS
    read_data(read_stream, In_FWHT);
    decimator(read_stream, pipe0);
    //U(5)BU^-1(5)
    FIFO_SIZE    = 16; // = 2^(U_k-1)
    for (unsigned pe = 0; pe < kComputeTiles; pe++)
    {
        #pragma HLS UNROLL
        Butterfly0_V2(pipe0[pe],pipe1[pe],FIFO_SIZE,pe*FIFO_SIZE,prev_buffer_1_1,prev_buffer_1_2);
    }
    //U(4)BU^-1(4)
    FIFO_SIZE    = 8; // = 2^(U_k-1)
    for (unsigned pe = 0; pe < kComputeTiles; pe++)
    {
        #pragma HLS UNROLL
        Butterfly0_V2(pipe1[pe],pipe2[pe],FIFO_SIZE,pe*FIFO_SIZE,prev_buffer_2_1,prev_buffer_2_2);
    }
    //U(3)BU^-1(3)
    FIFO_SIZE    = 4; // = 2^(U_k-1)
    for (unsigned pe = 0; pe < kComputeTiles; pe++)
    {
        #pragma HLS UNROLL
        Butterfly0_V2(pipe2[pe],pipe3[pe],FIFO_SIZE,pe*FIFO_SIZE,prev_buffer_3_1,prev_buffer_3_2);
    }
    //U(2)BU^-1(2)
    FIFO_SIZE    = 2; // = 2^(U_k-1)
    for (unsigned pe = 0; pe < kComputeTiles; pe++)
    {
        #pragma HLS UNROLL
        Butterfly0_V2(pipe3[pe],pipe4[pe],FIFO_SIZE,pe*FIFO_SIZE,prev_buffer_4_1,prev_buffer_4_2);
    }
    //U(1)BU^-1(1)
    last_UBRU_V2(pipe4, pipe5);

    
    // phi(1,0)
    phi<1,1>(pipe5,pipe6);
    
    /////////////////////////// URBU(k,j) 
    //U(1)BR(1)U^-1(1)
    last_URBU_V2(pipe6, out_stream_0);

    write_data(out_stream_0, Out_FWHT);


    //#ifndef __SYNTHESIS__
    //printf("Checkpoint 1 reached\n");
    //#endif
    
}
}