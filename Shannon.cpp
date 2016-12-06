// Shannon.cpp : 定义控制台应用程序的入口点。
//

#include "iostream"
#include "math.h"
#include "map"
#include "fstream"
#include <sstream>

using namespace std;

class shannon{
public:
	shannon(){};
	shannon(string file_name);
	void show();
	//TODO:
	//string to_shannon_code(string str = "");
	//string to_word(string str = "");
	

private:
	int make_code();
	string decimals_to_binary(double decimals, int figures);
	int get_probability(string file_name);
	multimap<double, string> word;
	multimap<string, string> already;
	string get_text;
};

shannon::shannon(string file_name){
	word.clear();
	get_text.clear();
	get_probability(file_name);
	make_code();
}

int shannon::get_probability(string file_name){
	double word_amount = 0;
	double probability = 0;
	ifstream infile;
	ofstream outfile;
	map<char, double> word_count;
	infile.open(file_name, ios::in);
	if (!infile){
		cout << "can not open word text" << endl;
		return 0;
	}
	else{
		getline(infile, get_text);
	}
	for (auto &s : get_text){
		++word_count[s];
		++word_amount;
	}
	outfile.open("probability.txt", ios::out);
	for (auto &w : word_count){
		ostringstream stream;
		probability = w.second / word_amount;
		stream << w.first;
		outfile << stream.str() << "\t" << probability << endl;
		word.insert(make_pair(probability, stream.str()));
		already.insert(make_pair(stream.str(), ""));
	}
	return 1;
}

int shannon::make_code(){
	double temp = 1.0;
	string code = "";
	int figures = 0;
	for (auto &w : word){
		temp -= w.first;
		figures = -(log(w.first) / log(2));
		code = decimals_to_binary(temp, figures);
		already.find(w.second)->second = code;
	}
	return 1;
}

string shannon::decimals_to_binary(double decimals, int figures){
	string code = "";
	for (int i = 0; i < figures; ++i){
		decimals *= 2;
		ostringstream stream;
		stream << int(decimals);
		code += stream.str();
		if (decimals >= 1){
			decimals -= 1; 
		}else{
			continue;
		}
	}
	return code;
}

void shannon::show(){
	for (auto s : already){
		cout << s.first << "\t" << s.second << endl;
	}
}

int main(){
	shannon a("demo.txt");
	a.show();
	system("pause");
}