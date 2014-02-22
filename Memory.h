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

class Memory{

public:
	Memory(string fileName = "pgm.txt"); //memory initialized with contents from this file

	void loadFile(string fileName);
	void write(int data, int adr);
	int &read(int addr);
protected:
	std::vector<int> MemVector; //vector to hold instructions

private:
	int  & operator [](int i); //set

};

#endif //MEMORY_H