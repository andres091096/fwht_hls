
open_project krnl_fwht 

add_files -cflags "-DHLSLIB_SYNTHESIS -DHLSLIB_XILINX -std=c++11 -DVITIS_MAJOR_VERSION=2019  -I../../../../include -I." "../../../../kernel/compute.cpp ../../../../kernel/connection.cpp krnl_fwht.cpp"
set_top krnl_fwht

open_solution -reset solution1

# Define technology and clock rate
set_part  {xcvu9p-flgb2104-2-i}
create_clock -period "100.0 MHz"
csynth_design

exit
