program: main.o os_main.o tasks.o timer.o
	gcc ./obj/main.o ./obj/os_main.o ./obj/tasks.o ./obj/timer.o -o program

main.o: ./src/general/main.c
	gcc -c ./src/general/main.c -I./src/general -I./src/os -o ./obj/main.o
	
os_main.o: ./src/os/os_main.c ./src/os/os_main.h
	gcc -c ./src/os/os_main.c -I./src/general -I./src/os -I./src/hal/windows -o ./obj/os_main.o

tasks.o: ./src/os/tasks.c
	gcc -c ./src/os/tasks.c -I./src/general -I./src/os -o ./obj/tasks.o

timer.o: ./src/hal/windows/timer.c
	gcc -c ./src/hal/windows/timer.c -I./src/general -I./src/hal/windows -o ./obj/timer.o
	
clean:
	rm ./obj/*