#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<Windows.h>
#include"Signs.h"
#include<conio.h>
using namespace std;
string Found_Predicates[INT16_MAX];
void clear_substring_from_____(string& str)
{
	size_t position = 0;
	for (size_t i = 0; i < 5; i++)
	{
		do
		{
			position = str.find(symbols_of_syntax[i]);
			if (position != string::npos)
			{
				str.erase(position, 1);
			}
		} while (position != string::npos);
		position = 0;
	}
}
void verify_that_predicate_was_not_mentioned_yet(string& temporary, size_t& number_of_predicates)
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
	clear_substring_from_____(temporary);
	Found_Predicates[number_of_predicates++] = temporary;
}
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "");
	//string** Found_Predicates;

	string filename = "testdata2.txt";
	string t = "Temporary.txt";
	wstring stemp = wstring(filename.begin(), filename.end());
	LPCWSTR sw = stemp.c_str();
	wstring k = wstring(t.begin(), t.end());
	LPCWSTR kk = k.c_str();
	int R = CopyFile(sw, kk, true);
	ifstream reading_filestream(t);
	string temporary;
	stringstream buffer;
	size_t number_of_predicates = 0;
	bool actual;
	while (getline(reading_filestream, temporary)) // ïîêà èçâëåêàåì èç ôàéëà ñòðîêè
	{
		buffer << temporary; // ïîìåùàåì ñòðîêó â áóôåð
		temporary.clear();
		while (buffer >> temporary) // ïîñëîâíîå èçâëå÷åíèå
		{
			actual = true;
			for (size_t i = 0; i < 2; i++)
			{
				size_t original_length = temporary.size();
				size_t position_found = temporary.rfind(reflexives[i]);
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
					size_t position_found = temporary.rfind(first_conjugation[i]);
					size_t original_length = temporary.size();
					size_t predicate_length = first_conjugation[i].length();
					if (original_length - position_found == predicate_length)
					{
						verify_that_predicate_was_not_mentioned_yet(temporary, number_of_predicates);
						actual = false;
						break;
					}
					position_found = temporary.rfind(second_conjugation[i]);
					original_length = temporary.size();
					predicate_length = second_conjugation[i].length();
					if (original_length - position_found == predicate_length)
					{
						verify_that_predicate_was_not_mentioned_yet(temporary, number_of_predicates);
						actual = false;
						break;
					}
				}
			}
			if (actual == true)
			{
				for (size_t i = 0; i < 4; i++)
				{
					size_t position_found = temporary.rfind(past_time[i]);
					size_t original_length = temporary.size();
					size_t predicate_length = past_time[i].length();
					if (original_length - position_found == predicate_length)
					{
						verify_that_predicate_was_not_mentioned_yet(temporary, number_of_predicates);
						actual = false;
						break;
					}
				}
			}
			if (actual == true)
			{
				for (size_t i = 0; i < 2; i++)
				{
					size_t position_found = temporary.rfind(imperative_mood[i]);
					size_t original_length = temporary.size();
					size_t predicate_length = imperative_mood[i].length();
					if (original_length - position_found == predicate_length)
					{
						verify_that_predicate_was_not_mentioned_yet(temporary, number_of_predicates);
						actual = false;
						break;
					}
				}
			}
			if (actual == true)
			{
				for (size_t i = 0; i < 2; i++)
				{
					size_t position_found = temporary.rfind(first_person[i]);
					size_t original_length = temporary.size();
					size_t predicate_length = first_person[i].length();
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
	cout << "continue?\n";
	char d; 
	d = _getch();
	if (d != 'y')
	{
		reading_filestream.close();
		DeleteFile(kk);
		return 0;
	}
	// second level
	
	ofstream writing_filestream(t);
	for (size_t i = 0; i < number_of_predicates; i++)
	{
		writing_filestream << Found_Predicates[i];
		if (i != number_of_predicates - 1)
		{
			writing_filestream << endl;
		}
	}
	writing_filestream.close();
	reading_filestream.close();
	reading_filestream.clear();
	reading_filestream.seekg(0);
	number_of_predicates = 0;
	reading_filestream.open(t);

	temporary.clear(); buffer.clear();
	ifstream EM_ENDING("predicates_with_em_ending.txt");
	while (getline(reading_filestream, temporary))
	{
		Found_Predicates[number_of_predicates++] = temporary;
	}
	for (size_t i = 0; i < number_of_predicates; i++)
	{
		EM_ENDING.clear(); EM_ENDING.seekg(0);
		actual = true;
		if (Found_Predicates[i].size() <= 2)
		{
			Found_Predicates[i].clear();
		}
		if (Found_Predicates[i].size() >= 5)
		{
			string f = Found_Predicates[i].substr(Found_Predicates[i].size() - 2, 2);
			if (f == reflexives[0])
			{
				size_t beginning_position = Found_Predicates[i].size() - 4;
				size_t ending_position = Found_Predicates[i].size() - 3;
				string h = "";
				h += Found_Predicates[i][beginning_position];
				h += Found_Predicates[i][ending_position];
				for (size_t j = 0; j < 6; j++)
				{
					if (h == reflexive_participles[j])
					{
						Found_Predicates[i].clear();
						actual = false;
						break;
					}
				}
			}
			if (actual == true)
			{
				string Temp = Found_Predicates[i].substr(Found_Predicates[i].size() - 2, 2);
				for (size_t j = 0; j < 7; j++)
				{
					if (Temp == some_exclusion[j])
					{
						Found_Predicates[i].clear();
						actual = false;
						break;
					}
				}
			}
		}
		if (actual == true)
		{
			for (size_t j = 0; j < 19; j++)
			{
				if (Found_Predicates[i] == sh_i_exclusions[j])
				{
					Found_Predicates[i].clear();
					actual = false;
					break;
				}
			}
		}
		if (actual == true)
		{
			if (Found_Predicates[i].size() >= 4)
			{
				string Temp = Found_Predicates[i].substr(Found_Predicates[i].size() - 2, 2);
				if (Temp == first_conjugation[2])
				{
					while (getline(EM_ENDING, Temp))
					{
						if (Temp == Found_Predicates[i])
						{
							actual = false;
							break;
						}
					}
					if (actual == true)
					{
						Found_Predicates[i].clear();
					}
				}
			}
			
		}
	}
	EM_ENDING.close();
	
	for (size_t i = 0; i < number_of_predicates; i++)
	{
		if (Found_Predicates[i].size() != false)
		{
			cout << Found_Predicates[i] << endl;
		}
	}
	reading_filestream.close();
	DeleteFile(kk);
}
