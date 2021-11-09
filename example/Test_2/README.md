# Data length experiment

In this experiment, we evaluate architectures with parallelization level of 1, changing the length of the data. We implement these architectures using the second version of the PEs,  so all the architecture are inside the [Butterfly_2](./Butterfly_2) folder. 

The Butterfly folder, contains 8 foldes (*length_*) that implement each architecture, the number afther the *_* symbol represent the data length that this architecture implements 

To run the experiment inside each *length* folder run the command 

```bash
make synthesize
```

This command produces a .rpt file that reports the latency and the resource usage 

