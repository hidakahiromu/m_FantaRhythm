#include "NotesManager.h"



NotesManager::NotesManager(const String& difpath) {
	TextureAsset::Register(U"note", U"resources/images/items/Nort3rd.png");
	TextureAsset::Preload(U"note");
	TextureAsset::Register(U"longef", U"resources/images/items/longNortsEffect2.png");
	TextureAsset::Preload(U"longef");
	CSVData csv;//���ʂ̎擾�@�������z��ŊǗ� 0 ���莞��(ms) 1 �����H 2 �������[��[0-3]
	Print << difpath;

	csv.load(difpath);//���ʂ̃��[�h
	NotesManager::Notes note;
	for (int j = 0; j < csv.rows(); j++) {
		int lane = csv.get<int>(j, 2);
		note.time = csv.get<int>(j, 0);
		note.longtime = note.time + csv.get<int>(j, 1);
		switch (csv.get<int>(j, 3)) {
			case 0:
				note.type = NORMAL;
				break;
			case 1:
				note.type = LONG;
				break;
		}
		note.display = true;
		notelist[lane].push_back(note);
	}
	for (int i = 0; i < LANESIZE; i++) {//���[�����Ƃɓ������Ԃ��i�[
		displayitr[i] = checkitr[i] = notelist[i].begin();//�`�F�b�N�p�̃C�e���[�^����
		longflag[i] = false;
	}

	laneStartX[0] = 520;
	laneStartX[1] = 600;
	laneStartX[2] = 680;
	laneStartX[3] = 760;
	laneJudgeX[0] = 430;
	laneJudgeX[1] = 570;
	laneJudgeX[2] = 710;
	laneJudgeX[3] = 850;
	laneStartY = 100;
	laneJudgeY = 650;//CHECKLINEY�̑���
	laneGoalY = 730;//���Y���W���E+10
	notespeed = 1.5;
	timeRequired = 2000 / notespeed;//�m�[�c�̏o�����画��܂ŗ���鎞��[ms]

}
NotesManager::~NotesManager() {
	TextureAsset::UnregisterAll();
}


void NotesManager::update(void)
{
	nowTime = MusicManager::getMusicTime();
	checkAttack();
	controlJudge();
}

void NotesManager::plusItr(int lane, std::list<Notes>::iterator& itr) {
	if (itr != notelist[lane].end())
		itr++;
}

void NotesManager::checkAttack(void) {
	 down[0] = KeyA.down();
	press[0] = KeyA.pressed();
	 down[1] = KeyS.down();
	press[1] = KeyS.pressed();
	 down[2] = KeyD.down();
	press[2] = KeyD.pressed();
	 down[3] = KeyF.down();
	press[3] = KeyF.pressed();
}
void NotesManager::controlJudge(void) {
	for (int i = 0;i < LANESIZE;i++) {
		switch (checkitr[i]->type) {
		case NORMAL:
			judgeNormal(i);
			break;
		case LONG:
			judgeLong(i);
			break;
		default:
			break;
		}
	}
}
void NotesManager::judgeNormal(int lane) {
	static const int bad = 200;//����̍ő�͈�[ms]��2
	static const int good = 100;//GOOD����͈�[ms]��2
	static const int great = 25;//GREAT����͈�[ms]��2
	int checktime = abs(nowTime - checkitr[lane]->time);
	if (down[lane] && checktime <= bad) {
		if (checktime <= great) {
			//GREAT
		}
		else if (checktime < good) {
			//GOOD
		}
		else{

		}
		checkitr[lane]->display = false;
		plusItr(lane, checkitr[lane]);
	}
	else if (nowTime >= checkitr[lane]->time + bad) {
		plusItr(lane, checkitr[lane]);
	}
}
void NotesManager::judgeLong(int lane) {
	static const int good = 150;//����̍ő�͈�
	int checktime = abs(nowTime - checkitr[lane]->time);

	//���������Q�[���̓��e���荇�킹
	//�X�R�A�̏o���@hp�̌���^�C�~���O
	//�X���b�h����擾����l
	//�����O�m�[�c�̔���
	//�����O�m�[�c�����	//���݂̌��_�@�����������Ƃ�
	/*	���������@
		�{�^������			��					����O�����f
			��										��
		����ʒu�ʂ�߂�����~�߂�					��
		�{�^���������@�@�@�@���@�����Ă��Ȃ�		��	
			��						��				��
		�X�R�A����				����O���f�igood��)	��
			��										��
		�C�e���[�^�i�߂適������������������������
	
	*/
	if (down[lane] && checktime <= good) {//�����ꂽ��t���O�𗧂Ă�
		longflag[lane] = true;
	}
	if (longflag[lane]) {
		if (press[lane]) {//�{�^��������
			if ((nowTime - checkitr[lane]->time) >= 0) {//�~�߂�^�C�~���O 
				checkitr[lane]->time = (int)(nowTime);//����ʒu�ȍ~�Ŏ~�߂�
			}
			if (nowTime >= checkitr[lane]->longtime) {//������Ă���܂ܔ���ʒu�֗�����
				checkitr[lane]->time = checkitr[lane]->longtime;
				if (nowTime >= checkitr[lane]->longtime + good) {//������Ă���Ԃ͔��莞�Ԃ��肬��܂őҋ@�����邽��good���Z
					longflag[lane] = false;
					checkitr[lane]++;
				}
			}
		}
		else {//������
			if ((abs(nowTime - checkitr[lane]->longtime)) <= good) {
				checkitr[lane]->display = false;//����
			}
			checkitr[lane]++;
			longflag[lane] = false;
		}
	}
	else if (nowTime >= checkitr[lane]->longtime) {//������Ă��Ȃ��܂܏I����
		checkitr[lane]++;
		longflag[lane] = false;
	}
}


void NotesManager::draw(void){
	Line(0, laneJudgeY, 1920, laneJudgeY).draw(3, Palette::Black);
	for(int i = 0; i < LANESIZE; i++){
		Line(laneStartX[i], laneStartY, laneJudgeX[i], laneJudgeY).draw(1, Palette::Red);
		for (std::list<Notes>::iterator itr = displayitr[i]; itr != notelist[i].end(); itr++) {
			if (nowTime < itr->time - timeRequired)//�`��O�Ȃ�`��ł��؂�
				break;
			if (itr->display == false)
				continue;

			switch (itr->type){
			case NORMAL:
				displayNormal(i, itr);
				break;
			case LONG:
				displayLong(i, itr);
				break;
			default:
				break;
			}
		}	
	}
}
void NotesManager::displayNormal(int lane, std::list<Notes>::iterator& itr) {
	double progressRate = (timeRequired - (itr->time - nowTime)) / timeRequired;
	double currentY = laneStartY + (laneJudgeY - laneStartY) * progressRate;
	if (currentY > laneGoalY) {
		plusItr(lane ,displayitr[lane]);
		return;
	}
	double currentX = laneStartX[lane] + (laneJudgeX[lane] - laneStartX[lane]) * progressRate;
	TextureAsset(U"note").drawAt(currentX, currentY);
}
void NotesManager::displayLong(int lane, std::list<Notes>::iterator& itr) {
	double progressRateEnd = (timeRequired - (itr->longtime - nowTime)) / timeRequired;
	double currentEndY = laneStartY + (laneJudgeY - laneStartY) * progressRateEnd;
	if (currentEndY > laneGoalY) {
		plusItr(lane, displayitr[lane]);
		return;
	}
	double currentEndX = laneStartX[lane] + (laneJudgeX[lane] - laneStartX[lane]) * progressRateEnd;

	double progressRateBgn = (timeRequired - (itr->time - nowTime)) / timeRequired;
	double currentBgnY = laneStartY + (laneJudgeY - laneStartY) * progressRateBgn;
	double currentBgnX = laneStartX[lane] + (laneJudgeX[lane] - laneStartX[lane]) * progressRateBgn;

	for (int linex = 0; linex <= 25; linex++) {
		if (currentEndX > currentBgnX) {		
			currentEndX = laneStartX[lane];
			currentEndY = laneStartY;
		}
		Line(currentEndX + linex, currentEndY, currentBgnX + linex, currentBgnY).draw(1, Color(150 + linex * 2, 50, 50));
		Line(currentEndX - linex, currentEndY, currentBgnX - linex, currentBgnY).draw(1, Color(150 + linex * 2, 50, 50));
	}
	TextureAsset(U"note").drawAt(currentEndX, currentEndY);
	TextureAsset(U"note").drawAt(currentBgnX, currentBgnY);
}
