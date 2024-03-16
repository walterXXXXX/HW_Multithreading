#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <map>
#include <random>
#include <algorithm>
#include <execution>
#include <condition_variable>
#include <conio.h>


using namespace std::chrono_literals;

std::once_flag flag;

void vecSum(std::vector<int>::const_iterator stVec1, 
			std::vector<int>::const_iterator stVec2,
			std::vector<int>::iterator resVec,
			int size) {
	std::call_once(flag, []() {
		std::cout << "Количество аппаратных ядер - " << std::thread::hardware_concurrency() << std::endl << std::endl;
		});
	for (int i = 0; i < size; i++) {
		*(resVec + i) = *(stVec1 + i) + *(stVec2 + i);
	}
}

double timeCalculate(const std::vector<int>& vec1, const std::vector<int>& vec2, int threadsCount) {
	if (vec1.size() != vec2.size())
		throw std::exception("Ошибка! Размеры векторов не совпадают");

	auto start = std::chrono::steady_clock::now();

	std::vector<int> result(vec1.size());
	std::vector<std::thread> threads;
	auto it1 = vec1.cbegin();
	auto it2 = vec2.cbegin();
	auto it3 = result.begin();
	int size = vec1.size() / threadsCount;

	for (int i = 0; i < threadsCount; i++) {
		if (i < threadsCount - 1) {
			threads.push_back(std::thread(vecSum, it1, it2, it3, size));
			it1 += size;
			it2 += size;
			it3 += size;
		}
		else {
			threads.push_back(std::thread(vecSum, it1, it2, it3, std::distance(it3, result.end())));
		}
	}
	for (auto& th : threads) {
		if (th.joinable())
			th.join();
	}

	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsedSeconds = end - start;
	return elapsedSeconds.count();
}

const int MAX_THREADS = 16;

int main() {
	setlocale(LC_ALL, "");

	std::mt19937 gen;
	std::uniform_int_distribution<int> dist(0, 1'000'000);

	std::map<int, std::vector<double>> resultsTable;

	int threadsCount = 1;

	while (threadsCount <= MAX_THREADS) {
		for (int i = 0; i < 4; i++) {
			int size = 1000 * pow (10, i);
			std::vector<int> vec1(size);
			std::vector<int> vec2(size);
			std::generate(std::execution::par, vec1.begin(), vec1.end(), [&]() {return dist(gen); });
			std::generate(std::execution::par, vec2.begin(), vec2.end(), [&]() {return dist(gen); });
			resultsTable[threadsCount].push_back(timeCalculate(vec1, vec2, threadsCount));
		}
		threadsCount *= 2;
	}

	std::cout.precision(7);
	std::cout << "\t\t1000\t\t10000\t\t100000\t\t1000000" << std::endl;
	for (const auto& pair : resultsTable) {
		std::cout << pair.first << " потоков\t";
		for (const auto& res : pair.second) {
			std::cout << res << "\t";
		}
		std::cout << std::endl;
	}

	std::cout << "\nДля выхода нажмите любую клавишу";
	_getch();

	return 0;
}