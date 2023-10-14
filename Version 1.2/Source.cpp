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
	reading_filestream.close();
}
bool check_for_ending(const string& input_word, const string& filename) // функция проверки слова на окончания глаголов
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
bool check_for_suitable(const string& input_word, const string& filename) // функция исключения частей речи с похожими признаками
{
	// преобразование к одному регистру слов
	string temp = input_word;
	if (input_word[0] > 191 && input_word[0] < 224)
	{
		temp[0] += 32;
	}
	ifstream reading_filestream(filename); // открыть файл с глаголами с этим признаком
	string file_iterator;
	while (getline(reading_filestream, file_iterator))
	{
		if (file_iterator == temp) // если найден глагол в файле
		{
			reading_filestream.close();
			return true;
		}
	}
	reading_filestream.close();
	return false;
}
bool check_for_part(const string& input_word, const string& filename) // проверка на окончание слова с -ся
{
	ifstream reading_filestream(filename);
	string file_iterator;
	while (getline(reading_filestream, file_iterator))
	{
		int position = input_word.rfind(file_iterator);
		if (position != string::npos)
		{
			int length_of_ending = file_iterator.size();
			if (input_word.size() - 2 - position == length_of_ending) // если перед постфиксом -ся есть окончание причастия
			{
				reading_filestream.close();
				return true;
			}
		}
		file_iterator.clear();
	}
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
	string t = "Temporary.txt";
	string tt = "temp.txt";
	ofstream writing_filestream(tt);
	string predicates[500]; // массив для найденных в предложении сказуемых

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
			if (word.size() == false)
			{
				continue;
			}
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
				if (check_for_ending(word, "Imperative_Mood.txt") == true) // проверить на окончание глаголов повелительного наклонения
				{
					predicates[number_of_predicates++] = word;
					word.clear();
					continue;
				}
				if (check_for_ending(word, "First_Person.txt") == true) // проверить на окончание глаголов первого лица
				{
					predicates[number_of_predicates++] = word;
					//word.clear();
					continue;
				}
			}
		}
		buffer.clear(); buffer.str("");
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


	// 1 уровень
	
	wstring stemp = wstring(tt.begin(), tt.end());
	LPCWSTR sw = stemp.c_str();
	wstring k = wstring(t.begin(), t.end());
	LPCWSTR kk = k.c_str();
	int R = CopyFile(sw, kk, true); // скопировать промежуточный файл

	writing_filestream.open(t, ios::trunc); // очистить временный файл на запись
	reading_filestream.open(tt); // открыть временный файл на чтение

	while (getline(reading_filestream, file_iterator))
	{
		if (file_iterator[0] == '#') // составные сказуемые, не подлежат дальнейшему анализу
		{
			writing_filestream << file_iterator << endl;
			file_iterator.clear();
			continue;
		}
		if (file_iterator[file_iterator.size() - 1] == 'ю') // исключение всех лишних частей речи с окончанием -ю
		{
			if (check_for_suitable(file_iterator, "Predicates_with_U_ending.txt") == true)
			{
				writing_filestream << file_iterator << endl;
				file_iterator.clear();
				continue;
			}
		}
		if (file_iterator[file_iterator.size() - 1] == 'у') // исключение всех лишних частей речи с окончанием -у
		{
			if (check_for_suitable(file_iterator, "Predicates_with_Y_ending.txt") == true)
			{
				writing_filestream << file_iterator << endl;
				file_iterator.clear();
				continue;
			}
		}
		if (file_iterator.substr(file_iterator.size() - 2, 2) == "ем") // исключение всех лишних частей речи с окончанием -ем
		{
			if (check_for_suitable(file_iterator, "Predicates_with_EM_ending.txt") == true)
			{
				writing_filestream << file_iterator << endl;
				file_iterator.clear();
				continue;
			}
		}
		if (file_iterator.substr(file_iterator.size() - 2, 2) == "ся") // исключение причастий
		{
			if (check_for_part(file_iterator, "Adjectives_Signs.txt") == true)
			{
				file_iterator.clear();
				continue;
			}
			else
			{
				writing_filestream << file_iterator << endl;
				file_iterator.clear();
				continue;
			}
		}
		writing_filestream << file_iterator << endl;
	}
	
	writing_filestream.close();
	reading_filestream.close();
	return 0;
}