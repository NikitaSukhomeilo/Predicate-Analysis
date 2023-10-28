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
using namespace std;
void make_register(string&);
string extract(const string&);
int extract_number_of_sentences(const string&);
string get_current_local_time();
void clear_substring_from_punctuation_marks(string&, ifstream&); // функция очистки строки от знаков препинания
struct Predicate
{
	string name;
	vector<int> sentences;
	int number_of_sentences = 0;
	void clear();
};
void extract_sentences(Predicate&, const string&);