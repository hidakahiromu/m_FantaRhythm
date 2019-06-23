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

	//���ꂼ��̗v�f���A���ݑI�����Ă���v�f�Y���A�ړ��p�̒l
	int musiccount, difcount;
	int musiccursor, difcursor;
	int musicrotation, difrotation;
	
	std::vector<String> musicvec, difvec;//�v�f���i�[����x�N�^�[

	void(SelectMusic::*stateUpdate)(void);
	void(SelectMusic::*stateDraw)(void);

	void changeState(SELECTSTATE nextstate);

	//����������
	void initDifficulty(void);
	void initMusic(void);
	//�������Ŏg�p����֐�
	String getDiffilepath(int musiccursor);
	void setVector(std::vector<String>& vec, String filepath, int& count);
	//�v�Z����
	void updateMusic(void);
	void updateDifficulty(void);
	//�`�揈��
	void drawMusic(void);
	void drawDifficulty(void);
	//�㉺�ړ����m����
	void difmoveCursor(void);
	void musicmoveCursor(void);
	//�ړ�����
	void rotatemusic(int& rotation);
	//�v���r���[�Đ�
	void playMusic(int musicNum);
};

