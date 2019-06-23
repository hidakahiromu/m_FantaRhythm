#pragma once
#include "FantaRhythm_v2.h"
#include "Scene.h"

class SceneManager {
public:
	enum SCENE {
		SCENE_TITLE,
		SCENE_SELECTMUSIC
	};
	SceneManager() = delete;
	static void initialize();
	static void finalize();

	static void updateScene();
	static void drawScene();
	static void changeScene(SCENE nextscene);
private:
	static Scene *scene;
};
