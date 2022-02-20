#include "includes.h"

int main() {
	std::string cmd = "";
	std::thread listener = std::thread([&]() {
		while (true) {
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
			if (GetAsyncKeyState(VK_INSERT) & 1) {
				Injector::OpenAndInject();
			}
		}
	});
	while (true) {
		std::cin >> cmd;	
		if (cmd == "i")
			Injector::OpenAndInject();
	}
	return 0;
}