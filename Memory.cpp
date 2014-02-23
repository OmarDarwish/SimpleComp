#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <unistd.h> //might be OS X specific

#include "Memory.h"
#include "Tokenizer.h"

using namespace std;

Memory::Memory(string fileName){
	MemVector = vector<int>(DEFAULT_MEM_SIZE, NO_INSTRUCTION); //init memory with default NO_INSTRUCTION
	loadFile(fileName);
}

void Memory::loadFile(string fileName){
	ifstream file(fileName.c_str(), std::ifstream::in);
	
	//check if file is ready for reading
	if(file.good()){
		string line;
		string tkn;
		Tokenizer tokenizer;
		int cursor = 0;

		//read all lines
		while(getline(file, line)){
			tokenizer.set(line);
			tkn = tokenizer.next();
			if(tkn == ".1000")
				cursor = 1000;
			else{
				MemVector[cursor] = atoi(tkn.c_str());
				cursor++;
			}
		}
		file.close();
	}else
		cout << "Could not open file " << fileName << endl;
}

void Memory::write(int data, int adr){
	MemVector[adr] = data;
}

 int Memory::read(int adr){
 	return MemVector.at(adr);
 }