#include <compute.h>
#include <krnl_fwht.h>

void Butterfly0_V1(hls::stream<float>& read_stream,
               hls::stream<float>& out_stream, 
               const int FIFO_SIZE, int memory_offset, float prev_buffer[])
{
    const int B_computations = STREAM_DEPTH/(2*FIFO_SIZE);
    int ix;
    #pragma HLS dataflow
    for (ix = 0; ix < FIFO_SIZE; ix++)
    {
        #pragma HLS PIPELINE II=1
        prev_buffer[ix+memory_offset] = read_stream.read();
    }
    
    float actual;
    float sum_out;
    float sub_out;
    for (int sub_arr = 0; sub_arr < B_computations; sub_arr++)
    {
        for (int j = 0; j < 2; j++)
        {
            for (ix = 0; ix < FIFO_SIZE; ix++)
            {
                #pragma HLS PIPELINE II=1

                const float prev   = prev_buffer[ix+memory_offset];
                if ((sub_arr==B_computations-1) && (j%2)){
                    actual = (float)0;
                }else{
                    actual = read_stream.read();
                }

                sum_out = prev + actual;
                sub_out = prev - actual;

                if (j%2){
                    prev_buffer[ix+memory_offset] = actual;
                    out_stream.write(prev);
                }else{
                    prev_buffer[ix+memory_offset] = sub_out;
                    out_stream.write(sum_out);
                }
                #pragma HLS DEPENDENCE variable=prev_buffer false
            }
        }
    }
}

void last_Butterfly0_V1(hls::stream<float> &read_stream, hls::stream<float> &out_stream)
{
    const int B_computations = STREAM_DEPTH/2;
    float prev_buffer;
    float result_temp;

    prev_buffer = read_stream.read();
    
    float actual;
    float sum_out;
    float sub_out;
    for (int sub_arr = 0; sub_arr < B_computations; sub_arr++)
    {
        for (int j = 0; j < 2; j++)
        {
            #pragma HLS PIPELINE II=1

            const float prev   = prev_buffer;
            if ((sub_arr==B_computations-1) && (j%2)){
                actual = (float)0;
            }else{
                actual = read_stream.read();
            }

            sum_out = prev + actual;
            sub_out = prev - actual;

            if (j%2){
                prev_buffer = actual;
                out_stream << result_temp;
            }else{
                result_temp = sub_out;
                out_stream << sum_out;
            }
            #pragma HLS DEPENDENCE variable=prev_buffer false
            
        }
    }
}

void Butterfly1_V1(hls::stream<float>& read_stream,
               hls::stream<float>& out_stream, 
               const int FIFO_SIZE, int memory_offset, float prev_buffer[])
{
    const int B_computations = STREAM_DEPTH/(2*FIFO_SIZE);
    int ix;
    #pragma HLS dataflow


    for (ix = 0; ix < FIFO_SIZE; ix++)
    {
        #pragma HLS PIPELINE II=1
        prev_buffer[ix+memory_offset] = read_stream.read();
    }
    
    float actual;
    float sum_out;
    float sub_out;
    for (int sub_arr = 0; sub_arr < B_computations; sub_arr++)
    {
        for (int j = 0; j < 2; j++)
        {
            for (ix = 0; ix < FIFO_SIZE; ix++)
            {
                #pragma HLS PIPELINE II=1

                const float prev   = prev_buffer[ix+memory_offset];
                if ((sub_arr==B_computations-1) && (j%2)){
                    actual = (float)0;
                }else{
                    actual = read_stream.read();
                }

                sum_out = prev + actual;
                sub_out = prev - actual;

                if (j%2){
                    prev_buffer[ix+memory_offset] = actual;
                    out_stream.write(prev);
                }else{
                    prev_buffer[ix+memory_offset] = sum_out;
                    out_stream.write(sub_out);
                }
                #pragma HLS DEPENDENCE variable=prev_buffer false
            }
        }
    }
}

void Butterfly2_V1(hls::stream<float>& read_stream,
               hls::stream<float>& out_stream, 
               const int FIFO_SIZE, int memory_offset, float prev_buffer[])
{
    const int B_computations = STREAM_DEPTH/(2*FIFO_SIZE);
    int ix;
    #pragma HLS dataflow


    for (ix = 0; ix < FIFO_SIZE; ix++)
    {
        #pragma HLS PIPELINE II=1
        prev_buffer[ix+memory_offset] = read_stream.read();
    }
    
    float actual;
    float sum_out;
    float sub_out;
    for (int sub_arr = 0; sub_arr < B_computations; sub_arr++)
    {
        for (int j = 0; j < 2; j++)
        {
            for (ix = 0; ix < FIFO_SIZE; ix++)
            {
                #pragma HLS PIPELINE II=1

                const float prev   = prev_buffer[ix+memory_offset];
                if ((sub_arr==B_computations-1) && (j%2)){
                    actual = (float)0;
                }else{
                    actual = read_stream.read();
                }

                sum_out = prev + actual;
                sub_out = actual - prev;

                if (j%2){
                    prev_buffer[ix+memory_offset] = actual;
                    out_stream.write(prev);
                }else{
                    prev_buffer[ix+memory_offset] = sub_out;
                    out_stream.write(sum_out);
                }
                #pragma HLS DEPENDENCE variable=prev_buffer false
            }
        }
    }
}

void Butterfly3_V1(hls::stream<float>& read_stream,
               hls::stream<float>& out_stream, 
               const int FIFO_SIZE, int memory_offset, float prev_buffer[])
{
    const int B_computations = STREAM_DEPTH/(2*FIFO_SIZE);
    int ix;
    #pragma HLS dataflow


    for (ix = 0; ix < FIFO_SIZE; ix++)
    {
        #pragma HLS PIPELINE II=1
        prev_buffer[ix+memory_offset] = read_stream.read();
    }
    
    float actual;
    float sum_out;
    float sub_out;
    for (int sub_arr = 0; sub_arr < B_computations; sub_arr++)
    {
        for (int j = 0; j < 2; j++)
        {
            for (ix = 0; ix < FIFO_SIZE; ix++)
            {
                #pragma HLS PIPELINE II=1

                const float prev   = prev_buffer[ix+memory_offset];
                if ((sub_arr==B_computations-1) && (j%2)){
                    actual = (float)0;
                }else{
                    actual = read_stream.read();
                }

                sum_out = prev + actual;
                sub_out = actual - prev;

                if (j%2){
                    prev_buffer[ix+memory_offset] = actual;
                    out_stream.write(prev);
                }else{
                    prev_buffer[ix+memory_offset] = sum_out;
                    out_stream.write(sub_out);
                }
                #pragma HLS DEPENDENCE variable=prev_buffer false
            }
        }
    }
}

void last_Butterfly2_V1(hls::stream<float> &read_stream, hls::stream<float> &out_stream)
{
    const int B_computations = STREAM_DEPTH/2;
    float prev_buffer[1];
    float result_temp[1];

    prev_buffer[0] = read_stream.read();
    
    float actual;
    float sum_out;
    float sub_out;
    for (int sub_arr = 0; sub_arr < B_computations; sub_arr++)
    {
        for (int j = 0; j < 2; j++)
        {
            #pragma HLS PIPELINE II=1

            const float prev   = prev_buffer[0];
            if ((sub_arr==B_computations-1) && (j%2)){
                actual = (float)0;
            }else{
                actual = read_stream.read();
            }

            sum_out = prev + actual;
            sub_out = actual - prev;

            if (j%2){
                prev_buffer[0] = actual;
                out_stream.write(result_temp[0]);
            }else{
                result_temp[0] = sub_out;
                out_stream.write(sum_out);
            }
            #pragma HLS DEPENDENCE variable=prev_buffer false
            
        }
    }
}

void last_Butterfly1_V1(hls::stream<float> &read_stream, hls::stream<float> &out_stream)
{
    const int B_computations = STREAM_DEPTH/2;
    int ix;
    float prev_buffer[1];
    float result_temp[1];

    prev_buffer[0] = read_stream.read();


    float actual;
    float sum_out;
    float sub_out;
    for (int sub_arr = 0; sub_arr < B_computations; sub_arr++)
    {
        for (int j = 0; j < 2; j++)
        {
            #pragma HLS PIPELINE II=1

            const float prev   = prev_buffer[0];
            if ((sub_arr==B_computations-1) && (j%2)){
                actual = (float)0;
            }else{
                actual = read_stream.read();
            }

            sum_out = prev + actual;
            sub_out = prev - actual;

            if (j%2){
                prev_buffer[0] = actual;
                out_stream.write(result_temp[0]);
            }else{
                result_temp[0] = sum_out;
                out_stream.write(sub_out);
            }
        }
    }
}

void last_Butterfly3_V1(hls::stream<float> &read_stream, hls::stream<float> &out_stream)
{
    const int B_computations = STREAM_DEPTH/2;
    float prev_buffer;
    float result_temp;

    prev_buffer = read_stream.read();
    
    float actual;
    float sum_out;
    float sub_out;
    for (int sub_arr = 0; sub_arr < B_computations; sub_arr++)
    {
        for (int j = 0; j < 2; j++)
        {
            #pragma HLS PIPELINE II=1

            const float prev   = prev_buffer;
            if ((sub_arr==B_computations-1) && (j%2)){
                actual = (float)0;
            }else{
                actual = read_stream.read();
            }

            sum_out = prev + actual;
            sub_out = actual - prev;

            if (j%2){
                prev_buffer = actual;
                out_stream << result_temp;
            }else{
                result_temp = sum_out;
                out_stream << sub_out;
            }
            #pragma HLS DEPENDENCE variable=prev_buffer false
            
        }
    }
}
void last_UBRU_V1(hls::stream<float> input_stream[], hls::stream<float> out_stream[])
{
    #pragma HLS dataflow
    int index = 0;
    for (unsigned pe = 0; pe < kComputeTiles/2; pe++)
    {
        #pragma HLS UNROLL
        last_Butterfly0_V1(input_stream[index],out_stream[index]);
        index++;
        last_Butterfly1_V1(input_stream[index],out_stream[index]);
        index++;
    }
}
void last_URBU_V1(hls::stream<float> input_stream[], hls::stream<float> out_stream[])
{
    #pragma HLS dataflow
    int index = 0;
    for (unsigned pe = 0; pe < kComputeTiles/2; pe++)
    {
        #pragma HLS UNROLL
        last_Butterfly0_V1(input_stream[index],out_stream[index]);
        index++;
        last_Butterfly2_V1(input_stream[index],out_stream[index]);
        index++;
    }
}

void Butterfly0_V2(hls::stream<float>& read_stream, hls::stream<float>& out_stream, const int FIFO_SIZE,int memory_offset, float buffer_1[], float buffer_2[])
{
    const int B_computations = STREAM_DEPTH/(2*FIFO_SIZE);
    int ix;

    #pragma HLS dataflow
    for (int ix = 0; ix < FIFO_SIZE; ix++)
    {
        #pragma HLS PIPELINE II=1
        buffer_1[ix+memory_offset] = read_stream.read();
    }
    float op_1;
    float op_2;
    float sum_out;
    for (int sub_arr = 0; sub_arr < B_computations; sub_arr++)
    {
        for (int j = 0; j < 2; j++)
        {
            for (int ix = 0; ix < FIFO_SIZE; ix++)
            {   
                #pragma HLS PIPELINE II=1
                
                float stream_in = ((sub_arr==B_computations-1) && (j%2)) ? (float)0 : read_stream.read();

                const float op_1 = (j%2) ? -1*buffer_1[ix+memory_offset] : buffer_1[ix+memory_offset];
                const float op_2 = (j%2) ?    buffer_2[ix+memory_offset] : stream_in;

                sum_out = op_1 + op_2;

                buffer_2[ix+memory_offset] = buffer_1[ix+memory_offset];
                buffer_1[ix+memory_offset] = stream_in;
                out_stream << sum_out;
            }
        }
    }
}
void Butterfly1_V2(hls::stream<float>& read_stream, hls::stream<float>& out_stream, const int FIFO_SIZE,int memory_offset, float buffer_1[], float buffer_2[])
{
    const int B_computations = STREAM_DEPTH/(2*FIFO_SIZE);
    int ix;

    #pragma HLS dataflow
    for (int ix = 0; ix < FIFO_SIZE; ix++)
    {
        #pragma HLS PIPELINE II=1
        buffer_1[ix+memory_offset] = read_stream.read();
    }
    float op_1;
    float op_2;
    float sum_out;
    for (int sub_arr = 0; sub_arr < B_computations; sub_arr++)
    {
        for (int j = 0; j < 2; j++)
        {
            for (int ix = 0; ix < FIFO_SIZE; ix++)
            {   
                #pragma HLS PIPELINE II=1
                
                float stream_in = ((sub_arr==B_computations-1) && (j%2)) ? (float)0 : read_stream.read();

                const float op_1 = buffer_1[ix+memory_offset];
                const float op_2 = (j%2) ? buffer_2[ix+memory_offset] : (float)(-1*stream_in);

                sum_out = op_1 + op_2;

                buffer_2[ix+memory_offset] = buffer_1[ix+memory_offset];
                buffer_1[ix+memory_offset] = stream_in;
                out_stream << sum_out;
            }
        }
    }
}
void Butterfly2_V2(hls::stream<float>& read_stream, hls::stream<float>& out_stream, const int FIFO_SIZE,int memory_offset, float buffer_1[], float buffer_2[])
{
    const int B_computations = STREAM_DEPTH/(2*FIFO_SIZE);
    int ix;

    #pragma HLS dataflow
    for (int ix = 0; ix < FIFO_SIZE; ix++)
    {
        #pragma HLS PIPELINE II=1
        buffer_1[ix+memory_offset] = read_stream.read();
    }
    float op_1;
    float op_2;
    float sum_out;
    for (int sub_arr = 0; sub_arr < B_computations; sub_arr++)
    {
        for (int j = 0; j < 2; j++)
        {
            for (int ix = 0; ix < FIFO_SIZE; ix++)
            {   
                #pragma HLS PIPELINE II=1
                
                float stream_in = ((sub_arr==B_computations-1) && (j%2)) ? (float)0 : read_stream.read();

                const float op_1 = buffer_1[ix+memory_offset];
                const float op_2 = (j%2) ? (float)(-1*buffer_2[ix+memory_offset]) : stream_in;

                sum_out = op_1 + op_2;

                buffer_2[ix+memory_offset] = buffer_1[ix+memory_offset];
                buffer_1[ix+memory_offset] = stream_in;
                out_stream << sum_out;
            }
        }
    }
}
void Butterfly3_V2(hls::stream<float>& read_stream, hls::stream<float>& out_stream, const int FIFO_SIZE,int memory_offset, float buffer_1[], float buffer_2[])
{
    const int B_computations = STREAM_DEPTH/(2*FIFO_SIZE);
    int ix;

    #pragma HLS dataflow
    for (int ix = 0; ix < FIFO_SIZE; ix++)
    {
        #pragma HLS PIPELINE II=1
        buffer_1[ix+memory_offset] = read_stream.read();
    }
    float op_1;
    float op_2;
    float sum_out;
    for (int sub_arr = 0; sub_arr < B_computations; sub_arr++)
    {
        for (int j = 0; j < 2; j++)
        {
            for (int ix = 0; ix < FIFO_SIZE; ix++)
            {   
                #pragma HLS PIPELINE II=1
                
                float stream_in = ((sub_arr==B_computations-1) && (j%2)) ? (float)0 : read_stream.read();

                const float op_1 = (j%2) ? buffer_1[ix+memory_offset] : -1*buffer_1[ix+memory_offset];
                const float op_2 = (j%2) ? buffer_2[ix+memory_offset] : stream_in;

                sum_out = op_1 + op_2;

                buffer_2[ix+memory_offset] = buffer_1[ix+memory_offset];
                buffer_1[ix+memory_offset] = stream_in;
                out_stream << sum_out;
            }
        }
    }
}
void last_Butterfly2_V2(hls::stream<float> &read_stream, hls::stream<float> &out_stream)
{
    const int B_computations = STREAM_DEPTH/2;
    float buffer_1 = read_stream.read();
    float buffer_2;
    float op_1;
    float op_2;
    float sum_out;
    for (int sub_arr = 0; sub_arr < B_computations; sub_arr++)
    {
        for (int j = 0; j < 2; j++)
        { 
            #pragma HLS PIPELINE II=1
            
            float stream_in = ((sub_arr==B_computations-1) && (j%2)) ? (float)0 : read_stream.read();

            const float op_1 = (j%2) ?  buffer_1 : buffer_1;
            const float op_2 = (j%2) ? (float)(-1*buffer_2) : stream_in;

            sum_out = op_1 + op_2;

            buffer_2 = buffer_1;
            buffer_1 = stream_in;
            out_stream << sum_out;
            
        }
    }
}
void last_Butterfly1_V2(hls::stream<float> &read_stream, hls::stream<float> &out_stream)
{
    
    const int B_computations = STREAM_DEPTH/2;
    float buffer_1 = read_stream.read();
    float buffer_2;
    float op_1;
    float op_2;
    float sum_out;
    for (int sub_arr = 0; sub_arr < B_computations; sub_arr++)
    {
        for (int j = 0; j < 2; j++)
        {
            #pragma HLS PIPELINE II=1
            
            float stream_in = ((sub_arr==B_computations-1) && (j%2)) ? (float)0 : read_stream.read();

            const float op_1 = (j%2) ? buffer_1 : buffer_1;
            const float op_2 = (j%2) ? buffer_2 : (float)(-1*stream_in);

            sum_out = op_1 + op_2;

            buffer_2 = buffer_1;
            buffer_1 = stream_in;
            out_stream << sum_out;
            
        }
    }

}
void last_Butterfly0_V2(hls::stream<float> &read_stream, hls::stream<float> &out_stream)
{
    const int B_computations = STREAM_DEPTH/2;
    float buffer_1 = read_stream.read();
    float buffer_2;
    float op_1;
    float op_2;
    float sum_out;
    for (int sub_arr = 0; sub_arr < B_computations; sub_arr++)
    {
        for (int j = 0; j < 2; j++)
        { 
            #pragma HLS PIPELINE II=1
            
            float stream_in = ((sub_arr==B_computations-1) && (j%2)) ? (float)0 : read_stream.read();

            const float op_1 = (j%2) ? (float)(-1*buffer_1) : buffer_1;
            const float op_2 = (j%2) ? buffer_2 : stream_in;

            sum_out = op_1 + op_2;

            buffer_2 = buffer_1;
            buffer_1 = stream_in;
            out_stream << sum_out;
            
        }
    }
}
void last_Butterfly3_V2(hls::stream<float> &read_stream, hls::stream<float> &out_stream)
{
    const int B_computations = STREAM_DEPTH/2;
    float buffer_1 = read_stream.read();
    float buffer_2;
    float op_1;
    float op_2;
    float sum_out;
    for (int sub_arr = 0; sub_arr < B_computations; sub_arr++)
    {
        for (int j = 0; j < 2; j++)
        { 
            #pragma HLS PIPELINE II=1
            
            float stream_in = ((sub_arr==B_computations-1) && (j%2)) ? (float)0 : read_stream.read();

            const float op_1 = (j%2) ? buffer_1 : -1*buffer_1;
            const float op_2 = (j%2) ? buffer_2 : stream_in;

            sum_out = op_1 + op_2;

            buffer_2 = buffer_1;
            buffer_1 = stream_in;
            out_stream << sum_out;
            
        }
    }
}
void last_UBRU_V2(hls::stream<float> input_stream[], hls::stream<float> out_stream[])
{
    #pragma HLS dataflow
    int index = 0;
    for (unsigned pe = 0; pe < kComputeTiles/2; pe++)
    {
        #pragma HLS UNROLL
        last_Butterfly0_V2(input_stream[index],out_stream[index]);
        index++;
        last_Butterfly1_V2(input_stream[index],out_stream[index]);
        index++;
    }
}
void last_URBU_V2(hls::stream<float> input_stream[], hls::stream<float> out_stream[])
{
    #pragma HLS dataflow
    int index = 0;
    for (unsigned pe = 0; pe < kComputeTiles/2; pe++)
    {
        #pragma HLS UNROLL
        last_Butterfly0_V2(input_stream[index],out_stream[index]);
        index++;
        last_Butterfly2_V2(input_stream[index],out_stream[index]);
        index++;
    }
}