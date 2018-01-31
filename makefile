# Target options:
#	- 'windows'
#	- 'AT4313'
TARGET = 'windows'

# Overall
program: General OS HAL
	gcc ./obj/main.o ./obj/os_main.o ./obj/tasks.o \
		./obj/print.o ./obj/timer.o \
		-o program

# General
General: ./src/general/main.c
	gcc -c ./src/general/main.c -I./src/general -I./src/os -I./src/hal/windows -o ./obj/main.o

# OS Components
OS: ./src/os/os_main.c ./src/os/tasks.c
	gcc -c ./src/os/os_main.c -I./src/general -I./src/os -I./src/hal/windows -o ./obj/os_main.o
	gcc -c ./src/os/tasks.c -I./src/general -I./src/os -I./src/hal/windows -o ./obj/tasks.o

# HAL Components
HAL:
ifeq ($(TARGET), 'windows')
	gcc -c ./src/hal/windows/timer.c -I./src/general -I./src/hal/windows -o ./obj/timer.o
	gcc -c ./src/hal/windows/print.c -I./src/general -I./src/hal/windows -o ./obj/print.o
else
	gcc -c ./src/hal/AT4313/timer.c -I./src/general -I./src/hal/windows -o ./obj/timer.o
	gcc -c ./src/hal/AT4313/print.c -I./src/general -I./src/hal/windows -o ./obj/print.o
endif
	
clean:
	rm ./obj/*