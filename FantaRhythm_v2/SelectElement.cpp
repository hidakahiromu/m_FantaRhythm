#include "SelectElement.h"

#define PI 3.141592



SelectElement::SelectElement(String filepath) :cursor(0),rotation(0){
	count = FileSystem::DirectoryContents(filepath, false).count();
	/*曲名取得*/
	String Path;
	for (int i = 0; i < count; i++) {
		Path = FileSystem::DirectoryContents(filepath, false).at(i);
		vec.push_back(FileSystem::BaseName(Path));
	}
}

SelectElement::~SelectElement(void) {}



// 戻り値 -1 操作なし 0(ROTATE)上下回転 1(FRONT)次の選択肢へ 2(BACK)元の選択肢へ
int SelectElement::update(void) {
	int tmp;
	if ((tmp = moveCursor()) < 0) {//上下無操作
		if (!rotation) {//移動処理が完了しているとき
			tmp = SwitchiCheck();
		}
	}
	rotatemusic();//移動処理
	return tmp;
}

void SelectElement::draw(void) {
	/*曲名の描画*/
	for (int i = 0; i < 5; i++) {
		//座標の指定
		int angle = 120 + 30 * i + rotation;
		int x = 1800 + cos((angle)* PI / 180.0) * 1000;
		int y = (Window::Height() / 2) - sin((angle)* PI / 180.0) * 500;
		//描画
		TextureAsset(U"title").drawAt(x, y);
		FontAsset(U"font")(vec[(cursor - 2 + i + count) % count]).drawAt(x, y, Color(0, 0, 0));
	}
}

//回転させるための関数　上下に操作あればROTATE返す
int SelectElement::moveCursor(void) {
	if (KeyUp.down()) {
		//0　～　count - 1を上方向ループ
		cursor == 0 ? cursor = count - 1 : cursor--;
		//選択肢を回転させるため角度を30度マイナス
		rotation = -30;
		return ROTATE;
	}
	if (KeyDown.down()) {
		//0　～　count - 1を下方向ループ
		cursor == count - 1 ? cursor = 0 : cursor++;
		//選択肢を回転させるため角度を30度プラス
		rotation = 30;
		return ROTATE;
	}
	return -1;
}

void SelectElement::rotatemusic(void) {
	if (rotation < 0) {
		//既定の位置にくるまで1フレームおきに角度をプラス
		rotation += 3;
	}
	if (rotation > 0) {
		//既定の位置にくるまで1フレームおきに角度をマイナス
		rotation -= 3;
	}
}

//右左検知　戻り値-1押されてない 1(FRONT),2(BACK)
int SelectElement::SwitchiCheck(void) {
	if (KeyRight.down()) {
		return FRONT;
	}
	if (KeyLeft.down()) {
		return BACK;
	}
	return -1;
}

String SelectElement::Get_Vec(int num) {
	return vec[num];
}
String SelectElement::Get_FileName(void) {
	return vec[cursor];
}
int SelectElement::Get_Cursor(void) {
	return cursor;
}
