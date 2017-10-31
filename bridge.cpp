#include <iostream>
#include <memory>

#include "bridge.h"
#include "Singelon.h"
#include "neural.h"
#include "runner.h"
#include "factory.h"

void Bridge::setFactory(const std::shared_ptr<BaseFactory>& se) {
	personFactory_ = se;
}

void Runner::selectStrategy() {
	while (true) {
		std::cout << "请问老婆大人需要重新训练神经数据吗？(yes/no): ";
		std::string inputStr = "";
		std::cin >> inputStr;
		if (inputStr.find("yes") != std::string::npos) {
			std::shared_ptr<Neural> neural = Singelon<Neural>::instance();
			neural->trainToDates();
			break;
		}
		else if (inputStr.find("no") != std::string::npos) {
			std::shared_ptr<Neural> neural = Singelon<Neural>::instance();
			neural->readFileToDates();
			break;
		}
		else {
			std::cout << "老婆大人输入错误啦！" << std::endl;
		}
	}
}

void OnlineAndOfflineBridge::display() {
	std::cout << std::endl;
	std::cout << "=============online and offline started============" << std::endl;
}

void OnlineAndOfflineBridge::run() {
	display();
	std::shared_ptr<BaseService>service = personFactory_->accquireService();
	service->process();
	std::cout << "=============online and offline end============" << std::endl;
	std::cout << std::endl;
}

void OnlineBridge::display() {
	std::cout << std::endl;
	std::cout << "=============online start============" << std::endl;
}

void OnlineBridge::run() {
	display();
	std::shared_ptr<BaseService>service = personFactory_->accquireService();
	service->process();
	std::cout << "=============online end============" << std::endl;
	std::cout << std::endl;
}

void Runner::addBridge(const std::shared_ptr<Bridge>& br) {
	bridgeVec_.push_back(br);
}

void Runner::run() {
	selectStrategy();
	for (auto it : bridgeVec_) {
		it->run();
	}
}