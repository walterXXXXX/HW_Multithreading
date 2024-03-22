#include <iostream>
#include <vector>
#include <random>
#include <exception>
#include <future>

template<typename Iterator>
void findMin(Iterator begin, Iterator end, std::promise<Iterator> pr) {
	if (begin == end - 1) {
		pr.set_value(begin);
		return;
	}
	Iterator cur = begin;
	Iterator min = cur;
	while (cur != end) {
		if (*cur < *min)
			min = cur;
		cur++;
	}
	pr.set_value(min);
}

template<typename Iterator>
void mySort(Iterator begin, Iterator end) {
	if (begin == end)
		return;
	for (auto it = begin+1; it < end; it++) {
		std::promise<Iterator> promise;
		std::future<Iterator> future = promise.get_future();
		auto res = std::async(findMin<Iterator>, it, end, std::move(promise));
		auto min = future.get();
		if (*(it - 1) > *min)
			std::swap(*(it - 1), *min);
	}
}

int main() {
	setlocale(LC_ALL, "");

	// задаем вектор случайных элементов
	const size_t count = 50;
	std::vector<int> elements(count);
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(0, 100);
	for (auto& el : elements)
		el = dist(gen);

	// исходный вектор
	std::cout << "Исходный вектор:\n";
	for (const auto& el : elements) {
		std::cout << el << "\t";
	}
	std::cout << std::endl << std::endl;

	// сортировка
	mySort(elements.begin(), elements.end());

	// отсортированный вектор
	std::cout << "Отсортированный вектор:\n";
	for (const auto& el : elements) {
		std::cout << el << "\t";
	}
	std::cout << std::endl;

	return 0;
}