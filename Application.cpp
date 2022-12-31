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
	//int len = 15;

	for (int i = 0; i < operateNum; i++) {
		cout <<' ' << i << ". " << operateText((OperateType)i) << endl;
	}
	cout << "---------------" << endl;

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
	case ERASE:
		showEarseWindow();
		break;
	case MODIFY:
		showAddWindow(false);
		break;
	case SHOW:
		showShowWindow();
		break;
	case EXIT:
		exit(0);
		break;
	}

	//清屏
	system("pause");
	system("cls");

	showMainWindow();
}

void Application::showProgramWindow() {	
	cout << "> 请输入你的代码(输入$结束): " << endl;

	string name;
	vector<string> resultB, resultH;
	int index = 0;
	while (true) {
		// 只有输入的指令合法时 才会继续
		while (true) {
			cout << setfill('0') << setw(2) << index << ' ';
			cin >> name;
			if (name == "$") {
				break;
			}
			else if(!manager.isExist(name)) {

				continue;
			}

			break;
		}

		if (name == "$") {
			break;
		}
		

		Command command = manager.getCommand(name);
		command.input();
		resultB.push_back(command.output(B));
		resultH.push_back(command.output(H));

		index++;
	}

	int format = 0;
	cout << "> 请输入要编码的格式(二进制: 0/十六进制: 1): ";
	cin >> format;
	if (format) {
		for (int i = 0; i < resultH.size(); i++) {
			cout << resultH[i]<<' ';
			if ((i+1) % 8 == 0) {
				cout << endl;
			}
		}
		cout << endl;
	}
	else {
		for (int i = 0; i < resultB.size(); i++) {
			cout << resultB[i] << endl;
		}
		cout << endl;
	}

}

void Application::showAddWindow(bool add) {

	cout << "> 请输入指令名称: ";
	string name;
	cin >> name;

	if (manager.isExist(name)&&add) {
		cout << "[Error] 指令已存在, 不可重复添加! " << endl;
		return;
	}

	cout << "> 请输入指令类型(R/I): ";
	//CommandType type = CommandType (getchar() - 'A');
	
	char type;
	cin >> type;
	if (( type != 'R') && (type != 'I')) {
		cout << "[Error] 不存在这种指令类型! " << endl;
		return;
	}

	cout << "> 请输入指令对应编码(十进制): ";
	int code;
	cin >> code;

	Command command(name, code, type);

	// 添加指令字段名
	int n = 0, m;
	cout << "> 请输入指令的操作数数量: ";
	cin >> n;

	vector<string> parts;
	if (n) {
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
	}

	command.setParts(parts);
	manager.addCommand(command, add);
	if (add) {
		cout << "[Information] 添加 " + name + " 成功!" << endl;
	}
	else {
		cout << "[Information] 修改 " + name + " 成功!" << endl;
	}

	cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
}


void Application::showShowWindow() {
	const map<string, Command>& texts = manager.getData();
	int len = 7;
	cout << setiosflags(ios::left) << setfill(' ');
	cout << "┏━━━━━━━━┳━━━━━━━━━━━━━━━┳━━━━━━━━┓" << endl;
	cout << "┃ " << setw(len) << "Name";
	cout << "┃ " << setw(2 * len) << "Number";
	cout << "┃ " << setw(len) << "Type";
	cout << "┃" << endl;
	cout << "┣━━━━━━━━╋━━━━━━━━━━━━━━━╋━━━━━━━━┫" << endl;
	for (auto it = texts.begin(); it != texts.end(); it++) {
		cout << "┃ " << setw(len) << it->second.getName();
		cout << "┃ " << setw(2*len) << it->second.showCommand();
		cout << "┃ " << setw(len) << it->second.getTypeText();
		cout << "┃" << endl;
	}
	cout << "┗━━━━━━━━┻━━━━━━━━━━━━━━━┻━━━━━━━━┛" << endl;
}


void Application::showEarseWindow() {
	string name;
	cout << "> 请选择要删除的指令名: ";
	cin >> name;

	if (manager.findCommand(name)) {
		manager.earseCommand(name);
		cout << "[Information] 删除 " + name + " 成功" << endl;
	}
	else {
		cout << "[Error] 指令不存在, 无法删除" << endl;
	}
}

void Application::exec() {
	manager.open();
	this->showMainWindow();
}