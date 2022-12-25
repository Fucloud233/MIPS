#pragma once

#include <string>
#include <map>
#include <vector>
#include <iostream>
using namespace std;

enum CommandPart{
	OP = 0x20, 
	RS = 0x10,
	RT = 0x8,
	RD = 0x4,
	SHAMT = 0x2,
	FUNCT = 0x1,
	IMM= 0xF
};

enum TranslateMode {
	B, H
};

enum CommandType {
	inValid, R, I, J
};

#define PATH_LEN 7
#define WORD_LENGTH 32
#define NAME_LEN 6

#define Long 

class Command
{
private:
	// 将数字转换为其他进制
	string toString(TranslateMode mode);

protected:
	char Name[NAME_LEN];

	// 存储可以输入操作数
	static const int LengthsNum = 6;
	int PartsNum;
	CommandPart Parts[LengthsNum];
	int Lengths[LengthsNum];
	int Codes[LengthsNum];

public:
	Command();
	//Command(const char* name, int command, const vector<CommandPart>& parts, CommandType type = CommandType::R);
	Command(const char* name, int command, const CommandPart* parts, int len, CommandType type = CommandType::R);
	Command(const char* name, int command, const CommandPart* parts, int len, char type = 'R');

	static CommandType char2Type(char type);

	bool input(int* number, int len);
	string output(TranslateMode mode, bool divide = false);

	//string getName() const;
	string getName() const;

	bool isEmpty() const;
};

