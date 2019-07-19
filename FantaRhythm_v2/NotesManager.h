#pragma once
#include "Game.h"
#include "FantaRhythm_v2.h"
#include <vector>
#include <list>

#define LANESIZE 4		//LANE�̐�

/*--------------------------------------------


-----------------------------------------------*/
class NotesManager {
private:
	enum NOTESTYPE {
		NORMAL,
		LONG
	};
	typedef struct _Notes {
		NOTESTYPE type;
		int time;
		int longtime;
		bool display;
	}Notes;
	
	float notespeed;

	//float checktime[4] = { 10,30,50,200 };
	
	std::list<Notes> notelist[LANESIZE];
	std::list<Notes>::iterator checkitr[LANESIZE];//���肷�ׂ��C�e���[�^�ێ�
	std::list<Notes>::iterator displayitr[LANESIZE];//�\�����ׂ��C�e���[�^�ێ�

	bool down[4];
	bool press[4];

	bool longflag[4];

	int laneStartX[4];
	int laneJudgeX[4];
	int laneStartY;
	int laneJudgeY;//CHECKLINEY�̑���
	int laneGoalY;//���Y���W���E+10
	float timeRequired;//�m�[�c�̏o�����画��܂ŗ���鎞��[ms]
	double nowTime;

	void plusItr(int i, std::list<Notes>::iterator& itr);
	void checkAttack(void);
	void controlJudge(void);
	void judgeNormal(int lane);
	void judgeLong(int lane);
	void displayNormal(int lane, std::list<Notes>::iterator& itr);
	void displayLong(int lane, std::list<Notes>::iterator& itr);
	
public:
	NotesManager(const String& difpath);
	~NotesManager();
	void update(void);
	void draw(void);

};