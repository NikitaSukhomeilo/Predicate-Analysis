#pragma once
#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<Windows.h>
#include<vector>
#include<iomanip>
#include<chrono>
#include<format>
#include<algorithm>
#include<filesystem>
using namespace std;
namespace fs = std::filesystem; // пространство имён для работы с файлами
struct Predicate // структура данных Сказуемое
{
	string name; // название сказуемого
	vector<int> sentences; // вектор предложений, в которых есть данное сказуемое
	int number_of_sentences = 0; // количество таких же сказуемых в предложении
	void clear() // очистка полей структуры
	{
		name = "";
		number_of_sentences = 0;
		sentences.clear();
	}
};
void make_register(string& str)// преобразование к одному регистру слов
{

	int i = str[0];
	if (i < (-32) && i >(-64))
	{
		str[0] += 32;
	}
}
string extr(const string& str) // извлечение 
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
int extrnum(const string& str)
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
string get_time()
{
	string str, out;
	auto const time = std::chrono::current_zone()->to_local(std::chrono::system_clock::now());
	str = format("{:%Y.%m.%d_%H.%M}", time);
	return str;
}
void clrpunct(string& str, ifstream& reading_filestream) // функция очистки строки от знаков препинания
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
void extsent(Predicate& Temporary, const string& str)
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
ifstream RF_Punct;
ifstream RF_FC;
ifstream RF_SC;
ifstream RF_Refl;
ifstream RF_Pt;
ifstream RF_ImpM;
ifstream RF_ET_END;
ifstream RF_First_Person;
ifstream RF_Prn;
ifstream RF_Prep;
ifstream RF_Bindv;
ifstream RF_Bindn;
ifstream RF_U_END;
ifstream RF_Y_END;
ifstream RF_EM_END;
ifstream RF_UT_END;
ifstream RF_AdjSigns;
ifstream RF_Conjunct;
ifstream RF_Noun;
bool chk_end(const string& inp, ifstream& rf) // функция проверки слова на окончания глаголов
{
	rf.clear();
	rf.seekg(0, ios::beg);
	string iter;
	string temp = inp;
	make_register(temp);
	while (getline(rf, iter))
	{
		int position = temp.find(iter); // поиск окончания в слове
		if (position != string::npos)
		{
			int l = iter.size(); // длина окончания из файла
			if (temp.size() - position == l) // если в конце слова окончание
			{
				return true;
			}
			else if (iter == temp)
			{
				return true;
			}
		}
		iter.clear();
	}
	return false;
}
bool chk_suit(const string& inp, ifstream& rf) // функция исключения частей речи с похожими признаками
{
	rf.clear();
	rf.seekg(0, ios::beg);
	string temp = inp;
	make_register(temp);
	string iter;
	while (getline(rf, iter))
	{
		if (iter == temp) // если найден глагол в файле
		{
			return true;
		}
	}
	return false;
}
bool chkp(const string& inp, ifstream& rf) // проверка на окончание слова с -ся
{
	rf.clear();
	rf.seekg(0, ios::beg);
	string iter;
	while (getline(rf, iter))
	{
		int p = inp.rfind(iter);
		if (p != string::npos)
		{
				return true;
		}
		iter.clear();
	}
	return false;
}
bool check_for_verb(const string& inp) // проверка на признаки глагола
{
	string word = inp;
	make_register(word);
	if (chk_end(word, RF_FC) == true) // проверить на окончание первого спряжения
	{
		return 1;
	}
	if (chk_end(word, RF_SC) == true) // проверить на окончание второго спряжения
	{
		return 1;
	}
	if (chk_end(word, RF_Refl) == true) // проверить на окончание возвратного глагола
	{
		return 1;
	}
	if (chk_end(word, RF_Pt) == true) // проверить на окончание глагола прошедшего времени
	{
		return 1;
	}
	if (chk_end(word, RF_ImpM) == true) // проверить на окончание глаголов повелительного наклонения
	{
		return 1;
	}
	if (chk_end(word, RF_First_Person) == true) // проверить на окончание глаголов первого лица
	{
		return 1;
	}
	return 0;
}
string complv(const string& inp, stringstream& buff, ifstream& rf) // функция анализа на составное глагольное сказуемое
{
	rf.clear();
	rf.seekg(0, ios::beg);
	string result;
	string temp;
	string blank = inp;
	make_register(blank);
	string file_iterator;
	while (getline(rf, file_iterator))
	{
		int  position = blank.find(file_iterator);
		if (position != string::npos)
		{
			if (position == 0)
			{
				result += inp;
				buff >> temp;
				clrpunct(temp, RF_Punct);
				if (check_for_verb(temp) == true)
				{
					return ("#" + result + " " + temp);
				}
				else
				{
					buff >> temp;
					clrpunct(temp, RF_Punct);
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
string compln(const string& str, stringstream& buff, ifstream& rf) // функция анализа на составные именные сказуемые
{
	rf.clear();
	rf.seekg(0, ios::beg);
	 string temporary = str;
	make_register(temporary);
	string temporary_1;
	while (getline(rf, temporary_1))
	{
		int  position = temporary_1.find(temporary);
		if (position != string::npos && position == 0)
		{
			temporary_1.clear();
			buff >> temporary_1;
			clrpunct(temporary_1, RF_Punct);
			return "#" + str + " " + temporary_1;
		}
	}
	return "";
}
bool comparator(Predicate a, Predicate b) // сравнение полей структуры Сказуемое
{
	return (a.name < b.name);
}
void f1(ifstream& rf, ofstream& wrf)
{
	string file_iterator;
	while (getline(rf, file_iterator)) // извлечение предложения из файла
	{
		stringstream buffer_verb;
		stringstream buffer_for_nominal;
		Predicate Temporary;
		if (file_iterator.size() == false)
		{
			continue;
		}
		buffer_verb << file_iterator; // заполнение строкового потока для глагольных сказуемых
		buffer_for_nominal << file_iterator; // заполнение строкового потока для именных сказуемых
		file_iterator.clear();
		string word, temp11;
		buffer_verb >> word;
		buffer_for_nominal >> temp11;
		word = word.substr(0, word.size() - 1);
		Temporary.sentences.push_back(stoi(word));
		Temporary.number_of_sentences++;
		word.clear();
		bool found = false;
		while (buffer_verb >> word) // пословное извлечение из предложения
		{
			buffer_for_nominal >> temp11;
			// очистка слова от попавших знаков препинания
			clrpunct(word, RF_Punct);
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
			if (word[0] < (-32) && word[0] >(-64)) // если не буква кириллицы
			{
				word.clear();
				continue;
			}
			// составное именное сказуемое
			string CNP = compln(word, buffer_for_nominal, RF_Bindn); // функция проверки на составное именное сказуемое
			if (CNP.size() != false)
			{
				found = true;
				Temporary.name = CNP;
				buffer_verb >> word;
				word.clear();
			}
			else
			{
				// составное глагольное сказуемое
				string CVP = complv(word, buffer_verb, RF_Bindv); // функция проверки на составное глагольное сказуемое
				if (CVP.size() != false)
				{
					found = true;
					Temporary.name = CVP;
					word.clear();
				}
				else if (check_for_verb(word) == true) // проверка первого слова на признаки глагола
				{
					found = true;
					Temporary.name = word;
					word.clear();
				}
			}
			if (found == true) // если сказуемое прошло проверки записать поля этой структуры в файл
			{
				wrf << Temporary.name << " " << Temporary.number_of_sentences << "  ";
				for (int i = 0; i < Temporary.number_of_sentences; i++)
				{
					wrf << Temporary.sentences[i] << ",";
				}
				wrf << endl;

				Temporary.name = "";
				found = false;
			}
		}
	}
}
void f2(ifstream& read_file, ofstream& wr_file)
{
	string iter;
	while (getline(read_file, iter))
	{
		string marker = extr(iter); // извлечение из строки названия сказуемого
		if (iter[0] == '#') // составные сказуемые, не подлежат дальнейшему анализу
		{
			wr_file << iter << endl;
			iter.clear();
			continue;
		}
		if (marker[marker.size() - 1] == 'ю') // исключение всех лишних частей речи с окончанием -ю
		{
			if (chk_suit(marker, RF_U_END) == true)
			{
				wr_file << iter << endl;
				iter.clear();
				continue;
			}
			else
			{
				iter.clear();
				continue;
			}
		}
		if (marker[marker.size() - 1] == 'у') // исключение всех лишних частей речи с окончанием -у
		{
			if (chk_suit(marker, RF_Y_END) == true)
			{
				wr_file << iter << endl;
				iter.clear();
				continue;
			}
			else
			{
				iter.clear();
				continue;
			}
		}
		if (marker.substr(marker.size() - 2, 2) == "ем") // исключение всех лишних частей речи с окончанием -ем
		{
			if (chk_suit(marker, RF_EM_END) == true)
			{
				wr_file << iter << endl;
				iter.clear();
				continue;
			}
			else
			{
				iter.clear();
				continue;
			}
		}
		if (marker.substr(marker.size() - 2, 2) == "ся") // исключение причастий
		{
			if (chkp(marker, RF_AdjSigns) == true) // проверка на причастия и прилагательные
			{
				iter.clear();
				continue;
			}
		}
		if (marker.substr(marker.size() - 2, 2) == "ут") // исключение всех лишних частей речи с окончанием -ут
		{
			if (chkp(marker, RF_UT_END) == true)
			{
				wr_file << iter << endl;
				iter.clear();
				continue;
			}
			else
			{
				iter.clear();
				continue;
			}
		}
		if (marker.substr(marker.size() - 2, 2) == "ет") // исключение всех лишних частей речи с окончанием -ут
		{
			if (chkp(marker, RF_ET_END) == true)
			{
				wr_file << iter << endl;
				iter.clear();
				continue;
			}
			else
			{
				iter.clear();
				continue;
			}
		}
		if (chk_end(marker, RF_AdjSigns) == true) // проверить на окончание возвратного глагола
		{
			iter.clear();
			continue;
		}
		if (chk_end(marker, RF_Prep) == true) // проверка на предлоги
		{
			iter.clear();
			continue;
		}
		if (chk_end(marker, RF_Conjunct) == true) // проверка на союзы
		{
			iter.clear();
			continue;
		}
		if (chk_end(marker, RF_Noun) == true) // проверка на имена существительные
		{
			iter.clear();
			continue;
		}
		if (chk_end(marker, RF_Prn) == true) // проверка на местоимения
		{
			iter.clear();
			continue;
		}
		wr_file << iter << endl;
		iter.clear();
	}
}
void f3(ifstream& readf, ofstream& wrf)
{
	vector<Predicate> pred;
	string iter, word;
	while (getline(readf, iter)) // чтение из промежуточного файла сказуемых
	{
		Predicate Temporary;
		if (iter[0] == '#')
		{
			iter = iter.substr(1, iter.size() - 1); // стирание служебных символов для составных сказуемых
		}
		Temporary.name = extr(iter); // извлечь название сказуемого
		Temporary.number_of_sentences = extrnum(iter); // извлечь количество найденных таких же сказуемых в предложении
		extsent(Temporary, iter); // извлечь все номера предложений, где встретилось данное сказуемое
		bool is_mentioned = false; // было ли сказуемое ранее в векторе
		bool same = false;
		for (auto& i : pred) // итерация по вектору сказуемых
		{
			if (i.name == Temporary.name)
			{
				i.number_of_sentences++;
				for (const auto& b : i.sentences)
				{
					if (b == Temporary.sentences[0])
					{
						same = true;
					}
				}
				is_mentioned = true;
				if (same == true)
				{
					continue;
				}
				else
				{
					i.sentences.push_back(Temporary.sentences[0]); // записать номер предложения, где встретилось это сказуемое
				}
			}
		}
		if (is_mentioned == false) // если сказуемое уникально
		{
			pred.push_back(Temporary); // записать его в вектор сказуемых
		}
		Temporary.clear();
	}

	// сортировка сказуемых по алфавиту по возрастанию
	sort(pred.begin(), pred.end(), comparator);

	// запись количества найденных сказуемых в форматированном виде
	wrf << "Найдено сказуемых: " << pred.size() << endl << endl;
	wrf << setiosflags(ios::left);
	wrf << setw(29) << "Сказуемое";
	wrf << setw(29) << "Частота встречаемости";
	wrf << setw(33) << "Предложения, где оно встретилось\n\n";

	// запись в выходной файл элементов массива в форматированном виде
	for (const auto& i : pred)
	{
		wrf << setw(29) << i.name;
		wrf << setw(29) << i.number_of_sentences;
		for (const auto& j : i.sentences)
		{
			wrf << j;
			if (j != i.sentences[i.sentences.size() - 1])
			{
				wrf << ", ";
			}
		}
		wrf << endl;
	}
}
int main()
{
	// вывод в консоль кириллицы
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "");
	fs::path path{fs::current_path()};
	string path_string{ path.string() };
	// получение названия входного файла
	string input_filename;
	cout << "Введите название входного файла с расширением: ";
	getline(cin, input_filename);

	ifstream readf(input_filename); // открыть исходный файл на чтение
	if (readf.is_open() == false)
	{
		cout << "Файл не найден.\n";
		system("pause");
		return 0;
	}
	// формирование названия выходного файла
	string inpfile = "Пронумерованный входной файл " + get_time() + ".txt";
	// составление нумерации текста
	ofstream k(inpfile);
	string x; size_t c = 1; string t; string sent;
	while (getline(readf, x))
	{
		if (x.size() == false)
		{
			continue;
		}
		if (t.size() != false)
		{
			int pos_1 = x.find('.');
			int pos_2 = x.find('?');
			int pos_3 = x.find('!');
			int res;
			if (pos_1 == string::npos)
			{
				if (pos_2 == string::npos)
				{
					res = pos_3;
				}
				else
				{
					if (pos_3 == string::npos)
					{
						res = pos_2;
					}
					else
					{
						res = min(pos_2, pos_3);
					}
				}
			}
			else
			{
				if (pos_2 == string::npos)
				{
					if (pos_3 == string::npos)
					{
						res = pos_1;
					}
					else
					{
						res = min(pos_1, pos_3);
					}

				}
				else
				{
					res = min(pos_1, pos_2, pos_3);
				}
			}
			t += " " + x.substr(0, res + 1);
			k << c++ << ") " << t << endl;
			x.erase(0, res + 1);
			t.clear();
		}
		if (x[x.size() - 1] != '.' && x[x.size() - 1] != '!' && x[x.size() - 1] != '?')
		{
			int pos_1 = x.rfind('.');
			int pos_2 = x.rfind('?');
			int pos_3 = x.rfind('!');
			int res = max(pos_1, pos_2, pos_3);
			if (pos_1 == string::npos && pos_2 == string::npos && pos_3 == string::npos)
			{
				t = x;
				continue;
			}
			t = x.substr(res + 2, x.size() - res);
		}
		for (int i = 0; i < x.size(); i++)
		{
			char it = x[i];
			sent += it;
			if (it == '.' || it == '?' || it == '!')
			{
				if (sent[0] == ' ')
				{
					sent.erase(0, 1);
				}
				k << c++ << ") " << sent << endl;
				sent.clear();
			}
		}
		x.clear();
	}
	k.close(); readf.close();
	readf.open(inpfile);
	string Level0 = "Level0.txt";
	ofstream wrf(Level0);
	// открытие файлов с признаками
	try
	{
		RF_Punct.open(path_string + "\\data\\Punctuation_Symbols.txt");
		RF_FC.open(path_string + "\\data\\First_Conjugation.txt");
		RF_SC.open(path_string + "\\data\\Second_Conjugation.txt");
		RF_Refl.open(path_string + "\\data\\Reflexives.txt");
		RF_Pt.open(path_string + "\\data\\Past_time.txt");
		RF_ImpM.open(path_string + "\\data\\Imperative_Mood.txt");
		RF_First_Person.open(path_string + "\\data\\First_Person.txt");
		RF_ET_END.open(path_string + "\\data\\ET_ending.txt");
		RF_Prn.open(path_string + "\\data\\Pronouns.txt");
		RF_Prep.open(path_string + "\\data\\Prepositions.txt");
		RF_Bindv.open(path_string + "\\data\\complex_verb.txt");
		RF_Bindn.open(path_string + "\\data\\complex_nominal.txt");
		RF_U_END.open(path_string + "\\data\\U_ending.txt");
		RF_Y_END.open(path_string + "\\data\\Y_ending.txt");
		RF_EM_END.open(path_string + "\\data\\EM_ending.txt");
		RF_UT_END.open(path_string + "\\data\\UT_ending.txt");
		RF_AdjSigns.open(path_string + "\\data\\Adjectives.txt");
		RF_Conjunct.open(path_string + "\\data\\Conjunctions.txt");
		RF_Noun.open(path_string + "\\data\\Noun.txt");
	}
	catch (exception& e)
	{
		cout << "ошибка открытия файлов.\n";
	}
	f1(readf, wrf);

	// закрыть файловые потоки на чтение входного файла и запись промежуточного
	wrf.close(); wrf.clear();
	readf.close(); readf.clear();

	string Level1 = "Level1.txt";
	readf.open(Level0);
	if (readf.is_open() == false)
	{
		cout << "ошибка.\n";
		return 0;
	}
	wrf.open(Level1);

	f2(readf, wrf);

	wrf.close();
	readf.close();

	// открыть файловые потоки на чтение промежуточного файла и запись выходного
	string Level2 = "Результат поиска сказуемых за ";
	Level2 += get_time();
	Level2 += ".txt";
	readf.open(Level1);
	wrf.open(Level2);

	f3(readf, wrf);

	// закрыть файловые потоки, открытые для чтения промежуточного файла и записи выходного
	wrf.close();
	readf.close();

	// закрыть файловые потоки с признаками
	RF_Bindv.close();
	RF_U_END.close();
	RF_Y_END.close();
	RF_EM_END.close();
	RF_AdjSigns.close();
	RF_Prep.close();
	RF_ET_END.close();
	RF_Punct.close();
	RF_FC.close();
	RF_SC.close();
	RF_Refl.close();
	RF_Noun.close();
	RF_Pt.close();
	RF_ImpM.close();
	RF_First_Person.close();
	RF_Bindn.close();
	RF_UT_END.close();
	RF_Prn.close();
	DeleteFile(L"Level0.txt");
	DeleteFile(L"Level1.txt");
	cout << "Поиск завершён.\n";
	system("pause");
	return 0;
}