#include <hls_stream.h>
#include <krnl_fwht.h>
#include <connection.h>
#include <compute.h>


extern "C" {
    void phi_1_4(hls::stream<float> input_stream[], hls::stream<float> out_stream[]){
    int index;
    #pragma HLS dataflow
    for (int i = 0; i < FEATURES/(kComputeTiles); i++)
    {
            if (i%2){
                index = 0;
                for (int k = 0; k < kComputeTiles/4; k++)
                {
                    #pragma HLS UNROLL
                    for (int k0 = 0; k0 < 4; k0++)
                    {
                        if (k%2){
                            const float temp = input_stream[index].read();
                            out_stream[index-4].write(temp);
                        }
                        else{
                            const float temp = input_stream[index].read();
                            out_stream[index+4].write(temp);
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
void write_case5(hls::stream<float> out_stream[], float *Out_FWHT)
{
    int NEW_ROWS = 8;
    #pragma HLS dataflow
    hls::stream<float, 2> fpipe1[NEW_ROWS];
    for (int k = 0; k < NEW_ROWS; k++)
    {
        for (int p = 0; p < 2; p++)
        {
            for (int j = 0; j < kComputeTiles/NEW_ROWS; j++)
            {
                for (int i = 0; i < FEATURES/(2*kComputeTiles); i++)
                {
                    float temp = out_stream[j+k*kComputeTiles/NEW_ROWS].read();
                    fpipe1[k].write(temp);
                }
            }
        }
    }

    //u_inv(3,8)
    int index = 0;
    for (int p = 0; p < 8; p++)
    {
        for (int i = 0; i < FEATURES/8; i++)
        {
            #pragma HLS PIPELINE II=1
            Out_FWHT[index] = fpipe1[p].read();
            index++;
        }
    }
}
void krnl_fwht(float *In_FWHT, float *Out_FWHT){
#pragma HLS INTERFACE m_axi port=In_FWHT   offset=slave bundle=gmem0
#pragma HLS INTERFACE m_axi port=Out_FWHT  offset=slave bundle=gmem0

#pragma HLS INTERFACE s_axilite port=In_FWHT   bundle=control
#pragma HLS INTERFACE s_axilite port=Out_FWHT   bundle=control
#pragma HLS INTERFACE s_axilite port=return bundle=control
    int index;
    int SIZE_R_BLOCK;
    int k_1;
    int phi_value;
    int FIFO_SIZE;

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
    hls::stream<float> pipe13[kComputeTiles];
    #pragma HLS STREAM variable=pipe13 depth=1


    float prev_buffer_1_1[FEATURES/2];
    float prev_buffer_1_2[FEATURES/2];
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_1_1 block factor=32 dim=1
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_1_2 block factor=32 dim=1
    float prev_buffer_2_1[FEATURES/4];
    float prev_buffer_2_2[FEATURES/4];
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_2_1 block factor=32 dim=1
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_2_2 block factor=32 dim=1
    float prev_buffer_3_1[FEATURES/2];
    float prev_buffer_3_2[FEATURES/2];
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_3_1 block factor=32 dim=1
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_3_2 block factor=32 dim=1
    float prev_buffer_4_1[FEATURES/4];
    float prev_buffer_4_2[FEATURES/4];
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_4_1 block factor=32 dim=1
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_4_2 block factor=32 dim=1
    float prev_buffer_5_1[FEATURES/4];
    float prev_buffer_5_2[FEATURES/4];
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_5_1 block factor=32 dim=1
    #pragma HLS ARRAY_PARTITION variable=prev_buffer_5_2 block factor=32 dim=1

    #pragma HLS dataflow
    //READ DATA AND PASS THEM TO "K" STREAMS
    read_data(input_strem, In_FWHT);
    decimator(input_strem, pipe0);
    
    //START URBU BLOCKS
    //U(3)BR(5)U^-1(3)
    FIFO_SIZE    = 4; // = 2^(U_k-1)
    SIZE_R_BLOCK = 16; // = 2^(R_k-1)
    index = 0;
    for (unsigned pe = 0; pe < kComputeTiles/(2*SIZE_R_BLOCK); pe++)
    {
        #pragma HLS UNROLL
        for (int BLOCK_R = 0; BLOCK_R < SIZE_R_BLOCK; BLOCK_R++)
        {
            #pragma HLS UNROLL
            Butterfly0_V2(pipe0[index],pipe1[index],FIFO_SIZE,index*FIFO_SIZE,prev_buffer_1_1,prev_buffer_1_2);
            index++;
        }
        for (int BLOCK_R = 0; BLOCK_R < SIZE_R_BLOCK; BLOCK_R++)
        {
            #pragma HLS UNROLL
            Butterfly1_V2(pipe0[index],pipe1[index],FIFO_SIZE,index*FIFO_SIZE,prev_buffer_1_1,prev_buffer_1_2);
            index++;
        }
    }
    //U(3)BU^-1(3)
    FIFO_SIZE    = 2; // = 2^(U_k-1)
    SIZE_R_BLOCK = 8; // = 2^(R_k-1)
    index = 0;
    for (unsigned pe = 0; pe < kComputeTiles/(2*SIZE_R_BLOCK); pe++)
    {
        #pragma HLS UNROLL
        for (int BLOCK_R = 0; BLOCK_R < SIZE_R_BLOCK; BLOCK_R++)
        {
            #pragma HLS UNROLL
            Butterfly0_V2(pipe1[index],pipe2[index],FIFO_SIZE,index*FIFO_SIZE,prev_buffer_2_1,prev_buffer_2_2);
            index++;
        }
        for (int BLOCK_R = 0; BLOCK_R < SIZE_R_BLOCK; BLOCK_R++)
        {
            #pragma HLS UNROLL
            Butterfly1_V2(pipe1[index],pipe2[index],FIFO_SIZE,index*FIFO_SIZE,prev_buffer_2_1,prev_buffer_2_2);
            index++;
        }
    }
    //U(1)BR(3)U^-1(1)
    SIZE_R_BLOCK = 4; // = 2^(R_k-1)
    index = 0;
    for (unsigned pe = 0; pe < kComputeTiles/(2*SIZE_R_BLOCK); pe++)
    {
        #pragma HLS UNROLL
        for (int BLOCK_R = 0; BLOCK_R < SIZE_R_BLOCK; BLOCK_R++)
        {
            #pragma HLS UNROLL
            last_Butterfly0_V2(pipe2[index],pipe3[index]);
            index++;
        }
        for (int BLOCK_R = 0; BLOCK_R < SIZE_R_BLOCK; BLOCK_R++)
        {
            #pragma HLS UNROLL
            last_Butterfly1_V2(pipe2[index],pipe3[index]);
            index++;
        }
    }
    
    /////////////////////////// phi(k,j) 
    // phi(3,2)
    phi<4,16>(pipe3,pipe4);
    phi<2,8>(pipe4,pipe5);
    phi_1_4(pipe5,pipe6);
    
    /////////////////////////// URBU(k,j) 
    
    //U(3)R(5)BU^-1(3)
    FIFO_SIZE    = 4; // = 2^(U_k-1)
    SIZE_R_BLOCK = 16; // = 2^(R_k-1)
    index = 0;
    for (unsigned pe = 0; pe < kComputeTiles/(2*SIZE_R_BLOCK); pe++)
    {
        #pragma HLS UNROLL
        for (int BLOCK_R = 0; BLOCK_R < SIZE_R_BLOCK; BLOCK_R++)
        {
            #pragma HLS UNROLL
            Butterfly0_V2(pipe6[index],pipe7[index],FIFO_SIZE,index*FIFO_SIZE,prev_buffer_3_1,prev_buffer_3_2);
            index++;
        }
        for (int BLOCK_R = 0; BLOCK_R < SIZE_R_BLOCK; BLOCK_R++)
        {
            #pragma HLS UNROLL
            Butterfly2_V2(pipe6[index],pipe7[index],FIFO_SIZE,index*FIFO_SIZE,prev_buffer_3_1,prev_buffer_3_2);
            index++;
        }
    }
    //U(2)R(4)BR(2)U^-1(2)
    FIFO_SIZE = 2; // = 2^(U_k-1)
    //R4 (no) R2(no)
    Butterfly0_V2(pipe7[0],pipe8[0],FIFO_SIZE,0*FIFO_SIZE,prev_buffer_4_1,prev_buffer_4_2);
    Butterfly0_V2(pipe7[1],pipe8[1],FIFO_SIZE,1*FIFO_SIZE,prev_buffer_4_1,prev_buffer_4_2);
    //R4 (no) R2(yes)
    Butterfly1_V2(pipe7[2],pipe8[2],FIFO_SIZE,2*FIFO_SIZE,prev_buffer_4_1,prev_buffer_4_2);
    Butterfly1_V2(pipe7[3],pipe8[3],FIFO_SIZE,3*FIFO_SIZE,prev_buffer_4_1,prev_buffer_4_2);
    //R4 (no) R2(no)
    Butterfly0_V2(pipe7[4],pipe8[4],FIFO_SIZE,4*FIFO_SIZE,prev_buffer_4_1,prev_buffer_4_2);
    Butterfly0_V2(pipe7[5],pipe8[5],FIFO_SIZE,5*FIFO_SIZE,prev_buffer_4_1,prev_buffer_4_2);
    //R4 (no) R2(yes)
    Butterfly1_V2(pipe7[6],pipe8[6],FIFO_SIZE,6*FIFO_SIZE,prev_buffer_4_1,prev_buffer_4_2);
    Butterfly1_V2(pipe7[7],pipe8[7],FIFO_SIZE,7*FIFO_SIZE,prev_buffer_4_1,prev_buffer_4_2);
    //R4 (yes) R2(no)
    Butterfly2_V2(pipe7[8],pipe8[8],FIFO_SIZE,8*FIFO_SIZE,prev_buffer_4_1,prev_buffer_4_2);
    Butterfly2_V2(pipe7[9],pipe8[9],FIFO_SIZE,9*FIFO_SIZE,prev_buffer_4_1,prev_buffer_4_2);
    //R4 (yes) R2(yes)
    Butterfly3_V2(pipe7[10],pipe8[10],FIFO_SIZE,10*FIFO_SIZE,prev_buffer_4_1,prev_buffer_4_2);
    Butterfly3_V2(pipe7[11],pipe8[11],FIFO_SIZE,11*FIFO_SIZE,prev_buffer_4_1,prev_buffer_4_2);
    //R4 (yes) R2(no)
    Butterfly2_V2(pipe7[12],pipe8[12],FIFO_SIZE,12*FIFO_SIZE,prev_buffer_4_1,prev_buffer_4_2);
    Butterfly2_V2(pipe7[13],pipe8[13],FIFO_SIZE,13*FIFO_SIZE,prev_buffer_4_1,prev_buffer_4_2);
    //R4 (yes) R2(yes)
    Butterfly3_V2(pipe7[14],pipe8[14],FIFO_SIZE,14*FIFO_SIZE,prev_buffer_4_1,prev_buffer_4_2);
    Butterfly3_V2(pipe7[15],pipe8[15],FIFO_SIZE,15*FIFO_SIZE,prev_buffer_4_1,prev_buffer_4_2);
    //R4 (no) R2(no) 
    Butterfly0_V2(pipe7[16],pipe8[16],FIFO_SIZE,16*FIFO_SIZE,prev_buffer_4_1,prev_buffer_4_2);
    Butterfly0_V2(pipe7[17],pipe8[17],FIFO_SIZE,17*FIFO_SIZE,prev_buffer_4_1,prev_buffer_4_2);
    //R4 (no) R2(yes)
    Butterfly1_V2(pipe7[18],pipe8[18],FIFO_SIZE,18*FIFO_SIZE,prev_buffer_4_1,prev_buffer_4_2);
    Butterfly1_V2(pipe7[19],pipe8[19],FIFO_SIZE,19*FIFO_SIZE,prev_buffer_4_1,prev_buffer_4_2);
    //R4 (no) R2(no)
    Butterfly0_V2(pipe7[20],pipe8[20],FIFO_SIZE,20*FIFO_SIZE,prev_buffer_4_1,prev_buffer_4_2);
    Butterfly0_V2(pipe7[21],pipe8[21],FIFO_SIZE,21*FIFO_SIZE,prev_buffer_4_1,prev_buffer_4_2);
    //R4 (no) R2(yes)
    Butterfly1_V2(pipe7[22],pipe8[22],FIFO_SIZE,22*FIFO_SIZE,prev_buffer_4_1,prev_buffer_4_2);
    Butterfly1_V2(pipe7[23],pipe8[23],FIFO_SIZE,23*FIFO_SIZE,prev_buffer_4_1,prev_buffer_4_2);
    //R4 (yes) R2(no)
    Butterfly2_V2(pipe7[24],pipe8[24],FIFO_SIZE,24*FIFO_SIZE,prev_buffer_4_1,prev_buffer_4_2);
    Butterfly2_V2(pipe7[25],pipe8[25],FIFO_SIZE,25*FIFO_SIZE,prev_buffer_4_1,prev_buffer_4_2);
    //R4 (yes) R2(yes)
    Butterfly3_V2(pipe7[26],pipe8[26],FIFO_SIZE,26*FIFO_SIZE,prev_buffer_4_1,prev_buffer_4_2);
    Butterfly3_V2(pipe7[27],pipe8[27],FIFO_SIZE,27*FIFO_SIZE,prev_buffer_4_1,prev_buffer_4_2);
    //R4 (yes) R2(no)
    Butterfly2_V2(pipe7[28],pipe8[28],FIFO_SIZE,28*FIFO_SIZE,prev_buffer_4_1,prev_buffer_4_2);
    Butterfly2_V2(pipe7[29],pipe8[29],FIFO_SIZE,29*FIFO_SIZE,prev_buffer_4_1,prev_buffer_4_2);
    //R4 (yes) R2(yes)
    Butterfly3_V2(pipe7[30],pipe8[30],FIFO_SIZE,30*FIFO_SIZE,prev_buffer_4_1,prev_buffer_4_2);
    Butterfly3_V2(pipe7[31],pipe8[31],FIFO_SIZE,31*FIFO_SIZE,prev_buffer_4_1,prev_buffer_4_2);
    
    //U(1)R(3)BR(1)U^-1(1)
  FIFO_SIZE = 1; // = 2^(U_k-1
    //R3 (no) R1(no)
    last_Butterfly0_V2(pipe8[0],pipe9[0]);
    //R3 (no) R1(yes)
    last_Butterfly1_V2(pipe8[1],pipe9[1]);
    //R3 (no) R1(no)
    last_Butterfly0_V2(pipe8[2],pipe9[2]);
    //R3 (no) R1(yes)
    last_Butterfly1_V2(pipe8[3],pipe9[3]);
    //R3 (yes) R1(no)
    last_Butterfly2_V2(pipe8[4],pipe9[4]);
    //R3 (yes) R1(yes)
    last_Butterfly3_V2(pipe8[5],pipe9[5]);
    //R3 (yes) R1(no)
    last_Butterfly2_V2(pipe8[6],pipe9[6]);
    //R3 (yes) R1(yes)
    last_Butterfly3_V2(pipe8[7],pipe9[7]);
    //R3 (no) R1(no)
    last_Butterfly0_V2(pipe8[8],pipe9[8]);
    //R3 (no) R1(yes)
    last_Butterfly1_V2(pipe8[9],pipe9[9]);
    //R3 (no) R1(no)
    last_Butterfly0_V2(pipe8[10],pipe9[10]);
    //R3 (no) R1(yes)
    last_Butterfly1_V2(pipe8[11],pipe9[11]);
    //R3 (yes) R1(no)
    last_Butterfly2_V2(pipe8[12],pipe9[12]);
    //R3 (yes) R1(yes)
    last_Butterfly3_V2(pipe8[13],pipe9[13]);
    //R3 (yes) R1(no)
    last_Butterfly2_V2(pipe8[14],pipe9[14]);
    //R3 (yes) R1(yes)
    last_Butterfly3_V2(pipe8[15],pipe9[15]);
    //R3 (no) R1(no) 
    last_Butterfly0_V2(pipe8[16],pipe9[16]);
    //R3 (no) R1(yes)
    last_Butterfly1_V2(pipe8[17],pipe9[17]);
    //R3 (no) R1(no)
    last_Butterfly0_V2(pipe8[18],pipe9[18]);
    //R3 (no) R1(yes)
    last_Butterfly1_V2(pipe8[19],pipe9[19]);
    //R3 (yes) R1(no)
    last_Butterfly2_V2(pipe8[20],pipe9[20]);
    //R3 (yes) R1(yes)
    last_Butterfly3_V2(pipe8[21],pipe9[21]);
    //R3 (yes) R1(no)
    last_Butterfly2_V2(pipe8[22],pipe9[22]);
    //R3 (yes) R1(yes)
    last_Butterfly3_V2(pipe8[23],pipe9[23]);
    //R3 (no) R1(no)
    last_Butterfly0_V2(pipe8[24],pipe9[24]);
    //R3 (no) R1(yes)
    last_Butterfly1_V2(pipe8[25],pipe9[25]);
    //R3 (no) R1(no)
    last_Butterfly0_V2(pipe8[26],pipe9[26]);
    //R3 (no) R1(yes)
    last_Butterfly1_V2(pipe8[27],pipe9[27]);
    //R3 (yes) R1(no)
    last_Butterfly2_V2(pipe8[28],pipe9[28]);
    //R3 (yes) R1(yes)
    last_Butterfly3_V2(pipe8[29],pipe9[29]);
    //R3 (yes) R1(no)
    last_Butterfly2_V2(pipe8[30],pipe9[30]);
    //R3 (yes) R1(yes)
    last_Butterfly3_V2(pipe8[31],pipe9[31]);
    
    //PHI OPERATOR: phi(k,j)
    /////////////////////////////////////////////////////////////////////////////////////
    
    // phi(2,0)
    phi<2,2>(pipe9,pipe10);
    phi<1,1>(pipe10,pipe11);


    //U(2)R(2)BU^-1(2)
    FIFO_SIZE    = 2; // = 2^(U_k-1)
    SIZE_R_BLOCK = 2; // = 2^(R_k-1)
    index = 0;
    for (unsigned pe = 0; pe < kComputeTiles/(2*SIZE_R_BLOCK); pe++)
    {
        #pragma HLS UNROLL
        for (int BLOCK_R = 0; BLOCK_R < SIZE_R_BLOCK; BLOCK_R++)
        {
            #pragma HLS UNROLL
            Butterfly0_V2(pipe11[index],pipe12[index],FIFO_SIZE,index*FIFO_SIZE,prev_buffer_5_1,prev_buffer_5_2);
            index++;
        }
        for (int BLOCK_R = 0; BLOCK_R < SIZE_R_BLOCK; BLOCK_R++)
        {
            #pragma HLS UNROLL
            Butterfly2_V2(pipe11[index],pipe12[index],FIFO_SIZE,index*FIFO_SIZE,prev_buffer_5_1,prev_buffer_5_2);
            index++;
        }
    }
    //U(1)R(1)BU^-1(1)
    last_URBU_V2(pipe12, pipe13);
    
    //U(2)R(2)BU^-1(2)
    write_case5(pipe13, Out_FWHT);
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