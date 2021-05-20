#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<iomanip>
#include<cstdlib>
#include<chrono>
using namespace std;
#define int long long
int nex[1000];
string lower(string s);
string RecordChapter[38] = { "chapter zero","chapter one","chapter two","chapter three"
							,"chapter four","chapter five","chapter six"
							,"chapter seven","chapter eight","chapter night"
							,"chapter ten","chapter eleven","chapter twelve"
							,"chapter thirteen","chapter fourteen","chapter fifteen"
							,"chapter sixteen","chapter seventeen","chapter eighteen"
							,"chapter nineteen","chapter twenty","chapter twenty-one"
							,"chapter twenty-two","chapter twenty-three","chapter twenty-four"
							,"chapter twenty-five","chapter twenty-six","chapter twenty-seven"
							,"chapter twenty-eight","chapter twenty-nine","chapter thirty"
							,"chapter thirty-one","chapter thirty-two","chapter thirty-three"
							,"chapter thirty-four","chapter thirty-five","chapter thirty-six"
							,"foreword" };
struct Result
{
	int line;
	int No;
	int Page;
	int Chapter;
	string BookName;
	string Sentence;
};
class Search
{
public:
	Search();
	void read_txt();
	void Getnex(string m);
	void KMP(int i);
	void find(string key);
	int find_page(int line);
	int find_chapter(int line);
	bool check(string s);
	string file_name[8];					//书名
	vector<string>content;					//每一行的文本信息
	vector<Result>ret;						//将每一个目标的相关信息存入vector中
	Result r;								//创建Result对象，保存一个目标的相关信息
	string sub_str, master_str;				//子串和主串
	int sum;								//总目标子串个数
	int eof_line[8 + 1];					//每本书读入结束时的行数
};