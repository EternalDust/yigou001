################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
Pockets/Serial.obj: ../Pockets/Serial.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"D:/ComprehensiveDesign/ccsv8/tools/compiler/ti-cgt-msp430_18.1.3.LTS/bin/cl430" -vmsp --use_hw_mpy=none --include_path="D:/ComprehensiveDesign/ccsv8/ccs_base/msp430/include" --include_path="D:/ti/msp430_finalReport/Pockets" --include_path="D:/ti/msp430_finalReport" --include_path="D:/ComprehensiveDesign/ccsv8/tools/compiler/ti-cgt-msp430_18.1.3.LTS/include" --advice:power="all" --define=__MSP430G2553__ -g --c99 --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="Pockets/$(basename $(<F)).d_raw" --obj_directory="Pockets" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


