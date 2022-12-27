#pragma once

#include "CommandManager.h"
enum OperateType {
	PROGRAM, ADD, ERASE, MODIFY, SHOW, EXIT
};

class Application
{
private:
	CommandManager manager;
	static int operateNum;
	string operateText(OperateType type);


	void executeOperate(OperateType type);

	void showProgramWindow();
	void showAddWindow();
	void showMainWindow();
	void showShowWindow();
public:
	void exec();
};

