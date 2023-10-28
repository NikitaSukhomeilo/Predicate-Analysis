#include"Auxilliary_Functions.h"
void make_register(string& str)
{
	// преобразование к одному регистру слов
	int i = str[0];
	if (i < (-32) && i >(-64))
	{
		str[0] += 32;
	}
}
string extract(const string& str)
{
	int position;
	for (const auto& i : str)
	{
		try
		{
			if (isdigit(i))
			{
				position = str.find(i);
				break;
			}
		}
		catch (exception& Err) {}
	}
	return str.substr(0, (position - 1));
}
int extract_number_of_sentences(const string& str)
{
	string temporary = str;
	int position;
	for (auto i : str)
	{
		try
		{
			if (isdigit(i))
			{
				position = str.find(i);
				break;
			}
		}
		catch (exception& Err) {}
	}
	temporary.clear();
	temporary = str.substr(position, str.size() - position);
	position = temporary.find(' ');
	temporary = temporary.substr(0, position);
	return stoi(temporary);
}
string get_current_local_time()
{
	string str, out;
	auto const time = std::chrono::current_zone()->to_local(std::chrono::system_clock::now());
	str = format("{:%Y.%m.%d_%H.%M}", time);
	return str;
}
void clear_substring_from_punctuation_marks(string& str, ifstream& reading_filestream) // функция очистки строки от знаков препинания
{
	reading_filestream.clear();
	reading_filestream.seekg(0, ios::beg);
	string file_iterator; // буферная строка
	getline(reading_filestream, file_iterator); // считать строку, состоящую из знаков препинания, из файла
	int position = 0;
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
void extract_sentences(Predicate& Temporary, const string& str)
{
	int position = str.rfind(' ');
	string temporary = str.substr(position + 1, str.size() - position);
	string temp;
	for (const auto& i : temporary)
	{
		if (i != ',')
		{
			temp += i;
		}
		else
		{
			Temporary.sentences.push_back(stoi(temp));
			temp.clear();
		}
	}
}
void Predicate::clear()
{
	name = "";
	number_of_sentences = 0;
	sentences.clear();
}