#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<Windows.h>
using namespace std;
void clear_substring_from_punctuation_marks(string& str) // ������� ������� ������ �� ������ ����������
{
	ifstream reading_filestream("Punctuation_Symbols.txt"); // �������� ����� �� ������� ����������
	string file_iterator; // �������� ������
	getline(reading_filestream, file_iterator); // ������� ������, ��������� �� ������ ����������, �� �����
	size_t position = 0;
	for (int i = 0; i < file_iterator.size(); i++) // �������� �� ������
	{
		do
		{
			position = str.find(file_iterator[i]); // ����� � ������ ����� ����������
			if (position != string::npos) // ���� ������ ���� ����������
			{
				str.erase(position, 1); // ������� ���
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
		int position = input_word.find(file_iterator); // ����� ��������� � �����
		if (position != string::npos)
		{
			int length_of_ending = file_iterator.size(); // ����� ��������� �� �����
			if (input_word.size() - position == length_of_ending) // ���� � ����� ����� ���������
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
	// ����� � ������� ���������
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "");

	string input_filename;
	cout << "������� �������� �������� �����: ";
	getline(cin, input_filename);

	ifstream reading_filestream(input_filename); // ������� �������� ���� �� ������
	ofstream writing_filestream("temp.txt");
	string predicates[50]; // ������ ��� ��������� � ����������� ���������

	int number_of_predicates = 0; // ���������� ��������� ���������

	string file_iterator;
	stringstream buffer;
	while (getline(reading_filestream, file_iterator))
	{
		buffer << file_iterator; // ��������� ������ �� ����� � ��������� �����
		file_iterator.clear();
		string word;
		while (buffer >> word) // ��������� ���������� �� ������
		{
			clear_substring_from_punctuation_marks(word);
			// ��������� �������
			// ��������� ����������

			// �������
			if (word == "��")
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
			if (word.size() > 2) // ��������������� ����������� ����� �������
			{
				if (check_for_ending(word, "First_Conjugation.txt") == true) // ��������� �� ��������� ������� ���������
				{
					predicates[number_of_predicates++] = word;
					word.clear();
					continue;
				}
				if (check_for_ending(word, "Second_Conjugation.txt") == true) // ��������� �� ��������� ������� ���������
				{
					predicates[number_of_predicates++] = word;
					word.clear();
					continue;
				}
				if (check_for_ending(word, "Reflexives.txt") == true) // ��������� �� ��������� ����������� �������
				{
					predicates[number_of_predicates++] = word;
					word.clear();
					continue;
				}
				if (check_for_ending(word, "Past_time.txt") == true) // ��������� �� ��������� ������� ���������� �������
				{
					predicates[number_of_predicates++] = word;
					word.clear();
					continue;
				}
				if(check_for_ending(word, "Imperative_Mood.txt") == true) // ��������� �� ��������� �������� �������������� ����������
				{
					predicates[number_of_predicates++] = word;
					word.clear();
					continue;
				}
				if (check_for_ending(word, "First_Person.txt") == true) // ��������� �� ��������� �������� ������� ����
				{
					predicates[number_of_predicates++] = word;
					word.clear();
					continue;
				}
			}
		}
		buffer.clear();
		for (int i = 0; i < number_of_predicates; i++) // ������ � ���� ��������� �������
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