#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <conio.h>

using namespace std::chrono_literals;

//std::memory_order memOrder = std::memory_order::memory_order_relaxed;
std::memory_order memOrder = std::memory_order::memory_order_seq_cst;



std::atomic<int> clientCount = 0;
bool stopFlag = false;

void newClient(int maxClients) {
	while (!stopFlag) {
		std::this_thread::sleep_for(1s);
		if (clientCount.load(memOrder) < maxClients)
			clientCount.fetch_add(1, memOrder);
		std::cout << "Клиентов в очереди: " << clientCount.load(memOrder) << std::endl;
	}
}

void windowOperator() {
//	std::this_thread::sleep_for(50ms);
	while (!stopFlag) {
		std::this_thread::sleep_for(2s);
		if (clientCount.load(memOrder) > 0)
			clientCount.fetch_sub(1, memOrder);
		std::cout << "Клиентов в очереди: " << clientCount.load(memOrder) << std::endl;
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