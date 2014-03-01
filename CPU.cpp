#include <iostream>
#include <string>
#include <limits>
#include <cstdlib>

#include "CPU.h"

using namespace std;

CPU::CPU(int threshold){
	interruptTimerThreshold = threshold;
	PC = 0;
	SP = 1000;
	IR = 0;
	AC = 0;
	X = 0;
	Y = 0;
	lastInt = 0;
	userSP = 1000;
	mode = USER;

}
void CPU::begin(){
	while(PC < 1000){
		int inst = fetch(PC);
		execute(inst);
		PC++;
	}
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
	int arg;
	switch(inst){
		case LOADVAL:
			PC++;
			arg = fetch(PC);
			loadVal(arg);
			break;

		case LOADADDR:
			PC++;
			arg = fetch(PC);
			loadAddr(arg);
			break;

		case LOADINDADDR:
			PC++;
			arg = fetch(PC);
			loadIndAddr(arg);
			break;

		case LOADIDXXADDR:
			PC++;
			arg = fetch(PC);
			loadIdxXaddr(arg);
			break;

		case LOADIDXYADDR:
			PC++;
			arg = fetch(PC);
			loadIdxYAddr(arg);
			break;

		case LOADSPX:
			loadSpX();
			break;

		case STOREADDR:
			PC++;
			arg = fetch(PC);
			storeAddr(arg);
			break;

		case GETRAND:
			getRand();
			break;

		case PUTPORT:
			PC++;
			arg = fetch(PC);
			putPort(arg);
			break;

		case ADDX:
			addX();
			break;

		case ADDY:
			addY();
			break;

		case SUBX:
			subX();
			break;

		case SUBY:
			subY();
			break;

		case COPYTOX:
			copyToX();
			break;

		case COPYFROMX:
			copyFromX();
			break;

		case COPYTOY:
			copyToY();
			break;

		case COPYFROMY:
			copyFromY();
			break;

		case COPYTOSP:
			copyToSp();
			break;

		case COPYFROMSP:
			copyFromSp();
			break;

		
		case CALLADDR:
			PC++;
			arg = fetch(PC);
			callAddr(arg);
			break;

		case RET:
			ret();
			break;

		case INCX:
			incX();
			break;

		case PUSH:
			push();
			break;

		case POP:
			pop();
			break;

		case INTERRUPT:			
			interrupt(SYSINT);
			break;

		case INTERRUPTRET:		
			interruptRet();
			break;

		case END:		
			end();
			break;

		case JUMPADDR:			
			arg = fetch(PC);
			jumpAddr(arg);
			break;

		case JUMPIFEQLADDR:		
			PC++;
			arg = fetch(PC);
			jumpIfEqlAddr(arg);
			break;

		case JUMPIFNOTEQUALADDR:		
			PC++;
			arg = fetch(PC);
			jumpIfNotEqualAddr(arg);
			break;

		default:
			terminate(inst);
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

void CPU::callAddr(int addr){
	SP--;
	write(SP, PC); //save PC to stack;
	jumpAddr(addr);
}

void CPU::ret(){	
	jumpAddr(fetch(SP));
	SP++;
}

void CPU::incX(){
	X++;
}

void CPU::push(){
	SP--;
	write(SP, AC);
}

void CPU::pop(){
	AC = fetch(SP);
	SP++;
}

void CPU::interrupt(int type){
	int userSP = SP;
	mode = KERNEL;
	
	SP = 1999;
	write(SP, userSP); //push user SP
	SP--;
	write(SP, PC); //push PC

	if(type = TIMER)
		PC = 1000;
	else if (type = SYSINT)
		PC = 1500;
} 

void CPU::interruptRet(){
	PC = fetch(SP);
	SP++;
	SP = fetch(SP);

	mode = USER;
} 

void CPU::end(){
	//end executuion by going to end of memory
	PC = 1000;
}

void CPU::terminate(int inst){
	dprintf(DISPLAY_OUTPUT_FDS, "Fatal error, unsupported inst: %d", inst);
}
