#pragma once
#include"io.h"
#include<vector>


#define INPUT1 KEY_INPUT_1
#define INPUT2 KEY_INPUT_2
#define INPUT3 KEY_INPUT_3
#define INPUT4 KEY_INPUT_4



class Qwindow {
public:
	int gra;
	int x;
	int y;
	int State;
	bool A;
	int Qs;
	int s;
	int Current_Num;
	bool Quest_Now;

	std::vector<const char*> text;
	std::vector<const char*> Q1;
	std::vector<int> Q1i1;
	std::vector<int> Q1i2;
	std::vector<int> Q1i3;
	std::vector<int> Q1i4;
	std::vector<int> Q1i5;

	std::vector<const char*> Q2;
	std::vector<int> Q2i1;
	std::vector<int> Q2i2;
	std::vector<int> Q2i3;
	std::vector<int> Q2i4;
	std::vector<int> Q2i5;
	
	std::vector<const char*> Q3;
	std::vector<int> Q3i1;
	std::vector<int> Q3i2;
	std::vector<int> Q3i3;
	std::vector<int> Q3i4;
	std::vector<int> Q3i5;
	
	std::vector<const char*> Q4;
	std::vector<int> Q4i1;
	std::vector<int> Q4i2;
	std::vector<int> Q4i3;
	std::vector<int> Q4i4;
	std::vector<int> Q4i5;

	int hp, sp, atk, def, spd;
	

	Qwindow();
	~Qwindow();

	void Qwindow_init();
	void fmove();
	void emove();
	void Q(int i);
	void view();

	void all();

	void Writing(const char* filename, std::vector<int> &items1 ,
		std::vector<int> &items2, std::vector<int> &items3,
		std::vector<int> &items4, std::vector<int> &items5, int n);
	void WritingText(const char*filename, std::vector<const char*> &Text,
		std::vector<const char*> &Ques1, std::vector<const char*> &Ques2,
		std::vector<const char*> &Ques3, std::vector<const char*> &Ques4,int n);

};