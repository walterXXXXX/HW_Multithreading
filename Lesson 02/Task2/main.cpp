#include <iostream>
#include <chrono>
#include <random>
#include <thread>
#include <mutex>
#include <vector>
#include <Windows.h>

using namespace std::chrono_literals;

void calcultaion(bool& exception) { // внешняя функция имитации расчета
    std::this_thread::sleep_for(200ms);
    const u_int chance = 10; // шанс выбрасывания исключения при ошибке расчета в процентах
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 100);
    exception = (dist(gen) <= chance); // exception = 1 - означает ошибку расчета
}

class CalcuationControl {
public:
    CalcuationControl(int countThreads, int countCalcs) {
        handle = GetStdHandle(STD_OUTPUT_HANDLE);
        _countThreads = countThreads;
        for (int i = 0; i < _countThreads; i++) {
            threads.push_back(std::thread(&CalcuationControl::calcThread, this, countCalcs, i));
        }
    }

    ~CalcuationControl() {
        for (int i = 0; i < _countThreads; i++) {
            if (threads[i].joinable())
                threads[i].join();
        }
        COORD coord = { 0, _countThreads + 1 };
        SetConsoleCursorPosition(handle, coord);
    }

private:
    int _countThreads;
    std::vector<std::thread> threads;
    std::mutex mt;
    std::once_flag onceFlag;
    HANDLE handle;
    
    void calcThread(int countCalcs, int numThread) {
        // захватываем поток вывода и выводим начальную информацию о потоке
        std::unique_lock<std::mutex> lk(mt);
        COORD coord = { 0, 0 };
        CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
       
        std::call_once(onceFlag, [&]() {
            std::cout << "#\t" << "id\t";
            GetConsoleScreenBufferInfo(handle, &bufferInfo);
            coord = bufferInfo.dwCursorPosition;
            int shift = 0;
            if (countCalcs > 12)
                shift = countCalcs - 12;
            coord.X += shift / 2;
            SetConsoleCursorPosition(handle, coord);
            std::cout << "Progress bar";
            coord.X += (13 + (shift - shift / 2));
            SetConsoleCursorPosition(handle, coord);
            std::cout << "Time";
            });
        
        coord.X = 0;
        coord.Y = numThread+1; 
        SetConsoleCursorPosition(handle, coord);
        std::cout << numThread << "\t" << std::this_thread::get_id() << "\t";

        // запоминаем получившиеся координаты курсора
        
        GetConsoleScreenBufferInfo(handle, &bufferInfo);
        coord = bufferInfo.dwCursorPosition;
        lk.unlock();
        
        // запускаем поток расчетов и выводим прогресс
        auto start = std::chrono::steady_clock::now();
        for (int i = 0; i < countCalcs; i++) {
            bool exception;
            calcultaion(exception);
            // в зависимости от корректности выполненного расчета (exception) выводим белый или красный прямоугольник
            lk.lock();
            SetConsoleCursorPosition(handle, coord);
            if (!exception) { // исключения нет - белый прямоугольник
                SetConsoleTextAttribute(handle, ((15 << 4) | 15));
                std::cout << " ";
                SetConsoleTextAttribute(handle, ((0 << 4) | 15));
            }
            else { // иначе - красный
                SetConsoleTextAttribute(handle, ((4 << 4) | 4));
                std::cout << " ";
                SetConsoleTextAttribute(handle, ((0 << 4) | 15));
            }
            coord.X++;
            lk.unlock();
        }
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsedSecons = end - start;
        // по окончанию выводим полное время работы потока
        lk.lock();
        coord.X++;
        if (countCalcs < 12)
            coord.X += 12 - countCalcs;
        SetConsoleCursorPosition(handle, coord);
        std::cout << elapsedSecons.count(); 
    }
};


int main() {
    setlocale(LC_ALL, "");

    const u_int countTreads = 15; // кол-во потоков
    const u_int countCalcs = 17; // кол-во расчетов

    CalcuationControl calcControl(countTreads, countCalcs);

    return 0;
}