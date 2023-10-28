#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
using namespace std;
void extract_appropriate_filename(string&);
void text_analysis_into_predicates(const string&);
string create_filename();
string get_current_local_time();
