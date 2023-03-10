#include "CommandManager.h"

CommandManager::CommandManager(string fileName) {
	this->FileName = fileName;
	openFlag = false;
}


CommandManager::~CommandManager() {
	this->close();
}

void CommandManager::open() {
	if (openFlag)
		return;

	loadData();
	openFlag = true;
}

void CommandManager::close() {
	if (!openFlag)
		return;

	saveData();
	openFlag = false;
}

void CommandManager::saveData() {
	file.open(FileName, ios::out | ios::binary);
	file.clear();
	for (auto it = data.begin(); it != data.end(); it++) {
		file.write((char*)&(it->second), sizeof(Command));
	}

	file.close();
}

void CommandManager::loadData() {
	file.open(FileName, ios::in | ios::binary);

	while (!file.eof()) {
		Command command;
		file.read((char*)&command, sizeof(Command));
		data.insert(pair<string, Command>(command.getName(), command));
	}
	
	data.erase("NULL");

	file.close();
}

map<string, Command> CommandManager::getData() {
	return data;
}

Command CommandManager::getCommand(string name) const {
	if (findCommand(name)) {
		return data.find(name)->second;
	}
	else {
		// 返回空指令 说明查找失败
		return Command();
	}
}

bool CommandManager::findCommand(string name) const {
	auto it = data.find(name);
	return it != data.end();
}

bool CommandManager::addCommand(const Command& command, bool add) {
	if (add) {
		if (findCommand(command.getName()) && add) {
			cerr << "[错误] 指令已存在, 不能重复添加! " << endl;
			return false;
		}
	}
	else {
		data.erase(command.getName());
	}

	data.insert({ command.getName(), command });
	saveData();
	return true;
}

//bool CommandManager::modifyCommand(const Command& command) {
//	if (findCommand(command.getName())) {
//		data.insert({ command.getName(), command });
//		return true;
//	}
//	else {
//		cerr << "[错误] 指令不存在, 不能修改! " << endl;
//		return false;
//	}
//}

bool CommandManager::earseCommand(string name) {
	if (findCommand(name)) {
		data.erase(name);
		return true;
	}
	else {
		cerr << "[错误] 指令不存在, 不能删除! " << endl;
		return false;
	}
}


vector<string> CommandManager::showAllCommand() {
	cout << "指令名" << '\t' << "操作数" << endl;

	vector<string> texts;
	for (auto it = data.begin(); it != data.end(); it++) {
		texts.push_back(it->second.showCommand());
	}

	return texts;
}


bool CommandManager::isExist(string name) {
	return data.find(name) != data.end();
}