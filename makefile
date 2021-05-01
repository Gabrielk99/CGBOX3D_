CC =g++
CFLAGS =-lGL\
		 -lGLU\
		 -lglut\

all: trabalhocg

trabalhocg: *.cpp *.c
	$(CC) -o  trabalhocg *.cpp *.c $(CFLAGS)
clean:
	rm -rf  trabalhocg
