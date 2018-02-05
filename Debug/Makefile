################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=
LINKER_SCRIPT_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS :=  \
../src \
../src/general \
../src/hal \
../src/os


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../src/general/main.c \
../src/hal/print.c \
../src/hal/timer.c \
../src/os/os_main.c \
../src/os/tasks.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
src/general/main.o \
src/hal/print.o \
src/hal/timer.o \
src/os/os_main.o \
src/os/tasks.o

OBJS_AS_ARGS +=  \
src/general/main.o \
src/hal/print.o \
src/hal/timer.o \
src/os/os_main.o \
src/os/tasks.o

C_DEPS +=  \
src/general/main.d \
src/hal/print.d \
src/hal/timer.d \
src/os/os_main.d \
src/os/tasks.d

C_DEPS_AS_ARGS +=  \
src/general/main.d \
src/hal/print.d \
src/hal/timer.d \
src/os/os_main.d \
src/os/tasks.d

OUTPUT_FILE_PATH +=NerfAVR.elf

OUTPUT_FILE_PATH_AS_ARGS +=NerfAVR.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

LINKER_SCRIPT_DEP+= 


# AVR32/GNU C Compiler











src/general/%.o: ../src/general/%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 5.4.0
	$(QUOTE)D:\Programs\Atmel\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -I"D:\Programs\Atmel\7.0\Packs\atmel\ATtiny_DFP\1.3.147\include" -I"../src/general" -I"../src/hal" -I"../src/os"  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=attiny4313 -B "D:\Programs\Atmel\7.0\Packs\atmel\ATtiny_DFP\1.3.147\gcc\dev\attiny4313" -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

src/hal/%.o: ../src/hal/%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 5.4.0
	$(QUOTE)D:\Programs\Atmel\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -I"D:\Programs\Atmel\7.0\Packs\atmel\ATtiny_DFP\1.3.147\include" -I"../src/general" -I"../src/hal" -I"../src/os"  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=attiny4313 -B "D:\Programs\Atmel\7.0\Packs\atmel\ATtiny_DFP\1.3.147\gcc\dev\attiny4313" -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

src/os/%.o: ../src/os/%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 5.4.0
	$(QUOTE)D:\Programs\Atmel\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -I"D:\Programs\Atmel\7.0\Packs\atmel\ATtiny_DFP\1.3.147\include" -I"../src/general" -I"../src/hal" -I"../src/os"  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=attiny4313 -B "D:\Programs\Atmel\7.0\Packs\atmel\ATtiny_DFP\1.3.147\gcc\dev\attiny4313" -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	



# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP) $(LINKER_SCRIPT_DEP)
	@echo Building target: $@
	@echo Invoking: AVR/GNU Linker : 5.4.0
	$(QUOTE)D:\Programs\Atmel\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="NerfAVR.map" -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,--gc-sections -mmcu=attiny4313 -B "D:\Programs\Atmel\7.0\Packs\atmel\ATtiny_DFP\1.3.147\gcc\dev\attiny4313"  
	@echo Finished building target: $@
	"D:\Programs\Atmel\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "NerfAVR.elf" "NerfAVR.hex"
	"D:\Programs\Atmel\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "NerfAVR.elf" "NerfAVR.eep" || exit 0
	"D:\Programs\Atmel\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objdump.exe" -h -S "NerfAVR.elf" > "NerfAVR.lss"
	"D:\Programs\Atmel\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures "NerfAVR.elf" "NerfAVR.srec"
	"D:\Programs\Atmel\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-size.exe" "NerfAVR.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "NerfAVR.elf" "NerfAVR.a" "NerfAVR.hex" "NerfAVR.lss" "NerfAVR.eep" "NerfAVR.map" "NerfAVR.srec" "NerfAVR.usersignatures"
	