CC=g++
CFLAGS=-c -g
all: test
	
test: Memory.o Tokenizer.o  CPU.o test.o
	$(CC) test.o Memory.o Tokenizer.o CPU.o -o test
test.o: test.cpp
	$(CC) $(CFLAGS) test.cpp
CPUProcess:

MemoryProcess:
	
CPU.o: CPU.cpp CPU.h
	$(CC) $(CFLAGS) CPU.cpp
Memory.o: Memory.cpp Memory.h
	$(CC) $(CFLAGS) Memory.cpp
Tokenizer.o: Tokenizer.cpp
	$(CC) $(CFLAGS) Tokenizer.cpp
clean: 
	rm -rf *o
