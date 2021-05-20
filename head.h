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
	string file_name[8];					//����
	vector<string>content;					//ÿһ�е��ı���Ϣ
	vector<Result>ret;						//��ÿһ��Ŀ��������Ϣ����vector��
	Result r;								//����Result���󣬱���һ��Ŀ��������Ϣ
	string sub_str, master_str;				//�Ӵ�������
	int sum;								//��Ŀ���Ӵ�����
	int eof_line[8 + 1];					//ÿ����������ʱ������
};