#include <hls_stream.h>

void Butterfly0_V1(hls::stream<float>& read_stream,
               hls::stream<float>& out_stream, 
               const int FIFO_SIZE, int memory_offset, float prev_buffer[]);
void Butterfly1_V1(hls::stream<float>& read_stream,
               hls::stream<float>& out_stream, 
               const int FIFO_SIZE, int memory_offset, float prev_buffer[]);
void Butterfly2_V1(hls::stream<float>& read_stream,
               hls::stream<float>& out_stream, 
               const int FIFO_SIZE, int memory_offset, float prev_buffer[]);
void Butterfly3_V1(hls::stream<float>& read_stream,
               hls::stream<float>& out_stream, 
               const int FIFO_SIZE, int memory_offset, float prev_buffer[]);
               
void last_Butterfly0_V1(hls::stream<float> &read_stream, hls::stream<float> &out_stream);
void last_Butterfly2_V1(hls::stream<float> &read_stream, hls::stream<float> &out_stream);
void last_Butterfly1_V1(hls::stream<float> &read_stream, hls::stream<float> &out_stream);
void last_Butterfly3_V1(hls::stream<float> &read_stream, hls::stream<float> &out_stream);

void last_UBRU_V1(hls::stream<float> input_stream[], hls::stream<float> out_stream[]);
void last_URBU_V1(hls::stream<float> input_stream[], hls::stream<float> out_stream[]);

void Butterfly0_V2(hls::stream<float>& read_stream, hls::stream<float>& out_stream, const int FIFO_SIZE,int memory_offset, float buffer_1[], float buffer_2[]);
void Butterfly1_V2(hls::stream<float>& read_stream, hls::stream<float>& out_stream, const int FIFO_SIZE,int memory_offset, float buffer_1[], float buffer_2[]);
void Butterfly2_V2(hls::stream<float>& read_stream, hls::stream<float>& out_stream, const int FIFO_SIZE,int memory_offset, float buffer_1[], float buffer_2[]);
void Butterfly3_V2(hls::stream<float>& read_stream, hls::stream<float>& out_stream, const int FIFO_SIZE,int memory_offset, float buffer_1[], float buffer_2[]);
void last_Butterfly2_V2(hls::stream<float> &read_stream, hls::stream<float> &out_stream);
void last_Butterfly1_V2(hls::stream<float> &read_stream, hls::stream<float> &out_stream);
void last_Butterfly0_V2(hls::stream<float> &read_stream, hls::stream<float> &out_stream);
void last_Butterfly3_V2(hls::stream<float> &read_stream, hls::stream<float> &out_stream);
void last_UBRU_V2(hls::stream<float> input_stream[], hls::stream<float> out_stream[]);
void last_URBU_V2(hls::stream<float> input_stream[], hls::stream<float> out_stream[]);