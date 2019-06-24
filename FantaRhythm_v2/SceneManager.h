#pragma once
#include "FantaRhythm_v2.h"
#include "Scene.h"

class SceneManager {
public:
	enum SCENE {
		SCENE_TITLE,
		SCENE_SELECTMUSIC,
		SCENE_NONE
	};
	SceneManager() = delete;
	static void initialize();
	static void finalize();

	static void updateScene();
	static void drawScene();
	static void setNextScene(SCENE next);
private:
	static Scene *scene;
	static SCENE nextscene;
	static void changeScene();
};
