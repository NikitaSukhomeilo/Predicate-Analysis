#include"Source.h"
void extract_appropriate_filename(string& str) // извлечение названия файла без запрещённых символов Windows
{
	string temporary = str;
	str.clear();
	size_t position = temporary.find_last_of(92) + 1;
	str = temporary.substr(position, temporary.size() - position);
}

void text_analysis_into_predicates(const string& filename) // функция анализа текста из файла
{
	ifstream reading_filestream(filename);
	string temporary;
	stringstream buffer;
	while (getline(reading_filestream, temporary)) // пока извлекаем из файла строки
	{
		buffer >> temporary; // помещаем строку в буфер
		temporary.clear();
		while (buffer << temporary) // пословное извлечение
		{
			// do smth
		}
	}

}

string create_filename() // создание названия файла с учётом системного времени
{
	string temp = "\\Файл с результатом сортировки за ";
	temp += get_current_local_time();
	temp += ".txt";
	return temp;
}

string get_current_local_time() // получение текущего системного времени
{
	time_t Current_Local_Time = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&Current_Local_Time);
	strftime(buf, sizeof(buf), "%d.%m.%y_%H-%M-%S", &tstruct);
	string k = buf;
	for (int i = 0; i < k.size(); i++)
	{
		if (k[i] == ':')
		{
			k[i] = '.';
		}
	}
	return buf;
}
