#include <fstream>
#include "chip8.h"

const unsigned int START_ADDRESS = 0x200;

using namespace std;

void Chip8::loadROM(char const* filename)
{
	std::ifstream file(filename, ios::binary | ios::ate);

	if (file.is_open())
	{
		streampos size = file.tellg();
		char* buffer = new char[size];

		file.seekg(0, ios::beg);
		file.read(buffer, size);
		file.close();

		for (long i = 0; i < size;++i)
		{
			memory[START_ADDRESS + i] = buffer[i];
		}

		delete[] buffer;

	}
}

Chip8::Chip8()
{
	pc = START_ADDRESS;
}