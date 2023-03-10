#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "Command.h"
using namespace std;

class CommandManager
{
private:
	string FileName;
	bool openFlag;
	fstream file;

	map<string, Command> data;

public:
	CommandManager(string fileName = "./Data.dat");
	~CommandManager();

	void open();
	void close();

	void saveData();
	void loadData();

	// 指令的增删改查
	vector<string> showAllCommand();
	bool findCommand(string name) const;
	bool addCommand(const Command& command, bool add = true);
	//bool modifyCommand(const Command& command);
	bool earseCommand(string name);


	map<string, Command> getData();
	Command getCommand(string name) const;

	bool isExist(string name);

};

