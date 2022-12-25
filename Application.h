#pragma once

#include "CommandManager.h"
enum OperateType {
	ADD, ERASE, MODIFY, SHOW, EXIT
};

class Application
{
private:
	CommandManager manager;
	static int operateNum;
	string operateText(OperateType type);


	void executeOperate(OperateType type);
	void showaddWindow();
	void showMainWindow();
public:
	void exec();
};

