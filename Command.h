#pragma once

#include <string>
#include <map>
#include <vector>
#include <iostream>
using namespace std;

enum CommandPart {
	INVALID = 0x0,
	OP = 0x20, 
	RS = 0x10,
	RT = 0x8,
	RD = 0x4,
	SHAMT = 0x2,
	FUNCT = 0x1,
	IMM= 0x7
};

enum TranslateMode {
	B, H
};

enum CommandType {
	R, I, J
};

#define PATH_LEN 7
#define WORD_LENGTH 32
#define NAME_LEN 8

#define Long 


const int LengthsNum = 6;

class Command
{
private:
	// 将数字转换为其他进制
	string toString(TranslateMode mode);

protected:
	char Name[NAME_LEN];
	CommandType commandType;
	bool isVaild;

	// 存储可以输入操作数
	int PartsNum;
	CommandPart Parts[LengthsNum];

	int Lengths[LengthsNum];
	int Codes[LengthsNum];

	// 辅助函数
	static CommandType char2Type(char type);
	static char type2Char(CommandType type);
	static CommandPart text2PartType(const string& text);
	static string partType2text(CommandPart part);

	// 初始化函数 设置指令的类型 和 指令的OP/Func
	void initial(string name, int command, CommandType type);
public:
	Command();
	//Command(const char* name, int command, const vector<CommandPart>& parts, CommandType type = CommandType::R);
	Command(const char* name, int command, const CommandPart* parts, int len, CommandType type = CommandType::R);
	Command(const char* name, int command, const CommandPart* parts, int len, char type = 'R');
	Command(string name, int command, char type = 'R');
	Command(string name, int command, CommandType type = CommandType::R);

	bool setParts(vector<string> parts);

	bool input(int* number, int len);
	bool input(const vector<int>& number);
	bool input();
	string output(TranslateMode mode = H, bool divide = false);

	//string getName() const;
	string getName() const;
	string showCommand() const;
	char getTypeText() const;

	int getPartsNum() const;

	bool isEmpty() const;
	bool isInvaild() const;
	
	//istream operator>>(istream in, string)
};

