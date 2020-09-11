#include <fstream>

#include "chip8.h"

const unsigned int START_ADDRESS = 0x200;
const unsigned int FONTSET_SIZE = 80;
const unsigned int FONTSET_START_ADDRESS = 0x50;

using namespace std;

//Character representation using 5 hex bytes
uint8_t fontset[FONTSET_SIZE] =
{
	0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
	0x20, 0x60, 0x20, 0x20, 0x70, // 1
	0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
	0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
	0x90, 0x90, 0xF0, 0x10, 0x10, // 4
	0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
	0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
	0xF0, 0x10, 0x20, 0x40, 0x40, // 7
	0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
	0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
	0xF0, 0x90, 0xF0, 0x90, 0x90, // A
	0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
	0xF0, 0x80, 0x80, 0x80, 0xF0, // C
	0xE0, 0x90, 0x90, 0x90, 0xE0, // D
	0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
	0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

Chip8::Chip8()
	: randGen(std::chrono::system_clock::now().time_since_epoch().count())
{
	//program counter used to hold address of next instruction
	pc = START_ADDRESS;

	//font goes into memory
	for (unsigned int i = 0;i < FONTSET_SIZE;i++)
	{
		memory[FONTSET_START_ADDRESS + i] = fontset[i];
	}

	randByte = uniform_int_distribution<uint8_t>(0, 255U);
}


void Chip8::loadROM(char const* filename)
{
	//ifstream opens file. ios::binary specifies to read it in binary, ate moves the file pointer to the end
	std::ifstream file(filename, ios::binary | ios::ate);

	if (file.is_open())
	{
		//tellg() returns current position of pointer
		streampos size = file.tellg();
		//buffer created to hold data
		char* buffer = new char[size];

		//ios::beg brings pointer to beginning of file
		file.seekg(0, ios::beg);
		file.read(buffer, size);
		file.close();

		//ROM content loading starting at 0x200
		for (long i = 0; i < size;++i)
		{
			memory[START_ADDRESS + i] = buffer[i];
		}

		//deallocation
		delete[] buffer;

	}
}

//CLS clear display by setting all memory bytes to 0.
void Chip8::op_00E0()
{
	memset(video, 0, sizeof(video));
}

//RET return from a subroutine. does so by going down stack
void Chip8::op_00EE()
{
	--sp;
	pc = stack[sp];
}

//JMP Jumps to address
void Chip8::op_1NNN()
{
	//u after hex is to set it as unsigned
	uint16_t address = opcode & 0x0FFFu;
	pc = address;
}

void Chip8::op_2NNN()
{

}


