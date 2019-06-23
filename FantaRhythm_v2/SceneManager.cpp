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
	//シーンの呼び出し
	scene->draw();
}
void SceneManager::changeScene(SCENE nextscene) {
	//現在のシーンの破棄
	delete scene;
	//次のシーンに変更
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