
#include<iostream>
#include<algorithm>
#include<fstream>
#include<string>
#include<cstring>
#include<string.h>
#include"fengzhuang.h"
using namespace std;
struct danci
{
	int num1 = 1;
	string content;
	int flag = 1,flag1=1;
};
danci word[100000];
danci word1[100000];
int num = 0;
int zhennum = 0;
int zhennum1 = 0;
bool cmp(danci x, danci y)
{
	if (x.num1 > y.num1)
		return true;
	else if (x.num1 == y.num1)
	{
		if (x.content > y.content)return false;
		else return true;
	}
	else
		return false;
}

int main(int argc, char* argv[])
{
	int w, m, n;
	string ww;
	bool mm = false, nn = false;
	for (w = 1; w < argc; w++)
	{
		if (strcmp(argv[w], "-m") == 0)
		{
			m = argv[w + 1][0] - 48;
			mm = true;
		}
		if (strcmp(argv[w], "-n") == 0)
		{
			n = argv[w + 1][0] - 48;
			nn = true;
		}
		if (strcmp(argv[w], "-w") == 0)
		{
			ww = argv[w+1];
		}
	}
	int linenum = 0;//一行的字符数 
	int linenumber = 0;//几行 
	int i, j, r;
	if (argv[2] == NULL)
	{
		cout << "NO INPUT!" << endl;
	}
	ifstream file(argv[2]);
	if (!file)
	{
		cout << "UNABLE TO OPEN!" << endl;
	}
	string d;
	int count = 0, size, linewordsize = 0;
	char pp[50];
	while (getline(file, d))
	{
		linewordsize = 0;
		linenum = d.size() + 1;
		count += linenum;
		bigtosmall(d);//大写转成小写
		//cout << count<<" "<<linenumber<<" "<<d << endl;
		for (i = 0; i < d.size(); i++)
		{
			if (d[i] >= 'a'&&d[i] <= 'z')
			{
				size = 0;
				pp[size] = d[i]; size++;
				for (j = i + 1; j < d.size(); j++)
				{
					if (d[j] >= 'a'&&d[j] <= 'z')
					{
						//cout << d[j];
						pp[size] = d[j];
						size++;
					}
					else
					{
						break;
					}
				}//cout << size << endl;
				//cout << pp << endl;
				if (size >= 4)
				{
					for (r = j; r < d.size(); r++)
					{
						if (d[r] != ' ')
						{
							pp[size] = d[r]; size++;
						}
						else
						{
							i = r; pp[size] = '\0';
							if (strcmp(pp, "title:") == 0 || strcmp(pp, "abstract:") == 0)
							{
								num--; break;
							}
							word[num].content = pp; linewordsize++;
							if (d.find("title: ") != string::npos&&ww=="1")
							{
								word[num].num1 = 10;
							}
							break;
						}
						if (r == d.size() - 1)
						{
							pp[size] = '\0';

							word[num].content = pp; i = r; linewordsize++;
							if (d.find("title: ") != string::npos&&ww == "1")
							{
								word[num].num1 = 10;
							}
						}
					}
					if (j >= d.size())
					{
						i = j; pp[size] = '\0';
						word[num].content = pp; linewordsize++;
						if (d.find("title: ") != string::npos&&ww == "1")
						{
							word[num].num1 = 10;
						}
					}
					num++;
				}
				else
				{
					word[num].content = pp; word[num].flag1 = 0; num++; linewordsize++;
					i = j;
				}
			}
		}
		if (linewordsize >= 1)
		{
			linenumber++;
		}
		if (d.find("title: ") != string::npos)
		{
			count = count - 7;
		}
		if (d.find("abstract: ") != string::npos)
		{
			count = count - 10;
		}
		if (d[0] >= 48 && d[0] <= 57) { count = count - d.size()-1;}
		if ((d[0] >= 48 && d[0] <= 57) && (linenumber >= 2)) {  count = count - 2; }
		//cout << linewordsize<<endl;
		//cout << "num:" << num << endl;
		if (mm == true)
		{
			for (i = num - linewordsize; i < num; i++)
			{
				if (num - i >= m)
				{
					if (word[i].flag1 == 1)
					{
						string temp = word[i].content;
						for (j = 1; j <= m - 1; j++)
						{
							if (word[i + j].flag1 == 1)
								word[i].content = word[i].content + " " + word[i + j].content;
							else if (word[i + j].flag1 == 0)
							{
								i = i + j; word[i].content = temp; break;
							}
							if (j == m - 1) word[i].flag1 = 2;
						}
					}
				}
				else break;
			}
		}
	}


	for (i = 0; i < num; i++)
	{
		if (word[i].flag1 == 2)
		{
			word[zhennum1] = word[i]; zhennum1++;
		}
	}
	if (mm == true)num = zhennum1;
	for (i = 0; i < num; i++)
	{
		if (word[i].flag == 0)
		{
			continue;
		}
		for (j = 0; j < num; j++)
		{
			if (i == j)continue;
			if (word[i].content == word[j].content)
			{
				word[i].num1 += word[j].num1;
				word[j].flag = 0;
			}
		}
	}
	for (i = 0; i < num; i++)
	{
		if (word[i].flag == 1)
		{
			word1[zhennum] = word[i]; zhennum++;
		}
	}
	sort(word1, word1 + zhennum, cmp);
	ofstream outfile;
	outfile.open("output.txt", ios::app);
	outfile << "characters: " << count - 1 << endl;
	outfile << "words: " << num << endl;
	outfile << "lines: " << linenumber << endl;
	if (nn == false)
	{
		if (zhennum >= 10)
		{
			for (i = 0; i < 10; i++)
			{
				outfile << "<" << word1[i].content << ">: " << word1[i].num1 << endl;
			}
		}
		else
		{
			for (i = 0; i < zhennum; i++)
			{
				outfile << "<" << word1[i].content << ">: " << word1[i].num1 << endl;
			}
		}
	}
	else
	{
		if (zhennum < n)
		{
			for (i = 0; i < zhennum; i++)
			{
				outfile << "<" << word1[i].content << ">: " << word1[i].num1 << endl;
			}
		}
		else
		{
			for (i = 0; i < n; i++)
			{
				outfile << "<" << word1[i].content << ">: " << word1[i].num1 << endl;
			}
		}
	}
	outfile.close();
}


