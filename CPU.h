#ifndef CPU_H
#define CPU_H

#include <iostream>
#include <string>

#include "Memory.h"

using namespace std;

class CPU{

public:
	enum Instructions	
	{
		LOADVAL = 1,				//Load value into AC
		LOADADDR = 2,				//Load the value at the address into the AC
		LOADINDADDR = 3,			//Load the value from the address found in the address specified into AC
		LOADIDXXADDR = 4,			//Load the value at (address + X) into the AC
		LOADIDXYADDR = 5,			//Load the value at (address + Y) into the AC
		LOADSPX = 6,				//Load from (SP + X) into the AC
		STOREADDR = 7,				//Store the value in AC into the address specified
		GETRAND = 8,				//Gets a random int from 1 to 100 inclusive to the AC
		PUTPORT = 9,				//If port = 1, writes AC as an int to the screen
									//If port = 2, writes AC as a char to the screen

		ADDX = 10,					//Add the value in X to the AC
		ADDY = 11,					//Add the value in X to the AC
		SUBX = 12,					//Subtract the value in X from the AC
		SUBY = 13,					//Subtract the value in Y from the AC
		COPYTOX = 14,				//Copy the value in the AC to X
		COPYFROMX = 15,				//Copy the value in X to the AC
		COPYTOY = 16,				//Copy the value in the AC to Y
		COPYFROMY = 17,				//Copy the value in Y to the AC
		COPYTOSP = 18,				//Copy the value in AC to the SP
		COPYFROMSP = 19,			//Copy the value in SP to the AC

		JUMPADDR = 20,				//Jump to the address
		JUMPIFEQLADDR= 21,			//Jump to the address if the value in AC is equal to 0
		JUMPIFNOTEQUALADDR = 22,	//Jump to the address if the value in AC is not equal to 0
		CALLADDR = 23,				//Push return address onto stack, jump to address
		RET = 24,					//Pop return address from the stack, jump to the address
		INCX = 25,					//Increment the value in X
		DECX = 26,					//Decrement the value in X

		PUSH = 27,					//Push AC onto the stack
		POP = 28,					//Pop from stack into AC
		INTERRUPT = 29,					//Set system mode, switch stack, push SP and PC, set new SP and PC
		INTERRUPTRET = 30,					//Restore registersm set user mode
		END = 50					//End Executuion
	};

	CPU(int threshold = 5);			//default interrupt timer threshold
	void begin();					//start execution
	void execute(int inst);			//passes instruction to its specified handler

protected:
	int fetch();					//fetches at PC location
	int fetch(int addr);			//fetches instruction from memory process
	void write(int addr, int val);	//writes val to memory address
	void terminate();				//error termination


	//instruction handlers
	void loadVal(int val);
	void loadAddr(int addr);
	void loadIndAddr(int addr);
	void loadIdxXaddr(int addr);
	void loadIdxYAddr(int addr);
	void loadSpX();
	void storeAddr(int addr);
	void getRand();
	void putPort(int port);
	void addX();
	void addY();
	void subX();
	void subY();
	void copyToX();
	void copyFromX();
	void copyToY();
	void copyFromY();
	void copytoSp();
	void copyFromSp();
	void jumpAddr(int addr);
	void jumpIfEqlAddr(int addr);
	void jumpIfNotEqualAddr(int addr);
	void callAddr();
	void ret();
	void incX();
	void push();
	void pop();
	void interrupt(); 
	void interruptRet(); 
	void end();


private:
	int PC, SP, IR, AC, X, Y; //registers
	int InterruptTimerThreshold; //num instructions before interrupt 
	int lastInt; //num instructions since last interrupt occured.
};

#endif //CPU_H