#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <windows.h>

using namespace std;

int main()
{
    int random_number;
    ofstream file, file2;
    time_t current_time;
    struct tm* timeinfo;
    int count = 0;

    while (true) {
        // Генерируем рандомное число от 0 до 100
        random_number = rand() % 101;

        // Получаем текущее время
        time(&current_time);
        timeinfo = localtime(&current_time);

        // Записываем значение в файл каждую секунду
        file.open("file.txt", ios::app);
        file << random_number << endl;
        file.close();

        // Записываем значение во второй файл каждую кратную(как кратную 2м) четную секунду 
        if (timeinfo->tm_sec % 2 == 0 && timeinfo->tm_sec != 0) {
            file2.open("file2.txt", ios::app);
            file2 << random_number << endl;
            file2.close();
        }

        // Удаляем данные из файла при достижении 10-ти значений 
        count++;
        if (count == 10) {
            remove("file.txt");
            count = 0;
        }

        // Задержка на 1 секунду
        Sleep(1000);
    }

    return 0;
}
// 1 файл удаляется, при заполнении 10ю значениями, а 2й заполняется постоянно. 1й файл постоянно пересоздаётся для новой записи значений.