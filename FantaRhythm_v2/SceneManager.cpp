#include "SceneManager.h"

Scene* SceneManager::scene;
SceneManager::SCENE SceneManager::nextscene;

void SceneManager::initialize() {
	scene = new Title();
}
void SceneManager::finalize() {
	delete scene;
}
void SceneManager::updateScene() {
	changeScene();
	scene->update();
}
void SceneManager::drawScene() {
	scene->draw();
}

void SceneManager::setNextScene(SCENE next) {
	nextscene = next;
}

void SceneManager::changeScene() {
	switch (nextscene) {//nextscene��NONE�ȊO�̎��V�[���ڍs����
	case SCENE_TITLE:
		delete scene;
		scene = new Title();
		nextscene = SCENE_NONE;
		break;
	case SCENE_SELECTMUSIC:
		delete scene;
		scene = new SelectMusic();
		nextscene = SCENE_NONE;
		break;
	case SCENE_NONE://�ڍs���Ȃ�
		break;
	default:
		break;
	}
}
