# Fast Hadamard Transform 

This is a HLS implementation of the fas Hadamard transformation.

*n = 64, K = 3*


$$
\delta_{(3)}\mu_{(3)}BR_{(3)}\mu_{(3)}^{-1}\cdots\mu_{(1)}BR_{(1)}\mu_{(1)}^{-1}\phi_{(3)}\cdots\phi_{(1)}\mu_{(3)}R_{(3)}B\mu_{(3)}^{-1}\cdots\mu_{(1)}R_{(1)}B\mu_{(1)}^{-1}\mu_{(3,6)}^{-1}
$$
Latency: 206 cycles

| Name  | BRAM_18K | DSP  | FF    | LUT   | URAM |
| ----- | -------- | ---- | ----- | ----- | ---- |
| Total | 66       | 192  | 37815 | 45050 | 0    |

###### Pipeline solution

Latency: 902 cycles

| Name  | BRAM_18K | DSP  | FF   | LUT  | URAM |
| ----- | -------- | ---- | ---- | ---- | ---- |
| Total | 20       | 22   | 5516 | 6928 | 0    |

### *N = 256*

*n = 8, K = 4*

###### Pipeline solution:

Latency: 4102 cycles

| Name  | BRAM_18K | DSP  | FF   | LUT  | URAM |
| ----- | -------- | ---- | ---- | ---- | ---- |
| Total | 24       | 30   | 7164 | 8859 | 0    |

###### Parallel-Pipeline solution:

Latency: 659 cycles

### *N = 1024*

###### Pipeline solution: 

Latency: 18438 cycles

| Name  | BRAM_18K | DSP  | FF   | LUT   | URAM |
| ----- | -------- | ---- | ---- | ----- | ---- |
| Total | 28       | 38   | 8844 | 10813 | 0    |

###### Parallel-Pipeline solution:

*n = 10, K = 5*

Latency : 2364 cycles

| Name  | BRAM_18K | DSP  | FF   | LUT   | URAM |
| ----- | -------- | ---- | ---- | ----- | ---- |
| Total | 28       | 38   | 8844 | 10813 | 0    |

### *N = 4096*

*n = 12, K = 6*

###### Pipeline solution: 

Latency: 81926 cycles

| Name  | BRAM_18K | DSP  | FF    | LUT   | URAM |
| ----- | -------- | ---- | ----- | ----- | ---- |
| Total | 34       | 46   | 10556 | 12783 |      |

