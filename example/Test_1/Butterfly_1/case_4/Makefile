test:
	vitis_hls -f run_test_hls.tcl
	rm -rf krnl_fwht/
	rm -rf *.log

test_full:
	vitis_hls -f run_test_hls.tcl

synthesize:
	vitis_hls -f run_synthesize_hls.tcl
	mv krnl_fwht/solution1/syn/report/krnl_fwht_csynth.rpt ./SynthesizeTest1But1Case4.rpt
	rm -rf krnl_fwht/
	rm -rf *.log

synthesize_full:
	vitis_hls -f run_synthesize_hls.tcl
	mv krnl_fwht/solution1/syn/report/krnl_fwht_csynth.rpt ./SynthesizeTest1But1Case4.rpt

clean: 
	rm -rf krnl_fwht/
	rm -rf *.rpt