#pragma once
#include <vector>
#include "FantaRhythm_v2.h"

enum ElementState {
	ROTATE,
	FRONT,
	BACK
};
/*----------------------------------------------------
	class SelectElement
	機能：選択肢に表示する要素一覧を保持し、計算処理と描画処理を関数として持つ
		一応スタックされる前提(今は)
----------------------------------------------------*/
class SelectElement {
private:
	int cursor;//現在中央に来ているvecの添字
	int rotation;
	int count;//保持している要素数
	int moveCursor(void);
	void rotatemusic(void);
	int SelectElement::SwitchiCheck(void);
	std::vector<String> vec;
public:
	//String filepath は相対パスで要素が入っているフォルダ指定
	SelectElement(String filepath);
	~SelectElement(void);
	//戻り値は -1 現状維持 0(ROTATE) 1(FRONT) 2(BACK)
	int update(void);
	void draw(void);
	String Get_Vec(int num);
	String Get_FileName(void);
	int Get_Cursor(void);

};

