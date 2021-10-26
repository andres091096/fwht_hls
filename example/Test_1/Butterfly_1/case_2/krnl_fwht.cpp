#define FEATURES 256
#define kComputeTiles 4
#define STREAM_DEPTH FEATURES/kComputeTiles
#define BUFFER_LENGTH FEATURES/(kComputeTiles*2) //2^(MAX_K-1) 2^(3-1)
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

#pragma HLS dataflow
    int index;
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
    hls::stream<float, 1> pipe10[kComputeTiles];
    hls::stream<float> pipe11[kComputeTiles];
    #pragma HLS STREAM variable=pipe11 depth=1
    hls::stream<float> pipe12[kComputeTiles];
    #pragma HLS STREAM variable=pipe12 depth=1
    hls::stream<float> out_stream_0[kComputeTiles];
    #pragma HLS STREAM variable=out_stream_0 depth=1


    float prev_buffer_1[FEATURES/2];
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_1 block factor=ComputeTilesExpr dim=1
    float prev_buffer_2[FEATURES/4];
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_2 block factor=ComputeTilesExpr dim=1
    float prev_buffer_3[FEATURES/8];
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_3 block factor=ComputeTilesExpr dim=1
    float prev_buffer_4[FEATURES/16];
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_4 block factor=ComputeTilesExpr dim=1
    float prev_buffer_5[FEATURES/32];
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_5 block factor=ComputeTilesExpr dim=1
    float prev_buffer_6[FEATURES/32];
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_6 block factor=ComputeTilesExpr dim=1
   
    
    //READ DATA AND PASS THEM TO "K" STREAMS
    read_data(input_strem, In_FWHT);
    decimator(input_strem, pipe0);
    
    //START URBU BLOCKS
    //U(6)BU^-1(6)
    for (unsigned pe = 0; pe < kComputeTiles; pe++)
    {
        #pragma HLS UNROLL
        Butterfly0_V1(pipe0[pe],pipe1[pe],32,pe*32,prev_buffer_1);
    }
    //U(5)BU^-1(5)
    for (unsigned pe = 0; pe < kComputeTiles; pe++)
    {
        #pragma HLS UNROLL
        Butterfly0_V1(pipe1[pe],pipe2[pe],16,pe*16,prev_buffer_2);
    }
    //U(4)BU^-1(4)
    for (unsigned pe = 0; pe < kComputeTiles; pe++)
    {
        #pragma HLS UNROLL
        Butterfly0_V1(pipe2[pe],pipe3[pe],8,pe*8,prev_buffer_3);
    }
    //U(3)BU^-1(3)
    for (unsigned pe = 0; pe < kComputeTiles; pe++)
    {
        #pragma HLS UNROLL
        Butterfly0_V1(pipe3[pe],pipe4[pe],4,pe*4,prev_buffer_4);
    }
    //U(2)BU^-1(2)
    index = 0;
    for (unsigned pe = 0; pe < kComputeTiles/(2*2); pe++)
    {
        #pragma HLS UNROLL
        for (int BLOCK_R = 0; BLOCK_R < 2; BLOCK_R++)
        {
            #pragma HLS UNROLL
            Butterfly0_V1(pipe4[index],pipe5[index],2,index*2,prev_buffer_5);
            index++;
        }
        for (int BLOCK_R = 0; BLOCK_R < 2; BLOCK_R++)
        {
            #pragma HLS UNROLL
            Butterfly1_V1(pipe4[index],pipe5[index],2,index*2,prev_buffer_5);
            index++;
        }
    }
    

    //U(1)BR(1)U^-1(1)
    last_UBRU_V1(pipe5, pipe6);

    /////////////////////////// phi(k,j) 
    // phi(2,0)
    phi<2,2>(pipe6,pipe7);
    // phi(1,0)
    phi<1,1>(pipe7,pipe8);
    
    /////////////////////////// URBU(k,j) 
    //U(2)BR(2)U^-1(2)
    index = 0;
    for (unsigned pe = 0; pe < kComputeTiles/(2*2); pe++)
    {
        #pragma HLS PIPELINE II=1
        for (int BLOCK_R = 0; BLOCK_R < 2; BLOCK_R++)
        {
            #pragma HLS UNROLL
            Butterfly0_V1(pipe8[index],pipe9[index],2,index*2,prev_buffer_6);
            index++;
        }
        for (int BLOCK_R = 0; BLOCK_R < 2; BLOCK_R++)
        {
            #pragma HLS UNROLL
            Butterfly2_V1(pipe8[index],pipe9[index],2,index*2,prev_buffer_6);
            index++;
        }
    }
    
    //U(1)BR(1)U^-1(1)
    last_URBU_V1(pipe9, out_stream_0);
    write_data(out_stream_0, Out_FWHT);

    //#ifndef __SYNTHESIS__
    //printf("Checkpoint 1 reached\n");
    //#endif

}
}