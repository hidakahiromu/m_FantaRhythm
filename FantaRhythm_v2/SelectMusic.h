#pragma once
#include "Scene.h"


class SelectMusic:public Scene{
public:
	SelectMusic(void);
	~SelectMusic(void);	
	void update(void);
	void draw(void);
private:
	enum SELECTSTATE {
		MUSIC,
		DIFFICULTY,
		TITLE,
		GAME
	};

	Audio* audio;

	//それぞれの要素数、現在選択している要素添字、移動用の値
	int musiccount, difcount;
	int musiccursor, difcursor;
	int musicrotation, difrotation;
	
	std::vector<String> musicvec, difvec;//要素を格納するベクター

	void(SelectMusic::*stateUpdate)(void);
	void(SelectMusic::*stateDraw)(void);

	void changeState(SELECTSTATE nextstate);

	//初期化処理
	void initDifficulty(void);
	void initMusic(void);
	//初期化で使用する関数
	String getDiffilepath(int musiccursor);
	void setVector(std::vector<String>& vec, String filepath, int& count);
	//計算処理
	void updateMusic(void);
	void updateDifficulty(void);
	//描画処理
	void drawMusic(void);
	void drawDifficulty(void);
	//上下移動検知処理
	void difmoveCursor(void);
	void musicmoveCursor(void);
	//移動処理
	void rotatemusic(int& rotation);
	//プレビュー再生
	void playMusic(int musicNum);
};

