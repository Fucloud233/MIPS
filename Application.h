#pragma once

#include "CommandManager.h"
enum OperateType {
	PROGRAM, TRANSLATE, ADD, MODIFY, ERASE, SHOW, EXIT
};

class Application
{
private:
	CommandManager manager;
	static int operateNum;
	string operateText(OperateType type);

	void executeOperate(OperateType type);

	void showProgramWindow();
	void showAddWindow(bool add = true);
	void showMainWindow();
	void showShowWindow();
	void showEarseWindow();
	void showTranslateWindow();

public:
	void exec();
};