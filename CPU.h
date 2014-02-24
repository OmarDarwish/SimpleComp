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
		LoadVal = 1,				//Load value into AC
		LoadAddr = 2,				//Load the value at the address into the AC
		LoadIndAddr = 3,			//Load the value from the address found in the address specified into AC
		LoadIdxXAddr = 4,			//Load the value at (address + X) into the AC
		LoadIdxYAddr = 5,			//Load the value at (address + Y) into the AC
		LoadSpX = 6,				//Load from (SP + X) into the AC
		StoreAddr = 7,				//Store the value in AC into the address specified
		GetRand = 8,				//Gets a random int from 1 to 100 inclusive to the AC
		PutPort = 9,				//If port = 1, writes AC as an int to the screen
									//If port = 2, writes AC as a char to the screen

		AddX = 10,					//Add the value in X to the AC
		AddY = 11,					//Add the value in X to the AC
		SubX = 12,					//Subtract the value in X from the AC
		SubY = 13,					//Subtract the value in Y from the AC
		CopyToX = 14,				//Copy the value in the AC to X
		CopyFromX = 15,				//Copy the value in X to the AC
		CopyToY = 16,				//Copy the value in the AC to Y
		CopyFromY = 17,				//Copy the value in Y to the AC
		CopyToSp = 18,				//Copy the value in AC to the SP
		CopyFromSp = 19,			//Copy the value in SP to the AC

		JumpAddr = 20,				//Jump to the address
		JumpIfEqlAddr= 21,			//Jump to the address if the value in AC is equal to 0
		JumpIfNotEqualAddr = 22,	//Jump to the address if the value in AC is not equal to 0
		CallAddr = 23,				//Push return address onto stack, jump to address
		Ret = 24,					//Pop return address from the stack, jump to the address
		IncX = 25,					//Increment the value in X
		DecX = 26,					//Decrement the value in X

		Push = 27,					//Push AC onto the stack
		Pop = 28,					//Pop from stack into AC
		Int = 29,					//Set system mode, switch stack, push SP and PC, set new SP and PC
		IRet = 30,					//Restore registersm set user mode
		End = 50					//End Executuion
	};

	CPU(int threshold = 5);			//default interrupt timer threshold
	void execute(int inst);			//passes instruction to its specified handler
	void execute(int inst, int arg); //passes instruction to its specified handler with arg

protected:
	int fetch();					//fetches instruction from memory process
	void terminate();				//error termination

	//instruction handlers
	void loadVal(int val);
	void loadAddr(int addr);
	void loadIndAddr(int addr);
	void loadIdxXaddr(int addr);
	void loadIdxYAddr(int addr);
	void loadSpX();
	void storeAddr(int addr);
	int getRand();
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
	void incY();
	void push();
	void pop();
	void interrupt(); 
	void interruptRet(); 
	void end();


private:
	int PC, SP, IR, AC, X, Y; //registers
	int InterruptTimerThreshold; //num instructions before interrupt 
	int InstrSinceLastInt; //num instructions since last interrupt occured.
};

#endif //CPU_H