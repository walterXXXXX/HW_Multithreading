#include <iostream>
#include <thread>
#include <chrono>
#include <conio.h>

using namespace std::chrono_literals;

int clientCount = 0;
bool stopFlag = false;

void newClient(int maxClients) {
	while (!stopFlag) {
		std::this_thread::sleep_for(1s);
		if (clientCount < maxClients) 
			clientCount++;
		std::cout << "Клиентов в очереди: " << clientCount << std::endl;
	}
}

void windowOperator() {
	std::this_thread::sleep_for(50ms);
	while (!stopFlag) {
		std::this_thread::sleep_for(2s);
		if (clientCount > 0) 
			clientCount--;
		std::cout << "Клиентов в очереди: " << clientCount << std::endl;
	}
}

int main() {
	setlocale(LC_ALL, "");

	std::cout << "Очередь клиентов. Для остановки программы нажмите любую клавишу" << std::endl;

	std::thread th1(newClient, 10);
	std::thread th2(windowOperator);

	_getch();
	stopFlag = true;

	if (th1.joinable())
		th1.join();
	if (th2.joinable())
		th2.join();

	return 0;
}