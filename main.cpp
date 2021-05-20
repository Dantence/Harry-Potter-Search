#include"head.h"

string lower(string s)					//���ַ�����Ӣ����ĸȫ��ת��ΪСд
{
	for (int i = 0; i < s.size(); ++i)
	{
		if (s[i] >= 'A' && s[i] <= 'Z')
		{
			s[i] += 32;
		}
	}
	return s;
}
Search::Search()
{
	file_name[0] = "Harry Potter Prequel.txt";
	file_name[1] = "Harry_Potter_and_the_Deathly_Hallows_Book_7.txt";
	file_name[2] = "Harry Potter and the Prisoner of Azkaban.txt";
	file_name[3] = "Harry_Potter_and_the_Chamber_of_Secrets_Book_2_.txt";
	file_name[4] = "Quidditch Through the Ages.txt";
	file_name[5] = "The Tales of Beedle the Bard.txt";
	file_name[6] = "Harry Potter and the Half-Blood Prince.txt";
	file_name[7] = "Harry Potter and the Goblet of Fire.txt";
	sum = 0;
	eof_line[0] = -1;
}
void Search::read_txt()
{
	for (int i = 0; i < 8; ++i)
	{
		ifstream ifs;
		string buf;
		ifs.open(file_name[i], ios::in);
		while (getline(ifs, buf))
		{
			buf.erase(0, buf.find_first_not_of(" "));
			if (buf.size() == 0)
				continue;
			buf.erase(buf.find_last_not_of(" ") + 1);
			content.push_back(buf);
		}
		eof_line[i + 1] = content.size();
	}
}
void Search::Getnex(string m)
{
	nex[0] = -1;
	int k = -1, j = 0;
	while (j < m.size())
	{
		if (k == -1 || m[k] == m[j])
		{
			k++; j++;
			nex[j] = k;
		}
		else
			k = nex[k];
	}
}
void Search::KMP(int i)      //KMP������i��
{
	int k = 0, j = 0;
	while (j < master_str.size())
	{
		if (k == -1 || sub_str[k] == master_str[j])
		{
			k++;
			j++;
		}
		else
		{
			k = nex[k];
		}
		if (k == sub_str.size())
		{
			r.line = i;
			ret.push_back(r);
			k = 0;
			sum++;
		}
	}
}
void Search::find(string key)
{
	int sum_line = content.size();
	sub_str = key;
	Getnex(key);
	for (int i = 0; i < sum_line; ++i)
	{
		master_str = content[i];
		KMP(i);
	}
}
int Search::find_page(int line)					//��ĳ�п�ʼѰ��ҳ�룬��Ϊҳ��С��4λ
{
	for (int i = line;; ++i)
	{
		if (content[i].size() <= 3 && check(content[i]))
		{
			return stoll(content[i]);
		}
	}
}
int Search::find_chapter(int line)						//�½���Ϊ0~36 + Foreword����ͳһΪСд ����Ϊ�ַ�������<=20
{
	for (int i = line;; i--)
	{
		if (content[i].size() <= 20)
		{
			string s = lower(content[i]);
			for (int j = 0; j < 38; j++)
			{
				if (RecordChapter[j] == s)
				{
					return j;
				}
			}
		}
	}
}
bool Search::check(string s)					//�ж�һ���ַ����Ƿ�Ϊ����
{
	for (int i = 0; i < s.size(); ++i)
	{
		if (s[i] < '0' || s[i] > '9')
		{
			return false;
		}
	}
	return true;
}
void main()
{
	cout << "��ӭʹ�ù������ؼ���ϵͳ��" << endl;
	cout << "������Ҫ���������ݣ����»س������ɿ�ʼ���ļ���֮�ã�" << endl << endl << endl << endl;
	while (true)
	{
		cout << "������Ҫ��ѯ�ĵ�����������" << endl;
		string key;
		again:
		getline(cin, key);
		Search s;
		int len;
		auto start = chrono::steady_clock::now();
		s.read_txt();
		s.find(" "+key);
		auto end = chrono::steady_clock::now();
		chrono::duration<double>elapsed = end - start;
		ofstream ofs;
		ofs.open("result.txt", ios::out);
		if (s.sum == 0)
		{
			cout << endl;
			cout << "δ���ҵ�\"" << key << "\"!" << endl << endl;
			cout << "������������Ҫ���������������" << endl;
			goto again;
		}
		else
		{
			ofs << setw(5) << "���" << setw(18) << "����/����" << setw(10) << "ҳ��" << setw(8) << "�½�" << setw(35) << "����" << endl << endl;
			len = s.ret.size();
			for (int i = 0; i < len; ++i)
			{
				for (int j = 0; j < 8; ++j)
				{
					if (s.ret[i].line > s.eof_line[j] && s.ret[i].line <= s.eof_line[j + 1])
					{
						string x = s.file_name[j];
						x.erase(x.end() - 4, x.end());
						s.ret[i].BookName = x;
						break;
					}
				}
				s.ret[i].Page = s.find_page(s.ret[i].line);
				s.ret[i].Chapter = s.find_chapter(s.ret[i].line);
				s.ret[i].No = i + 1;
				ofs << setw(5) << s.ret[i].No;
				ofs << setw(18) << key;
				ofs << setw(10) << s.ret[i].Page;
				if (s.ret[i].Chapter == 37)
				{
					ofs << setw(8) << "Foreword" << endl;
				}
				else
				{
					ofs << setw(8) << s.ret[i].Chapter;
				}
				ofs << setw(55) << s.ret[i].BookName << endl << endl;
			}
			cout << endl;
			cout << "����ʱ�䣺" << elapsed.count() << " ��" << endl << endl;
			cout << "��������Ѿ�������result.txt�ļ��У���鿴" << endl;
			cout << endl;
			cout << "����0����,���������ʾ����/����ǰ���һ������" << endl << endl;
			int op;
			while (cin>>op)
			{
				if (op == 0)
				{
					system("cls");
					break;
				}
				else if (!(op >= 0 && op <= len))
				{
					cout << "������������������" << endl;
				}
				else
				{
					s.ret[op - 1].Sentence = s.content[s.ret[op - 1].line];
					cout << endl << s.ret[op - 1].Sentence << endl << endl;
				}
			}
		}

		string Clean_The_Enter = "\n";
		getline(cin, Clean_The_Enter);
	}
	system("pause");
}