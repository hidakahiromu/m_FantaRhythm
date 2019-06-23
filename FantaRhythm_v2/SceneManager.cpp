#include "SceneManager.h"

Scene* SceneManager::scene;

void SceneManager::initialize() {
	scene = new Title();
}
void SceneManager::finalize() {
	delete scene;
}
void SceneManager::updateScene() {
	scene->update();
}
void SceneManager::drawScene() {
	//�V�[���̌Ăяo��
	scene->draw();
}
void SceneManager::changeScene(SCENE nextscene) {
	//���݂̃V�[���̔j��
	delete scene;
	//���̃V�[���ɕύX
	switch (nextscene) {
	case SCENE_TITLE:
		scene = new Title();
		break;
	case SCENE_SELECTMUSIC:
		scene = new SelectMusic();
		break;
	default:
		break;
	}
}
/*
void SceneManager::updateScene() {
	//�V�[���ɕύX���������Ƃ�
	if (nowScene != nextScene) {
		changeScene();
		nowScene = nextScene;
	}	
}

void SceneManager::drawScene() {
	//�V�[���̌Ăяo��
	nextScene = scene->update();
	scene->draw();
}

void SceneManager::changeScene(){
	//���݂̃V�[���̔j��
	delete scene;
	//���̃V�[���ɕύX
	switch (nextScene){
	case SCENE_TITLE:
		scene = new Title();
		break;
	case SCENE_SELECTMUSIC:
		scene = new SelectMusic();
		break;
	default:
		break;
	}
}
*/