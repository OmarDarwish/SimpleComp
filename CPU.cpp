#include <iostream>
#include <string>
#include <limits>

#include "CPU.h"

using namespace std;

CPU::CPU(int threshold){
	InterruptTimerThreshold = threshold;
	PC = 0;
	SP = 0;
	IR = 0;
	AC = 0;
	X = 0;
	Y = 0;
	lastInt = 0;
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
	PC++;

	return IR;
}

void write(int addr, int val){
	cout << addr << " " << val << endl;
}

void CPU::execute(int inst){
	switch(inst){
		case LOADVAL:
			loadVal(inst);
			break;

		case LOADADDR:
			loadAddr(inst);
			break;

		case LOADINDADDR:
			loadIndAddr(inst);
			break;

		case LOADIDXXADDR:
			loadIdxXaddr(inst);
			break;

		case LOADIDXYADDR:
			loadIdxYAddr(inst);
			break;

		case LOADSPX:
			loadSpX();
			break;

		case STOREADDR:
			storeAddr(inst);
			break;

		case GETRAND:
			getRand();
			break;

		case PUTPORT:
			putPort(inst);
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
			copytoSp();
			break;

		case COPYFROMSP:
			copyFromSp();
			break;

		
		case CALLADDR:
			callAddr();
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
			interrupt();
			break;

		case INTERRUPTRET:		
			interruptRet();
			break;

		case END:		
			end();
			break;

		case JUMPADDR:			
			jumpAddr(inst);
			break;

		case JUMPIFEQLADDR:		
			jumpIfEqlAddr(inst);
			break;

		case JUMPIFNOTEQUALADDR:		
			jumpIfNotEqualAddr(inst);
			break;

		default:
			terminate();
			break;
	}
}

void CPU::loadVal(int val){

}

void CPU::loadAddr(int addr){

}

void CPU::loadIndAddr(int addr){

}

void CPU::loadIdxXaddr(int addr){

}

void CPU::loadIdxYAddr(int addr){

}

void CPU::loadSpX(){

}

void CPU::storeAddr(int addr){

}

void CPU::getRand(){

}

void CPU::putPort(int port){

}

void CPU::addX(){

}

void CPU::addY(){

}

void CPU::subX(){

}

void CPU::subY(){

}

void CPU::copyToX(){

}

void CPU::copyFromX(){

}

void CPU::copyToY(){

}

void CPU::copyFromY(){

}

void CPU::copytoSp(){

}

void CPU::copyFromSp(){

}

void CPU::jumpAddr(int addr){

}

void CPU::jumpIfEqlAddr(int addr){

}

void CPU::jumpIfNotEqualAddr(int addr){

}

void CPU::callAddr(){

}

void CPU::ret(){

}

void CPU::incX(){

}

void CPU::push(){

}

void CPU::pop(){

}

void CPU::interrupt(){

} 

void CPU::interruptRet(){

} 

void CPU::end(){

}

void CPU::terminate(){

}
