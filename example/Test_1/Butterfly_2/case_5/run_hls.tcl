
open_project krnl_fwht 

add_files -cflags "-DHLSLIB_SYNTHESIS -DHLSLIB_XILINX -std=c++11 -I. -DVITIS_MAJOR_VERSION=2019" "
          krnl_fwht.cpp"
set_top krnl_fwht
# Add test bench & files
add_files -tb "../test_hls.cpp" -cflags "-DHLSLIB_SYNTHESIS -DHLSLIB_XILINX -std=c++11 -I. -fno-builtin" -csimflags "-Wno-unknown-pragmas"

open_solution -reset solution1

# Define technology and clock rate
set_part  {xcvu9p-flgb2104-2-i}
create_clock -period "100.0 MHz"
csim_design
csynth_design
#cosim_design

exit
