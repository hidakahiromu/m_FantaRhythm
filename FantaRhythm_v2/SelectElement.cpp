#include "SelectElement.h"

#define PI 3.141592



SelectElement::SelectElement(String filepath) :cursor(0),rotation(0){
	count = FileSystem::DirectoryContents(filepath, false).count();
	/*�Ȗ��擾*/
	String Path;
	for (int i = 0; i < count; i++) {
		Path = FileSystem::DirectoryContents(filepath, false).at(i);
		vec.push_back(FileSystem::BaseName(Path));
	}
}

SelectElement::~SelectElement(void) {}



// �߂�l -1 ����Ȃ� 0(ROTATE)�㉺��] 1(FRONT)���̑I������ 2(BACK)���̑I������
int SelectElement::update(void) {
	int tmp;
	if ((tmp = moveCursor()) < 0) {//�㉺������
		if (!rotation) {//�ړ��������������Ă���Ƃ�
			tmp = SwitchiCheck();
		}
	}
	rotatemusic();//�ړ�����
	return tmp;
}

void SelectElement::draw(void) {
	/*�Ȗ��̕`��*/
	for (int i = 0; i < 5; i++) {
		//���W�̎w��
		int angle = 120 + 30 * i + rotation;
		int x = 1800 + cos((angle)* PI / 180.0) * 1000;
		int y = (Window::Height() / 2) - sin((angle)* PI / 180.0) * 500;
		//�`��
		TextureAsset(U"title").drawAt(x, y);
		FontAsset(U"font")(vec[(cursor - 2 + i + count) % count]).drawAt(x, y, Color(0, 0, 0));
	}
}

//��]�����邽�߂̊֐��@�㉺�ɑ��삠���ROTATE�Ԃ�
int SelectElement::moveCursor(void) {
	if (KeyUp.down()) {
		//0�@�`�@count - 1����������[�v
		cursor == 0 ? cursor = count - 1 : cursor--;
		//�I��������]�����邽�ߊp�x��30�x�}�C�i�X
		rotation = -30;
		return ROTATE;
	}
	if (KeyDown.down()) {
		//0�@�`�@count - 1�����������[�v
		cursor == count - 1 ? cursor = 0 : cursor++;
		//�I��������]�����邽�ߊp�x��30�x�v���X
		rotation = 30;
		return ROTATE;
	}
	return -1;
}

void SelectElement::rotatemusic(void) {
	if (rotation < 0) {
		//����̈ʒu�ɂ���܂�1�t���[�������Ɋp�x���v���X
		rotation += 3;
	}
	if (rotation > 0) {
		//����̈ʒu�ɂ���܂�1�t���[�������Ɋp�x���}�C�i�X
		rotation -= 3;
	}
}

//�E�����m�@�߂�l-1������ĂȂ� 1(FRONT),2(BACK)
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
