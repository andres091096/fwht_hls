# Parallelization levels experiment

In this experiment, we compare six different parallelization levels in the same data. We implement these architectures using the two versions of PEs so, the [Butterfly_1](./Butterfly_1) folder implements the six architectures using PE version 1 and the [Butterfly_2](./Butterfly_2) folder implements the six architecture using PE version 2. 

Inside each Butterfly folder, we find six folders (case_*), the case_0 correspond to a parallelization level 0, the case_1 folder implement the parallelization level 1, and so on until the case_5 folder that implements the parallelization level 5. 

To run the experiment inside each case folder run the command 

```bash
make synthesize
```

This command produces a .rpt file that reports the latency and the resource usage 

