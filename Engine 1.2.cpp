#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<Windows.h>
using namespace std;
void clear_substring_from_punctuation_marks(string& str) // функция очистки строки от знаков препинания
{
	ifstream reading_filestream("Punctuation_Symbols.txt"); // открытие файла со знаками пунктуации
	string file_iterator; // буферная строка
	getline(reading_filestream, file_iterator); // считать строку, состоящую из знаков препинания, из файла
	size_t position = 0;
	for (int i = 0; i < file_iterator.size(); i++) // пройтись по строке
	{
		do
		{
			position = str.find(file_iterator[i]); // поиск в строке знака препинания
			if (position != string::npos) // если найден знак препинания
			{
				str.erase(position, 1); // удалить его
			}
		} while (position != string::npos);
		position = 0;
	}
}
bool check_for_ending(const string& input_word, const string& filename)
{
	ifstream reading_filestream(filename);
	string file_iterator;
	while (getline(reading_filestream, file_iterator))
	{
		int position = input_word.find(file_iterator); // поиск окончания в слове
		if (position != string::npos)
		{
			int length_of_ending = file_iterator.size(); // длина окончания из файла
			if (input_word.size() - position == length_of_ending) // если в конце слова окончание
			{
				reading_filestream.close();
				return true;
			}
		}
		file_iterator.clear();
	}
	reading_filestream.close();
	return false;
}
int main()
{
	// вывод в консоль кириллицы
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "");

	string input_filename;
	cout << "Введите название входного файла: ";
	getline(cin, input_filename);

	ifstream reading_filestream(input_filename); // открыть исходный файл на чтение
	ofstream writing_filestream("temp.txt");
	string predicates[50]; // массив для найденных в предложении сказуемых

	int number_of_predicates = 0; // количество найденных сказуемых

	string file_iterator;
	stringstream buffer;
	while (getline(reading_filestream, file_iterator))
	{
		buffer << file_iterator; // занесение строки из файла в строковый поток
		file_iterator.clear();
		string word;
		while (buffer >> word) // пословное извлечение из строки
		{
			clear_substring_from_punctuation_marks(word);
			// составное именное
			// составное глагольное

			// глаголы
			if (word == "ел")
			{
				predicates[number_of_predicates++] = word;
				word.clear();
				continue;
			}
			if (word.size() < 2)
			{
				word.clear();
				continue;
			}
			if (word.size() > 2) // приблизительная минимальная длина глагола
			{
				if (check_for_ending(word, "First_Conjugation.txt") == true) // проверить на окончание первого спряжения
				{
					predicates[number_of_predicates++] = word;
					word.clear();
					continue;
				}
				if (check_for_ending(word, "Second_Conjugation.txt") == true) // проверить на окончание второго спряжения
				{
					predicates[number_of_predicates++] = word;
					word.clear();
					continue;
				}
				if (check_for_ending(word, "Reflexives.txt") == true) // проверить на окончание возвратного глагола
				{
					predicates[number_of_predicates++] = word;
					word.clear();
					continue;
				}
				if (check_for_ending(word, "Past_time.txt") == true) // проверить на окончание глагола прошедшего времени
				{
					predicates[number_of_predicates++] = word;
					word.clear();
					continue;
				}
				if(check_for_ending(word, "Imperative_Mood.txt") == true) // проверить на окончание глаголов повелительного наклонения
				{
					predicates[number_of_predicates++] = word;
					word.clear();
					continue;
				}
				if (check_for_ending(word, "First_Person.txt") == true) // проверить на окончание глаголов первого лица
				{
					predicates[number_of_predicates++] = word;
					word.clear();
					continue;
				}
			}
		}
		buffer.clear();
		for (int i = 0; i < number_of_predicates; i++) // запись в файл элементов массива
		{
			writing_filestream << predicates[i];
			if (i != number_of_predicates)
			{
				writing_filestream << endl;
			}
		}
		number_of_predicates = 0;
	}
	writing_filestream.close();
	reading_filestream.close();
	return 0;
}