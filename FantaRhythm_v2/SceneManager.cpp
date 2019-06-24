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
	//シーンの呼び出し
	scene->draw();
}
void SceneManager::changeScene() {
	switch (nextscene) {
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
	case SCENE_NONE:
		break;
	default:
		break;
	}
}
void SceneManager::setNextScene(SCENE next) {
	nextscene = next;
}
/*
void SceneManager::updateScene() {
	//シーンに変更があったとき
	if (nowScene != nextScene) {
		changeScene();
		nowScene = nextScene;
	}	
}

void SceneManager::drawScene() {
	//シーンの呼び出し
	nextScene = scene->update();
	scene->draw();
}

void SceneManager::changeScene(){
	//現在のシーンの破棄
	delete scene;
	//次のシーンに変更
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