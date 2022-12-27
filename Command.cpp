#include "Command.h"
#include <string.h>
#include <cmath>
#include <algorithm>
#include <sstream>
#include <iomanip>

Command::Command() {
	strcpy_s(Name, "NULL");
	PartsNum = 0;
	isVaild = false;
}


Command::Command(const char* name, int command, const CommandPart* parts, int partsNum, CommandType type) {
	initial(string(name), command, type);

	// 转换为大写

	//for (int i = 0; i < strlen(Name); i++) {
	//	Name[i] &= 0x8F;
	//}

	// 记录可以输入块
	PartsNum = partsNum;
	for (int i = 0; i < PartsNum; i++) {
		Parts[i] = parts[i];
	}

	isVaild = true;
}

Command::Command(const char* name, int command, const CommandPart* parts, int len, char type)
	:Command(name, command, parts, len, Command::char2Type(type)) {
}

Command::Command(string name, int command, char type) {
	initial(name, command, char2Type(type));
}

Command::Command(string name, int command, CommandType type) {
	initial(name, command, type);
}


void Command::initial(string name, int command, CommandType type) {
	this->PartsNum = 0;

	strcpy_s(Name, name.c_str());

	// 初始化
	for (int i = 0; i < LengthsNum; i++) {
		Codes[i] = 0;
	}

	// R型指令构造
	if (type == R) {
		int arr[] = { 6, 5, 5, 5, 5, 6 };
		for (int i = 0; i < LengthsNum; i++) {
			Lengths[i] = arr[i];
		}

		// 输入初值
		Codes[0] = command;
	}
	// I型指令构造
	else if (type == I) {
		// 构造长度结构 注意: 留空 保留虚拟长度
		int arr[] = { 0, 0, 16, 5, 5, 6 };
		for (int i = 0; i < LengthsNum; i++) {
			Lengths[i] = arr[i];
		}

		// 输入初值
		Codes[LengthsNum - 1] = command;
	}

	isVaild = false;
}

CommandType Command::char2Type(char type) {
	switch (type) {
	case 'R':
		return CommandType::R;
	case 'I':
		return CommandType::I;
	case 'J':
		return CommandType::J;
	default:
		return CommandType::R;
	}
}

CommandPart Command::text2PartType(const string& text) {
	if (text == "RS") {
		return RS;
	}
	else if (text == "RT") {
		return RT;
	}
	else if (text == "RS") {
		return RS;
	}
	else if (text == "RT") {
		return RT;
	}
	else if (text == "RD") {
		return RD;
	}
	else if (text == "SHAMT") {
		return SHAMT;
	}
	else if (text == "IMM") {
		return IMM;
	}
	else {
		return INVALID;
	}
}

string Command::partType2text(CommandPart part) {
	switch (part) {
	case OP:
		return "OP";
	case RS:
		return "RS";
	case RT:
		return "RT";
	case RD:
		return "RD";
	case SHAMT:
		return "SHAMT";
	case FUNCT:
		return "FUNCT";
	case IMM:
		return "IMM";
	}
}

string Command::toString(TranslateMode mode) {
	unsigned long num = 0;
	for (int i = LengthsNum -1; i >=1 ; i--) {
		num += Codes[i];
		num <<= Lengths[i-1];
	}
	// 追加最后一个数
	num += Codes[0];

	// 转换进制
	int base, logBase;
	string text = "";

	if (mode == H) {
		base = 16;
		logBase = (int) log2(base);

		for (int i = 0; i < WORD_LENGTH / logBase; i++) {
			char n = num % base;
			if (n < 10) {
				n += '0';
			}
			else {
				n += 'A' - 10;
			}
			
			text.push_back(n);
			num >>= logBase;
		}
	}
	else if(mode == B) {
		base = 2;
		logBase = (int)log2(base);

		for (int i = 0; i < WORD_LENGTH  / logBase; i++) {
			text.push_back((num % 2) + '0');
			num >>= logBase;
		}

	}

	// 反转
	reverse(text.begin(), text.end());

	return text;
}


bool Command::setParts(vector<string> parts) {
	for (int i = 0; i < parts.size();i++) {
		CommandPart part = text2PartType(parts[i]);
		if (part == INVALID) {
			return false;
		}
		Parts[i] = part;
	}

	PartsNum = parts.size();
	isVaild = true;

	return true;
}

bool Command::input(int* number, int len) {
	if (len != PartsNum) {
		return false;
	}

	for (int i = 0; i < PartsNum; i++) {
		int index = (int)log2((int)Parts[i]);
		Codes[index] = number[i];
	}
}

bool Command::input() {
	int n;
	for (int i = 0; i < PartsNum; i++) {
		cin >> n;
		int index = (int)log2((int)Parts[i]);
		Codes[index] = n;
	}

	return true;
}

string Command::output(TranslateMode mode, bool divide) {
	int len = 4;
	string text = toString(mode);

	if (mode == B && divide) {
		int index = 0;
		for (int i = 0; i < LengthsNum; i++) {
			index += Lengths[i];
			text.insert(index++, 1, ' ');
		}
	}

	return text;
}

//string Command::getName() const{
//	return string(Name);
//}

string Command::getName() const {
	return string(Name);
}

bool Command::isEmpty() const {
	return Name=="NULL" || !PartsNum;
}

bool Command::isInvaild() const {
	bool flag = (PartsNum == 0);
	
	return flag || isEmpty();
}

string Command::showCommand() const {
	string text = Name;
	text += '\t';
	for (int i = 0; i < PartsNum; i++) {
		text += partType2text(Parts[i]) + ' ';
	}

	return text;
}