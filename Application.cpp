#include "Application.h"
#include <iomanip>
#include <limits>

int Application::operateNum = 6;

string Application::operateText(OperateType type) {
	switch (type) {
	case PROGRAM:
		return "编写指令";
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
	//cin.ignore();

	for (int i = 0; i < operateNum; i++) {
		cout <<' ' << i << ". " << operateText((OperateType)i) << endl;
	}

	// 获取执行操作
	int command = 0;
	cout << "> 请选择操作: ";
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

	switch (type) {
	case PROGRAM:
		showProgramWindow();
		break;
	case ADD:
		showAddWindow();
		break;
	//case ERASE:
	//case MODIFY:
	case SHOW:
		showShowWindow();
		break;
	case EXIT:
		exit(0);
		break;
	}

	showMainWindow();
}

void Application::showProgramWindow() {
	string name;
	
	int index = 0;
	while (true) {
		cout <<setfill('0') << setw(2) << index << ' ';
		cin >> name;
		if (name == "$") {
			break;
		}

		Command command = manager.getCommand(name);
		command.input();
		cout << command.output(B, true) << endl;

		index++;
	}
}

void Application::showAddWindow() {

	cout << "> 请输入指令类型(R/I): ";
	//CommandType type = CommandType (getchar() - 'A');
	char type;
	cin >> type;

	cout << "> 请输入指令名称: ";
	string name;
	cin >> name;

	cout << "> 请输入指令对应编码(十进制): ";
	int code;
	cin >> code;

	Command command(name, code, type);

	// 添加指令字段名
	int n = 0, m;
	cout << "> 请输入指令的操作数数量: ";
	cin >> n;

	vector<string> parts;
	cout << "> 请按顺序输入操作数类型";

	if (type == 'R') {
		cout << "(RS:0 RT:1 RD:2 SHAMT:3): ";

		for (int i = 0; i < n; i++) {
			cin >> m;
			
			bool flag = true;

			switch (m) {
			case 0:
				parts.push_back("RS");
				break;
			case 1:
				parts.push_back("RT");
				break;
			case 2:
				parts.push_back("RD");
				break;
			case 3:
				parts.push_back("SHAMT");
				break;
			default:
				flag = false;
			}

			// 如果输入错误
			if (!flag) {
				cout << "[Error] 输入错误! " << endl;
				break;
			}
		}
	}
	else if (type == 'I') {
		cout << "(RS:0 RT:1 IMM:2) : ";

		for (int i = 0; i < n; i++) {
			cin >> m;

			bool flag = true;

			switch (m) {
			case 0:
				parts.push_back("RS");
				break;
			case 1:
				parts.push_back("RT");
				break;
			case 2:
				parts.push_back("IMM");
				break;
			default:
				flag = false;
			}

			// 如果输入错误
			if (!flag) {
				cout << "[Error] 输入错误! " << endl;
				break;
			}
		}
	}

	command.setParts(parts);
	manager.addCommand(command);
	cout << "[Information] 添加 " + name + " 成功!" << endl;

	cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
}


void Application::showShowWindow() {
	const vector<string>& texts = manager.showAllCommand();
	for (auto it = texts.begin(); it != texts.end(); it++) {
		cout << *it << '\n';
	}
}


void Application::exec() {
	manager.open();
	this->showMainWindow();
}