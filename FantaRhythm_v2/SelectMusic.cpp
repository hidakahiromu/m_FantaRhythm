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

void SelectMusic::setVector(std::vector<String>&vec,String filepath,int& count) {//ベクターに要素を設定　要素数も設定
	String Path;
	count = FileSystem::DirectoryContents(filepath, false).count();
	for (int i = 0; i < count; i++) {
		Path = FileSystem::DirectoryContents(filepath, false).at(i);
		vec.push_back(FileSystem::BaseName(Path));
	}
}
String SelectMusic::getDiffilepath(int cursor) {//難易度ファイルパス取得
	return (U"resources/musics/main/" + musicvec[cursor] + U"/score");
}

void SelectMusic::update(void) {
	//状態に合わせた計算処理
	(this->*stateUpdate)();
}

void SelectMusic::updateMusic(void) {
	musicmoveCursor();
	if (!musicrotation) {//移動処理が完了しているとき
		if (KeyRight.down()) {//難易度へ
			changeState(DIFFICULTY);
		}else if (KeyLeft.down()) {//タイトルへ戻る
			changeState(TITLE);
		}
	}
	else {
		rotatemusic(musicrotation);//移動処理
	}
}
void SelectMusic::updateDifficulty(void) {
	difmoveCursor();//上下移動処理
	if (!difrotation) {//移動処理が完了しているとき
		if (KeyRight.down()) {//ゲームへ
			
		}
		if (KeyLeft.down()) {//曲選択へ
			changeState(MUSIC);
		}
	}
	else {
		rotatemusic(difrotation);//移動処理
	}
}

void SelectMusic::rotatemusic(int& rotation) {
	if (rotation < 0) {
		rotation += 3;//既定の位置にくるまで1フレームおきに角度をプラス
	}
	if (rotation > 0) {
		rotation -= 3;//既定の位置にくるまで1フレームおきに角度をマイナス
	}
}

void SelectMusic::draw(void) {
	//背景画像描画
	TextureAsset(U"back").draw();
	//現在の状態に合わせた選択肢の描画
	(this->*stateDraw)();
}
void SelectMusic::difmoveCursor(void) {
	if (KeyUp.down()) {
		difcursor == 0 ? difcursor = difcount - 1 : difcursor--;//0　～　count - 1を上方向ループ
		difrotation = -30;//選択肢を回転させるため角度を30度マイナス
	}
	if (KeyDown.down()) {
		difcursor == difcount - 1 ? difcursor = 0 : difcursor++;
		difrotation = 30;//選択肢を回転させるため角度を30度プラス
	}
}
void SelectMusic::musicmoveCursor(void) {
	if (KeyUp.down()) {
		musiccursor == 0 ? musiccursor = musiccount - 1 : musiccursor--;//0　～　count - 1を上方向ループ
		musicrotation = -30;//選択肢を回転させるため角度を30度マイナス
		playMusic(musiccursor);
		initDifficulty();//曲に合わせた難易度へ初期化

	}
	if (KeyDown.down()) {
		musiccursor == musiccount - 1 ? musiccursor = 0 : musiccursor++;
		musicrotation = 30;//選択肢を回転させるため角度を30度プラス
		playMusic(musiccursor);
		initDifficulty();//曲に合わせた難易度へ初期化
	}
}

void SelectMusic::playMusic(int musicNum) {
	delete audio;
	audio = new Audio(U"resources/musics/main/" + musicvec[musicNum] + U"/preview.wav");
	audio->setLoop(true);
	audio->play();
}

void SelectMusic::drawMusic(void) {
	/*曲名の描画*/
	for (int i = 0; i < 5; i++) {
		//座標の指定
		int angle = 120 + 30 * i + musicrotation;
		int x = 1800 + cos((angle)* PI / 180.0) * 1000;
		int y = (Window::Height() / 2) - sin((angle)* PI / 180.0) * 500;
		//描画
		TextureAsset(U"title").drawAt(x, y);
		FontAsset(U"font")(musicvec[(musiccursor - 2 + i + musiccount) % musiccount]).drawAt(x, y, Color(0, 0, 0));
	}
}
void SelectMusic::drawDifficulty(void) {
	/*曲名の描画*/
	for (int i = 0; i < 5; i++) {
		//座標の指定
		int angle = 120 + 30 * i + difrotation;
		int x = 1800 + cos((angle)* PI / 180.0) * 1000;
		int y = (Window::Height() / 2) - sin((angle)* PI / 180.0) * 500;
		//描画
		TextureAsset(U"title").drawAt(x, y);
		FontAsset(U"font")(difvec[(difcursor - 2 + i + difcount) % difcount]).drawAt(x, y, Color(0, 0, 0));
	}
}