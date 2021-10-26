all: synthesize

test:
	vitis_hls -f run_test_hls.tcl
	rm -rf krnl_fwht/
	rm -rf *.log

synthesize:
	vitis_hls -f run_synthesize_hls.tcl
	mv krnl_fwht/solution1/syn/report/krnl_fwht_csynth.rpt ./SynthesizeTest1But1Case0.rpt
	rm -rf krnl_fwht/
	rm -rf *.log

test_full:
	vitis_hls -f run_test_hls.tcl
	rm -rf krnl_fwht/
	rm -rf *.log

synthesize_full:
	vitis_hls -f run_synthesize_hls.tcl
	mv krnl_fwht/solution1/syn/report/krnl_fwht_csynth.rpt ./SynthesizeTest1But1Case0.rpt
	rm -rf krnl_fwht/
	rm -rf *.log

clean:
	rm -rf krnl_fwht/
	rm -rf *.log
	rm -rf *.rpt