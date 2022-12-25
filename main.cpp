#include "Command.h"
#include "CommandManager.h"
#include "Application.h"

void CommandTest() {
	//CommandPart parts[] = {RD, RS, RT};
	//int len = 3;
	//RCommand command(string("ADD"), 32, parts, len);

	CommandPart parts[] = { RS, RT, IMM };
	int len = 3;
	Command command("BEQ", 4, parts, len, R);

	int number[] = { 3, 4, 5 };
	command.input(number, len);
	cout << command.output(B) << endl;
	cout << command.output(H) << endl;
}

void OperatorTest() {
	CommandManager Operator("./Data.dat");
	Operator.open();

	// 插入指令
	CommandPart parts[] = { RS, RT, IMM };
	int len = 3;
	Command command("ADD", 4, parts, len, R);
	bool flag = Operator.addCommand(command);
	//cout << flag << endl;
	//cout << command.getName() << endl;
	//Operator.saveData();
	//Operator.loadData();

	// 读取指令
	Command command2 = Operator.getCommand("ADD");

	if (!command2.isEmpty()) {
		int number[] = { 3, 4, 5 };
		command2.input(number, len);
		cout << command2.output(B, true) << endl;
		cout << command2.output(H) << endl;
	}
	else {
		cout << "无指令" << endl;
	}

}

void AppTest() {
	Application a;
	a.exec();
}

int main() {
	OperatorTest();
	//AppTest();

	system("pause");
}