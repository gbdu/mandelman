#

NAME = Mandel
CC = gcc
FLAGS = -lSDL -lm
OUTPUT = Mandelman

OBJS = main.o \
	pixeltools.o \
	complex.c

SRCS = $(OBJS, .o=.c)

# Executable
$(OUTPUT): $(OBJS)
	$(CC) $(OBJS) $(FLAGS) -o $(OUTPUT)
	
# Files
.c.o:
	$(CC) -c $*.c

clean:
	rm *.o
	
	
