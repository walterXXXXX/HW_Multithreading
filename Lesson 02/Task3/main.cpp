#include <iostream>
#include <thread>
#include <mutex>

struct Data {
    std::mutex m;
    int field1;
    bool field2;
    Data(int f1, bool f2) : field1(f1), field2(f2) {}
};

void swap1(Data& d1, Data& d2) {
    if (&d1 == &d2)
        return;
    std::lock(d1.m, d2.m);
    std::lock_guard<std::mutex> l1(d1.m, std::adopt_lock);
    std::lock_guard<std::mutex> l2(d2.m, std::adopt_lock);
    std::swap(d1.field1, d2.field1);
    std::swap(d1.field2, d2.field2);
}

void swap2(Data& d1, Data& d2) {
    if (&d1 == &d2)
        return;
    std::scoped_lock(d1.m, d2.m);
    std::swap(d1.field1, d2.field1);
    std::swap(d1.field2, d2.field2);
}

void swap3(Data& d1, Data& d2) {
    if (&d1 == &d2)
        return;
    std::unique_lock l1(d1.m, std::defer_lock);
    std::unique_lock l2(d2.m, std::defer_lock);
    std::lock(l1, l2);
    std::swap(d1.field1, d2.field1);
    std::swap(d1.field2, d2.field2);
}

int main() {
    setlocale(LC_ALL, "");
    Data d1(1, true);
    Data d2(2, false);

    std::cout << "Исходные значения:\n";
    std::cout << "d1.field1 = " << d1.field1 << " d1.field2 = " << d1.field2 << std::endl;
    std::cout << "d2.field1 = " << d2.field1 << " d2.field2 = " << d2.field2 << std::endl << std::endl;

    swap1(d1, d2);
    std::cout << "1й swap с применением std::lock. Результат:\n";
    std::cout << "d1.field1 = " << d1.field1 << " d1.field2 = " << d1.field2 << std::endl;
    std::cout << "d2.field1 = " << d2.field1 << " d2.field2 = " << d2.field2 << std::endl << std::endl;
    
    swap2(d1, d2);
    std::cout << "2й swap с применением std::scoped_lock. Результат:\n";
    std::cout << "d1.field1 = " << d1.field1 << " d1.field2 = " << d1.field2 << std::endl;
    std::cout << "d2.field1 = " << d2.field1 << " d2.field2 = " << d2.field2 << std::endl << std::endl;

    swap3(d1, d2);
    std::cout << "3й swap с применением std::unique_lock. Результат:\n";
    std::cout << "d1.field1 = " << d1.field1 << " d1.field2 = " << d1.field2 << std::endl;
    std::cout << "d2.field1 = " << d2.field1 << " d2.field2 = " << d2.field2 << std::endl << std::endl;

    return 0;
}