#include"Auxilliary_Functions.h"
ifstream RF_Punctuation_Symbols;
ifstream RF_First_Conjugation;
ifstream RF_Second_Conjugation;
ifstream RF_Reflexives;
ifstream RF_Past_time;
ifstream RF_Imperative_Mood;
ifstream RF_First_Person;
ifstream RF_Parts_of_binding_verb_in_complex_verb_predicate("Parts_of_binding_verb_in_complex_verb_predicate.txt");
ifstream RF_Parts_of_binding_verb_in_complex_nominal_predicate("Parts_of_binding_verb_in_complex_nominal_predicate.txt");
ifstream RF_Predicates_with_U_ending("Predicates_with_U_ending.txt");
ifstream RF_Predicates_with_Y_ending("Predicates_with_Y_ending.txt");
ifstream RF_Predicates_with_EM_ending("Predicates_with_EM_ending.txt");
ifstream RF_Predicates_with_UT_ending("Predicates_with_UT_ending.txt");
ifstream RF_Adjectives_Signs("Adjectives_Signs.txt");
bool check_for_ending(const string& input_word, ifstream& reading_filestream) // функция проверки слова на окончания глаголов
{
	reading_filestream.clear();
	reading_filestream.seekg(0, ios::beg);
	string file_iterator;
	while (getline(reading_filestream, file_iterator))
	{
		int position = input_word.find(file_iterator); // поиск окончания в слове
		if (position != string::npos)
		{
			int length_of_ending = file_iterator.size(); // длина окончания из файла
			if (input_word.size() - position == length_of_ending) // если в конце слова окончание
			{
				return true;
			}
		}
		file_iterator.clear();
	}
	return false;
}
bool check_for_suitable(const string& input_word, ifstream& reading_filestream) // функция исключения частей речи с похожими признаками
{
	reading_filestream.clear();
	reading_filestream.seekg(0, ios::beg);
	string temp = input_word;
	make_register(temp);
	string file_iterator;
	while (getline(reading_filestream, file_iterator))
	{
		if (file_iterator == temp) // если найден глагол в файле
		{
			return true;
		}
	}
	return false;
}
bool check_for_part(const string& input_word, ifstream& reading_filestream) // проверка на окончание слова с -ся
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
			if (input_word.size() - 2 - position == length_of_ending) // если перед постфиксом -ся есть окончание причастия
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
	if (check_for_ending(word, RF_First_Conjugation) == true) // проверить на окончание первого спряжения
	{
		return 1;
	}
	if (check_for_ending(word, RF_Second_Conjugation) == true) // проверить на окончание второго спряжения
	{
		return 1;
	}
	if (check_for_ending(word, RF_Reflexives) == true) // проверить на окончание возвратного глагола
	{
		return 1;
	}
	if (check_for_ending(word, RF_Past_time) == true) // проверить на окончание глагола прошедшего времени
	{
		return 1;
	}
	if (check_for_ending(word, RF_Imperative_Mood) == true) // проверить на окончание глаголов повелительного наклонения
	{
		return 1;
	}
	if (check_for_ending(word, RF_First_Person) == true) // проверить на окончание глаголов первого лица
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
					buffer >> temp;
					clear_substring_from_punctuation_marks(temp, RF_Punctuation_Symbols);
					if (check_for_verb(temp) == true)
					{
						return ("#" + result + " " + temp);
					}
					return result;
				}
			}
		}
	}
	return "";
}
string complex_nominal_predicate(const string& str, stringstream& buffer, ifstream& reading_filestream)
{
	reading_filestream.clear();
	reading_filestream.seekg(0, ios::beg);
	string temporary = str;
	make_register(temporary);
	string temporary_1;
	while (getline(reading_filestream, temporary_1))
	{
		int  position = temporary_1.find(temporary);
		if (position != string::npos && position == 0)
		{
			temporary_1.clear();
			buffer >> temporary_1;
			clear_substring_from_punctuation_marks(temporary_1, RF_Punctuation_Symbols);
			return "#" + str + " " + temporary_1;
		}
	}
	return "";
}
bool comparator(Predicate a, Predicate b)
{
	return (a.name < b.name);
}
void f1(ifstream& reading_filestream, ofstream& writing_filestream)
{
	string file_iterator;
	while (getline(reading_filestream, file_iterator)) // извлечение предложения из файла
	{
		stringstream buffer_for_verb;
		stringstream buffer_for_nominal;
		Predicate Temporary;
		if (file_iterator.size() == false)
		{
			continue;
		}
		buffer_for_verb << file_iterator;
		buffer_for_nominal << file_iterator;
		file_iterator.clear();
		string word, temp11;
		buffer_for_verb >> word;
		buffer_for_nominal >> temp11;
		word = word.substr(0, word.size() - 1);
		Temporary.sentences.push_back(stoi(word));
		Temporary.number_of_sentences++;
		word.clear();
		bool found = false;
		while (buffer_for_verb >> word) // пословное извлечение из предложения
		{
			buffer_for_nominal >> temp11;
			if (word == "ел")
			{
				Temporary.name = word;
				word.clear();
				continue;
			}
			if (word.size() < 3) // приблизительная минимальная длина глагола
			{
				word.clear();
				continue;
			}

			// очистка слова от попавших знаков препинания
			clear_substring_from_punctuation_marks(word, RF_Punctuation_Symbols);

			// составное именное сказуемое
			string CNP = complex_nominal_predicate(word, buffer_for_nominal, RF_Parts_of_binding_verb_in_complex_nominal_predicate);
			if (CNP.size() != false)
			{
				found = true;
				Temporary.name = CNP;
				buffer_for_verb >> word;
				word.clear();
			}
			else
			{
				// составное глагольное сказуемое
				string CVP = complex_verb_predicate(word, buffer_for_verb, RF_Parts_of_binding_verb_in_complex_verb_predicate);
				if (CVP.size() != false)
				{
					found = true;
					Temporary.name = CVP;
					word.clear();
				}
				else if (check_for_verb(word) == true)
				{
					found = true;
					Temporary.name = word;
					word.clear();
				}
			}
			if (found == true)
			{
				writing_filestream << Temporary.name << " " << Temporary.number_of_sentences << "  ";
				for (int i = 0; i < Temporary.number_of_sentences; i++)
				{
					writing_filestream << Temporary.sentences[i] << ",";
				}
				writing_filestream << endl;

				Temporary.name = "";
				found = false;
			}
		}
	}
}
void f2(ifstream& reading_filestream, ofstream& writing_filestream)
{
	string file_iterator;
	while (getline(reading_filestream, file_iterator))
	{
		string marker = extract(file_iterator);
		if (file_iterator[0] == '#') // составные сказуемые, не подлежат дальнейшему анализу
		{
			writing_filestream << file_iterator << endl;
			file_iterator.clear();
			continue;
		}
		if (marker[marker.size() - 1] == 'ю') // исключение всех лишних частей речи с окончанием -ю
		{
			if (check_for_suitable(marker, RF_Predicates_with_U_ending) == false)
			{
				file_iterator.clear();
				continue;
			}
		}
		if (marker[marker.size() - 1] == 'у') // исключение всех лишних частей речи с окончанием -у
		{
			if (check_for_suitable(marker, RF_Predicates_with_Y_ending) == false)
			{
				file_iterator.clear();
				continue;
			}
		}
		if (marker.substr(marker.size() - 2, 2) == "ем") // исключение всех лишних частей речи с окончанием -ем
		{
			if (check_for_suitable(marker, RF_Predicates_with_EM_ending) == false)
			{
				file_iterator.clear();
				continue;
			}
		}
		if (marker.substr(marker.size() - 2, 2) == "ся") // исключение причастий
		{
			if (check_for_part(marker, RF_Adjectives_Signs) == true)
			{
				file_iterator.clear();
				continue;
			}
		}
		if (marker.substr(marker.size() - 2, 2) == "ут") //// исключение всех лишних частей речи с окончанием -ут
		{
			if (check_for_part(marker, RF_Predicates_with_UT_ending) == false)
			{
				file_iterator.clear();
				continue;
			}
		}
		if (check_for_ending(marker, RF_Adjectives_Signs) == true) // проверить на окончание возвратного глагола
		{
			file_iterator.clear();
			continue;
		}
		writing_filestream << file_iterator << endl;
		file_iterator.clear();
	}
}
void f3(ifstream& reading_filestream, ofstream& writing_filestream)
{
	vector<Predicate> array_of_predicates;
	int number_of_predicates = 0; // количество найденных сказуемых
	stringstream buffer;
	string file_iterator, word;
	while (getline(reading_filestream, file_iterator))
	{
		Predicate Temporary;
		if (file_iterator[0] == '#')
		{
			file_iterator = file_iterator.substr(1, file_iterator.size() - 1);
		}
		Temporary.name = extract(file_iterator);
		Temporary.number_of_sentences = extract_number_of_sentences(file_iterator);
		extract_sentences(Temporary, file_iterator);
		bool is_mentioned = false;
		for (auto& i : array_of_predicates)
		{
			if (i.name == Temporary.name)
			{
				i.number_of_sentences++;
				i.sentences.push_back(Temporary.sentences[0]);
				is_mentioned = true;
			}
		}
		if (is_mentioned == false)
		{
			array_of_predicates.push_back(Temporary);
		}
		Temporary.clear();
	}

	// сортировка сказуемых по алфавиту по возрастанию
	sort(array_of_predicates.begin(), array_of_predicates.end(), comparator);

	// запись количества найденных сказуемых
	writing_filestream << "Найдено сказуемых: " << array_of_predicates.size() << endl << endl;
	writing_filestream << setiosflags(ios::left);
	writing_filestream << setw(29) << "Сказуемое";
	writing_filestream << setw(29) << "Частота встречаемости";
	writing_filestream << setw(33) << "Предложения, где оно встретилось\n\n";

	// запись в выходной файл элементов массива
	for (const auto& i : array_of_predicates)
	{
		writing_filestream << setw(29) << i.name;
		writing_filestream << setw(29) << i.number_of_sentences;
		//writing_filestream << setw(33) << i.sentences[0];
		for (const auto& j : i.sentences)
		{
			writing_filestream << j;
			if (j != i.sentences[i.sentences.size() - 1])
			{
				writing_filestream << ", ";
			}
		}
		writing_filestream << endl;
	}
}
int main()
{
	// вывод в консоль кириллицы
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "");
	
	// получение названия входного файла
	string input_filename;
	cout << "Введите название входного файла: ";
	getline(cin, input_filename);

	ifstream reading_filestream(input_filename); // открыть исходный файл на чтение
	string Buffer_For_Level0 = "Buffer_For_Level0.txt";
	ofstream writing_filestream(Buffer_For_Level0);


	RF_Punctuation_Symbols.open("Punctuation_Symbols.txt"); // открытие файла со знаками пунктуации
	RF_First_Conjugation.open("First_Conjugation.txt");
	RF_Second_Conjugation.open("Second_Conjugation.txt");
	RF_Reflexives.open("Reflexives.txt");
	RF_Past_time.open("Past_time.txt");
	RF_Imperative_Mood.open("Imperative_Mood.txt");
	RF_First_Person.open("First_Person.txt");

	f1(reading_filestream, writing_filestream);

	// закрыть файловые потоки на чтение входного файла и запись промежуточного
	writing_filestream.close();
	reading_filestream.close();

	string Buffer_For_Level1 = "Buffer_For_Level1.txt";
	reading_filestream.open(Buffer_For_Level0);
	writing_filestream.open(Buffer_For_Level1);

	f2(reading_filestream, writing_filestream);

	writing_filestream.close();
	reading_filestream.close();

	// открыть файловые потоки на чтение промежуточного файла и запись выходного
	string Buffer_For_Level2 = "Результат поиска сказуемых за ";
	Buffer_For_Level2 += get_current_local_time();
	Buffer_For_Level2 += ".txt";
	reading_filestream.open(Buffer_For_Level1);
	writing_filestream.open(Buffer_For_Level2);

	f3(reading_filestream, writing_filestream);

	// закрыть файловые потоки, открытые для чтения промежуточного файла и записи выходного
	writing_filestream.close();
	reading_filestream.close();

	// закрыть файловые потоки с признаками
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
	RF_Parts_of_binding_verb_in_complex_nominal_predicate.close();
	RF_Predicates_with_UT_ending.close();
	DeleteFile(L"Buffer_For_Level0.txt");
	DeleteFile(L"Buffer_For_Level1.txt");
	cout << "Поиск завершён.\n";
	return 0;
}