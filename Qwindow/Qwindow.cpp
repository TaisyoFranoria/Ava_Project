#include"Qwindow.h"


Qwindow::Qwindow() {
	x = 1100;
	y = 100;
	gra = LoadGraph("img/Qwindow.png");
	State = 0;
	A = false;

	//テスト
	//text.push_back("あいうえお");
	//Q1.push_back("1");
	int items[5];
	Writing("Q/item1.csv", Q1i1,Q1i2,Q1i3,Q1i4,Q1i5, sizeof items / sizeof items[0]);
	

	//Q2.push_back("2");

	Writing("Q/item2.csv", Q2i1, Q2i2, Q2i3, Q2i4, Q2i5, sizeof items / sizeof items[0]);
	

	//Q3.push_back("3");
	Writing("Q/item3.csv", Q3i1, Q3i2, Q3i3, Q3i4, Q3i5, sizeof items / sizeof items[0]);
	

	//Q4.push_back("4");
	Writing("Q/item4.csv", Q4i1, Q4i2, Q4i3, Q4i4, Q4i5, sizeof items / sizeof items[0]);

	WritingText("Q/Questions.csv",text,Q1,Q2,Q3,Q4, sizeof items / sizeof items[0]);

		
	
	

	hp = 0;
	sp = 0;
	atk = 0;
	def = 0;
	spd = 0;

	Qs = (Q1i1.size() + Q2i1.size() + Q3i1.size() + Q4i1.size()) / 4;
	if (Qs != Q1i1.size()) DebugBreak();
	s = 0;
	Current_Num = 0;
	Quest_Now = true;
	
}

Qwindow::~Qwindow() {

}

//名前が非常に紛らわしく後悔しているが、これは質問の初期化ではない。ウインドウの位置を始点にセットするものである。
void Qwindow::Qwindow_init() {
	x = 1200;
	y = 100;
	State = 1;
	A = false;
	Current_Num++;
}

void Qwindow::fmove() {

	x -= 60;
}

void Qwindow::emove() {

	x -= 60;

}

void Qwindow::Q(int i) {
	if (Qs >= i) {
		s = i;
	}

	SetFontSize(30);
	DrawFormatString(360, 140, GetColor(255, 255, 255), text[0]);
	SetFontSize(20);
	DrawFormatString(370, 420,GetColor(250,0,0),Q1[0]);
	DrawFormatString(520,420,GetColor(250,0,0),Q2[0]);
	DrawFormatString(670, 420, GetColor(250, 0, 0), Q3[0]);
	DrawFormatString(820, 420, GetColor(250, 0, 0), Q4[0]);


	if (CheckHitKey(INPUT1)) {
		hp += Q1i1[s];
		sp += Q1i2[s];
		atk += Q1i3[s];
		def += Q1i4[s];
		spd += Q1i5[s];

		A = true;
	}
	if (CheckHitKey(INPUT2)) {
		hp += Q2i1[s];
		sp += Q2i2[s];
		atk += Q2i3[s];
		def += Q2i4[s];
		spd += Q2i5[s];
		A = true;
	}
	if (CheckHitKey(INPUT3)) {
		hp += Q3i1[s];
		sp += Q3i2[s];
		atk += Q3i3[s];
		def += Q3i4[s];
		spd += Q3i5[s];

		A = true;
	}
	if (CheckHitKey(INPUT4)) {
		hp += Q4i1[s];
		sp += Q4i2[s];
		atk += Q4i3[s];
		def += Q4i4[s];
		spd += Q4i5[s];
		A = true;
	}

}

void Qwindow::view() {
	DrawExtendGraph(x, y, x + 700, y + 524, gra, TRUE);
}


void Qwindow::all() {

	view();


	if (x >= 330) fmove();
	else {
		if (A == false) {
			Q(Current_Num);
		}
		else if(A == true){
			emove();
		}
	}

	if (x < -500)Qwindow_init();
	if (Current_Num >= Qs)Quest_Now = false;
}

void Qwindow::Writing(const char* filename, std::vector<int> &items1,
	std::vector<int> &items2, std::vector<int> &items3, std::vector<int> &items4,
	std::vector<int> &items5, int n) {


	FILE* fp;
	fp = fopen(filename, "r");
	if (fp == NULL)DebugBreak();
	int c;
	int retu = 0;
	int gyou = 0;
	char buf[10];
	memset(buf, 0, sizeof(buf));
	bool eofFlag = false;
	for (int i = 0; i < 1000; i++) {
		while (1) {
			c = fgetc(fp);
			if (c == EOF) {
				eofFlag = true;
				break;
			}
			if (c != ',' && c != '\n') {
				strcat(buf, (const char*)&c);

			}
			else if (retu == 0) {
				items1.push_back(atoi(buf));
				memset(buf, 0, sizeof(buf));
				break;
			}
			else if (retu == 1) {
				items2.push_back(atoi(buf));
				memset(buf, 0, sizeof(buf));
				break;
			}
			else if (retu == 2) {
				items3.push_back(atoi(buf));
				memset(buf, 0, sizeof(buf));
				break;
			}
			else if (retu == 3) {
				items4.push_back(atoi(buf));
				memset(buf, 0, sizeof(buf));
				break;
			}
			else if (retu == 4) {
				items5.push_back(atoi(buf));
				memset(buf, 0, sizeof(buf));
				break;
			}
			else {
				memset(buf, 0, sizeof(buf));
				break;
			}
		}

		if (eofFlag)break;
		if (c == ',')retu++;
		if (c == '\n') {
			gyou++;
			retu = 0;
		}
	}
	fclose(fp);

	
}

void Qwindow::WritingText(const char*filename, std::vector<const char*> &Text,
	std::vector<const char*> &Ques1, std::vector<const char*> &Ques2,
	std::vector<const char*> &Ques3, std::vector<const char*> &Ques4,int n) {

	FILE* fp;
	fp = fopen(filename, "r");
	if (fp == NULL)DebugBreak();
	int c;
	int retu = 0;
	int gyou = 0;
	char buf[64];
	const char* c_buf;
	memset(buf, 0, sizeof(buf));
	bool eofFlag = false;
	for (int i = 0; i < 1000; i++) {
		while (1) {
			c = fgetc(fp);
			if (c == EOF) {
				eofFlag = true;
				break;
			}
			if (c != ',' && c != '\n') {
				strcat(buf, (const char*)&c);
				c_buf = (const char*)buf;
			}
			else if (retu == 0) {
				Text.push_back(buf);
				memset(buf, 0, sizeof(buf));
				break;
			}
			else if (retu == 1) {
				Ques1.push_back(buf);
				memset(buf, 0, sizeof(buf));
				break;
			}
			else if (retu == 2) {
				Ques2.push_back(buf);
				memset(buf, 0, sizeof(buf));
				break;
			}
			else if (retu == 3) {
				Ques3.push_back(buf);
				memset(buf, 0, sizeof(buf));
				break;
			}
			else if (retu == 4) {
				Ques4.push_back(buf);
				memset(buf, 0, sizeof(buf));
				break;
			}
			else {
				memset(buf, 0, sizeof(buf));
				break;
			}
		}

		if (eofFlag)break;
		if (c == ',')retu++;
		if (c == '\n') {
			gyou++;
			retu = 0;
		}
	}
	fclose(fp);

}
