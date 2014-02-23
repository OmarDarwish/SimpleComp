/* Memory class that stores integers
 * Author: Omar Darwish
 * CS 4348
 * 02/18/2014
*/
#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;
const int DEFAULT_MEM_SIZE = 2000;
const int NO_INSTRUCTION = -1;

class Memory{

public:
	Memory(string fileName = "pgm.txt"); //memory initialized with contents from this file

	void loadFile(string fileName); //load file into memory
	void write(int data, int adr); //write to mem address
	int read(int addr); //read memory address

protected:
	

private:
	std::vector<int> MemVector; //vector to hold instructions
};

#endif //MEMORY_H