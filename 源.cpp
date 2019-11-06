#include <sstream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <functional>
#include <conio.h>
#include<cstring> 
#include <stdio.h>
#include<string>
#include<cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include<iomanip>
#include <winbase.h>
#include <functional>
#include <ctime>
#include<time.h>
#include<io.h>
#define print_lines 15
using namespace std;
void get_file_name(string path, vector<string>& files, string suffix)
{
	//获取文件名列表放到参数中的vector

	long hFile = 0;
	struct _finddata_t fileinfo;
	string p;
	//cout << path<< endl;
	string suffix2 = "/*." + suffix;
	if ((hFile = _findfirst(p.assign(path).append(suffix2).c_str(), &fileinfo)) != -1)
	{
		//cout << "sub" << endl;
		do {
			if ((fileinfo.attrib & _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					get_file_name(p.assign(path).append("/").append(fileinfo.name), files, suffix);
			}
			else
			{
				files.push_back(p.assign(path).append("/").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}


class Word {
public:
	string word;
	double fre;
	int review_times;
	int forget_time;
	Word();
};
Word::Word()
{
	word = "";
	fre = 0;
	review_times = 0;
	forget_time = 0;

}

class Word_Book {
public:
	vector<Word>mybook;
	string file_path;
	void load_book();
	void quit_book();
	int review_time;
	Word_Book();
};

Word_Book::Word_Book()
{
	file_path = "";
	review_time = 0;
}

class System {
public:
	Word_Book myword_book;
	int search_word();
	int add_word();
	int delete_word();
	int review_word();
	int print_word();
	int menu();
	int run();
	int myquit();
	void get_file_name(string path, vector<string>& files, string suffix);
	int print_single(Word& a);
	int get_all_word();
	int print_allword();
	vector<Word>all_word;
};

void System::get_file_name(string path, vector<string>& files, string suffix)
{
	//获取文件名列表放到参数中的vector

	long hFile = 0;
	struct _finddata_t fileinfo;
	string p;
	//cout << path<< endl;
	string suffix2 = "/*." + suffix;
	if ((hFile = _findfirst(p.assign(path).append(suffix2).c_str(), &fileinfo)) != -1)
	{
		//cout << "sub" << endl;
		do {
			if ((fileinfo.attrib & _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					get_file_name(p.assign(path).append("/").append(fileinfo.name), files, suffix);
			}
			else
			{
				files.push_back(p.assign(path).append("/").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}

int System::get_all_word()
{
	vector<string>file_name;
	Word mytempword;
	get_file_name("./Word", file_name, "txt");
	for (int i(0); i < file_name.size(); i++)
	{
		ifstream infile;
		infile.open(file_name[i]);
		if (infile.fail())
		{
			cout << "文件导入失败!!!" << endl;
			Sleep(2000);
			return 1;
		}
		string mid;
		infile >> mid;
		while (!infile.eof())
		{
			Word temp;
			infile >> temp.word;
			string mid;
			infile >> mid;
			if (mid.size() == 0)
				temp.forget_time = 0;
			else
				temp.forget_time = stoi(mid);
			infile >> mid;
			if (mid.size() == 0)
				temp.review_times = 0;
			else
				temp.review_times = stoi(mid);
			if (temp.review_times == 0)
			{
				temp.fre = 0.0;
			}
			else
			{
				temp.fre = double(temp.forget_time) / double(temp.review_times);
			}
			all_word.push_back(temp);
		}
		all_word.pop_back();
	}
	return 0;
}

int main()
{
	System start;
	start.get_all_word();
	start.run();
	return 0;
}

int  System::run()
{
	while (1)
	{
		system("cls");
		system("color f1");
		cout << "\n\n\t\t\t＋====================================================================＋\n";
		cout << "\t\t\t ｜ chooce one book and  input filepath              \n";
		cout << "\t\t\t ｜ cin '-'  to skip this process                    \n";
		cout << "\t\t\t ｜ cin '-1' or '0' to use yesterday or tomorrow wordbook quickly   \n";
		cout << "\t\t\t ｜ just enter quit to quit the system  \n";
		cout << "\t\t\t＋====================================================================＋\n";
		rewind(stdin);
		cin >> myword_book.file_path;
		if (myword_book.file_path == "quit")
		{
			return 0;
		}
		myword_book.load_book();
		menu();
		myword_book.quit_book();
	}
	return 0;
}

int System::menu()
{
	system("cls");
	system("color f1");
	cout << "\n\n\t\t\t＋==============================＋\n";
	cout << "\t\t\t ｜ 1.start to recite              \n";
	cout << "\t\t\t ｜ 2.start to review              \n";
	cout << "\t\t\t ｜ 3.let me see all word          \n";
	cout << "\t\t\t ｜ 4.search word                  \n";
	cout << "\t\t\t ｜ 5.delete word                  \n";
	cout << "\t\t\t ｜ 6.just quit                    \n";
	cout << "\t\t\t ｜ 7.see all word                  \n";
	cout << "\t\t\t＋==============================＋\n";
	rewind(stdin);
	while (1)
	{
		char op;
		int adnumtemp(0);
		rewind(stdin);
		cin >> op;
		rewind(stdin);
		if (op<'0' || op>'8')
		{
			adnumtemp = 100;
		}
		else
		{
			adnumtemp = op - '0';
		}
		switch (adnumtemp)
		{
		case 1:add_word(); break;
		case 2:review_word(); break;
		case 3:print_word(); break;
			//case 4:search_word(); break;
		case 5:delete_word(); break;
		case 6: return 0;
		case 7:print_allword(); break;
		default:cout << "输入有误，请重新输入" << endl;
		}
		system("cls");
		system("color f1");
		cout << "\n\n\t\t\t＋==============================＋\n";
		cout << "\t\t\t ｜ 1.start to recite              \n";
		cout << "\t\t\t ｜ 2.start to review              \n";
		cout << "\t\t\t ｜ 3.let me see all word          \n";
		cout << "\t\t\t ｜ 4.search word                  \n";
		cout << "\t\t\t ｜ 5.delete word                  \n";
		cout << "\t\t\t ｜ 6.just quit                    \n";
		cout << "\t\t\t ｜ 7.see all word                  \n";
		cout << "\t\t\t＋==============================＋\n";
		rewind(stdin);
	}
	return 1;
}

void Word_Book::load_book()
{
	mybook.clear();
	ifstream infile;
	if (file_path == "-")
	{
		time_t t = time(NULL);
		tm* tp = localtime(&t);
		string name;
		name += to_string(tp->tm_year + 1900) + "_" + to_string(tp->tm_mon + 1) + "_" + to_string(tp->tm_mday);
		vector<string>file_name;
		get_file_name("./Word", file_name, "txt");
		int flag(0);
		for (int i(0); i< file_name.size(); i++)
		{
			if (file_name[i] == "./Word/" + name + ".txt")
			{
				cout << "Today wordbook is existed. Do not add again!!!" << endl;
				Sleep(2000);
				file_path = name;
				flag = 1;
				break;
			}
		}
		if (!flag)
			return;
	}
	if (file_path == "0")
	{
		time_t t = time(NULL);
		tm* tp = localtime(&t);
		string name;
		name += to_string(tp->tm_year + 1900) + "_" + to_string(tp->tm_mon + 1) + "_" + to_string(tp->tm_mday);
		file_path = name;
	}
	if (file_path == "-1")
	{
		time_t t = time(NULL);
		tm* tp = localtime(&t);
		string name;
		name += to_string(tp->tm_year + 1900) + "_" + to_string(tp->tm_mon + 1) + "_" + to_string(tp->tm_mday - 1);
		file_path = name;
	}
	file_path = "./Word/" + file_path + ".txt";
	infile.open(file_path);
	if (infile.fail())
	{
		cout << "文件导入失败!!!" << endl;
		Sleep(2000);
		return;
	}
	string mid;
	infile >> mid;
	if (mid.size() == 0)
		review_time = 1;
	else
		review_time = stoi(mid) + 1;
	while (!infile.eof())
	{
		Word temp;
		infile >> temp.word;
		string mid;
		infile >> mid;
		if (mid.size() == 0)
			temp.forget_time = 0;
		else
			temp.forget_time = stoi(mid);
		infile >> mid;
		if (mid.size() == 0)
			temp.review_times = 0;
		else
			temp.review_times = stoi(mid);
		if (temp.review_times == 0)
		{
			temp.fre = 0.0;
		}
		else
		{
			temp.fre = double(temp.forget_time) / double(temp.review_times);
		}
		mybook.push_back(temp);
	}
	mybook.pop_back();
	return;
}

void Word_Book::quit_book()
{
	fstream myoperate;
	if (file_path == "-")
	{
		time_t t = time(NULL);
		tm* tp = localtime(&t);
		string name;
		name += "./Word/" + to_string(tp->tm_year + 1900) + "_" + to_string(tp->tm_mon + 1) + "_" + to_string(tp->tm_mday) + ".txt";
		file_path = name;
	}
	myoperate.open(file_path, ofstream::out);
	if (myoperate.fail())
	{
		cout << "文件导出失败!!!" << endl;
		Sleep(2000);
		return;
	}
	int length(0);
	length = mybook.size();
	myoperate << to_string(review_time);
	myoperate << endl;
	for (int i(0); i < length; i++)
	{
		string usage;
		usage = mybook[i].word;
		myoperate << usage << " ";

		usage = to_string(mybook[i].forget_time);
		myoperate << usage << " ";

		usage = to_string(mybook[i].review_times);
		myoperate << usage << " ";

		myoperate << endl;
	}
	return;
}

int System::print_single(Word& temp)
{
	cout << left << setw(30) << temp.word << "|";
	cout << left << setw(15) << temp.forget_time << "|";
	cout << left << setw(15) << temp.review_times << "|";
	cout << left << setw(15) << temp.fre * 100 << "%" << "|";
	cout << endl;
	return 0;
}

int System::print_word()
{
	int pagenum(1);
	int maxpage(0);
	int songsize = myword_book.mybook.size();
	maxpage = songsize / print_lines;
	if (maxpage * print_lines != songsize)
	{
		maxpage++;
	}
	system("cls");
	system("color f1");
	cout << "这是第 " << pagenum << " 页" << endl;
	cout << left << setw(30) << "单词" << "|";
	cout << left << setw(15) << "忘记次数" << "|";
	cout << left << setw(15) << "复习次数" << "|";
	cout << left << setw(15) << "遗忘率" << "|";
	cout << endl;
	for (int i(-print_lines); i < 0 && (i + pagenum * print_lines) < songsize; i++)
	{
		Word temp = myword_book.mybook[i + pagenum * print_lines];
		print_single(temp);
	}
	cout << endl;
	cout << "按上或下翻页。按esc退出浏览模式" << endl;
	char ch;
	while ((ch = _getch()) != 0x1B)
	{
		if (ch == -32)
		{
			ch = _getch();
			if (ch == 80)
			{
				system("cls");
				system("color f1");
				if (pagenum == maxpage)
				{
					cout << "已经是最后一页啦！" << endl;
				}
				else
					pagenum++;
				cout << "这是第 " << pagenum << " 页" << endl;
				cout << left << setw(30) << "单词" << "|";
				cout << left << setw(15) << "忘记次数" << "|";
				cout << left << setw(15) << "复习次数" << "|";
				cout << left << setw(15) << "遗忘率" << "|";
				cout << endl;
				for (int i(-print_lines); i < 0 && (i + pagenum * print_lines) < songsize; i++)
				{
					Word temp = myword_book.mybook[i + pagenum * print_lines];
					print_single(temp);
				}
				cout << endl;
				cout << "按上或下翻页。按esc退出浏览模式" << endl;
			}
			if (ch == 72)
			{
				system("cls");
				system("color f1");
				if (pagenum == 1)
				{
					cout << "已经是第一页啦！" << endl;
				}
				else
					pagenum--;
				cout << "这是第 " << pagenum << " 页" << endl;
				cout << left << setw(30) << "单词" << "|";
				cout << left << setw(15) << "忘记次数" << "|";
				cout << left << setw(15) << "复习次数" << "|";
				cout << left << setw(15) << "遗忘率" << "|";
				cout << endl;
				for (int i(-print_lines); i < 0 && (i + pagenum * print_lines) < songsize; i++)
				{
					Word temp = myword_book.mybook[i + pagenum * print_lines];
					print_single(temp);
				}
				cout << endl;
				cout << "按上或下翻页。按esc退出浏览模式" << endl;
			}
		}
		else
		{
			{
				system("cls");
				system("color f1");
				cout << "这是第 " << pagenum << " 页" << endl;
				cout << left << setw(30) << "单词" << "|";
				cout << left << setw(15) << "忘记次数" << "|";
				cout << left << setw(15) << "复习次数" << "|";
				cout << left << setw(15) << "遗忘率" << "|";
				cout << endl;
				for (int i(-print_lines); i < 0 && (i + pagenum * print_lines) < songsize; i++)
				{
					Word temp = myword_book.mybook[i + pagenum * print_lines];
					print_single(temp);
				}
				cout << endl;
				cout << "按上或下翻页。按esc退出浏览模式" << endl;
				cout << "**********不合法的按键************" << endl;
			}
		}
		rewind(stdin);
	}
	return 0;
}

int System::add_word()
{
	while (1)
	{
		Word tempa;
		cout << "input word" << endl;
		string temp;
		cin >> temp;
		if (temp == ":q")
			break;
		tempa.word = temp;

		for (int i(0); i < myword_book.mybook.size(); i++)
		{
			if (tempa.word == myword_book.mybook[i].word)
			{
				cout << "已经有这一个单词了了" << endl;
				Sleep(1500);
			}
		}
		myword_book.mybook.push_back(tempa);
	}
	Sleep(2000);
	return 0;
}

int System::review_word()
{
	for (int i(0); i < myword_book.mybook.size(); i++)
	{
		system("cls");
		system("color f1");
		cout << myword_book.mybook[i].word << endl;
		cout << "Still remember it? [y/n]" << endl;
		string a;
		cin >> a;
		while (1)
		{
			if (a == "y")
			{
				myword_book.mybook[i].review_times += 1;
				myword_book.mybook[i].fre = (double)myword_book.mybook[i].forget_time / (double)myword_book.mybook[i].review_times;
				break;
			}
			if (a == "n")
			{
				myword_book.mybook[i].review_times += 1;
				myword_book.mybook[i].forget_time += 1;
				myword_book.mybook[i].fre = (double)myword_book.mybook[i].forget_time / (double)myword_book.mybook[i].review_times;
				break;
			}
		}
	}
	system("cls");
	system("color f1");
	cout << "review All successfully!!!! " << endl;
	Sleep(2000);
	return 1;
}

int System::delete_word()
{
	cout << "请输入你想删除的单词" << endl;
	string a;
	cin >> a;
	int serielnumber(-1);
	for (int i(0); i < myword_book.mybook.size(); i++)
	{
		if (myword_book.mybook[i].word == a)
		{
			serielnumber = i;
			break;
		}
	}
	if (serielnumber < 0 || serielnumber >= myword_book.mybook.size())
	{
		cout << "没有找到，即将返回上一级" << endl;
		Sleep(2000);
		return 0;
	}
	cout << "delete " << myword_book.mybook[serielnumber].word << " ?[y/n] operation comfirm" << endl;
	while (1)
	{
		string temp;
		cin >> temp;
		if (temp == "y")
		{
			myword_book.mybook.erase(myword_book.mybook.begin() + serielnumber);
			break;
		}
		else
		{
			break;
		}
	}
	Sleep(1000);
	return 1;
}

int System::print_allword()
{
	int pagenum(1);
	int maxpage(0);
	int songsize = all_word.size();
	maxpage = songsize / print_lines;
	if (maxpage * print_lines != songsize)
	{
		maxpage++;
	}
	system("cls");
	system("color f1");
	cout << "这是第 " << pagenum << " 页" << endl;
	cout << left << setw(30) << "单词" << "|";
	cout << left << setw(15) << "忘记次数" << "|";
	cout << left << setw(15) << "复习次数" << "|";
	cout << left << setw(15) << "遗忘率" << "|";
	cout << endl;
	for (int i(-print_lines); i < 0 && (i + pagenum * print_lines) < songsize; i++)
	{
		Word temp = all_word[i + pagenum * print_lines];
		print_single(temp);
	}
	cout << endl;
	cout << "按上或下翻页。按esc退出浏览模式" << endl;
	char ch;
	while ((ch = _getch()) != 0x1B)
	{
		if (ch == -32)
		{
			ch = _getch();
			if (ch == 80)
			{
				system("cls");
				system("color f1");
				if (pagenum == maxpage)
				{
					cout << "已经是最后一页啦！" << endl;
				}
				else
					pagenum++;
				cout << "这是第 " << pagenum << " 页" << endl;
				cout << left << setw(30) << "单词" << "|";
				cout << left << setw(15) << "忘记次数" << "|";
				cout << left << setw(15) << "复习次数" << "|";
				cout << left << setw(15) << "遗忘率" << "|";
				cout << endl;
				for (int i(-print_lines); i < 0 && (i + pagenum * print_lines) < songsize; i++)
				{
					Word temp = all_word[i + pagenum * print_lines];
					print_single(temp);
				}
				cout << endl;
				cout << "按上或下翻页。按esc退出浏览模式" << endl;
			}
			if (ch == 72)
			{
				system("cls");
				system("color f1");
				if (pagenum == 1)
				{
					cout << "已经是第一页啦！" << endl;
				}
				else
					pagenum--;
				cout << "这是第 " << pagenum << " 页" << endl;
				cout << left << setw(30) << "单词" << "|";
				cout << left << setw(15) << "忘记次数" << "|";
				cout << left << setw(15) << "复习次数" << "|";
				cout << left << setw(15) << "遗忘率" << "|";
				cout << endl;
				for (int i(-print_lines); i < 0 && (i + pagenum * print_lines) < songsize; i++)
				{
					Word temp = all_word[i + pagenum * print_lines];
					print_single(temp);
				}
				cout << endl;
				cout << "按上或下翻页。按esc退出浏览模式" << endl;
			}
		}
		else
		{
			{
				system("cls");
				system("color f1");
				cout << "这是第 " << pagenum << " 页" << endl;
				cout << left << setw(30) << "单词" << "|";
				cout << left << setw(15) << "忘记次数" << "|";
				cout << left << setw(15) << "复习次数" << "|";
				cout << left << setw(15) << "遗忘率" << "|";
				cout << endl;
				for (int i(-print_lines); i < 0 && (i + pagenum * print_lines) < songsize; i++)
				{
					Word temp = all_word[i + pagenum * print_lines];
					print_single(temp);
				}
				cout << endl;
				cout << "按上或下翻页。按esc退出浏览模式" << endl;
				cout << "**********不合法的按键************" << endl;
			}
		}
		rewind(stdin);
	}
	return 0;
}
