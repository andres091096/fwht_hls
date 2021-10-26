
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
    hls::stream<float> pipe10[kComputeTiles];
    #pragma HLS STREAM variable=pipe10 depth=1
    hls::stream<float> pipe11[kComputeTiles];
    #pragma HLS STREAM variable=pipe11 depth=1
    hls::stream<float> pipe12[kComputeTiles];
    #pragma HLS STREAM variable=pipe12 depth=1
    hls::stream<float> out_stream_0[kComputeTiles];
    #pragma HLS STREAM variable=out_stream_0 depth=1


    float prev_buffer_1_1[FEATURES/2];
    float prev_buffer_1_2[FEATURES/2];
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_1_1 block factor=16 dim=1
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_1_2 block factor=16 dim=1
    float prev_buffer_2_1[FEATURES/4];
    float prev_buffer_2_2[FEATURES/4];
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_2_1 block factor=16 dim=1
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_2_2 block factor=16 dim=1
    float prev_buffer_3_1[FEATURES/8];
    float prev_buffer_3_2[FEATURES/8];
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_3_1 block factor=16 dim=1
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_3_2 block factor=16 dim=1
    float prev_buffer_4_1[FEATURES/2];
    float prev_buffer_4_2[FEATURES/2];
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_4_1 block factor=16 dim=1
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_4_2 block factor=16 dim=1
    float prev_buffer_5_1[FEATURES/4];
    float prev_buffer_5_2[FEATURES/4];
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_5_1 block factor=16 dim=1
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_5_2 block factor=16 dim=1
    float prev_buffer_6_1[FEATURES/8];
    float prev_buffer_6_2[FEATURES/8];
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_6_1 block factor=16 dim=1
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_6_2 block factor=16 dim=1

    #pragma HLS dataflow
    //READ DATA AND PASS THEM TO "K" STREAMS
    read_data(input_strem, In_FWHT);
    decimator(input_strem, pipe0);
    
    //START URBU BLOCKS
    //U(4)BU^-1(4)
    index = 0;
    for (unsigned pe = 0; pe < kComputeTiles/(2*8); pe++)
    {
        #pragma HLS UNROLL
        for (int BLOCK_R = 0; BLOCK_R < 8; BLOCK_R++)
        {
            #pragma HLS UNROLL
            Butterfly0_V2(pipe0[index],pipe1[index],8,index*8,prev_buffer_1_1,prev_buffer_1_2);
            index++;
        }
        for (int BLOCK_R = 0; BLOCK_R < 8; BLOCK_R++)
        {
            #pragma HLS UNROLL
            Butterfly1_V2(pipe0[index],pipe1[index],8,index*8,prev_buffer_1_1,prev_buffer_1_2);
            index++;
        }
    }
    //U(3)BU^-1(3)
    index = 0;
    for (unsigned pe = 0; pe < kComputeTiles/(2*4); pe++)
    {
        #pragma HLS UNROLL
        for (int BLOCK_R = 0; BLOCK_R < 4; BLOCK_R++)
        {
            #pragma HLS UNROLL
            Butterfly0_V2(pipe1[index],pipe2[index],4,index*4,prev_buffer_2_1,prev_buffer_2_2);
            index++;
        }
        for (int BLOCK_R = 0; BLOCK_R < 4; BLOCK_R++)
        {
            #pragma HLS UNROLL
            Butterfly1_V2(pipe1[index],pipe2[index],4,index*4,prev_buffer_2_1,prev_buffer_2_2);
            index++;
        }
    }
    //U(2)BU^-1(2)
    index = 0;
    for (unsigned pe = 0; pe < kComputeTiles/(2*2); pe++)
    {
        #pragma HLS UNROLL
        for (int BLOCK_R = 0; BLOCK_R < 2; BLOCK_R++)
        {
            #pragma HLS UNROLL
            Butterfly0_V2(pipe2[index],pipe3[index],2,index*2,prev_buffer_3_1,prev_buffer_3_2);
            index++;
        }
        for (int BLOCK_R = 0; BLOCK_R < 2; BLOCK_R++)
        {
            #pragma HLS UNROLL
            Butterfly1_V2(pipe2[index],pipe3[index],2,index*2,prev_buffer_3_1,prev_buffer_3_2);
            index++;
        }
    }
    

    //U(1)BR(1)U^-1(1)
    last_UBRU_V2(pipe3, pipe4);

    /////////////////////////// phi(k,j) 
    // phi(4,0)
    phi<8,8>(pipe4,pipe5);
    phi<4,4>(pipe5,pipe6);
    phi<2,2>(pipe6,pipe7);
    phi<1,1>(pipe7,pipe8);
    
    /////////////////////////// URBU(k,j) 
    
    //U(4)BR(4)U^-1(4)
    index = 0;
    for (unsigned pe = 0; pe < kComputeTiles/(2*8); pe++)
    {
        #pragma HLS UNROLL
        for (int BLOCK_R = 0; BLOCK_R < 8; BLOCK_R++)
        {
            #pragma HLS UNROLL
            Butterfly0_V2(pipe8[index],pipe9[index],8,index*8,prev_buffer_4_1,prev_buffer_4_2);
            index++;
        }
        for (int BLOCK_R = 0; BLOCK_R < 8; BLOCK_R++)
        {
            #pragma HLS UNROLL
            Butterfly2_V2(pipe8[index],pipe9[index],8,index*8,prev_buffer_4_1,prev_buffer_4_2);
            index++;
        }
    }
    //U(3)BR(3)U^-1(3)
    index = 0;
    for (unsigned pe = 0; pe < kComputeTiles/(2*4); pe++)
    {
        #pragma HLS UNROLL
        for (int BLOCK_R = 0; BLOCK_R < 4; BLOCK_R++)
        {
            #pragma HLS UNROLL
            Butterfly0_V2(pipe9[index],pipe10[index],4,index*4,prev_buffer_5_1,prev_buffer_5_2);
            index++;
        }
        for (int BLOCK_R = 0; BLOCK_R < 4; BLOCK_R++)
        {
            #pragma HLS UNROLL
            Butterfly2_V2(pipe9[index],pipe10[index],4,index*4,prev_buffer_5_1,prev_buffer_5_2);
            index++;
        }
    }
    //U(2)BU^-1(2)
    index = 0;
    for (unsigned pe = 0; pe < kComputeTiles/(2*2); pe++)
    {
        #pragma HLS UNROLL
        for (int BLOCK_R = 0; BLOCK_R < 2; BLOCK_R++)
        {
            #pragma HLS UNROLL
            Butterfly0_V2(pipe10[index],pipe11[index],2,index*2,prev_buffer_6_1,prev_buffer_6_2);
            index++;
        }
        for (int BLOCK_R = 0; BLOCK_R < 2; BLOCK_R++)
        {
            #pragma HLS UNROLL
            Butterfly2_V2(pipe10[index],pipe11[index],2,index*2,prev_buffer_6_1,prev_buffer_6_2);
            index++;
        }
    }
    
    //U(1)BR(1)U^-1(1)
    last_URBU_V2(pipe11, out_stream_0);

    write_data(out_stream_0, Out_FWHT);
    /*
    index = 0;
    for (int k = 0; k < FEATURES/(4*kComputeTiles); k++)
    {
        for (int j = 0; j < kComputeTiles; j++)
        {
            for (int i = 0; i < 4; i++)
            {
                Out_FWHT[index] = pipe9[j].read();
                index++;
            }
        }
    }
    */
    //#ifndef __SYNTHESIS__
    //printf("Checkpoint 1 reached\n");
    //#endif

}
}