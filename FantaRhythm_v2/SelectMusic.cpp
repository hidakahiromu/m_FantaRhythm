#include "FantaRhythm_v2.h"
#include "SelectMusic.h"
#include "SceneManager.h"

#define PI 3.141592

SelectMusic::SelectMusic(void)  {
	TextureAsset::Register(U"back", U"resources/images/back/BackScreen.jpg");
	TextureAsset::Preload(U"back");
	TextureAsset::Register(U"title", U"resources/images/items/title.png");
	TextureAsset::Preload(U"title");

	FontAsset::Register(U"font", 30);
	FontAsset::Preload(U"font");
	musicrotation = difrotation = 0;
	initMusic();
	initDifficulty();

	changeState(MUSIC);
	playMusic(musiccursor);	
}

SelectMusic::~SelectMusic(void) {
	delete audio;
	TextureAsset::UnregisterAll();
	FontAsset::Unregister(U"font");

}

void SelectMusic::changeState(SELECTSTATE nextstate) {
	switch (nextstate) {
	case MUSIC:
		stateUpdate = &SelectMusic::updateMusic;
		stateDraw = &SelectMusic::drawMusic;
		break;
	case DIFFICULTY:
		stateUpdate = &SelectMusic::updateDifficulty;
		stateDraw = &SelectMusic::drawDifficulty;
		break;
	case TITLE:
		SceneManager::changeScene(SceneManager::SCENE_TITLE);
		break;
	case GAME:
		break;

	}
}

void SelectMusic::initMusic(void) {
	musiccursor = 0;
	difvec.clear();
	setVector(musicvec, U"resources/musics/main/", musiccount);
}

void SelectMusic::initDifficulty(void) {
	difcursor = 0;
	difvec.clear();
	setVector(difvec, getDiffilepath(musiccursor), difcount);
}

void SelectMusic::setVector(std::vector<String>&vec,String filepath,int& count) {//�x�N�^�[�ɗv�f��ݒ�@�v�f�����ݒ�
	String Path;
	count = FileSystem::DirectoryContents(filepath, false).count();
	for (int i = 0; i < count; i++) {
		Path = FileSystem::DirectoryContents(filepath, false).at(i);
		vec.push_back(FileSystem::BaseName(Path));
	}
}
String SelectMusic::getDiffilepath(int cursor) {//��Փx�t�@�C���p�X�擾
	return (U"resources/musics/main/" + musicvec[cursor] + U"/score");
}

void SelectMusic::update(void) {
	//��Ԃɍ��킹���v�Z����
	(this->*stateUpdate)();
}

void SelectMusic::updateMusic(void) {
	musicmoveCursor();
	if (!musicrotation) {//�ړ��������������Ă���Ƃ�
		if (KeyRight.down()) {//��Փx��
			changeState(DIFFICULTY);
		}else if (KeyLeft.down()) {//�^�C�g���֖߂�
			changeState(TITLE);
		}
	}
	else {
		rotatemusic(musicrotation);//�ړ�����
	}
}
void SelectMusic::updateDifficulty(void) {
	difmoveCursor();//�㉺�ړ�����
	if (!difrotation) {//�ړ��������������Ă���Ƃ�
		if (KeyRight.down()) {//�Q�[����
			
		}
		if (KeyLeft.down()) {//�ȑI����
			changeState(MUSIC);
		}
	}
	else {
		rotatemusic(difrotation);//�ړ�����
	}
}

void SelectMusic::rotatemusic(int& rotation) {
	if (rotation < 0) {
		rotation += 3;//����̈ʒu�ɂ���܂�1�t���[�������Ɋp�x���v���X
	}
	if (rotation > 0) {
		rotation -= 3;//����̈ʒu�ɂ���܂�1�t���[�������Ɋp�x���}�C�i�X
	}
}

void SelectMusic::draw(void) {
	//�w�i�摜�`��
	TextureAsset(U"back").draw();
	//���݂̏�Ԃɍ��킹���I�����̕`��
	(this->*stateDraw)();
}
void SelectMusic::difmoveCursor(void) {
	if (KeyUp.down()) {
		difcursor == 0 ? difcursor = difcount - 1 : difcursor--;//0�@�`�@count - 1����������[�v
		difrotation = -30;//�I��������]�����邽�ߊp�x��30�x�}�C�i�X
	}
	if (KeyDown.down()) {
		difcursor == difcount - 1 ? difcursor = 0 : difcursor++;
		difrotation = 30;//�I��������]�����邽�ߊp�x��30�x�v���X
	}
}
void SelectMusic::musicmoveCursor(void) {
	if (KeyUp.down()) {
		musiccursor == 0 ? musiccursor = musiccount - 1 : musiccursor--;//0�@�`�@count - 1����������[�v
		musicrotation = -30;//�I��������]�����邽�ߊp�x��30�x�}�C�i�X
		playMusic(musiccursor);
		initDifficulty();//�Ȃɍ��킹����Փx�֏�����

	}
	if (KeyDown.down()) {
		musiccursor == musiccount - 1 ? musiccursor = 0 : musiccursor++;
		musicrotation = 30;//�I��������]�����邽�ߊp�x��30�x�v���X
		playMusic(musiccursor);
		initDifficulty();//�Ȃɍ��킹����Փx�֏�����
	}
}

void SelectMusic::playMusic(int musicNum) {
	delete audio;
	audio = new Audio(U"resources/musics/main/" + musicvec[musicNum] + U"/preview.wav");
	audio->setLoop(true);
	audio->play();
}

void SelectMusic::drawMusic(void) {
	/*�Ȗ��̕`��*/
	for (int i = 0; i < 5; i++) {
		//���W�̎w��
		int angle = 120 + 30 * i + musicrotation;
		int x = 1800 + cos((angle)* PI / 180.0) * 1000;
		int y = (Window::Height() / 2) - sin((angle)* PI / 180.0) * 500;
		//�`��
		TextureAsset(U"title").drawAt(x, y);
		FontAsset(U"font")(musicvec[(musiccursor - 2 + i + musiccount) % musiccount]).drawAt(x, y, Color(0, 0, 0));
	}
}
void SelectMusic::drawDifficulty(void) {
	/*�Ȗ��̕`��*/
	for (int i = 0; i < 5; i++) {
		//���W�̎w��
		int angle = 120 + 30 * i + difrotation;
		int x = 1800 + cos((angle)* PI / 180.0) * 1000;
		int y = (Window::Height() / 2) - sin((angle)* PI / 180.0) * 500;
		//�`��
		TextureAsset(U"title").drawAt(x, y);
		FontAsset(U"font")(difvec[(difcursor - 2 + i + difcount) % difcount]).drawAt(x, y, Color(0, 0, 0));
	}
}