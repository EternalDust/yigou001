################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"D:/TI/ccs/tools/compiler/ti-cgt-msp430_21.6.1.LTS/bin/cl430" -vmsp --opt_for_speed=5 --use_hw_mpy=none --include_path="D:/TI/ccs/ccs_base/msp430/include" --include_path="D:/Studying/Projects/CCS/MSP430/Template" --include_path="D:/TI/ccs/tools/compiler/ti-cgt-msp430_21.6.1.LTS/include" --advice:power=all --define=__MSP430G2553__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Serial.obj: ../Serial.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"D:/TI/ccs/tools/compiler/ti-cgt-msp430_21.6.1.LTS/bin/cl430" -vmsp --opt_for_speed=5 --use_hw_mpy=none --include_path="D:/TI/ccs/ccs_base/msp430/include" --include_path="D:/Studying/Projects/CCS/MSP430/Template" --include_path="D:/TI/ccs/tools/compiler/ti-cgt-msp430_21.6.1.LTS/include" --advice:power="all" --define=__MSP430G2553__ -g --c99 --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"D:/TI/ccs/tools/compiler/ti-cgt-msp430_21.6.1.LTS/bin/cl430" -vmsp --opt_for_speed=5 --use_hw_mpy=none --include_path="D:/TI/ccs/ccs_base/msp430/include" --include_path="D:/Studying/Projects/CCS/MSP430/Template" --include_path="D:/TI/ccs/tools/compiler/ti-cgt-msp430_21.6.1.LTS/include" --include_path="D:/TI/ccs/ccs_base/msp430/include" --include_path="D:/Studying/Projects/CCS/MSP430/Template" --include_path="D:/TI/ccs/tools/compiler/ti-cgt-msp430_21.6.1.LTS/include" --advice:power=all --define=__MSP430G2553__ -g --c99 --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

