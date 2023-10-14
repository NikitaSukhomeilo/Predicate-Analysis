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
	reading_filestream.close();
}
bool check_for_ending(const string& input_word, const string& filename) // ������� �������� ����� �� ��������� ��������
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
bool check_for_suitable(const string& input_word, const string& filename) // ������� ���������� ������ ���� � �������� ����������
{
	// �������������� � ������ �������� ����
	string temp = input_word;
	if (input_word[0] > 191 && input_word[0] < 224)
	{
		temp[0] += 32;
	}
	ifstream reading_filestream(filename); // ������� ���� � ��������� � ���� ���������
	string file_iterator;
	while (getline(reading_filestream, file_iterator))
	{
		if (file_iterator == temp) // ���� ������ ������ � �����
		{
			reading_filestream.close();
			return true;
		}
	}
	reading_filestream.close();
	return false;
}
bool check_for_part(const string& input_word, const string& filename) // �������� �� ��������� ����� � -��
{
	ifstream reading_filestream(filename);
	string file_iterator;
	while (getline(reading_filestream, file_iterator))
	{
		int position = input_word.rfind(file_iterator);
		if (position != string::npos)
		{
			int length_of_ending = file_iterator.size();
			if (input_word.size() - 2 - position == length_of_ending) // ���� ����� ���������� -�� ���� ��������� ���������
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
	// ����� � ������� ���������
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "");

	string input_filename;
	cout << "������� �������� �������� �����: ";
	getline(cin, input_filename);

	ifstream reading_filestream(input_filename); // ������� �������� ���� �� ������
	string t = "Temporary.txt";
	string tt = "temp.txt";
	ofstream writing_filestream(tt);
	string predicates[500]; // ������ ��� ��������� � ����������� ���������

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
			if (word.size() == false)
			{
				continue;
			}
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
				if (check_for_ending(word, "Imperative_Mood.txt") == true) // ��������� �� ��������� �������� �������������� ����������
				{
					predicates[number_of_predicates++] = word;
					word.clear();
					continue;
				}
				if (check_for_ending(word, "First_Person.txt") == true) // ��������� �� ��������� �������� ������� ����
				{
					predicates[number_of_predicates++] = word;
					//word.clear();
					continue;
				}
			}
		}
		buffer.clear(); buffer.str("");
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


	// 1 �������
	
	wstring stemp = wstring(tt.begin(), tt.end());
	LPCWSTR sw = stemp.c_str();
	wstring k = wstring(t.begin(), t.end());
	LPCWSTR kk = k.c_str();
	int R = CopyFile(sw, kk, true); // ����������� ������������� ����

	writing_filestream.open(t, ios::trunc); // �������� ��������� ���� �� ������
	reading_filestream.open(tt); // ������� ��������� ���� �� ������

	while (getline(reading_filestream, file_iterator))
	{
		if (file_iterator[0] == '#') // ��������� ���������, �� �������� ����������� �������
		{
			writing_filestream << file_iterator << endl;
			file_iterator.clear();
			continue;
		}
		if (file_iterator[file_iterator.size() - 1] == '�') // ���������� ���� ������ ������ ���� � ���������� -�
		{
			if (check_for_suitable(file_iterator, "Predicates_with_U_ending.txt") == true)
			{
				writing_filestream << file_iterator << endl;
				file_iterator.clear();
				continue;
			}
		}
		if (file_iterator[file_iterator.size() - 1] == '�') // ���������� ���� ������ ������ ���� � ���������� -�
		{
			if (check_for_suitable(file_iterator, "Predicates_with_Y_ending.txt") == true)
			{
				writing_filestream << file_iterator << endl;
				file_iterator.clear();
				continue;
			}
		}
		if (file_iterator.substr(file_iterator.size() - 2, 2) == "��") // ���������� ���� ������ ������ ���� � ���������� -��
		{
			if (check_for_suitable(file_iterator, "Predicates_with_EM_ending.txt") == true)
			{
				writing_filestream << file_iterator << endl;
				file_iterator.clear();
				continue;
			}
		}
		if (file_iterator.substr(file_iterator.size() - 2, 2) == "��") // ���������� ���������
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