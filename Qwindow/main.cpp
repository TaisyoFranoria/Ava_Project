#include"io.h"
#include "Qwindow.h"


void Output_AVADATA(int P_HP, int P_SP, int P_ATK, int P_DEF, int P_SPD, bool RESET_DATA) {
	FILE *fp;
	char *fname = "AVATER.csv";



	if(RESET_DATA)fp = fopen(fname, "w");
	else fp = fopen(fname,"a");

	if (fp == NULL) {
		DebugBreak();
	}

	if (RESET_DATA == false)fprintf(fp, "\n");

	fprintf(fp, "%d,%d,%d,%d,%d", P_HP, P_SP, P_ATK, P_DEF, P_SPD);

	fclose(fp);
}


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);

	SetGraphMode(1280, 720, 32);

	int back;
	int Test_IMG;
	int coution_img;

	int MH;
	int AI;
	float PT;
	float TT;

	float camX = 0;
	float camY = 17;
	float camZ = -20;

	float sX = 0;
	float sY = -10;
	float sZ = -50;
	//モデルの読み込み

	bool reset = false;

	Qwindow* win = new Qwindow();


	MH = MV1LoadModel("3D/Shikimi2018_X/Shikimi_MMD.pmd");
	back = MV1LoadModel("3D/cyber/cyberzone.pmd");
	Test_IMG = LoadGraph("img/TestIMG.png");
	coution_img = LoadGraph("img/coution.png");

	//カメラの描画範囲
	SetCameraNearFar(0.1f, 1000.0f);

	//カメラの位置（何処からどこを見るか）
	SetCameraPositionAndTarget_UpVecY(VGet(camX, camY, camZ), VGet(0.0f, 10.0f, 0.0f));

	//一番最初のアニメーションをアタッチする
	AI = MV1AttachAnim(MH, 1, -1, FALSE);

	//アニメーションの総合時間を取得
	TT = MV1GetAnimTotalTime(MH, AI);

	//アニメーション開始時間を初期化
	PT = 0.0f;

	//メインwhileループ
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen()) {

		//再生時間を進める
		PT += 0.2f;

		//再生時間がアニメーションの最大時間になったらPTをリセット
		if (PT >= TT) {
			PT = 0.0f;
		}


		SetCameraPositionAndTarget_UpVecY(VGet(camX, camY, camZ), VGet(0.0f, 10.0f, -5000.0f));

		MV1SetAttachAnimTime(MH, AI, PT);
		MV1SetPosition(MH,VGet(camX+sX,camY+sY,camZ+sZ));

		MV1DrawModel(back);
		//MV1DrawModel(MH);

		if (CheckHitKey(KEY_INPUT_RIGHT)) {
			if (camX > -20)camX--;
		}
		if (CheckHitKey(KEY_INPUT_LEFT)) {
			if (camX < 20)camX++;
		}
		if (CheckHitKey(KEY_INPUT_ESCAPE))break;
		camZ -= 6;
		if (camZ <= -200)camZ = 1100;

		if(win->Quest_Now)win->all();
		if (CheckHitKey(KEY_INPUT_0))win->State++;

		DrawFormatString(0, 0, GetColor(0, 255, 255), "x:%d", win->x);
		DrawFormatString(0, 16, GetColor(0, 255, 255), "y:%d", win->y);
		DrawFormatString(0, 32, GetColor(255, 0,0), ":%d:%d:%d:%d:%d:",win->hp,win->sp,win->atk,win->def,win->spd);
		DrawFormatString(0, 48, GetColor(255, 255, 255), "%d", win->Qs);

	

		if (win->Quest_Now == false)break;
		
	}


	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen()) {
		DrawGraph(0,0,Test_IMG,TRUE);
		
		if (CheckHitKey(KEY_INPUT_ESCAPE)) {
			reset = true;
		}
		if (CheckHitKey(KEY_INPUT_SPACE)) {
			reset = false;
			break;
		}
		if (reset) {
			DrawGraph(380,280,coution_img,TRUE);
			
			if (CheckHitKey(KEY_INPUT_Y)) break;
			if (CheckHitKey(KEY_INPUT_N)) reset = false;
		}

	}
	Output_AVADATA(win->hp,win->sp,win->atk,win->def,win->spd,reset);

	



	DxLib_End();

	delete win;

	return 0;
}

