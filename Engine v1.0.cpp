#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<Windows.h>
using namespace std;
string Found_Predicates[INT16_MAX];
const string reflexives[2] = { "ся", "сь" };
const string first_conjugation[6] = { "ешь", "ет", "ем", "ете", "ут", "т" };
const string second_conjugation[6] = { "ишь", "ит", "им", "ите", "ат", "ят" };
void verify_that_predicate_was_not_mentioned_yet(const string& temporary, size_t& number_of_predicates)
{
	if (number_of_predicates != 0)
	{
		for (size_t j = 0; j < number_of_predicates; j++)
		{
			if (temporary == Found_Predicates[j])
			{
				return;
			}
		}
	}
	Found_Predicates[number_of_predicates++] = temporary;
}
int main()
{
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);
	setlocale(LC_ALL, "");
	//string** Found_Predicates;

	string filename = "testdata2.txt";
	ifstream reading_filestream(filename);
	string temporary;
	stringstream buffer;
	size_t number_of_predicates = 0;
	bool actual;
	while (getline(reading_filestream, temporary)) // пока извлекаем из файла строки
	{
		buffer << temporary; // помещаем строку в буфер
		temporary.clear();
		while (buffer >> temporary) // пословное извлечение
		{
			actual = true;
			for (size_t i = 0; i < 2; i++)
			{
				size_t original_length = temporary.size() / 2;
				size_t position_found = temporary.rfind(reflexives[i]) / 2;
				if (original_length - position_found == 2)
				{
					verify_that_predicate_was_not_mentioned_yet(temporary, number_of_predicates);
					actual = false;
					break;
				}
			}
			if (actual == true)
			{
				for (size_t i = 0; i < 6; i++)
				{
					size_t position_found = temporary.rfind(first_conjugation[i]) / 2;
					size_t original_length = temporary.size() / 2;
					size_t predicate_length = first_conjugation[i].length() / 2;
					if (original_length - position_found == predicate_length)
					{
						verify_that_predicate_was_not_mentioned_yet(temporary, number_of_predicates);
						actual = false;
						break;
					}
					position_found = temporary.rfind(second_conjugation[i]) / 2;
					original_length = temporary.size() / 2;
					predicate_length = second_conjugation[i].length() / 2;
					if (original_length - position_found == predicate_length)
					{
						verify_that_predicate_was_not_mentioned_yet(temporary, number_of_predicates);
						actual = false;
						break;
					}
				}
			}
		}
		temporary.clear(); buffer.clear();
	}
	for (size_t i = 0; i < number_of_predicates; i++)
	{
		cout << Found_Predicates[i] << endl;
	}
}
