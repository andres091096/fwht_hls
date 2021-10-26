#include <krnl_fwht.h>
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

    hls::stream<float> read_stream;
    #pragma HLS STREAM variable=read_stream depth=1
    hls::stream<float> out_stream_0[kComputeTiles];
    #pragma HLS STREAM variable=out_stream_0 depth=1

    int index;
    int SIZE_R_BLOCK;
    int k_1;
    int FIFO_SIZE;
    int offset; //buffer offset

    //DELTA 
    read_data(read_stream, In_FWHT);

    hls::stream<float> pipe0[kComputeTiles];
    #pragma HLS STREAM variable=pipe0 depth=1
    decimator(read_stream, pipe0);
    
    //START URBU BLOCKS
    //U(5)BU^-1(5)
    offset = 16;
    hls::stream<float> pipe1[kComputeTiles];
    #pragma HLS STREAM variable=pipe1 depth=1
    float prev_buffer_1[FEATURES/2];
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_1 block factor = kComputeTiles dim=1
    for (unsigned pe = 0; pe < kComputeTiles; pe++)
    {
        #pragma HLS UNROLL
        Butterfly0_V1(pipe0[pe],pipe1[pe],offset,pe*offset,prev_buffer_1);
        //ProcessingElement(pipe0[pe],pipe1[pe],offset);
    }
   
    //U(4)BU^-1(4)
    offset = 8;
    hls::stream<float> pipe2[kComputeTiles];
    #pragma HLS STREAM variable=pipe2 depth=1
    float prev_buffer_2[FEATURES/4];
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_2 block factor = kComputeTiles dim=1
    for (unsigned pe = 0; pe < kComputeTiles; pe++)
    {
        #pragma HLS UNROLL
        Butterfly0_V1(pipe1[pe],pipe2[pe],offset,pe*offset,prev_buffer_2);
    }
    //U(3)BR(3)U^-1(3)
    offset = 4;
    SIZE_R_BLOCK = 4; // = 2^(R_k-1)
    index = 0;
    hls::stream<float> pipe3[kComputeTiles];
    #pragma HLS STREAM variable=pipe3 depth=1
    float prev_buffer_3[FEATURES/8];
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_3 block factor = kComputeTiles dim=1
    for (unsigned pe = 0; pe < kComputeTiles/(2*SIZE_R_BLOCK); pe++)
    {
        #pragma HLS UNROLL
        for (int BLOCK_R = 0; BLOCK_R < SIZE_R_BLOCK; BLOCK_R++)
        {
            #pragma HLS UNROLL
            Butterfly0_V1(pipe2[index],pipe3[index],offset,index*offset,prev_buffer_3);
            index++;
        }
        for (int BLOCK_R = 0; BLOCK_R < SIZE_R_BLOCK; BLOCK_R++)
        {
            #pragma HLS UNROLL
            Butterfly1_V1(pipe2[index],pipe3[index],offset, index*offset, prev_buffer_3);
            index++;
        }
    }
    //U(2)BR(2)U^-1(2)
    offset = 2;
    SIZE_R_BLOCK = 2; // = 2^(R_k-1)
    index = 0;
    hls::stream<float> pipe4[kComputeTiles];
    #pragma HLS STREAM variable=pipe4 depth=1
    float prev_buffer_4[FEATURES/16];
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_4 block factor = kComputeTiles dim=1
    for (unsigned pe = 0; pe < kComputeTiles/(2*SIZE_R_BLOCK); pe++)
    {
        #pragma HLS UNROLL
        for (int BLOCK_R = 0; BLOCK_R < SIZE_R_BLOCK; BLOCK_R++)
        {
            #pragma HLS UNROLL
            Butterfly0_V1(pipe3[index],pipe4[index],offset,index*offset,prev_buffer_4);
            index++;
        }
        for (int BLOCK_R = 0; BLOCK_R < SIZE_R_BLOCK; BLOCK_R++)
        {
            #pragma HLS UNROLL
            Butterfly1_V1(pipe3[index],pipe4[index],offset,index*offset,prev_buffer_4);
            index++;
        }
    }
    //U(1)BR(1)U^-1(1)
    hls::stream<float> pipe5[kComputeTiles];
    #pragma HLS STREAM variable=pipe5 depth=1
    last_UBRU_V1(pipe4, pipe5);
    
    //PHI OPERATOR: phi(k,j)
    // phi(3,0)
    
    hls::stream<float> pipe6[kComputeTiles];
    #pragma HLS STREAM variable=pipe6 depth=1
    phi<4,4>(pipe5, pipe6);
    // phi(2,0)
    hls::stream<float> pipe7[kComputeTiles];
    #pragma HLS STREAM variable=pipe7 depth=1
    phi<2,2>(pipe6, pipe7);
    // phi(1,0)
    hls::stream<float> pipe8[kComputeTiles];
    #pragma HLS STREAM variable=pipe8 depth=1
    phi<1,1>(pipe7, pipe8);
    
    //LAST URBU BLOCKS
    //U(3)R(3)BU^-1(3)
    offset = 4;
    SIZE_R_BLOCK = 4; // = 2^(R_k-1)
    index = 0;
    hls::stream<float> pipe9[kComputeTiles];
    #pragma HLS STREAM variable=pipe9 depth=1
    float prev_buffer_5[FEATURES/8];
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_5 block factor = 8 dim=1
    for (unsigned pe = 0; pe < kComputeTiles/(2*SIZE_R_BLOCK); pe++)
    {
        #pragma HLS UNROLL
        for (int BLOCK_R = 0; BLOCK_R < SIZE_R_BLOCK; BLOCK_R++)
        {
            #pragma HLS UNROLL
            Butterfly0_V1(pipe8[index],pipe9[index],offset,index*offset,prev_buffer_5);
            index++;
        }
        for (int BLOCK_R = 0; BLOCK_R < SIZE_R_BLOCK; BLOCK_R++)
        {
            #pragma HLS UNROLL
            Butterfly2_V1(pipe8[index],pipe9[index],offset, index*offset, prev_buffer_5);
            index++;
        }
    }
    //U(2)R(2)BU^-1(2)
    offset = 2;
    SIZE_R_BLOCK = 2; // = 2^(R_k-1)
    index = 0;
    hls::stream<float> pipe10[kComputeTiles];
    #pragma HLS STREAM variable=pipe10 depth=1
    float prev_buffer_6[FEATURES/16];
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_6 block factor = 8 dim=1
    for (unsigned pe = 0; pe < kComputeTiles/(2*SIZE_R_BLOCK); pe++)
    {
        #pragma HLS UNROLL
        for (int BLOCK_R = 0; BLOCK_R < SIZE_R_BLOCK; BLOCK_R++)
        {
            #pragma HLS UNROLL
            Butterfly0_V1(pipe9[index],pipe10[index],offset,index*offset,prev_buffer_6);
            index++;
        }
        for (int BLOCK_R = 0; BLOCK_R < SIZE_R_BLOCK; BLOCK_R++)
        {
            #pragma HLS UNROLL
            Butterfly2_V1(pipe9[index],pipe10[index],offset, index*offset, prev_buffer_6);
            index++;
        }
    }
    //U(1)R(1)BU^-1(1)
    hls::stream<float> pipe11[kComputeTiles];
    #pragma HLS STREAM variable=pipe11 depth=1
    last_URBU_V1(pipe10, pipe11);

    //WRITE DATA
    write_data(pipe11, Out_FWHT);

    //#ifndef __SYNTHESIS__
    //printf("Checkpoint 1 reached\n");
    //#endif
    
}
}