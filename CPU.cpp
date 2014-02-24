#include <iostream>
#include <string>
#include <limits>
#include <cstdlib>

#include "CPU.h"

using namespace std;

CPU::CPU(int threshold){
	interruptTimerThreshold = threshold;
	PC = 0;
	SP = 0;
	IR = 0;
	AC = 0;
	X = 0;
	Y = 0;
	lastInt = 0;
	kernelSP = 1999;
	mode = USER;

}

int CPU::fetch(){
	return fetch(PC);
}

int CPU::fetch(int addr){
	//clear out all other input
	cin.ignore(numeric_limits<streamsize>::max());
	//write to stdout the addr that needs be retrieved
	cout << addr << endl;
	
	//wait until memory responds to stdin
	cin >> IR;

	return IR;
}

void CPU::write(int addr, int val){
	cout << addr << " " << val << endl;
}

void CPU::execute(int inst){
	switch(inst){
		case LOADVAL:
			PC++;
			loadVal(inst);
			break;

		case LOADADDR:
			PC++;
			loadAddr(inst);
			break;

		case LOADINDADDR:
			PC++;
			loadIndAddr(inst);
			break;

		case LOADIDXXADDR:
			PC++;
			loadIdxXaddr(inst);
			break;

		case LOADIDXYADDR:
			PC++;
			loadIdxYAddr(inst);
			break;

		case LOADSPX:
			PC++;
			loadSpX();
			break;

		case STOREADDR:
			PC++;
			storeAddr(inst);
			break;

		case GETRAND:
			PC++;
			getRand();
			break;

		case PUTPORT:
			PC++;
			putPort(inst);
			break;

		case ADDX:
			PC++;
			addX();
			break;

		case ADDY:
			PC++;
			addY();
			break;

		case SUBX:
			PC++;
			subX();
			break;

		case SUBY:
			PC++;
			subY();
			break;

		case COPYTOX:
			PC++;
			copyToX();
			break;

		case COPYFROMX:
			PC++;
			copyFromX();
			break;

		case COPYTOY:
			PC++;
			copyToY();
			break;

		case COPYFROMY:
			PC++;
			copyFromY();
			break;

		case COPYTOSP:
			PC++;
			copyToSp();
			break;

		case COPYFROMSP:
			PC++;
			copyFromSp();
			break;

		
		case CALLADDR:
			PC++;
			callAddr();
			break;

		case RET:
			PC++;
			ret();
			break;

		case INCX:
			PC++;
			incX();
			break;

		case PUSH:
			PC++;
			push();
			break;

		case POP:
			PC++;
			pop();
			break;

		case INTERRUPT:			
			PC++;
			interrupt(SYSINT);
			break;

		case INTERRUPTRET:		
			PC++;
			interruptRet();
			break;

		case END:		
			PC++;
			end();
			break;

		case JUMPADDR:			
			PC++;
			jumpAddr(inst);
			break;

		case JUMPIFEQLADDR:		
			PC++;
			jumpIfEqlAddr(inst);
			break;

		case JUMPIFNOTEQUALADDR:		
			PC++;
			jumpIfNotEqualAddr(inst);
			break;

		default:
			terminate();
			break;
	}
}

void CPU::loadVal(int val){
	AC = val;
}

void CPU::loadAddr(int addr){
	int val = fetch(addr);
	AC = val;
}

void CPU::loadIndAddr(int addr){
	int tempAddr = fetch(addr);
	int val = fetch(tempAddr);
	AC = val;
}

void CPU::loadIdxXaddr(int addr){
	int tempAddr = addr + X;
	int val = fetch(tempAddr);
	AC = val;
}

void CPU::loadIdxYAddr(int addr){
	int tempAddr = addr + Y;
	int val = fetch(tempAddr);
	AC = val;
}

void CPU::loadSpX(){
	int val = SP + X;
	AC = val;
}

void CPU::storeAddr(int addr){
	write(addr, AC);
}

void CPU::getRand(){
	int val = (rand() % 100) + 1;
	AC = val;
}

void CPU::putPort(int port){
	if(port == 1){
		dprintf(DISPLAY_OUTPUT_FDS, "%d", AC);
	}
	else if(port == 2){
		dprintf(DISPLAY_OUTPUT_FDS, "%c", AC);
	}
}

void CPU::addX(){
	AC += X;
}

void CPU::addY(){
	AC += Y;
}

void CPU::subX(){
	AC -= X;
}

void CPU::subY(){
	AC -= Y;
}

void CPU::copyToX(){
	X = AC;
}

void CPU::copyFromX(){
	AC = X;
}

void CPU::copyToY(){
	Y = AC;
}

void CPU::copyFromY(){
	AC = Y;
}

void CPU::copyToSp(){
	SP = AC;
}

void CPU::copyFromSp(){
	AC = SP;
}

void CPU::jumpAddr(int addr){
	PC = addr;
}

void CPU::jumpIfEqlAddr(int addr){
	if(AC == 0) PC = addr;
}

void CPU::jumpIfNotEqualAddr(int addr){
	if(AC != 0) PC = addr;
}

void CPU::callAddr(){
	write(SP, PC); //save PC to stack;
	SP--; 
}

void CPU::ret(){
	 SP++;
	 jumpAddr(fetch(SP));
}

void CPU::incX(){
	X++;
}

void CPU::push(){
	write(SP, AC);
	SP--;
}

void CPU::pop(){
	SP++;
	AC = fetch(SP);
}

void CPU::interrupt(int type){
	int userSP = SP;
	mode = KERNEL;
	
	SP = 1999;
	write(SP, userSP); //push user SP
	SP--;
	write(SP, PC); //push

	if(type = TIMER)
		PC = 1000;
	else if (type = SYSINT)
		PC = 1500;
} 

void CPU::interruptRet(){
	SP++;
	PC = fetch(PC);
	SP++;
	SP = fetch(SP);

	mode = USER;
} 

void CPU::end(){

}

void CPU::terminate(){

}
