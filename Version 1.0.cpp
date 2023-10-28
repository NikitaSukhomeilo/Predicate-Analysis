#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<conio.h>
using namespace std;

// this code should be moved
//
void display_splash_screen()
{
	cout << "[1] - Загрузить входной файл\n";
	cout << "[2] - Ввести название выходного файла и сохранить в него данные\n";
	cout << "[3] - Выйти из программы";
}
//
//

int main()
{
	char keyboard; // символ с клавиатуры для меню
	bool end_of_program = false; // показатель окончания работы с программой
	do
	{
		display_splash_screen();
		keyboard = _getch(); // считывание символа с клавиатуры
		switch (keyboard)
		{
			case '1': // выбрать входной файл
			{
			// вызвать функцию выбора входного файла
			// выполнить анализ текста на сказуемые
			}
			case '2': // сохранить данные в файл
			{
			// вызвать функцию, где пользователь вводит название файла
			// вызвать функцию, где происходит занесение информации по сказуемым
			// вывести диагностическое сообщение
			}
			case '3': // выйти из программы
			{
				end_of_program = true;
			}
		default:
			break;
		}


	} while (end_of_program == false);


}
