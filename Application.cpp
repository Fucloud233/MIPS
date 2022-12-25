#include "Application.h"

int Application::operateNum = 5;

string Application::operateText(OperateType type) {
	switch (type) {
	case ADD:
		return "添加指令";
	case ERASE:
		return "删除指令";
	case MODIFY:
		return "修改指令";
	case SHOW:
		return "显示指令";
	case EXIT:
		return "退出";
	}
}

void Application::showMainWindow() {
	cout << "> 请选择操作:" << endl;

	for (int i = 0; i < operateNum; i++) {
		cout <<' ' << i << ". " << operateText((OperateType)i) << endl;
	}

	// 获取指令
	int command = 0;
	cin >> command;
	if (command >= operateNum) {
		cout << "[警告] 输入了非法操作, 请重新输入!" << endl;
		system("pause");
		showMainWindow();
	}
	else {
		executeOperate((OperateType)command);
	}
}


void Application::executeOperate(OperateType type) {
	cin.ignore();

	switch (type) {
	case ADD:
		showaddWindow();
		break;
	//case ERASE:
	//case MODIFY:
	//case SHOW:
	//case EXIT:
	}
}

void Application::showaddWindow() {

	cout << "> 请输入指令类型(R/I): ";
	//CommandType type = CommandType (getchar() - 'A');
	char type = getchar();

	cout << "> 请输入指令名称: ";
	string name;
	cin >> name;

	cout << "> 请输入指令对应编码(十进制): ";
	int code;
	cin >> code;

	if (type == 'R') {

	}
	else if (type == 'I') {

	}

}


void Application::exec() {
	manager.open();
	this->showMainWindow();
}