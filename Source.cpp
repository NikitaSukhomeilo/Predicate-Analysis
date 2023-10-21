#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<Windows.h>
using namespace std;
ifstream RF_Punctuation_Symbols;
ifstream RF_First_Conjugation;
ifstream RF_Second_Conjugation;
ifstream RF_Reflexives;
ifstream RF_Past_time;
ifstream RF_Imperative_Mood;
ifstream RF_First_Person;
void make_register(string& input_word)
{
	// �������������� � ������ �������� ����
	if (input_word[0] > 127 && input_word[0] < 159)
	{
		input_word[0] += 32;
	}
}
void clear_substring_from_punctuation_marks(string& str, ifstream& reading_filestream) // ������� ������� ������ �� ������ ����������
{
	reading_filestream.clear();
	reading_filestream.seekg(0, ios::beg);
	string file_iterator; // �������� ������
	getline(reading_filestream, file_iterator); // ������� ������, ��������� �� ������ ����������, �� �����
	int position = 0;
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
bool check_for_ending(const string& input_word, ifstream& reading_filestream) // ������� �������� ����� �� ��������� ��������
{
	reading_filestream.clear();
	reading_filestream.seekg(0, ios::beg);
	string file_iterator;
	while (getline(reading_filestream, file_iterator))
	{
		int position = input_word.find(file_iterator); // ����� ��������� � �����
		if (position != string::npos)
		{
			int length_of_ending = file_iterator.size(); // ����� ��������� �� �����
			if (input_word.size() - position == length_of_ending) // ���� � ����� ����� ���������
			{
				return true;
			}
		}
		file_iterator.clear();
	}
	return false;
}
bool check_for_suitable(const string& input_word, ifstream& reading_filestream) // ������� ���������� ������ ���� � �������� ����������
{
	reading_filestream.clear();
	reading_filestream.seekg(0, ios::beg);
	string temp = input_word;
	make_register(temp);
	string file_iterator;
	while (getline(reading_filestream, file_iterator))
	{
		if (file_iterator == temp) // ���� ������ ������ � �����
		{
			return true;
		}
	}
	return false;
}
bool check_for_part(const string& input_word, ifstream& reading_filestream) // �������� �� ��������� ����� � -��
{
	reading_filestream.clear();
	reading_filestream.seekg(0, ios::beg);
	string file_iterator;
	while (getline(reading_filestream, file_iterator))
	{
		int position = input_word.rfind(file_iterator);
		if (position != string::npos)
		{
			int length_of_ending = file_iterator.size();
			if (input_word.size() - 2 - position == length_of_ending) // ���� ����� ���������� -�� ���� ��������� ���������
			{
				return true;
			}
		}
		file_iterator.clear();
	}
	return false;
}
bool check_for_verb(const string& word)
{
	if (check_for_ending(word, RF_First_Conjugation) == true) // ��������� �� ��������� ������� ���������
	{
		return 1;
	}
	if (check_for_ending(word, RF_Second_Conjugation) == true) // ��������� �� ��������� ������� ���������
	{
		return 1;
	}
	if (check_for_ending(word, RF_Reflexives) == true) // ��������� �� ��������� ����������� �������
	{
		return 1;
	}
	if (check_for_ending(word, RF_Past_time) == true) // ��������� �� ��������� ������� ���������� �������
	{
		return 1;
	}
	if (check_for_ending(word, RF_Imperative_Mood) == true) // ��������� �� ��������� �������� �������������� ����������
	{
		return 1;
	}
	if (check_for_ending(word, RF_First_Person) == true) // ��������� �� ��������� �������� ������� ����
	{
		return 1;
	}
	return 0;
}
string complex_verb_predicate(const string& input_word, stringstream& buffer, ifstream& reading_filestream)
{
	reading_filestream.clear();
	reading_filestream.seekg(0, ios::beg);
	string result;
	string temp;
	string blank = input_word;
	make_register(blank);
	string file_iterator;
	while (getline(reading_filestream, file_iterator))
	{
		int  position = blank.find(file_iterator);
		if (position != string::npos)
		{
			if (position == 0)
			{
				result += input_word;
				buffer >> temp;
				clear_substring_from_punctuation_marks(temp, RF_Punctuation_Symbols);
				if (check_for_verb(temp) == true)
				{
					return ("#" + result + " " + temp);
				}
				else
				{
					return result;
				}
			}
		}
	}
	return "";
}
bool compound_nominal_predicate(const string& input_word, const string& filename)
{
	fstream file;
	string file_iterator;
	file.open(filename, ios::in);
	while (getline(file, file_iterator))
	{
		if (file_iterator == input_word)
		{
			file.close();
			return true;
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

	// ��������� �������� �������� �����
	string input_filename;
	cout << "������� �������� �������� �����: ";
	getline(cin, input_filename);

	ifstream reading_filestream(input_filename); // ������� �������� ���� �� ������
	string Previous_Level_Results = "PLR.txt";
	string Buffer_For_Level = "BFL.txt";
	ofstream writing_filestream(Buffer_For_Level);
	string predicates[100]; // ������ ��� ��������� � ����������� ���������

	int number_of_predicates = 0; // ���������� ��������� ���������

	string file_iterator;
	stringstream buffer;

	RF_Punctuation_Symbols.open("Punctuation_Symbols.txt"); // �������� ����� �� ������� ����������
	ifstream RF_Parts_of_binding_verb_in_complex_verb_predicate("Parts_of_binding_verb_in_complex_verb_predicate.txt");
	//ifstream RF_Parts_of_binding_verb_in_complex_nominal_predicate("Parts_of_binding_verb_in_complex_nominal_predicate.txt");
	ifstream RF_Predicates_with_U_ending("Predicates_with_U_ending.txt");
	ifstream RF_Predicates_with_Y_ending("Predicates_with_Y_ending.txt");
	ifstream RF_Predicates_with_EM_ending("Predicates_with_EM_ending.txt");
	ifstream RF_Adjectives_Signs("Adjectives_Signs.txt");
	RF_First_Conjugation.open("First_Conjugation.txt");
	RF_Second_Conjugation.open("Second_Conjugation.txt");
	RF_Reflexives.open("Reflexives.txt");
	RF_Past_time.open("Past_time.txt");
	RF_Imperative_Mood.open("Imperative_Mood.txt");
	RF_First_Person.open("First_Person.txt");

	while (getline(reading_filestream, file_iterator))
	{
		buffer << file_iterator; // ��������� ������ �� ����� � ��������� �����
		file_iterator.clear();
		string word;
		bool is_compound_nominal_predicate = false;
		while (buffer >> word) // ��������� ���������� �� ������
		{
			if (word.size() == false)
			{
				continue;
			}
			clear_substring_from_punctuation_marks(word, RF_Punctuation_Symbols);
			// ��������� �������

			/*if (is_compound_nominal_predicate == true)
			{
				is_compound_nominal_predicate = false;
				predicates[number_of_predicates++] = word;
				word.clear();
				continue;
			}
			if (compound_nominal_predicate(word, "bundle.txt") == true)
			{
				predicates[number_of_predicates++] = word;
				is_compound_nominal_predicate = true;
				word.clear();
				continue;
			}*/

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

			// ��������� ���������� ���������
			if (word.size() > 2) // ��������������� ����������� ����� �������
			{
				string CVP = complex_verb_predicate(word, buffer, RF_Parts_of_binding_verb_in_complex_verb_predicate);
				if (CVP.size() != false)
				{
					predicates[number_of_predicates++] = CVP;
					word.clear();
					continue;
				}
				if (check_for_verb(word) == true)
				{
					predicates[number_of_predicates++] = word;
					word.clear();
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

	wstring W_Buffer_For_Level = wstring(Buffer_For_Level.begin(), Buffer_For_Level.end());
	LPCWSTR L_Buffer_For_Level = W_Buffer_For_Level.c_str();
	wstring W_Previous_Level_Results = wstring(Previous_Level_Results.begin(), Previous_Level_Results.end());
	LPCWSTR L_Previous_Level_Results = W_Previous_Level_Results.c_str();
	CopyFile(L_Buffer_For_Level, L_Previous_Level_Results, true); // ����������� ������������� ���� �� ������ ������ ������� � ���� ��� �������� �����������

	writing_filestream.open(Buffer_For_Level, ios::trunc); // �������� ��������� ���� �� ������
	reading_filestream.open(Previous_Level_Results); // ������� ��������� ���� �� ������

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
			if (check_for_suitable(file_iterator, RF_Predicates_with_U_ending) == true)
			{
				writing_filestream << file_iterator << endl;
				file_iterator.clear();
				continue;
			}
		}
		if (file_iterator[file_iterator.size() - 1] == '�') // ���������� ���� ������ ������ ���� � ���������� -�
		{
			if (check_for_suitable(file_iterator, RF_Predicates_with_Y_ending) == true)
			{
				writing_filestream << file_iterator << endl;
				file_iterator.clear();
				continue;
			}
		}
		if (file_iterator.substr(file_iterator.size() - 2, 2) == "��") // ���������� ���� ������ ������ ���� � ���������� -��
		{
			if (check_for_suitable(file_iterator, RF_Predicates_with_EM_ending) == true)
			{
				writing_filestream << file_iterator << endl;
				file_iterator.clear();
				continue;
			}
		}
		if (file_iterator.substr(file_iterator.size() - 2, 2) == "��") // ���������� ���������
		{
			if (check_for_part(file_iterator, RF_Adjectives_Signs) == true)
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

	CopyFile(L_Buffer_For_Level, L_Previous_Level_Results, true); // ����������� ������������� ���� �� ������ ������ ������� � ���� ��� �������� �����������
	writing_filestream.open(Buffer_For_Level, ios::trunc); // �������� ��������� ���� �� ������
	reading_filestream.open(Previous_Level_Results); // ������� ��������� ���� �� ������
	while (getline(reading_filestream, file_iterator))
	{
		if (file_iterator[0] == '#') // ��������� ���������, �� �������� ����������� �������
		{
			file_iterator = file_iterator.substr(1, file_iterator.size() - 1);
		}
		writing_filestream << file_iterator << endl;
	}

	writing_filestream.close();
	reading_filestream.close();
	string Outbound_Filename = "FoundPredicates.txt";
	wstring W_Outbound_Filename = wstring(Outbound_Filename.begin(), Outbound_Filename.end());
	LPCWSTR L_Outbound_Filename = W_Outbound_Filename.c_str();
	CopyFile(L_Buffer_For_Level, L_Outbound_Filename, true); // ����������� ������������� ���������� � �������� ����

	// ������� �������� ������ � ����������
	RF_Parts_of_binding_verb_in_complex_verb_predicate.close();
	RF_Predicates_with_U_ending.close();
	RF_Predicates_with_Y_ending.close();
	RF_Predicates_with_EM_ending.close();
	RF_Adjectives_Signs.close();
	RF_Punctuation_Symbols.close();
	RF_First_Conjugation.close();
	RF_Second_Conjugation.close();
	RF_Reflexives.close();
	RF_Past_time.close();
	RF_Imperative_Mood.close();
	RF_First_Person.close();
	//RF_Parts_of_binding_verb_in_complex_nominal_predicate.close();
	DeleteFile(L"PLR.txt");
	DeleteFile(L"BFL.txt");
	return 0;
}