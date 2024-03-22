#include <iostream>
#include <vector>
#include <random>
#include <exception>
#include <future>
#include <mutex>

// фукцния заполнения случайными целыми значениями из диапазона [min; max]
template<typename Iterator>
void randomEach(Iterator first, Iterator last) {
	const int min = 0;
	const int max = 1'000'000;
	std::random_device rd;
	std::mt19937 gen{ rd() };
	std::uniform_int_distribution<> dis(min, max);
	for (auto& it = first; it < last; it++) {
		*it = dis(gen);
	}
}

// функция вывода не печать
template<typename Iterator>
void printEach(Iterator first, Iterator last) {
	for (auto& it = first; it < last; it++) {
		std::cout << *it << "\t";
	}
}

// функция извлечения квадратного корня
template<typename Iterator>
void sqrtEach(Iterator first, Iterator last) {
	for (auto& it = first; it < last; it++) {
		if (*it < 0)
			throw (std::exception("Ошибка извлечения корня из отрицательного числа"));
		*it = std::sqrt(*it);
	}
}

template<typename Iterator, typename Function>
void para_for_each(Iterator first, Iterator last, Function func, std::launch launchType = std::launch::async) {
	const size_t size = 25;
	auto length = std::distance(first, last);
	if (length <= size) {
		func(first, last);
		return;
	}
	std::vector<int>::iterator mid = first;
	std::advance(mid, length / 2);
	std::future<void> ft = std::async(launchType, func, first, mid);
	if (launchType == std::launch::deferred)
		ft.wait();
	func(mid, last);
} 


int main() {
	setlocale(LC_ALL, "");

	std::vector<int> vec(100);
	para_for_each(vec.begin(), vec.end(), randomEach<std::vector<int>::iterator>);
	para_for_each(vec.begin(), vec.end(), printEach<std::vector<int>::iterator>, std::launch::deferred);
	std::cout << "\n\n";

	para_for_each(vec.begin(), vec.end(), sqrtEach<std::vector<int>::iterator>);
	para_for_each(vec.begin(), vec.end(), printEach<std::vector<int>::iterator>, std::launch::deferred);
	std::cout << "\n\n";

	para_for_each(vec.begin(), vec.end(), [](auto first, auto last) {
		for (auto& it = first; it < last; it++) 
			(*it)++; 
		});

	para_for_each(vec.begin(), vec.end(), printEach<std::vector<int>::iterator>, std::launch::deferred);
	std::cout << "\n\n";

	return 0;
}

