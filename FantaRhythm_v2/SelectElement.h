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
	�@�\�F�I�����ɕ\������v�f�ꗗ��ێ����A�v�Z�����ƕ`�揈�����֐��Ƃ��Ď���
		�ꉞ�X�^�b�N�����O��(����)
----------------------------------------------------*/
class SelectElement {
private:
	int cursor;//���ݒ����ɗ��Ă���vec�̓Y��
	int rotation;
	int count;//�ێ����Ă���v�f��
	int moveCursor(void);
	void rotatemusic(void);
	int SelectElement::SwitchiCheck(void);
	std::vector<String> vec;
public:
	//String filepath �͑��΃p�X�ŗv�f�������Ă���t�H���_�w��
	SelectElement(String filepath);
	~SelectElement(void);
	//�߂�l�� -1 ����ێ� 0(ROTATE) 1(FRONT) 2(BACK)
	int update(void);
	void draw(void);
	String Get_Vec(int num);
	String Get_FileName(void);
	int Get_Cursor(void);

};

