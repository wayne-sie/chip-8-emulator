#pragma once

#include <cstdint>
#include <chrono>
#include <random>

class Chip8
{

public:
	uint8_t registers[16];
	uint8_t memory[4096];
	uint16_t index;
	uint16_t pc;
	uint16_t stack[16];
	uint8_t sp;
	uint8_t delayTimer;
	uint8_t soundTimer;
	uint32_t video[64 * 32];
	uint16_t opcode;
	void loadROM(char const* filename);
	
	std::default_random_engine randGen;
	std::uniform_int_distribution<uint8_t> randByte;

private:

	void op_6XNN();
	void op_8XY0();
	void op_7XNN();
	void op_8XY4();
	void op_8XY5();
	void op_8XY7();
	void op_8XY2();
	void op_8XY1();
	void op_8XY3();
	void op_8XY6();
	void op_8XYE();
	void op_CXNN();
	void op_1NNN();
	void op_BNNN();
	void op_2NNN();
	void op_00EE();
	void op_0NNN();
	void op_3XNN();
	void op_5XY0();
	void op_4XNN();
	void op_9XY0();
	void op_FX15();
	void op_FX07();
	void op_FX18();
	void op_FX0A();
	void op_EX9E();
	void op_EXA1();
	void op_ANNN();
	void op_FX1E();
	void op_DXYN();
	void op_00E0();
	void op_FX29();
	void op_FX33();
	void op_FX55();
	void op_FX65();

};